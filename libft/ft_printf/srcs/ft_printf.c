/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:19:39 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 06:56:29 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static void		print(t_format *helper)
{
	char	backslashzero;
	char	flag;

	backslashzero = '\0';
	flag = 0;
	if (helper->xpt == 1 || (helper->xpt == 2 && helper->minus))
	{
		write(1, &backslashzero, 1);
		flag = 1;
	}
	ft_putstr_fd(helper->content, 1);
	if (helper->xpt == 2 && !flag)
		write(1, &backslashzero, 1);
	if (helper->content)
		helper->ret += (int)ft_strlen(helper->content);
	if (helper->xpt)
		helper->ret += 1;
}

static int		init(t_format *helper, char *format, va_list args)
{
	helper->idx++;
	while (format[helper->idx] &&
				ft_strchr("-.*0123456789", format[helper->idx]))
		set_config(helper, format, args);
	if (!format[helper->idx])
		return (0);
	helper->type = format[helper->idx];
	set_content(helper, args);
	validate_config(helper, helper->type);
	apply_config(helper);
	print(helper);
	free(helper->content);
	reset_struct(helper);
	if (helper->content == NULL)
		return (ERROR);
	helper->idx++;
	return (1);
}

static void		init_struct(t_format *helper)
{
	helper->idx = 0;
	helper->ret = 0;
	reset_struct(helper);
}

int				ft_printf(const char *format, ...)
{
	t_format	*helper;
	va_list		args;
	int			ret;

	if (!(helper = malloc(sizeof(t_format))))
		return (-1);
	init_struct(helper);
	va_start(args, format);
	while (format[helper->idx] != '\0')
		if (format[helper->idx] == '%')
		{
			if (init(helper, (char *)format, args) == ERROR)
				return (ERROR);
		}
		else
		{
			write(1, &format[helper->idx], 1);
			helper->ret++;
			helper->idx++;
		}
	va_end(args);
	ret = helper->ret;
	free(helper);
	return (ret);
}
