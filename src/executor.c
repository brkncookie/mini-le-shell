/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:19:07 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/25 18:03:50 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include <sys/errno.h>

int	do_builtin(t_tree *cmdtree)
{
	if (!ft_strncmp(cmdtree->tkn->val, "echo", 4))
		return (1, do_echo(cmdtree));
	else if (!ft_strncmp(cmdtree->tkn->val, "cd", 2))
		return (1, do_cd(cmdtree));
	else if (!ft_strncmp(cmdtree->tkn->val, "pwd", 3))
		return (1, do_pwd(cmdtree));
	// else if (!ft_strncmp(cmdtree->tkn->val, "env", 4))
	// 	return (1, do_env(cmdtree));
	// else if (!ft_strncmp(cmdtree->tkn->val, "export", 7))
	// 	return (1, do_export(cmdtree));
	// else if (!ft_strncmp(cmdtree->tkn->val, "unset", 6))
	// 	return (1, do_unset(cmdtree));
	else
		return (0);
}

int	do_cmd(t_tree *cmdtree, int	*redr_fds, int limn)
{
	int		r_val;
	int		pid;
	char	*prgm;

	if ((cmdtree->tkn->type & (REDR_I | REDR_O | APPEND)))
		return (free(rslv_redr(cmdtree, redr_fds, 0, 1)), errno);
	prgm = ft_strndup(cmdtree->tkn->val, cmdtree->tkn->len);
	// if (do_builtin(cmdtree))
	// 	return (0);
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
	pipe_close(redr_fds, limn);
	waitpid(pid, &r_val, 0);
	return (r_val);
}

int	do_lqados(t_tree *cmdtree, int	*redr_fds, int limn)
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
		return (do_cmd(cmdtree, redr_fds, limn));
	pipe(pipefd);
	lisr_fds[1] = pipefd[1];
	limn_fds[0] = pipefd[0];
	if (cmdtree->redr && rslv_redr(cmdtree->redr, &lisr_fds[0], 0, 0))
		rslv_redr(cmdtree->redr, &limn_fds[0], 1, 0);
	return (do_logops(cmdtree->lisr, &lisr_fds[0], 1), \
			do_logops(cmdtree->limn, &limn_fds[0], 1));
}

int	do_logops(t_tree *cmdtree, int	*redr_fds, int limn)
{
	int	r_lisr;
	int	r_limn;

	if (!(cmdtree->tkn->type & (OR | AND)))
		return (do_lqados(cmdtree, redr_fds, limn));
	if (cmdtree->redr)
		redr_fds = rslv_redr(cmdtree->redr, redr_fds, 0, 1);
	r_lisr = do_logops(cmdtree->lisr, redr_fds, limn = 0);
	if ((!r_lisr && cmdtree->tkn->type & AND) \
			|| (r_lisr && cmdtree->tkn->type & OR))
		r_limn = do_logops(cmdtree->limn, redr_fds, limn = 1);
	else
		return (r_lisr);
	return (r_limn);
}

void	executor(t_tree *cmdtree)
{
	do_logops(cmdtree, NULL, 0);
}
