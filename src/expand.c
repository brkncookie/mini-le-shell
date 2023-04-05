/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:16 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/05 02:10:41 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	do_the_work(t_tree **tmp, int *fd, char *str)
{
	int	j;

	if ((*tmp)->tkn->val[fd[0]] == '$' && !ft_strncmp2((*tmp)->tkn->val + fd[0],
			str, ft_strlen(str) - 1) && fd[1] % 2)
	{
		j = fd[0];
		while ((*tmp)->tkn->val[++j])
			if ((*tmp)->tkn->val[j] == '$')
				return (fd[0] = fd[0] + 1, 1);
		return (fd[0] = 0, fd[1] = 0, 1);
	}
	else if ((*tmp)->tkn->val[fd[0]] == '$' && !ft_strncmp2((*tmp)->tkn->val
			+ fd[0], str, ft_strlen(str) - 1))
	{
		j = fd[0];
		while ((*tmp)->tkn->val[++j])
			if ((*tmp)->tkn->val[j] == '$')
				return (fd[0] = fd[0] + 1, 0);
		return (fd[0] = 0, fd[1] = 0, 0);
	}
	return (2);
}

int	is_inquotes(t_tree **cmdtree, char *str)
{
	t_tree		*tmp;
	static int	fd[2];
	static int	j;
	int			ret;

	tmp = *cmdtree;
	while (tmp->tkn->val[fd[0]])
	{
		if (tmp->tkn->val[fd[0]] == '\"' && !(fd[1] % 2))
		{
			fd[0]++;
			j = !(j) * 1;
		}
		if (!j && tmp->tkn->val[fd[0]] == '\'' && ++fd[0])
			fd[1]++;
		ret = do_the_work(&tmp, fd, str);
		if (ret == 1)
			return (1);
		else if (ret == 0)
			return (0);
		fd[0]++;
	}
	return (fd[0] = 0, fd[1] = 0, 0);
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
