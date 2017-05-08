/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:31:03 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 19:41:28 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

void	ft_comm_handler(int fd, char *buf, char *who)
{
	write(fd, buf, strlen(buf) + 1);
	printf("%s\n", who);
	fputs(buf, stdout);
	printf("\n");
	fflush(stdout);
}

void	ft_socket_loop(t_server *info, int s_fd)
{
	char	buf[BUFF_SIZE];
	int		bytes;

	bytes = 0;
	while (1)
	{
		memset(&buf, '\0', BUFF_SIZE);
		if ((bytes = read(info->client_fd, buf, sizeof(buf))) <= 0)
		{
		}
		else
			ft_comm_handler(s_fd, buf, "From client:");
		memset(&buf, '\0', BUFF_SIZE);
		if ((bytes = read(s_fd, buf, sizeof(buf))) <= 0)
		{
		}
		else
			ft_comm_handler(info->client_fd, buf, "From server:");
	}
}

void	*ft_run_socket(void *arg)
{
	t_server			*info;
	struct sockaddr_in	s_sd;
	int					s_fd;

	info = (t_server *)arg;
	s_fd = 0;
	if ((s_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Server socket failed to create\n");
	else
	{
		memset(&s_sd, 0, sizeof(s_sd));
		s_sd.sin_family = AF_INET;
		s_sd.sin_port = htons(atoi(info->port));
		s_sd.sin_addr.s_addr = inet_addr(info->ip);
		if ((connect(s_fd, (struct sockaddr *)&s_sd, sizeof(s_sd))) < 0)
			printf("Server connection not established\n");
		else
		{
			printf("Server socket connected...\n");
			ft_socket_loop(info, s_fd);
		}
	}
	return (NULL);
}
