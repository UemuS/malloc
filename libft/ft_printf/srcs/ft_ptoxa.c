/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoxa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:09:39 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 05:19:53 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int	ft_pnumlen(unsigned long long n)
{
	unsigned long long	tempn;
	int					len;

	len = 0;
	tempn = n;
	while (tempn)
	{
		tempn /= 16;
		len++;
	}
	return ((n != 0) ? len : len + 1);
}

char		*ft_ptoxa(unsigned long long n, t_format *helper)
{
	char	*out;
	int		numlen;
	int		i;
	char	*final;

	i = 0;
	if (!n && helper->prc_dot && !helper->precision)
		return (ft_strdup("0x"));
	numlen = ft_pnumlen(n);
	if (!(out = malloc(sizeof(char) * (numlen + 1))))
		return (NULL);
	out[0] = '0';
	while (n)
	{
		if ((n % 16) < 10)
			out[numlen - i - 1] = (n % 16) + '0';
		else
			out[numlen - i - 1] = (n % 16) + 'a' - 10;
		n /= 16;
		i++;
	}
	out[numlen] = '\0';
	final = ft_strjoin("0x", out);
	free(out);
	return (final);
}
