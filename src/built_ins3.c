/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:33 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/01 16:00:47 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

extern int	g_flag[2];

void	add_variable(t_list **vars_lst, t_tree *cmdtree, int *i)
{
	t_var	*var;
	int		equ;

	var = ft_calloc(1, sizeof(t_var));
	equ = ft_strchrr(cmdtree->arg[*i], '=');
	var->key = ft_substr(cmdtree->arg[*i], 0, equ);
	var->val = ft_substr(cmdtree->arg[*i], equ + 1,
			ft_strlen(cmdtree->arg[*i]));
	ft_lstadd_back(vars_lst, ft_lstnew(var));
}

void	add_or_replace(t_list **vars_lst, t_tree *cmdtree, int *i)
{
	t_list	*tmp;
	int		equ;
	int		found;

	tmp = *vars_lst;
	found = 0;
	while (tmp)
	{
		if (!ft_strncmp(cmdtree->arg[*i], ((t_var *)tmp->ctnt)->key,
				ft_strlen(((t_var *)tmp->ctnt)->key)))
		{
			equ = ft_strchrr(cmdtree->arg[*i], '=');
			free(((t_var *)tmp->ctnt)->val);
			((t_var *)tmp->ctnt)->val = ft_substr(cmdtree->arg[*i], equ + 1,
					ft_strlen(cmdtree->arg[*i]));
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_variable(vars_lst, cmdtree, i);
}

void	do_export(t_tree *cmdtree, t_list **vars_lst)
{
	t_list	*tmp;
	int		i;

	g_flag[0] = 0;
	i = 1;
	tmp = *vars_lst;
	while (!cmdtree->arg[1] && tmp)
	{
		printf("declare -x %s=%s\n", ((t_var *)tmp->ctnt)->key,
			((t_var *)tmp->ctnt)->val);
		tmp = tmp->next;
	}
	while (cmdtree->arg[i])
	{
		if ((ft_isdigit(cmdtree->arg[i][0]) && cmdtree->arg[i][0] == '=')
			|| !ft_strchr(cmdtree->arg[i], '='))
		{
			printf("export: %s: invalid argument\n", cmdtree->arg[i++]);
			g_flag[0] = 1;
			continue ;
		}
		add_or_replace(vars_lst, cmdtree, &i);
		i++;
	}
}

void	del_one(t_list **vars_lst, char *str, t_list **prev, t_list **tmp)
{
	while (*tmp)
	{
		if (!ft_strncmp(str, ((t_var *)(*tmp)->ctnt)->key,
			ft_strlen(((t_var *)(*tmp)->ctnt)->key)))
		{
			if (*tmp != *vars_lst)
				(*prev)->next = (*tmp)->next;
			else
				*vars_lst = (*tmp)->next;
			free(((t_var *)(*tmp)->ctnt)->key);
			free(((t_var *)(*tmp)->ctnt)->val);
			free((*tmp)->ctnt);
			free(*tmp);
			break ;
		}
		*prev = *tmp;
		*tmp = (*tmp)->next;
	}
}

void	do_unset(t_tree *cmdtree, t_list **vars_lst)
{
	int		i;
	t_list	*tmp;
	t_list	*prev;

	i = -1;
	g_flag[0] = 0;
	prev = NULL;
	while (cmdtree->arg[++i])
	{
		if (ft_isdigit(cmdtree->arg[i][0]))
		{
			printf("unset: %s: invalid argument\n", cmdtree->arg[i]);
			g_flag[0] = 1;
			continue ;
		}
		tmp = *vars_lst;
		del_one(vars_lst, cmdtree->arg[i], &prev, &tmp);
	}
}
