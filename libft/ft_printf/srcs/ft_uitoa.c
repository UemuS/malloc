/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:59:37 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 05:03:32 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int		ft_unumlen(unsigned int n)
{
	unsigned int	tempn;
	int				len;

	len = 0;
	tempn = n;
	while (tempn)
	{
		tempn /= 10;
		len++;
	}
	return ((n != 0) ? len : len + 1);
}

char	*ft_uitoa(unsigned int n, t_format *helper)
{
	char		*out;
	int			numlen;
	size_t		i;

	if (!n && helper->prc_dot && !helper->precision)
		return (ft_strdup(""));
	i = 0;
	numlen = ft_unumlen(n);
	if (!(out = malloc(sizeof(char) * (numlen + 1))))
		return (NULL);
	out[0] = '0';
	while (n)
	{
		out[numlen - i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	out[numlen] = '\0';
	return (out);
}
