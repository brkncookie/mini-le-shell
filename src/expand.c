/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:16 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/04 00:39:30 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_inquotes(t_tree **cmdtree, char *str, int arg_num)
{
	t_tree		*tmp;
	static int	i = 0;
	int			arg;

	tmp = *cmdtree;
	arg = 0;
	while (tmp->tkn->next && arg <= arg_num)
	{
		while (tmp->tkn->val[i] && tmp->tkn->val[i] != '$' && i < tmp->tkn->len)
			i++;
		if (!ft_strncmp2(tmp->tkn->val + i, str, ft_strlen(str) - 1)
			&& (tmp->tkn->stat & (IN_QUOTE)))
		{
			while (tmp && tmp->tkn->prev)
				tmp->tkn = tmp->tkn->prev;
			return (i++, 1);
		}
		i = 0;
		if (tmp->tkn->val[0] == ' ')
			arg++;
		tmp->tkn = tmp->tkn->next;
	}
	while (tmp && tmp->tkn->prev)
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

	val = ft_getenvi(cmdtree->arg[i] + *j + 1, *vars_lst, &len);
	if (!is_inquotes(&cmdtree, cmdtree->arg[i] + *j, i) && val)
	{
		len += *j;
		val = ft_realloc(val, ft_strlen(val) + ft_strlen(cmdtree->arg[i] + len)
				+ 1);
		ft_strlcat(val, cmdtree->arg[i] + len, ft_strlen(val)
			+ ft_strlen(cmdtree->arg[i] + len) + 1);
		cmdtree->arg[i] = ft_realloc(cmdtree->arg[i], *j);
		cmdtree->arg[i] = ft_realloc(cmdtree->arg[i], ft_strlen(cmdtree->arg[i])
				+ ft_strlen(val) + 1);
		ft_strlcat(cmdtree->arg[i], val, ft_strlen(val)
			+ ft_strlen(cmdtree->arg[i]) + 1);
	}
	else
		*j = *j + 1;
	free(val);
}
