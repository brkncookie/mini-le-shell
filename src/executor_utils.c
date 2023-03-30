/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:09:02 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/29 15:49:11 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	pipe_close(int *pipefd, int limn)
{
	struct stat	read;
	struct stat	write;

	if (limn == -2)
		return (0);
	if (!pipefd || !limn)
		return (0);
	fstat(pipefd[0], &read);
	fstat(pipefd[1], &write);
	if ((read.st_mode & S_IFMT) == S_IFIFO)
		close(pipefd[0]);
	if ((write.st_mode & S_IFMT) == S_IFIFO)
		close(pipefd[1]);
	return (0);
}

int	*open_files(t_tree *redr, int	*fds, char *file)
{
	char	*buf;
	int		hdfds[2];

	if (redr->tkn->type & REDR_I)
		fds[0] = open(file, O_RDONLY);
	else if (redr->tkn->type & REDR_O)
		fds[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redr->tkn->type & APPEND)
		fds[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (redr->tkn->type & HERE_DOC)
	{
		if (pipe(hdfds) < 0)
			return (free(file), perror("pipe"), NULL);
		while (1)
		{
			buf = readline("> ");
			if (!buf || !ft_strncmp(buf, file, ft_strlen(file) + 1))
				break ;
			write(hdfds[1], buf, ft_strlen(buf));
			write(hdfds[1], "\n", 1);
		}
		close(hdfds[1]);
		fds[0] = hdfds[0];
	}
	return (fds);
}

int	*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd)
{
	int		fds[2];
	char	*file;

	fds[0] = 0;
	fds[1] = 1;
	while (redr)
	{
		file = ft_strndup(redr->limn->tkn->val, redr->limn->tkn->len);
		if (!file)
			return (NULL);
		if (!open_files(redr, fds, file))
			return (NULL);
		if (fds[1] < 0 || fds[0] < 0)
			return (free(file), perror("open"), NULL);
		redr = redr->redr;
		free(file);
	}
	if (!limn && fds[0] != 0)
		redr_fds[0] = fds[0];
	if (limn && fds[1] != 1)
		redr_fds[1] = fds[1];
	if (cmd && fds[1] != 1)
		redr_fds[1] = fds[1];
	return (redr_fds);
}

void	fre2d(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
		free(path[i++]);
	free(path);
}

char	*is_vld_exc(char *path, t_list **vars_lst, char	*ppath, char	**paths)
{
	int		i;

	if (dir_exists(path))
		return (printf("%s: is a directory\n", path), free(path), NULL);
	if (!access(path, F_OK) && !access(path, X_OK))
		return (path);
	ppath = ft_getenv("PATH", *vars_lst);
	if (!ppath)
		return (free(path), printf("Error Fetching $PATH\n"), NULL);
	paths = ft_split(ppath, ':');
	i = -1;
	while (paths && paths[++i])
	{
		ppath = ft_calloc(ft_strlen(paths[i]) + ft_strlen(path) + 2, \
				sizeof(*ppath));
		if (!ppath)
			return (fre2d(paths), free(path), NULL);
		ft_strlcpy(ppath, paths[i], ft_strlen(paths[i]) + ft_strlen(path) + 2);
		*(ppath + ft_strlen(paths[i])) = '/';
		ft_strlcat(ppath, path, ft_strlen(paths[i]) + ft_strlen(path) + 2);
		if (!access(ppath, F_OK) && !access(ppath, X_OK))
			return (fre2d(paths), free(path), ppath);
		free(ppath);
	}
	return (fre2d(paths), free(path), printf("Not a valid executable\n"), NULL);
}
