/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chardup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:51:05 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 04:51:46 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

char	*ft_chardup(char c)
{
	char *out;

	if (!(out = malloc(sizeof(char) * 2)))
		return (NULL);
	out[0] = c;
	out[1] = '\0';
	return (out);
}
