#include "../include/executor.h"
#include "../include/global.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
		printf("exit: too many arguments");
	else
	{
		printf("exit: numeric argument required");
		exit(2);
	}
}

void	add_variable(t_list **vars_lst, char *str, int equ)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	var->key = ft_substr(str, 0, equ);
	var->val = ft_substr(str, equ + 1, ft_strlen(str));
	ft_lstadd_back(vars_lst, ft_lstnew(var));
}

void	do_export(t_tree *cmdtree, t_list **vars_lst)
{
	t_list	*tmp;
	int		i;
	int		equ;
	int		found;

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
	else if (!(ft_isdigit(cmdtree->arg[1][0]) || cmdtree->arg[1][0] == '=')
			&& ft_strchr(cmdtree->arg[1], '='))
	{
		while (cmdtree->arg[i])
		{
			found = 0;
			tmp = *vars_lst;
			while (tmp && tmp->content)
			{
				equ = ft_strchrr(cmdtree->arg[i], '=');
				if (!ft_strncmp(cmdtree->arg[i], ((t_var *)tmp->content)->key,
						ft_strlen(((t_var *)tmp->content)->key)))
				{
					free(((t_var *)tmp->content)->val);
					((t_var *)tmp->content)->val = ft_substr(cmdtree->arg[i],
							equ + 1, ft_strlen(cmdtree->arg[i]));
					found = 1;
					break ;
				}
				tmp = tmp->next;
			}
			if (!found)
				add_variable(vars_lst, cmdtree->arg[i], equ);
			i++;
		}
	}
	else
		printf("export: invalid argument\n");
}

void	do_unset(t_tree *cmdtree, t_list **vars_lst)
{
	int		i;
	t_list	*tmp;
	t_list	*next;

	tmp = *vars_lst;
	while (tmp && tmp->next->content)
	{
		i = 1;
		while (cmdtree->arg[i])
		{
			if (!ft_strncmp(cmdtree->arg[i], ((t_var *)tmp->next->content)->key,
					ft_strlen(((t_var *)tmp->next->content)->key)))
			{
				next = tmp->next;
				tmp->next = next->next;
				free(((t_var *)next->content)->key);
				free(((t_var *)next->content)->val);
				free(next->content);
				free(next);
				g_flag = 0;
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
