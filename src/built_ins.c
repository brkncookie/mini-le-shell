#include "../include/executor.h"

int	dir_exists(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

int	do_echo(t_tree *cmdtree)
{
	int	i;

	i = 1;
	while (cmdtree->arg[i])
	{
		if (i == 1 && ft_strncmp(cmdtree->arg[i], "-n", 2) && i++)
			continue ;
		printf("%s", cmdtree->arg[i++]);
	}
	if (ft_strncmp(cmdtree->arg[1], "-n", 2))
		printf("\n");
	return (0);
}

int	do_pwd(t_tree *cmdtree)
{
	char	*pwd;

	pwd = getcwd(0, 500);
	printf("%s", pwd);
	free(pwd);
	return (0);
}

int	do_cd(t_tree *cmdtree)
{
	if (!cmdtree->arg[1])
		chdir(getenv("HOME"));
	else if (cmdtree->arg[2])
		printf("cd: too many arguments");
	else
	{
		if (dir_exists(cmdtree->arg[1]))
			chdir(cmdtree->arg[1]);
		else
			printf("invalid directory path");
	}
	return (0);
}
