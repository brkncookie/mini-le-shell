#include "../include/executor.h"

extern int	g_flag;

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

int	next_isspace(t_tree **cmdtree, char *str)
{
	t_tree	*tmp;

	tmp = *cmdtree;
	while (tmp->tkn->prev)
		tmp->tkn = tmp->tkn->prev;
	while (tmp->tkn->next)
	{
		if (!ft_strncmp(tmp->tkn->val, str, ft_strlen(str))
			&& !(tmp->tkn->next->type & (WORD | QUOTE | DQUOTE)))
			return (1);
		tmp->tkn = tmp->tkn->next;
	}
	return (0);
}

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

void	do_export(t_tree *cmdtree, t_list **vars_lst)
{
	t_list	*tmp;
	int		i;
	int		equ;
	int		found;

	g_flag = 0;
	i = 1;
	tmp = *vars_lst;
	if (!cmdtree->arg[1])
	{
		while (tmp)
		{
			printf("declare -x %s=%s\n", ((t_var *)tmp->content)->key,
				((t_var *)tmp->content)->val);
			tmp = tmp->next;
		}
	}
	while (cmdtree->arg[i])
	{
		equ = ft_strchrr(cmdtree->arg[i], '=');
		if ((ft_isdigit(cmdtree->arg[i][0]) && cmdtree->arg[i][0] == '=')
			|| !ft_strchr(cmdtree->arg[i], '='))
		{
			printf("export: %s: invalid argument\n", cmdtree->arg[i++]);
			g_flag = 1;
			continue ;
		}
		found = 0;
		tmp = *vars_lst;
		while (tmp && tmp->content)
		{
			if (!ft_strncmp(cmdtree->arg[i], ((t_var *)tmp->content)->key,
					ft_strlen(((t_var *)tmp->content)->key)))
			{
				free(((t_var *)tmp->content)->val);
				((t_var *)tmp->content)->val = ft_substr(cmdtree->arg[i], equ
						+ 1, ft_strlen(cmdtree->arg[i]));
				found = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (!found)
			add_variable(vars_lst, cmdtree, &i);
		i++;
	}
}

void	do_unset(t_tree *cmdtree, t_list **vars_lst)
{
	int		i;
	t_list	*tmp;
	t_list	*next;

	g_flag = 0;
	tmp = *vars_lst;
	while (tmp && tmp->next && tmp->next->content)
	{
		i = 1;
		while (cmdtree->arg[i])
		{
			if ((ft_isdigit(cmdtree->arg[i][0])))
			{
				printf("unset: %s: invalid argument\n", cmdtree->arg[i++]);
				g_flag = 1;
				continue ;
			}
			if (!ft_strncmp(cmdtree->arg[i], ((t_var *)tmp->next->content)->key,
					ft_strlen(((t_var *)tmp->next->content)->key) + 1))
			{
				next = tmp->next;
				tmp->next = next->next;
				free(((t_var *)next->content)->key);
				free(((t_var *)next->content)->val);
				free(next->content);
				free(next);
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
