/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 22:17:03 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 22:39:47 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/socket.h>
# include <sys/types.h>
# include <resolv.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 65535

typedef struct	s_connect
{
	char		*ip;
	char		*port;
}				t_connect;

int				ft_isnum(char c);
int				ft_check_for_ip(char *str, char **ip);
int				ft_get_info(char **av, t_connect *info);
void			ft_comm_handler(int sd);
void			ft_connect_to_server(t_connect *info);

#endif
