/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:10:33 by mnadir            #+#    #+#             */
/*   Updated: 2023/04/03 13:14:43 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	file_close(int *redr_fds)
{
	struct stat	read;
	struct stat	write;

	fstat(redr_fds[0], &read);
	fstat(redr_fds[1], &write);
	if ((read.st_mode & S_IFMT) == S_IFREG)
		close(redr_fds[0]);
	if ((write.st_mode & S_IFMT) == S_IFREG)
		close(redr_fds[1]);
}

int	*here_doc(int *fds, char *file)
{
	char	*buf;
	int		hdfds[2];

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
	return (fds);
}
