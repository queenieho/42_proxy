/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:20:56 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 22:43:32 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_comm_handler(int sd)
{
	char				buf[BUFF_SIZE];

	while (1)
	{
		bzero(&buf, BUFF_SIZE);
		printf("Enter message to server:\n");
		fgets(buf, BUFF_SIZE, stdin);
		write(sd, buf, strlen(buf));
		if (strncmp(buf, "!exit", 5) == 0)
		{
			printf("Closing connection\n");
			close(sd);
			return ;
		}
		printf("\nServer response:\n");
		bzero(&buf, BUFF_SIZE);
		read(sd, buf, BUFF_SIZE);
		fputs(buf, stdout);
		printf("\n");
	}
}

void	ft_connect_to_server(t_connect *info)
{
	int					sd;
	struct sockaddr_in	client_sd;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket failed to create\n");
	else
	{
		memset(&client_sd, 0, sizeof(client_sd));
		client_sd.sin_family = AF_INET;
		client_sd.sin_port = htons(atoi(info->port));
		client_sd.sin_addr.s_addr = INADDR_ANY;
		connect(sd, (struct sockaddr *)&client_sd, sizeof(client_sd));
		ft_comm_handler(sd);
	}
}

int		main(int ac, char **av)
{
	t_connect	info;

	if (ac != 3)
		printf("Invalid usage\n");
	else
	{
		if ((ft_get_info(av, &info)) == -1)
		{
			printf("Invalid proxy settings. Please confirm and try again\n");
			exit(1);
		}
		else
		{
			printf("ip :%s\n", info.ip);
			printf("port %s\n", info.port);
			ft_connect_to_server(&info);
		}
	}
	return (0);
}
