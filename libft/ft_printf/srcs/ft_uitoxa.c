/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoxa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:04:20 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 05:05:15 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int		ft_uxnumlen(unsigned int n)
{
	unsigned int	tempn;
	int				len;

	len = 0;
	tempn = n;
	while (tempn)
	{
		tempn /= 16;
		len++;
	}
	return ((n != 0) ? len : len + 1);
}

char			*ft_uitoxa(unsigned int n, t_bool iscap, t_format *helper)
{
	char		*out;
	size_t		numlen;
	char		c;
	size_t		i;

	if (!n && helper->prc_dot && !helper->precision)
		return (ft_strdup(""));
	i = 0;
	c = (iscap) ? 'A' : 'a';
	numlen = ft_uxnumlen(n);
	if (!(out = malloc(sizeof(char) * (numlen + 1))))
		return (NULL);
	out[0] = '0';
	while (n)
	{
		if ((n % 16) < 10)
			out[numlen - i - 1] = (n % 16) + '0';
		else
			out[numlen - i - 1] = (n % 16) + c - 10;
		n /= 16;
		i++;
	}
	out[numlen] = '\0';
	return (out);
}
