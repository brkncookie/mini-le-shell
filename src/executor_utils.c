/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:09:02 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/12 16:42:52 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	pipe_close(int *pipefd, int limn)
{
	struct stat	read;
	struct stat	write;

	if (!pipefd || !limn)
		return ;
	fstat(pipefd[0], &read);
	fstat(pipefd[1], &write);
	if ((read.st_mode & S_IFMT) == S_IFIFO)
		close(pipefd[0]);
	if ((write.st_mode & S_IFMT) == S_IFIFO)
		close(pipefd[1]);
}

int	*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd)
{
	int	fds[2];
	char	*file;
	char	*buf;
	t_tree	*t_redr;

	fds[0] = 0;
	fds[1] = 1;
	t_redr = NULL;
	while (redr)
	{
		file = ft_strndup(redr->limn->tkn->val, redr->limn->tkn->len);
		if (!file)
			return (free(file), NULL);
		if (redr->tkn->type & REDR_I)
			fds[0] = open(file, O_RDONLY);
		else if (redr->tkn->type & REDR_O)
			fds[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (redr->tkn->type & APPEND)
			fds[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (redr->tkn->type & HERE_DOC)
		{
			if (!t_redr)
				t_redr = redr;
			if (pipe(fds))
				perror("pipe");
			while (1)
			{
				buf = readline("> ");
				if (!buf || !ft_strncmp(buf, file, ft_strlen(file) + 1))
					break ;
				write(fds[1], buf, ft_strlen(buf));
				write(fds[1], "\n", 1);
			}
			close(fds[1]);
		}
		if (fds[1] < 0 || fds[0] < 0)
			return (free(file), perror(NULL), NULL);
		redr = redr->redr;
		free(file);
	}
	if (redr_fds)
	{
		if (!limn && fds[0] != 0)
			redr_fds[0] = fds[0];
		if (limn && fds[1] != 1)
			redr_fds[1] = fds[1];
		if (cmd && fds[1] != 1)
		{
			if (t_redr)
			{
				if (!(t_redr->tkn->type & HERE_DOC))
					redr_fds[1] = fds[1];
			}
			else
					redr_fds[1] = fds[1];
		}
		return (redr_fds);
	}
	return (redr_fds);
}

void	fre2d(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

char	*is_vld_exc(char	*path)
{
	char	*ppath;
	char	**paths;
	char	*npath;
	int		i;

	if (ft_strchr(path, '/') && *(ft_strchr(path, '/') + 1))
	{
		if (!access(path, F_OK) && !access(path, X_OK))
			return (path);
		else
			return (free(path), printf("Not a valid executable\n"), NULL);
	}
	ppath = getenv("PATH");
	if (!ppath)
		return (perror(NULL), NULL);
	paths = ft_split(ppath, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		npath = ft_calloc(ft_strlen(paths[i]) + ft_strlen(path) + 2, \
				sizeof(*npath));
		if (!npath)
			return (fre2d(paths), NULL);
		ft_strlcpy(npath, paths[i], ft_strlen(paths[i]) + ft_strlen(path) + 2);
		*(npath + ft_strlen(paths[i])) = '/';
		ft_strlcat(npath, path, ft_strlen(paths[i]) + ft_strlen(path) + 2);
		if (!access(npath, F_OK) && !access(npath, X_OK))
			return (fre2d(paths), free(path), npath);
		free(npath);
		i++;
	}
	return (fre2d(paths), free(path), printf("Not a valid executable\n"), NULL);
}
