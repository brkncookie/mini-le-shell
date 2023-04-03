/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:57 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/03 15:17:12 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	swap_args(t_tree *cmdtree, int i, int num, int args_num)
{
	char	*tmp;
	int		n;

	n = num - i - 2;
	while (i < num - 1)
	{
		tmp = cmdtree->arg[i + 1];
		cmdtree->arg[i + 1] = cmdtree->arg[args_num - n];
		cmdtree->arg[args_num - n] = tmp;
		args_num++;
		i++;
	}
}

int	fix_args(t_tree *cmdtree, int i, int args_num, int n)
{
	DIR				*d;
	struct dirent	*fil;

	d = opendir(".");
	if (d)
	{
		fil = readdir(d);
		while (fil)
		{
			if (fil && ft_strncmp(fil->d_name, ".", 1) && n == args_num && n--)
				(free(cmdtree->arg[i]), cmdtree->arg[i] = \
				ft_strdup(fil->d_name));
			else if (fil && ft_strncmp(fil->d_name, ".", 1))
			{
				free(cmdtree->arg[args_num]);
				cmdtree->arg[args_num] = ft_strdup(fil->d_name);
				if (!cmdtree->arg[args_num++] || !cmdtree->arg[i])
					return (0);
			}
			fil = readdir(d);
		}
		closedir(d);
	}
	return (swap_args(cmdtree, i, n + 1, args_num - 1), 1);
}

void	expand3(t_tree *cmdtree, int i)
{
	int	num;
	int	args_num;

	args_num = count_args(cmdtree);
	num = args_num;
	if (!ft_strncmp(cmdtree->arg[i], "*", 2))
	{
		cmdtree->arg = reallocate(cmdtree->arg, sizeof(char *) * args_num,
				(count_dir() + args_num) * sizeof(char *));
		if (!cmdtree->arg)
			return ;
		if (!fix_args(cmdtree, i, args_num, num))
		{
			fre2d(cmdtree->arg);
			cmdtree->arg = NULL;
			return ;
		}
	}
}

void	*reallocate(void *ptr, int oldsize, int size)
{
	void	*newptr;

	newptr = ft_calloc(1, size);
	if (!newptr)
		return (free(ptr), NULL);
	newptr = ft_memcpy(newptr, ptr, oldsize);
	return (free(ptr), newptr);
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
