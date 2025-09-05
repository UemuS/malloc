/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:14:41 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 06:18:20 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

char	*ft_super_strdup(const char *s1)
{
	if (s1 == NULL)
		return (ft_strdup("(null)"));
	else
		return (ft_strdup(s1));
}

char	*ft_super_itoa(int n, t_format *helper)
{
	if (!n && helper->prc_dot && !helper->precision)
		return (ft_strdup(""));
	else
		return (ft_itoa(n));
}

void	validate_config(t_format *helper, char c)
{
	if (helper->prc_dot && ft_strchr("diuxX", c))
		helper->zero = 0;
	if (helper->minus)
		helper->zero = 0;
}

void	reset_struct(t_format *s)
{
	s->has_width = 0;
	s->min_width = 0;
	s->prc_dot = 0;
	s->precision = 0;
	s->type = 0;
	s->zero = 0;
	s->minus = 0;
	s->xpt = 0;
}
