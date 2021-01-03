/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:22:31 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/17 14:41:47 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_positive_n_write(long long nbr, int fd)
{
	int			i;
	char		a[12];

	i = 0;
	while (nbr > 0)
	{
		a[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	i = i - 1;
	while (i >= 0)
	{
		ft_putchar_fd(a[i], fd);
		i--;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	long long	nbr;

	nbr = (long long)n;
	if (nbr == 0)
		ft_putchar_fd('0', fd);
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 0)
	{
		ft_positive_n_write(nbr, fd);
	}
}
