/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:21:09 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/19 17:24:19 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// int	main(void)
// {
// 	t_list	**lst;
// 	t_list	*ls;

// 	ls = ft_lstnew(ft_strdup(" 0"));
// 	ls->next = ft_lstnew(ft_strdup(" 1"));
// 	ls->next->next = ft_lstnew(ft_strdup(" 2"));
// 	ls->next->next->next = ft_lstnew(ft_strdup("3"));
// 	*lst = ls;
// 	ft_lstdelone(ls->next->next, freeList);
// 	while (*lst)
// 	{
// 		printf("%s \t", (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// }
