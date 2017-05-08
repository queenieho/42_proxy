/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 18:57:31 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 22:20:30 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROXY_H
# define PROXY_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <pthread.h>
# include <unistd.h>

# define BUFF_SIZE 65535

typedef struct	s_connect
{
	char		*ip;
	char		*s_port;
	char		*c_port;
}				t_connect;

typedef struct	s_server
{
	int			client_fd;
	char		*ip;
	char		*port;
}				t_server;

int				ft_hostname_to_ip(char *hostname, char **ip);
int				ft_isnum(char c);
int				ft_check_for_ip(char *str, char **ip);
int				ft_get_info(int arg_count, char **av, t_connect *info);
void			ft_comm_handler(int fd, char *buf, char *who);
void			ft_socket_loop(t_server *info, int s_fd);
void			*ft_run_socket(void *arg);
void			ft_proxy_loop(int c_fd, int p_fd, char *ip, char *s_port);
void			ft_run_proxy(t_connect *info);
void			ft_clear_info(t_connect *info);

#endif
