/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 19:11:40 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/17 00:18:33 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	minus;
	int	num;

	minus = 1;
	num = 0;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
				|| *str == '\f' || *str == '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (*str - '0') + (num * 10);
		str++;
	}
	return (minus * num);
}
