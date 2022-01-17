/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:31:58 by jrobert           #+#    #+#             */
/*   Updated: 2021/09/16 17:32:00 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	get_bits(int s_num, siginfo_t *info, void *ucontext)
{
	static int	c;
	static int	shift;

	(void)*ucontext;
	c <<= 1;
	if (s_num == SIGUSR1)
		c++;
	if (++shift > 7)
	{
		write(1, &c, 1);
		shift = 0;
		c = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		write(2, "Error - kill\n", 13);
		exit (1);
	}
}

int	main(void)
{
	struct sigaction	s;
	int					pid;

	pid = getpid();
	ft_putstr_fd(ft_itoa(pid), 1);
	write(1, "\n", 1);
	s.sa_flags = SA_SIGINFO;
	s.sa_sigaction = get_bits;
	if (sigaction(SIGUSR1, &s, NULL) == -1
		|| sigaction(SIGUSR2, &s, NULL) == -1)
	{
		write(2, "Error - sigaction\n", 18);
		return (0);
	}
	while (1)
		pause();
	return (0);
}
