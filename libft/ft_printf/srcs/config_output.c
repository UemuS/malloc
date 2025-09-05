/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:09:16 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 06:17:22 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static void	finish_precision(t_format *tab, char *tmp, int size)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, tab->content + size);
	free(tab->content);
	tab->content = ft_strdup(tmp2);
	free(tmp2);
}

static void	except_case_preci(t_format *tab, char *tmp, char *strprefix)
{
	free(tmp);
	tmp = ft_strjoin(strprefix, tab->content);
	tab->content = ft_strdup(tmp);
	free(tmp);
	free(strprefix);
}

static void	apply_precision(t_format *helper, char c)
{
	int		size;
	int		prx;
	char	*tmp;
	char	*strprefix;

	if (ft_strchr("diuxXp", c))
	{
		strprefix = ft_prefix(helper, c);
		prx = (strprefix != 0) ? ft_strlen(strprefix) : 0;
		size = ft_strlen(helper->content);
		tmp = ft_padhelp(helper->precision - size + prx, '0');
		size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
		finish_precision(helper, tmp, size);
		if (strprefix != 0)
			return (except_case_preci(helper, tmp, strprefix));
		free(strprefix);
		free(tmp);
	}
	else if (c == 's')
	{
		tmp = helper->content;
		helper->content = ft_strndup(helper->content, helper->precision);
		free(tmp);
	}
}

static void	apply_width(t_format *helper, char pad)
{
	int		size;
	char	*padding;
	char	*tmp;

	size = 0;
	if (helper->min_width > (int)ft_strlen(helper->content))
	{
		padding = ft_padding(helper, pad, &size);
		if (helper->minus)
		{
			tmp = helper->content;
			helper->content = ft_strjoin(helper->content, padding);
			free(tmp);
		}
		else
		{
			tmp = helper->content;
			helper->content = ft_strjoin(padding, helper->content + size);
			free(tmp);
		}
		free(padding);
	}
}

void		apply_config(t_format *helper)
{
	if (helper->prc_dot && ft_strchr(FORMATS, helper->type))
		apply_precision(helper, helper->type);
	if (helper->has_width)
		apply_width(helper, (helper->zero == 1) ? '0' : ' ');
}
