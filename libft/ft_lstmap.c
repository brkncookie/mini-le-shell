/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:36:57 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:36:58 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*save;

	if (!lst || !f || !del)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (0);
	save = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&save, del);
			return (0);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (save);
}

/*
void * addOne(void * p)
{
	void * r = malloc(sizeof(int));
	*(int*)r = *(int*)p + 1;
	return (r);
}

int main(void)
{
	int tab[] = {0, 1, 2, 3};
	t_list *l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list *m = ft_lstmap(l, addOne, free);
	t_list *tmp = l;
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", ( *(int *)tmp->content));
		tmp = tmp->next;
	}
	tmp = m;
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", (*(int*)tmp->content));
		tmp = tmp->next;
	}
	return (0);
}
*/