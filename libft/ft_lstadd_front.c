/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:33:30 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/19 15:57:34 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int	main(void)
// {
// 	t_list	**lst;
// 	t_list	*ls;

// 	ls = ft_lstnew("first");
// 	*lst = ls;
// 	ls->next = ft_lstnew(" sconde");
// 	ls->next->next = 0;
// 	ft_lstadd_front(lst, ft_lstnew("0"));
// 	while (*lst)
// 	{
// 		printf("%s", (char *) (*lst)->content);
// 		*lst= (*lst)->next;
// 	}
// }
