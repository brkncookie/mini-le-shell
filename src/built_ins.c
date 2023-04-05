/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:50 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/04 21:48:54 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

extern int	g_flag[2];

void	expand_in_tree(t_tree *cmdtree, t_list **vars_lst)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (cmdtree->redr)
		expand_in_tree(cmdtree->redr, vars_lst);
	cmdtree = cmdtree->limn;
	tmp = ft_strndup(cmdtree->tkn->val, cmdtree->tkn->len);
	while (tmp && tmp[i])
	{
		if (tmp[i] == '$')
			replace_var(cmdtree, &tmp, &i, vars_lst);
		else
			i++;
	}
	if (cmdtree->tkn->len)
		free(tmp);
}

void	expand(t_tree *cmdtree, t_list **vars_lst)
{
	int	i;
	int	j;

	i = 0;
	while (cmdtree->arg && cmdtree->arg[i])
	{
		j = 0;
		while (cmdtree->arg && cmdtree->arg[i] && cmdtree->arg[i][j])
		{
			if (cmdtree->arg[i][j] == '$')
				expand2(cmdtree, i, &j, vars_lst);
			else
				j++;
		}
		expand3(cmdtree, i);
		i++;
	}
	if (cmdtree->tkn->type & (REDR_I | REDR_O | APPEND | HERE_DOC))
		expand_in_tree(cmdtree, vars_lst);
	else if (cmdtree->redr)
		expand_in_tree(cmdtree->redr, vars_lst);
}

int	built_in(t_tree *cmdtree, t_list **vars_lst, char *pwd, int *redr_fds)
{
	if (cmdtree->arg)
	{
		if (!ft_strncmp(cmdtree->arg[0], "echo", 5))
			return (do_echo(cmdtree, redr_fds), 1);
		if (!ft_strncmp(cmdtree->arg[0], "exit", 5))
			return (do_exit(cmdtree->arg[1], count_args(cmdtree)), 1);
		else if (!ft_strncmp(cmdtree->arg[0], "cd", 3))
			return (do_cd(cmdtree, pwd, vars_lst), 1);
		else if (!ft_strncmp(cmdtree->arg[0], "pwd", 4))
			return (do_pwd(pwd), 1);
		else if (!ft_strncmp(cmdtree->arg[0], "env", 4))
			return (do_env(cmdtree, vars_lst), 1);
		else if (!ft_strncmp(cmdtree->arg[0], "export", 7))
			return (do_export(cmdtree, vars_lst), 1);
		else if (!ft_strncmp(cmdtree->arg[0], "unset", 6))
			return (do_unset(cmdtree, vars_lst), 1);
	}
	return (0);
}

int	is_built_in(t_tree *cmdtree)
{
	if (cmdtree->arg)
	{
		if (!ft_strncmp(cmdtree->arg[0], "echo", 5))
			return (1);
		if (!ft_strncmp(cmdtree->arg[0], "exit", 5))
			return (1);
		else if (!ft_strncmp(cmdtree->arg[0], "cd", 3))
			return (1);
		else if (!ft_strncmp(cmdtree->arg[0], "pwd", 4))
			return (1);
		else if (!ft_strncmp(cmdtree->arg[0], "env", 4))
			return (1);
		else if (!ft_strncmp(cmdtree->arg[0], "export", 7))
			return (1);
		else if (!ft_strncmp(cmdtree->arg[0], "unset", 6))
			return (1);
	}
	return (0);
}

int	do_builtin(t_tree *cmdtree, int *redr_fds, int *oredr_fds,
		t_list **vars_lst)
{
	int			bkup[2];
	static char	*pwd;

	if (!is_built_in(cmdtree))
		return (0);
	if (!pwd)
		pwd = getcwd(0, PATH_MAX);
	bkup[0] = dup(0);
	bkup[1] = dup(1);
	if (dup2(redr_fds[0], 0) < 0 || dup2(redr_fds[1], 1) < 0 || bkup[0] < 0
		|| bkup[1] < 0)
		return (perror("dup/dup2"), g_flag[0] = 1, 0);
	if (built_in(cmdtree, vars_lst, pwd, redr_fds))
	{
		if (cmdtree->redr)
			(file_close(redr_fds),
				ft_memcpy(redr_fds, oredr_fds, sizeof redr_fds));
		if (dup2(bkup[0], 0) < 0 || dup2(bkup[1], 1) < 0)
			return (perror("dup2"), g_flag[0] = 1);
		return (1);
	}
	else if (dup2(bkup[0], 0) < 0 || dup2(bkup[1], 1) < 0)
		return (perror("dup2"), g_flag[0] = 1, 0);
	return (0);
}
