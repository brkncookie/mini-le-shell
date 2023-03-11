#include "../include/executor.h"

int	g_flag;

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
	if (!cmdtree->arg[1] || ft_strncmp(cmdtree->arg[1], "-n", 2))
		printf("\n");
	g_flag = EXIT_SUCCESS;
}

void	do_pwd(t_tree *cmdtree)
{
	char	*pwd;

	(void)cmdtree;
	pwd = getcwd(0, 500);
	printf("%s\n", pwd);
	free(pwd);
	g_flag = EXIT_SUCCESS;
}

void	do_cd(t_tree *cmdtree)
{
	g_flag = 0;
	if (!cmdtree->arg[1] || !ft_strncmp(cmdtree->arg[1], "~", 2))
		chdir(getenv("HOME"));
	else if (cmdtree->arg[2])
	{
		g_flag = 1;
		printf("cd: too many arguments\n");
	}
	else
	{
		if (dir_exists(cmdtree->arg[1]))
			chdir(cmdtree->arg[1]);
		else
		{
			g_flag = 1;
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
		g_flag = 0;
	}
	else
		g_flag = 127;
}
