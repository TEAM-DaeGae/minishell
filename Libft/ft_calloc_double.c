/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:33:12 by daelee            #+#    #+#             */
/*   Updated: 2021/01/30 15:05:54 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void            **ft_calloc_double(size_t count, size_t size)
{
    char        **str;
    char        *tokens;
    size_t      i;
    size_t      j;

    tokens = ft_calloc(20, sizeof(char)); //명령어 토큰 갯수...대충..
    if (!(**str = malloc(sizeof(char *)count))))
        return (NULL);
    i = 0;
    while (i++ < count)
    {
        *str = malloc(tokens); 
        j = 0;
        while (j++ < 20)
            strncpy(str[j], tokens, 20);
    }
    return (*str);
}