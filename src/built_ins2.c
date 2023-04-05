/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:43 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/04 21:57:49 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int		g_flag[2] = {0, 1};

int	not_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	do_echo(t_tree *cmdtree, int *redr_fds)
{
	int	i;
	int	d;

	i = 1;
	d = 0;
	if (!cmdtree->arg)
	{
		write(redr_fds[1], "\n", 1);
		return ;
	}
	while (cmdtree->arg[i])
	{
		while (!d && cmdtree->arg[i] && !not_option(cmdtree->arg[i]))
			i++;
		if (cmdtree->arg[i])
		{
			write(redr_fds[1], cmdtree->arg[i], ft_strlen(cmdtree->arg[i]));
			d = 1;
			if (cmdtree->arg[++i])
				write(redr_fds[1], " ", 1);
		}
	}
	if (!cmdtree->arg[1] || not_option(cmdtree->arg[1]))
		write(redr_fds[1], "\n", 1);
	g_flag[0] = EXIT_SUCCESS;
}

void	do_pwd(char *pwd)
{
	if (pwd)
	{
		printf("%s\n", pwd);
		g_flag[0] = EXIT_SUCCESS;
	}
	else
		g_flag[0] = EXIT_FAILURE;
}

void	replace_env(char *key, char *val, t_list **vars_lst)
{
	t_list	*tmp;
	t_var	*var;

	tmp = *vars_lst;
	while (tmp)
	{
		var = tmp->ctnt;
		if (!ft_strncmp(var->key, key, ft_strlen(key)))
		{
			free(var->val);
			var->val = ft_strdup(val);
			break ;
		}
		tmp = tmp->next;
	}
}

void	do_cd(t_tree *cmdtree, char *pwd, t_list **vars_lst)
{
	char	*tmp;

	g_flag[0] = 0;
	tmp = getcwd(0, PATH_MAX);
	if ((!cmdtree->arg[1] || !ft_strncmp(cmdtree->arg[1], "~", 2)) && \
		!chdir(ft_getenv("HOME", *vars_lst)))
		(replace_env("OLDPWD", pwd, vars_lst), pwd = getcwd(pwd, PATH_MAX));
	else if (!ft_strncmp(cmdtree->arg[1], "..", 3) && !chdir(".."))
		(replace_env("OLDPWD", pwd, vars_lst), pwd = getcwd(pwd, PATH_MAX));
	else if (dir_exists(cmdtree->arg[1]) && tmp && !chdir(cmdtree->arg[1]))
		(replace_env("OLDPWD", pwd, vars_lst), pwd = getcwd(pwd, PATH_MAX));
	else if (ft_strncmp(cmdtree->arg[1], "..", 3))
	{
		g_flag[0] = 1;
		if (cmdtree->arg[2])
			printf("cd: too many arguments\n");
		else
			printf("cd: invalid directory path\n");
	}
	else
		(replace_env("OLDPWD", pwd, vars_lst), pwd = getcwd(pwd, PATH_MAX));
	replace_env("PWD", pwd, vars_lst);
	free(tmp);
}
