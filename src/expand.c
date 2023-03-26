/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:36:14 by saltysushi        #+#    #+#             */
/*   Updated: 2023/03/26 23:17:23 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_inquotes(t_tree **cmdtree, char *str)
{
	t_tree		*tmp;
	static int	i;

	i = 0;
	tmp = *cmdtree;
	while (tmp->tkn->next)
	{
		while (tmp->tkn->val[i] && tmp->tkn->val[i] != '$')
			i++;
		if (!ft_strncmp(tmp->tkn->val + i, str, ft_strlen(str))
			&& (tmp->tkn->stat & (IN_QUOTE)))
			return (i++, 1);
		i = 0;
		tmp->tkn = tmp->tkn->next;
	}
	while (tmp->tkn->prev)
		tmp->tkn = tmp->tkn->prev;
	return (0);
}

char	*ft_realloc(char *str, int len)
{
	char	*new;

	new = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(new, str, len + 1);
	free(str);
	return (new);
}

void	expand2(t_tree *cmdtree, int i, int *j, t_list **vars_lst)
{
	char	*val;
	int		len;

	if (!is_inquotes(&cmdtree, cmdtree->arg[i] + *j))
	{
		val = ft_getenvi(cmdtree->arg[i] + *j + 1, *vars_lst, &len);
		len += *j;
		ft_strlcat(val, cmdtree->arg[i] + len, ft_strlen(val)
			+ ft_strlen(cmdtree->arg[i] + len) + 1);
		cmdtree->arg[i] = ft_realloc(cmdtree->arg[i], *j);
		ft_strlcat(cmdtree->arg[i], val, ft_strlen(val)
			+ ft_strlen(cmdtree->arg[i]) + 1);
		if (ft_strncmp(val, cmdtree->arg[i] + len, ft_strlen(cmdtree->arg[i]
					+ len)))
			*j = *j + 1;
		free(val);
	}
	else
		*j = *j + 1;
}
