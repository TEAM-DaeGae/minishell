/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:23:14 by gaekim            #+#    #+#             */
/*   Updated: 2021/01/07 23:12:23 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	if (!(str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char))))
		return (NULL);
	while (i < len_s1)
		str[i++] = s1[j++];
	j = 0;
	while (i < len_s1 + len_s2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
