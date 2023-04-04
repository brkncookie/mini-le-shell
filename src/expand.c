/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:16 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/04 17:45:55 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_inquotes(t_tree **cmdtree, char *str)
{
	t_tree		*tmp;
	static int	i;
	int			j;
	static int	quotes;

	tmp = *cmdtree;
	while (tmp->tkn->val[i])
	{
		if (tmp->tkn->val[i] == '\'')
			quotes++;
		if (tmp->tkn->val[i] == '$' && !ft_strncmp2(tmp->tkn->val + i, str,
				ft_strlen(str) - 1) && quotes % 2)
		{
			j = i;
			while (tmp->tkn->val[++j])
				if (tmp->tkn->val[j] == '$')
					return (i++, 1);
			return (i = 0, quotes = 0, 1);
		}
		else if (tmp->tkn->val[i] == '$' && !ft_strncmp2(tmp->tkn->val + i, str,
				ft_strlen(str) - 1))
		{
			j = i;
			while (tmp->tkn->val[++j])
				if (tmp->tkn->val[j] == '$')
					return (i++, 0);
			return (i = 0, quotes = 0, 0);
		}
		i++;
	}
	return (i = 0, quotes = 0, 0);
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
	if (!is_inquotes(&cmdtree, cmdtree->arg[i] + *j) && val)
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
