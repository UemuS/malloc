/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:15:04 by yihssan           #+#    #+#             */
/*   Updated: 2019/10/10 20:04:40 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*current;

	if (!alst)
		return ;
	current = *alst;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*alst = new;
}
