#include "../include/executor.h"

void	expand(t_tree *cmdtree, int i)
{
	DIR				*d;
	struct dirent	*fil;
	int				num;
	int				args_num;

	num = count_dir();
	args_num = count_args(cmdtree);
	if (!ft_strncmp(cmdtree->arg[i], "*", 2))
	{
		cmdtree->arg = reallocate(cmdtree->arg, sizeof(char *) * args_num, (num
					+ args_num) * sizeof(char *));
		d = opendir(".");
		if (d)
		{
			fil = readdir(d);
			free(cmdtree->arg[i]);
			cmdtree->arg[i] = fil->d_name;
			while (fil)
			{
				fil = readdir(d);
				if (fil)
					if (ft_strncmp(fil->d_name, ".", 1))
						cmdtree->arg[args_num++] = fil->d_name;
			}
			cmdtree->arg[args_num] = NULL;
			//closedir(d);       kanzidha kaykhsr kolchi
		}
	}
}

void	*reallocate(void *ptr, int oldsize, int size)
{
	void	*newptr;

	newptr = malloc(size);
	newptr = ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}

int	count_dir(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				num;

	d = opendir(".");
	num = 0;
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (ft_strncmp(dir->d_name, ".", 1))
				num++;
			dir = readdir(d);
		}
		closedir(d);
	}
	return (num);
}

int	count_args(t_tree *cmdtree)
{
	int	i;

	i = 0;
	while (cmdtree->arg && cmdtree->arg[i])
		i++;
	return (i);
}
