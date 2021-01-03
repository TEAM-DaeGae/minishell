/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:20:43 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/17 14:33:48 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_num_len(int n)
{
	long long	nbr;
	int			cnt;

	nbr = (long long)n;
	cnt = 0;
	if (nbr == 0)
		cnt = 1;
	else if (nbr < 0)
	{
		nbr = -nbr;
		cnt = 1;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	long long	nbr;
	char		*str;
	int			n_len;
	int			flag;

	n_len = ft_num_len(n);
	if (!(str = (char *)malloc(sizeof(char) * (n_len + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[n_len] = '\0';
	flag = (n >= 0 ? 0 : 1);
	nbr = (n >= 0 ? (long long)n : -(long long)n);
	n_len = n_len - 1;
	while (n_len >= flag)
	{
		str[n_len] = nbr % 10 + '0';
		nbr /= 10;
		n_len--;
	}
	return (str);
}
