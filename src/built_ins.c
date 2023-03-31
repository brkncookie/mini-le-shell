/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:11:16 by saltysushi        #+#    #+#             */
/*   Updated: 2023/03/31 12:30:39 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

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

void	expand(t_tree *cmdtree, t_list **vars_lst)
{
	int	i;
	int	j;

	i = 0;
	while (cmdtree->arg && cmdtree->arg[i])
	{
		j = 0;
		while (cmdtree->arg[i][j])
		{
			if (cmdtree->arg[i][j] == '$')
				expand2(cmdtree, i, &j, vars_lst);
			else
				j++;
		}
		expand3(cmdtree, i);
		i++;
	}
}

int	built_in(t_tree *cmdtree, t_list **vars_lst, char *pwd, int *redr_fds)
{
	if (!ft_strncmp(cmdtree->arg[0], "echo", 5))
		return (do_echo(cmdtree, redr_fds), 1);
	if (!ft_strncmp(cmdtree->arg[0], "exit", 5))
		return (do_exit(cmdtree->arg[1], count_args(cmdtree)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "cd", 3))
		return (do_cd(cmdtree, pwd), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "pwd", 4))
		return (do_pwd(pwd), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "env", 4))
		return (do_env(cmdtree, vars_lst), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "export", 7))
		return (do_export(cmdtree, vars_lst), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "unset", 6))
		return (do_unset(cmdtree, vars_lst), 1);
	return (0);
}

int	do_builtin(t_tree *cmdtree, int *redr_fds, t_list **vars_lst)
{
	int			in;
	int			out;
	static char	*pwd;

	if (!pwd)
		pwd = getcwd(0, 500);
	in = dup(0);
	out = dup(1);
	if (dup2(redr_fds[0], 0) < 0 || dup2(redr_fds[1], 1) < 0)
		return (perror("dup2"), exit(errno), 1);
	expand(cmdtree, vars_lst);
	if (built_in(cmdtree, vars_lst, pwd, redr_fds))
	{
		if (dup2(in, 0) < 0 || dup2(out, 1) < 0)
			return (perror("dup2"), exit(errno), 1);
		return (1);
	}
	else if (dup2(in, 0) < 0 || dup2(out, 1) < 0)
		return (perror("dup2"), exit(errno), 0);
	return (0);
}
