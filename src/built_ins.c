#include "../include/executor.h"

int	dir_exists(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

int	do_echo(t_tree *cmdtree, int *redr_fds)
{
	int	i;
	int	in;
	int	out;

	i = 1;
	if (redr_fds)
	{
		in = dup(0);
		out = dup(1);
		(dup2(redr_fds[0], 0), dup2(redr_fds[1], 1));
	}
	if (!cmdtree->arg)
		return (printf("\n"), 0);
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
	(dup2(in, 0), dup2(out, 1));
	return (0);
}

int	do_pwd(t_tree *cmdtree, int *redr_fds)
{
	char	*pwd;
	int		in;
	int		out;

	if (redr_fds)
	{
		in = dup(0);
		out = dup(1);
		(dup2(redr_fds[0], 0), dup2(redr_fds[1], 1));
	}
	pwd = getcwd(0, 500);
	printf("%s\n", pwd);
	free(pwd);
	(dup2(in, 0), dup2(out, 1));
	return (0);
}

int	do_cd(t_tree *cmdtree, int *redr_fds)
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
	return (0);
}

int	do_env(t_tree *cmdtree, int *redr_fds, char **envp)
{
	int	i;

	i = 0;
	if (!cmdtree->arg[1])
		while (envp[i])
			printf("%s\n", envp[i++]);
	return (0);
}
