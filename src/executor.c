/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:42:33 by mnadir            #+#    #+#             */
/*   Updated: 2023/04/03 14:35:39 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

extern int	g_flag[2];

int	do_child(char *prgm, t_tree *cmdtree, t_list **vars_lst, int *redr_fds)
{
	char	**envs;

	if (cmdtree && cmdtree->arg)
		prgm = ft_strndup(cmdtree->arg[0], ft_strlen(cmdtree->arg[0]));
	if (!prgm)
		return (exit(errno), 1);
	envs = get_dblarr(vars_lst);
	prgm = is_vld_exc(prgm, vars_lst, NULL, NULL);
	if (!prgm)
		exit(127);
	if (dup2(redr_fds[0], 0) < 0 || dup2(redr_fds[1], 1) < 0)
		return (perror("dup2"), exit(errno), 1);
	execve(prgm, cmdtree->arg, envs);
	return (free(prgm), free_dblarr(envs, ft_lstsize(*vars_lst)),
		perror("execve"), exit(errno), 1);
}

int	do_cmd(t_tree *cmdtree, int *rdrfd, int limn, t_list **vars_lst)
{
	int	r_val;
	int	pid;
	int	ordrfd[2];

	ft_memcpy(ordrfd, rdrfd, sizeof(rdrfd));
	if ((cmdtree->tkn->type & (REDR_I | REDR_O | APPEND | HERE_DOC)))
		return (rslv_redr(cmdtree, rdrfd, 0, 1), errno);
	if (cmdtree->redr && !rslv_redr(cmdtree->redr, rdrfd, 0, 1))
		return (errno);
	if (do_builtin(cmdtree, rdrfd, ordrfd, vars_lst))
		return (pipe_close(rdrfd, limn), g_flag[0]);
	pid = fork();
	if (pid < 0)
		return (pipe_close(rdrfd, limn), perror("fork"), g_flag[0] = 254);
	if (!pid)
		do_child(NULL, cmdtree, vars_lst, rdrfd);
	g_flag[1] = !isatty(STDIN_FILENO);
	pipe_close(rdrfd, limn);
	if (cmdtree->redr)
		(file_close(rdrfd), ft_memcpy(rdrfd, ordrfd, sizeof rdrfd));
	if (limn > 0 || limn == -2)
		waitpid(pid, &r_val, 0);
	g_flag[0] = (128 + WTERMSIG(r_val)) * WIFSIGNALED(r_val)
		+ WEXITSTATUS(r_val) * !WIFSIGNALED(r_val);
	return (g_flag[1] = 1, g_flag[0]);
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
	if (cmdtree->redr && (!rslv_redr(cmdtree->redr, &lisr_fds[0], 0, 0)
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
	file_close(redr_fds);
}
