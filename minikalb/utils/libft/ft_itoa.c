/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:28 by okassimi          #+#    #+#             */
/*   Updated: 2022/11/14 02:46:23 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	long	l;
	int		count;

	count = 0;
	l = n;
	if (l < 0)
	{
		count = 1;
		l = l * -1;
	}
	count++;
	while (l >= 10)
	{
		l = l / 10;
		count++;
	}
	return (count);
}
// signevar    ca    count 
//   a[0]     a[1]    a[2] 

char	*ft_itoa(int n)
{
	char		*p;
	long long	l;
	int			a[3];

	l = n;
	a[2] = ft_count(n);
	a[0] = 0;
	p = malloc((a[2] + 1) * (sizeof(char)));
	if (!p)
		return (0);
	if (l < 0)
	{
		p[0] = '-';
		l = l * -1;
		a[0] = 1;
	}
	p[a[2]--] = '\0';
	while (a[2] >= a[0])
	{
		a[1] = l % 10;
		p[a[2]] = a[1] + '0';
		l = l / 10;
		a[2]--;
	}
	return (p);
}
