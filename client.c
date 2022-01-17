/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:31:52 by jrobert           #+#    #+#             */
/*   Updated: 2021/09/16 17:38:11 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	syntax(void)
{
	write(1, "Syntax => ./client [pid] [message]\n", 35);
	exit (1);
}

void	error(void)
{
	write(2, "Error - bad pid\n", 16);
	exit (1);
}

void	send_bits(char *msg, int id)
{
	static int	c;
	static char	*s;
	static int	pid;
	static int	shift = -1;

	if (!s)
		s = msg;
	if (id != -1)
		pid = id;
	if (shift < 0)
	{
		c = *s++;
		if (!c)
			exit(0);
		shift = 7;
	}	
	if ((c >> shift--) & 1)
	{
		if (kill(pid, SIGUSR1) == -1)
			error();
	}
	else
		if (kill(pid, SIGUSR2) == -1)
			error();
}

void	acknowledged(int s_num, siginfo_t *info, void *ucontext)
{
	(void)*info;
	(void)*ucontext;
	usleep(100);
	if (s_num == SIGUSR1)
		send_bits(NULL, -1);
}

int	main(int argc, char **argv)
{
	struct sigaction	ack;
	int					pid;

	(void)argc;
	if (argc != 3)
		syntax();
	pid = ft_atoi(argv[1]);
	if (pid <= 1)
		syntax();
	ack.sa_flags = SA_SIGINFO;
	ack.sa_sigaction = acknowledged;
	if (sigaction(SIGUSR1, &ack, NULL) == -1)
	{
		write(2, "Error - sigaction\n", 18);
		return (0);
	}
	send_bits(argv[2], pid);
	while (1)
		pause();
	return (0);
}
