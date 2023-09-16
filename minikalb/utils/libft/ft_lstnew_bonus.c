/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:10:25 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/22 19:10:28 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*con;

	con = (t_lst *)malloc(sizeof(t_lst));
	if (!con)
		return (NULL);
	con->content = content;
	con->next = NULL;
	return (con);
}