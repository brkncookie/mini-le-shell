#include "../include/executor.h"

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
	if (ft_strncmp(cmdtree->arg[1], "-n", 3))
		printf("\n");
}

void	do_pwd(t_tree *cmdtree)
{
	char	*pwd;

	pwd = getcwd(0, 500);
	printf("%s\n", pwd);
	free(pwd);
}

void	do_cd(t_tree *cmdtree)
{
	if (!cmdtree->arg[1])
		chdir(getenv("HOME"));
	else if (cmdtree->arg[2])
		printf("cd: too many arguments\n");
	else
	{
		if (dir_exists(cmdtree->arg[1]))
			chdir(cmdtree->arg[1]);
		else
			printf("cd: invalid directory path\n");
	}
}

void	do_env(t_tree *cmdtree, t_list *vars_lst)
{
	int	i;

	i = 0;
	if (!cmdtree->arg[1])
		while (envp[i])
			printf("%s\n", envp[i++]);
}
