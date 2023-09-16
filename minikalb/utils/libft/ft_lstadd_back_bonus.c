/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:11:03 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/22 19:11:04 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*a;

	if (lst == NULL)
		return ;
	a = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (a->next != NULL)
		a = a->next;
	a->next = new;
}