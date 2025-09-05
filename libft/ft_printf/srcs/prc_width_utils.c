/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prc_width_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:34:09 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 05:35:54 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

char	*ft_padhelp(int size, char pad)
{
	char	*out;
	int		i;

	if (!(out = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
		out[i++] = pad;
	out[i] = '\0';
	return (out);
}

char	*ft_prefix(t_format *helper, char c)
{
	int		size;
	char	*prefix;

	size = ft_strlen(helper->content);
	if (ft_strchr("diuxXp", c) == NULL)
		return (NULL);
	if (size >= 1 && helper->content[0] == '-')
		prefix = ft_strdup("-");
	else if (c == 'p' && size >= 2 && helper->content[0] == '0' &&
									helper->content[1] == 'x')
		prefix = ft_strdup("0x");
	else
		prefix = NULL;
	return (prefix);
}

char	*ft_padding(t_format *helper, char pad, int *outsize)
{
	char	*out;
	int		size;
	char	*tmp;
	char	*strprefix;

	size = helper->min_width - ft_strlen(helper->content);
	size -= (helper->xpt) ? 1 : 0;
	if (!(out = ft_padhelp(size, pad)))
		return (NULL);
	if (helper->zero && !helper->minus)
	{
		strprefix = ft_prefix(helper, helper->type);
		tmp = ft_strjoin(strprefix, out);
		*outsize = (strprefix != NULL) ? ft_strlen(strprefix) : 0;
		free(out);
		out = ft_strdup(tmp);
		free(tmp);
		free(strprefix);
	}
	return (out);
}
