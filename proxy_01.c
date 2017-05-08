/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:20:49 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 19:41:17 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

void	ft_proxy_loop(int c_fd, int p_fd, char *ip, char *s_port)
{
	pthread_t	tid;
	t_server	*item;

	while (1)
	{
		c_fd = accept(p_fd, (struct sockaddr *)NULL, NULL);
		printf("Client #%d has connected!\n\n", c_fd);
		if (c_fd > 0)
		{
			item = (t_server *)malloc(sizeof(t_server));
			item->client_fd = c_fd;
			item->ip = strdup(ip);
			item->port = strdup(s_port);
			pthread_create(&tid, NULL, ft_run_socket, (void *)item);
			sleep(1);
		}
	}
}

void	ft_run_proxy(t_connect *info)
{
	int					c_fd;
	int					s_fd;
	struct sockaddr_in	c_sd;

	c_fd = 0;
	s_fd = 0;
	signal(SIGPIPE, SIG_IGN);
	if ((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Failed to create socket\n");
	printf("Running proxy server...\n\n");
	memset(&c_sd, 0, sizeof(c_sd));
	c_sd.sin_family = AF_INET;
	c_sd.sin_port = htons(atoi(info->c_port));
	c_sd.sin_addr.s_addr = INADDR_ANY;
	if ((bind(c_fd, (struct sockaddr*)&c_sd, sizeof(c_sd))) < 0)
		printf("Failed to bind socket\n");
	if ((listen(c_fd, SOMAXCONN)) < 0)
		printf("Failed to listen\n");
	printf("Waiting for connection...\n\n");
	ft_proxy_loop(s_fd, c_fd, info->ip, info->s_port);
}

void	ft_clear_info(t_connect *info)
{
	free(info->ip);
	free(info->s_port);
	free(info->c_port);
}

int		main(int ac, char **av)
{
	t_connect	info;

	if (ac < 3 || ac > 4)
		printf("Invalid usage.\n");
	else
	{
		if ((ft_get_info(ac, av, &info)) == -1)
		{
			printf("Invalid hostname. Please confirm and try again\n");
			exit(1);
		}
		else
		{
			ft_run_proxy(&info);
			ft_clear_info(&info);
		}
	}
	return (0);
}
