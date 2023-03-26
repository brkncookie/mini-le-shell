#include "../include/executor.h"

int	is_inquotes(t_tree **cmdtree, char *str)
{
	t_tree		*tmp;
	static int	i = 0;

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

void	expand2(t_tree *cmdtree, int i, int *j, t_list **vars_lst)
{
	char	*val;
	int		len;

	if (!is_inquotes(&cmdtree, cmdtree->arg[i] + *j))
	{
		val = ft_getenvi(cmdtree->arg[i] + *j + 1, *vars_lst, &len, j);
		len += *j;
		ft_strlcat(val, cmdtree->arg[i] + len, ft_strlen(val)
			+ ft_strlen(cmdtree->arg[i] + len) + 1);
		cmdtree->arg[i][*j] = '\0';
		ft_strlcat(cmdtree->arg[i], val, ft_strlen(val)
			+ ft_strlen(cmdtree->arg[i]) + 1);
		if (!ft_strncmp(val, "0", 2))
			*j = *j + 1;
	}
	else
		*j = *j + 1;
}