/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:18:23 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/29 01:05:26 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current -> next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}

//You have to free a tmp node
//If you delete current node
//You don"t have access to the next one (current -> next)
//Can use ft_delone but for sake of understanding I didn;t
