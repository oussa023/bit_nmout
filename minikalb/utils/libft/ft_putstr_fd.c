/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:24:24 by okassimi          #+#    #+#             */
/*   Updated: 2023/09/10 18:40:59 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd, int flag)
{
	int	i;

	i = 0;
	(void)flag;
	if (!s || fd == -1)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (flag == 1)
		write(fd, " ", 1);
	if (flag == 2)
		write(fd, "\n", 1);
}
