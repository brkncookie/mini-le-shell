/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:19:07 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/15 15:53:53 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	do_cmd(t_tree *cmdtree, int	*redr_fds)
{
	int		r_val;
	int		pid;
	char	*prgm;

	prgm = ft_strndup(cmdtree->tkn->val, cmdtree->tkn->len);
	if (cmdtree->redr)
		redr_fds = rslv_redr(cmdtree->redr, redr_fds, 0, 1);
	pid = fork();
	if (!pid)
	{
		if (redr_fds)
			(dup2(redr_fds[0], 0), dup2(redr_fds[1], 1));
		prgm = is_vld_exc(prgm);
		if (!prgm)
			exit(EXIT_FAILURE);
		execve(prgm, cmdtree->arg, NULL);
	}
	waitpid(pid, &r_val, 0);
	return (r_val);
}

int	do_lqados(t_tree *cmdtree, int	*redr_fds)
{
	int	lisr_fds[2];
	int	limn_fds[2];
	int	pipefd[2];

	if (redr_fds)
		lisr_fds[0] = redr_fds[0];
	else
		lisr_fds[0] = 0;
	lisr_fds[1] = 1;
	limn_fds[0] = 0;
	limn_fds[1] = 1;
	if (!(cmdtree->tkn->type & PIPE))
		return (do_cmd(cmdtree, redr_fds));
	pipe(pipefd);
	lisr_fds[1] = pipefd[1];
	limn_fds[0] = pipefd[0];
	if (cmdtree->redr && rslv_redr(cmdtree->redr, &lisr_fds[0], 0, 0))
		rslv_redr(cmdtree->redr, &limn_fds[0], 1, 0);
	return (do_logops(cmdtree->lisr, &lisr_fds[0]), \
			do_logops(cmdtree->limn, &limn_fds[0]));
}

int	do_logops(t_tree *cmdtree, int	*redr_fds)
{
	int	r_lisr;
	int	r_limn;

	if (!(cmdtree->tkn->type & (OR | AND)))
		return (do_lqados(cmdtree, redr_fds));
	if (cmdtree->redr)
		redr_fds = rslv_redr(cmdtree->redr, redr_fds, 0, 1);
	r_lisr = do_logops(cmdtree->lisr, redr_fds);
	if ((!r_lisr && cmdtree->tkn->type & AND) \
			|| (r_lisr && cmdtree->tkn->type & OR))
		r_limn = do_logops(cmdtree->limn, redr_fds);
	else
		return (r_lisr);
	return (r_limn);
}

void	executor(t_tree *cmdtree)
{
	do_logops(cmdtree, NULL);
}
