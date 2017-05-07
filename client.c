/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:20:56 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 13:00:48 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>  
#include <sys/types.h>  
#include <resolv.h>  
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h>
 // main entry point  

#define BUFF_SIZE 65535

typedef struct	s_connect
{
	char		*ip;
	char		*port;
}				t_connect;

int		ft_get_info(char **av, t_connect *info)
{
	if (strcmp(av[1], "127.0.0.1") != 0)
		return (-1);
	else
	{
		info->ip = strdup(av[1]);
		info->port = strdup(av[2]);
	}
	return (0);
}

void	ft_connect_to_proxy(t_connect *info)
{
	char	buf[BUFF_SIZE];
	int		sd;
	struct	sockaddr_in client_sd;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket failed to create\n");
	else
	{
		memset(&client_sd, 0, sizeof(client_sd));
		client_sd.sin_family = AF_INET;
		client_sd.sin_port = htons(atoi(info->port));
		client_sd.sin_addr.s_addr = INADDR_ANY;
		connect(sd, (struct sockaddr *)&client_sd, sizeof(client_sd));
		while (1)
		{
			printf("Enter message to server:\n");
			fgets(buf, BUFF_SIZE, stdin);
			write(sd, buf, BUFF_SIZE);
			if (strncmp(buf, "!exit", 5) == 0)
			{
				printf("Closing connection\n");
				close(sd);
				return ;
			}
			printf("\n Server response:\n");
			read(sd, buf, BUFF_SIZE);
			fputs(buf, stdout);
			printf("\n");
		}
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
			ft_connect_to_proxy(&info);
		}
	}
	return (0);
}

// int main(int argc, char* argv[])  
// {  
// 	//socket variables  
// 	char IP[200];  
// 	char port[200];  
// 	char buffer[65535];  
// 	int sd;  
// 	struct sockaddr_in client_sd;  
// 	printf("\nEnter proxy address:");  
// 	fgets(IP,sizeof("127.0.0.1\n")+1,stdin);  
// 	fputs(IP,stdout);  
// 	printf("\nEnter a port:");  
// 	fgets(port,sizeof("5000\n")+1,stdin);  
// 	fputs(port,stdout);  
// 	if((strcmp(IP,"127.0.0.1\n"))!=0 || (strcmp(port,"5000\n"))!=0)  
// 	{  
// 		printf("Invalida proxy settings. Try again...");  
// 	}  
// 	else  
// 	{  
// 		// create a socket  
// 		if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
// 		{  
// 		    printf("socket not created\n");  
// 		}  
// 		memset(&client_sd, 0, sizeof(client_sd));  
// 		// set socket variables  
// 		client_sd.sin_family = AF_INET;  
// 		client_sd.sin_port = htons(5000);  
// 		// assign any IP address to the client's socket  
// 		client_sd.sin_addr.s_addr = INADDR_ANY;   
// 		// connect to proxy server at mentioned port number  
// 		connect(sd, (struct sockaddr *)&client_sd, sizeof(client_sd));  
// 		//send and receive data contunuously  
// 		while(1)  
// 		{  
// 		    printf("Type here:");  
// 		    fgets(buffer, sizeof(buffer), stdin);  
// 		    write(sd, buffer, sizeof(buffer));  
// 		    printf("\nServer response:\n\n");  
// 		    read(sd, buffer, sizeof(buffer));  
// 		    fputs(buffer, stdout);  
// 		      //printf("\n");       
// 		};  
// 		//close(sd);  
// 	}  
// 	return 0;  
// }  