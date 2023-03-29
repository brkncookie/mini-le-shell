/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:19:07 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/28 23:31:00 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

extern int	g_flag[2];

int	do_child(char	*prgm, t_tree	*cmdtree, t_list **vars_lst, int *redr_fds)
{
	char	**envs;

	envs = get_dblarr(vars_lst);
	prgm = is_vld_exc(prgm, vars_lst, NULL, NULL);
	if (!prgm)
		exit(127);
	if (dup2(redr_fds[0], 0) < 0 || dup2(redr_fds[1], 1) < 0)
		return (perror("dup2"), exit(errno), 1);
	execve(prgm, cmdtree->arg, envs);
	return (free_dblarr(envs, ft_lstsize(*vars_lst)), \
		perror("execve"), exit(errno), 1);
}

int	do_cmd(t_tree *cmdtree, int *redr_fds, int limn, t_list **vars_lst)
{
	int		r_val;
	int		pid;
	char	*prgm;

	if ((cmdtree->tkn->type & (REDR_I | REDR_O | APPEND | HERE_DOC)))
		return (rslv_redr(cmdtree, redr_fds, 0, 1), errno);
	if (cmdtree->redr && !rslv_redr(cmdtree->redr, redr_fds, 0, 1))
		return (errno);
	if (do_builtin(cmdtree, redr_fds, vars_lst))
		return (pipe_close(redr_fds, limn), g_flag[0]);
	prgm = ft_strndup(cmdtree->arg[0], ft_strlen(cmdtree->arg[0]));
	if (!prgm)
		return (printf("Allocation error\n"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), g_flag[0] = 254);
	if (!pid)
		do_child(prgm, cmdtree, vars_lst, redr_fds);
	g_flag[1] = !isatty(STDIN_FILENO);
	pipe_close(redr_fds, limn);
	if (limn > 0 || limn == -2)
		waitpid(pid, &r_val, 0);
	if (WIFSIGNALED(r_val))
		g_flag[0] = 128 + WTERMSIG(r_val);
	else
		g_flag[0] = WEXITSTATUS(r_val);
	g_flag[1] = 1;
	return (free(prgm), g_flag[0]);
}

int	do_lqados(t_tree *cmdtree, int *redr_fds, int limn, t_list **vars_lst)
{
	int	lisr_fds[2];
	int	limn_fds[2];
	int	pipefd[2];
	int	r_val;

	if (!(cmdtree->tkn->type & PIPE))
		return (do_cmd(cmdtree, redr_fds, limn, vars_lst));
	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	lisr_fds[0] = redr_fds[0];
	lisr_fds[1] = pipefd[1];
	limn_fds[0] = pipefd[0];
	limn_fds[1] = redr_fds[1];
	if (cmdtree->redr && (!rslv_redr(cmdtree->redr, &lisr_fds[0], 0, 0) \
				|| !rslv_redr(cmdtree->redr, &limn_fds[0], 1, 0)))
		return (errno);
	if (cmdtree->lisr->tkn->type & (VAR | WORD))
		do_cmd(cmdtree->lisr, &lisr_fds[0], -1, vars_lst);
	else
		do_logops(cmdtree->lisr, &lisr_fds[0], 1, vars_lst);
	r_val = do_logops(cmdtree->limn, &limn_fds[0], 1, vars_lst);
	waitpid(-1, NULL, WNOHANG * !(cmdtree->lisr->tkn->type & (VAR | WORD)));
	return (r_val);
}

int	do_logops(t_tree *cmdtree, int *redr_fds, int limn, t_list **vars_lst)
{
	int	r_lisr;
	int	r_limn;

	if (!(cmdtree->tkn->type & (OR | AND)))
		return (do_lqados(cmdtree, redr_fds, limn, vars_lst));
	if (cmdtree->redr)
		redr_fds = rslv_redr(cmdtree->redr, redr_fds, 0, 1);
	r_lisr = do_logops(cmdtree->lisr, redr_fds, limn = -2, vars_lst);
	if ((!r_lisr && cmdtree->tkn->type & AND) || (r_lisr
			&& cmdtree->tkn->type & OR))
		r_limn = do_logops(cmdtree->limn, redr_fds, limn = 1, vars_lst);
	else
		return (r_lisr);
	return (r_limn);
}

void	executor(t_tree *cmdtree, t_list **vars_lst)
{
	int	redr_fds[2];

	redr_fds[0] = 0;
	redr_fds[1] = 1;
	do_logops(cmdtree, &redr_fds[0], 1, vars_lst);
}
