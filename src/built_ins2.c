/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:43 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/03 15:50:32 by mnadir           ###   ########.fr       */
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
		while (!d && cmdtree->arg[i] && !ft_strncmp(cmdtree->arg[i], "-n", 2))
			i++;
		if (cmdtree->arg[i])
		{
			write(redr_fds[1], cmdtree->arg[i], ft_strlen(cmdtree->arg[i]));
			d = 1;
			if (cmdtree->arg[++i])
				write(redr_fds[1], " ", 1);
		}
	}
	if (!cmdtree->arg[1] || ft_strncmp(cmdtree->arg[1], "-n", 2))
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

void	do_cd(t_tree *cmdtree, char *pwd, t_list **vars_lst)
{
	char	*tmp;

	g_flag[0] = 0;
	tmp = getcwd(0, 500);
	if (!cmdtree->arg[1] || !ft_strncmp(cmdtree->arg[1], "~", 2))
		chdir(ft_getenv("HOME", *vars_lst));
	else if (!ft_strncmp(cmdtree->arg[1], "..", 3))
		chdir("..");
	else if (dir_exists(cmdtree->arg[1]) && tmp && !chdir(cmdtree->arg[1]))
		pwd = getcwd(pwd, 500);
	else
	{
		g_flag[0] = 1;
		if (cmdtree->arg[2])
			printf("cd: too many arguments\n");
		else
			printf("cd: invalid directory path\n");
	}
	if (tmp || !ft_strncmp(cmdtree->arg[1], "..", 3))
		pwd = getcwd(pwd, 500);
	free(tmp);
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
