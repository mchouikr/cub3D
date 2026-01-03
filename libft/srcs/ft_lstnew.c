/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:34:25 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/27 17:49:58 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem -> content = content;
	elem -> next = NULL;
	return (elem);
}

/* void print_list(t_list* head) {
    while (head != NULL) {
        printf("%d -> ", head->content);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    t_list* head = new_node(10);
    head->next = new_node(20);
    head->next->next = new_node(30);

    print_list(head);

    return 0;
}*/
