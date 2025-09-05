/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:51:34 by yihssan           #+#    #+#             */
/*   Updated: 2021/01/06 02:37:54 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "libft.h"

# include <stdarg.h>
# define FORMATS "cspdiuxX%"

# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef unsigned char	t_bool;

typedef struct	s_format
{
	char			*content;
	int				idx;
	char			type;
	t_bool			minus;
	t_bool			zero;
	t_bool			prc_dot;
	t_bool			has_width;
	int				precision;
	int				min_width;
	int				xpt;
	int				ret;
}				t_format;

char			*ft_chardup(char c);
char			*ft_strndup(const char *src, size_t n);
int				ft_unumlen(unsigned int n);
char			*ft_uitoa(unsigned int n, t_format *helper);
char			*ft_uitoxa(unsigned int n, t_bool iscap, t_format *helper);
char			*ft_ptoxa(unsigned long long n, t_format *helper);
char			*ft_super_strdup(const char *s1);
char			*ft_super_itoa(int n, t_format *helper);
void			validate_config(t_format *helper, char c);
void			set_config(t_format *helper, char *fstr, va_list args);
void			set_content(t_format *helper, va_list args);
char			*ft_padhelp(int size, char pad);
char			*ft_prefix(t_format *helper, char c);
char			*ft_padding(t_format *helper, char pad, int *outsize);
void			apply_config(t_format *helper);
void			reset_struct(t_format *s);
int				ft_printf(const char *format, ...);

#endif
