/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:46:31 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/05 00:18:27 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

extern int	g_flag[2];

void	do_exit(char *arg, int args_num)
{
	if (args_num == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (args_num == 2 && is_num(arg))
		exit(ft_atoi(arg));
	else if (args_num > 2)
		printf("exit: too many arguments\n");
	else
	{
		printf("exit: numeric argument required\n");
		exit(2);
	}
}

void	do_env(t_tree *cmdtree, t_list **vars_lst)
{
	t_list	*tmp;

	if (vars_lst)
	{
		tmp = *vars_lst;
		if (cmdtree && !cmdtree->arg[1])
		{
			while (tmp)
			{
				printf("%s=%s\n", ((t_var *)tmp->ctnt)->key,
					((t_var *)tmp->ctnt)->val);
				tmp = tmp->next;
			}
			g_flag[0] = 0;
		}
	}
	else
		g_flag[0] = 127;
}

void	replace_var(t_tree *cmdtree, char **tmp, int *i, t_list **vars_lst)
{
	char	*val;
	int		l;

	val = ft_getenvi((*tmp) + *i + 1, *vars_lst, &l);
	if (!is_inquotes(&cmdtree, (*tmp) + *i) && val)
	{
		l += *i;
		val = ft_realloc(val, ft_strlen(val) + ft_strlen((*tmp) + l) + 1);
		ft_strlcat(val, (*tmp) + l, ft_strlen(val) + ft_strlen((*tmp) + l) + 1);
		(*tmp) = ft_realloc((*tmp), *i);
		(*tmp) = ft_realloc((*tmp), ft_strlen(val) + ft_strlen((*tmp)) + 1);
		ft_strlcat((*tmp), val, ft_strlen(val) + ft_strlen((*tmp)) + 1);
		cmdtree->tkn->val = (*tmp);
		cmdtree->tkn->len = 0;
	}
	else
		*i = *i + 1;
	free(val);
}

int	newline_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}
