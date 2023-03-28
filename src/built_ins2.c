/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:32:04 by saltysushi        #+#    #+#             */
/*   Updated: 2023/03/28 16:54:54 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int		g_flag[2] = {0, 1};

int	dir_exists(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	do_echo(t_tree *cmdtree)
{
	int	i;

	i = 1;
	if (!cmdtree->arg)
	{
		printf("\n");
		return ;
	}
	while (cmdtree->arg[i])
	{
		if (i == 1 && !ft_strncmp(cmdtree->arg[i], "-n", 3) && i++)
			continue ;
		printf("%s", cmdtree->arg[i++]);
		if (cmdtree->arg[i])
			printf(" ");
	}
	if (!cmdtree->arg[1] || ft_strncmp(cmdtree->arg[1], "-n", 3))
		printf("\n");
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

void	do_cd(t_tree *cmdtree, char *pwd)
{
	char	*tmp;

	g_flag[0] = 0;
	if (!cmdtree->arg[1] || !ft_strncmp(cmdtree->arg[1], "~", 2)
		|| !ft_strncmp(cmdtree->arg[1], "..", 3))
	{
		if (ft_strncmp(cmdtree->arg[1], "..", 3))
			chdir(getenv("HOME"));
		else
			chdir("..");
		free(pwd);
		pwd = getcwd(0, 500);
	}
	else
	{
		tmp = getcwd(0, 500);
		if (dir_exists(cmdtree->arg[1]) && tmp)
		{
			chdir(cmdtree->arg[1]);
			free(pwd);
			pwd = getcwd(0, 500);
			free(tmp);
		}
		else
		{
			g_flag[0] = 1;
			if (cmdtree->arg[2])
				printf("cd: too many arguments\n");
			else
				printf("cd: invalid directory path\n");
		}
	}
}

void	do_env(t_tree *cmdtree, t_list **vars_lst)
{
	t_list	*tmp;

	tmp = *vars_lst;
	if (!cmdtree->arg[1])
	{
		while (tmp)
		{
			printf("%s=%s\n", ((t_var *)tmp->content)->key,
				((t_var *)tmp->content)->val);
			tmp = tmp->next;
		}
		g_flag[0] = 0;
	}
	else
		g_flag[0] = 127;
}
