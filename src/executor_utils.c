/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:09:02 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/12 12:28:36 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	*rslv_redr(t_tree *redr)
{
	int		*fds;
	char	*file;

	fds = ft_calloc(2, sizeof(*fds));
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
	return (fds);
}
