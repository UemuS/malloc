/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:21:17 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 05:27:32 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int	set_flags(char *fstr, t_format *helper)
{
	if (fstr[helper->idx] == '-' && helper->idx++)
		return ((helper->minus = 1));
	else if (fstr[helper->idx] == '0' && helper->idx++)
		return ((helper->zero = 1));
	return (0);
}

static int	set_width(char *fstr, t_format *helper, va_list args)
{
	if (fstr[helper->idx] == '*')
	{
		helper->min_width = va_arg(args, int);
		helper->has_width = 1;
		if (helper->min_width < 0)
		{
			helper->minus = 1;
			helper->min_width = -helper->min_width;
		}
		return ((helper->idx += 1));
	}
	else if (ft_isdigit(fstr[helper->idx]))
	{
		while (fstr[helper->idx] == '0')
			helper->idx++;
		helper->min_width = ft_atoi(&fstr[helper->idx]);
		helper->idx += ft_unumlen(helper->min_width);
		return ((helper->has_width = 1));
	}
	return (0);
}

static int	set_precision(char *fstr, t_format *helper, va_list args)
{
	if (fstr[helper->idx] == '.')
	{
		helper->idx++;
		if (fstr[helper->idx] == '*')
		{
			helper->precision = va_arg(args, int);
			helper->prc_dot = (helper->precision >= 0) ? 1 : 0;
			return ((helper->idx += 1));
		}
		while (fstr[helper->idx] == '0')
			helper->idx++;
		if (!ft_isdigit(fstr[helper->idx]))
		{
			helper->precision = 0;
			return ((helper->prc_dot = 1));
		}
		helper->precision = ft_atoi(&fstr[helper->idx]);
		helper->idx += ft_unumlen(helper->precision);
		return ((helper->prc_dot = 1));
	}
	return (0);
}

void		set_content(t_format *helper, va_list args)
{
	if (helper->type == 'i' || helper->type == 'd')
		helper->content = ft_super_itoa(va_arg(args, int), helper);
	else if (helper->type == 's')
		helper->content = ft_super_strdup(va_arg(args, char*));
	else if (helper->type == 'c')
	{
		helper->content = ft_chardup(va_arg(args, int));
		if (helper->content[0] == '\0')
			helper->xpt = (helper->precision || helper->min_width) ? 2 : 1;
	}
	else if (helper->type == 'x')
		helper->content = ft_uitoxa(va_arg(args, unsigned int), FALSE, helper);
	else if (helper->type == 'X')
		helper->content = ft_uitoxa(va_arg(args, unsigned int), TRUE, helper);
	else if (helper->type == 'p')
		helper->content = ft_ptoxa(va_arg(args, unsigned long long), helper);
	else if (helper->type == 'u')
		helper->content = ft_uitoa(va_arg(args, unsigned int), helper);
	else
		helper->content = ft_chardup(helper->type);
}

void		set_config(t_format *helper, char *fstr, va_list args)
{
	if (set_flags(fstr, helper) == 1)
		return ;
	if (set_width(fstr, helper, args) == 1)
		return ;
	if (set_precision(fstr, helper, args) == 1)
		return ;
}
