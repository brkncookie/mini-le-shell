/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:09:02 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/12 16:45:44 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd)
{
	int		*fds;
	char	*file;

	fds = ft_calloc(2, sizeof(*fds));
	fds[0] = 0;
	fds[1] = 1;
	while (redr)
	{
		file = ft_strndup(redr->limn->tkn->val, redr->limn->tkn->len);
		if (!file || !fds)
			return (free(file), free(fds), NULL);
		if (redr->tkn->type & REDR_I)
			fds[0] = open(file, O_RDONLY);
		else if (redr->tkn->type & REDR_O)
			fds[1] = open(file, O_WRONLY | O_CREAT);
		else if (redr->tkn->type & APPEND)
			fds[1] = open(file, O_WRONLY | O_CREAT | O_APPEND);
		if (fds[1] < 0 || fds[0] < 0)
			return (free(fds), free(file), perror(NULL), NULL);
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
			redr_fds[1] = fds[1];
		return (free(fds), redr_fds);
	}
	return (fds);
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
		return (path);
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
