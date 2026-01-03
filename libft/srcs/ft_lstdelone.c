/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:08:52 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/29 15:10:48 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// Free the content pointed by lst.

/*
void	print_list(t_list *list)
{
	while (list)
	{
		if (!list)
			return ;
		write(1, &*(char *)list->content, 1);
		if (list -> next)
			write(1, " -> ", 4);
		list = list-> next;

	}
	write(1, " END\n", 5);
}

int	main()
{
	t_list	*head;


	head = malloc(sizeof(t_list));
	head->content = malloc(sizeof(char));
	*(char *)head->content = 'a';
	head->next = malloc(sizeof(t_list));
	head->next->content = malloc(sizeof(char));
	*(char *)head->next->content = 'b';
	head->next->next = malloc(sizeof(t_list));
	head->next->next->content = malloc(sizeof(char));
	*(char *)head->next->next->content = 'c';
	head->next->next->next = NULL;


	print_list(head);
	ft_lstdelone(head->next, &free);
	print_list(head);

	return (0);
}*/
