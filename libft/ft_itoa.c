/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:28:14 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/15 11:43:09 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strln(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb / 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static void	ft_st(long nb, char *ito, int i)
{
	while (nb)
	{
		i--;
		ito[i] = (nb % 10) + 48;
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*ito;
	int		ln;

	nb = n;
	if (!nb)
		return (ft_strdup("0"));
	ln = ft_strln(n);
	ito = (char *)malloc(sizeof(char) * (1 + ln));
	if (!ito)
		return (NULL);
	if (nb < 0)
	{
		ito[0] = '-';
		nb = nb * -1;
	}
	ft_st(nb, ito, ln);
	ito[ln] = 0;
	return (ito);
}
