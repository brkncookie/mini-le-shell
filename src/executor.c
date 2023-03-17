/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:19:07 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/17 23:56:10 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

extern int	g_flag;

int	do_builtin(t_tree *cmdtree, int *redr_fds, t_list **vars_lst)
{
	int		i;
	int		j;
	int		len;
	int		in;
	int		out;
	char	*val;

	if (redr_fds)
	{
		in = dup(0);
		out = dup(1);
		(dup2(redr_fds[0], 0), dup2(redr_fds[1], 1));
	}
	i = 0;
	while (cmdtree->arg && cmdtree->arg[i])
	{
		j = 0;
		while (cmdtree->arg[i][j])
		{
			if (cmdtree->arg[i][j] == '$')
			{
				val = ft_calloc(ft_strlen(ft_getenvi(cmdtree->arg[i] + j + 1, *vars_lst, &len)) + 1, 1);
				val = ft_getenvi(cmdtree->arg[i] + j + 1, *vars_lst, &len);
				len += j;
				if (!ft_strncmp(cmdtree->arg[i], "$?", 3))
					cmdtree->arg[i] = ft_itoa(g_flag);
				else if (val)
				{
					ft_strlcat(val, cmdtree->arg[i] + len, ft_strlen(val)
						+ ft_strlen(cmdtree->arg[i] + len) + 1);
					cmdtree->arg[i][j] = '\0';
					ft_strlcat(cmdtree->arg[i], val, ft_strlen(val)
						+ ft_strlen(cmdtree->arg[i]) + 1);
				}
			}
			j++;
		}
		expand(cmdtree, i);
		i++;
	}
	if (!ft_strncmp(cmdtree->arg[0], "echo", 5))
		return (do_echo(cmdtree), (dup2(in, 0), dup2(out, 1)), 1);
	if (!ft_strncmp(cmdtree->arg[0], "exit", 5))
		return (do_exit(cmdtree->arg[1], count_args(cmdtree)), (dup2(in, 0),
				dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "cd", 3))
		return (do_cd(cmdtree), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "pwd", 4))
		return (do_pwd(cmdtree), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "env", 4))
		return (do_env(cmdtree, vars_lst), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "export", 7))
		return (do_export(cmdtree, vars_lst), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "unset", 6))
		return (do_unset(cmdtree, vars_lst), (dup2(in, 0), dup2(out, 1)), 1);
	else
		return ((dup2(in, 0), dup2(out, 1)), 0);
}

int	do_cmd(t_tree *cmdtree, int *redr_fds, int limn, t_list **vars_lst)
{
	int		r_val;
	int		pid;
	char	*prgm;
	char	**envs;

	envs = get_dblarr(vars_lst);
	if ((cmdtree->tkn->type & (REDR_I | REDR_O | APPEND | HERE_DOC)))
		return (rslv_redr(cmdtree, redr_fds, 0, 1), errno);
	if (cmdtree->redr)
	{
		redr_fds = rslv_redr(cmdtree->redr, redr_fds, 0, 1);
		if (!redr_fds)
			return (errno);
	}
	if (do_builtin(cmdtree, redr_fds, vars_lst))
		return (pipe_close(redr_fds, limn), g_flag);
	prgm = ft_strndup(cmdtree->arg[0], ft_strlen(cmdtree->arg[0]));
	//prot
	pid = fork();
	//prot
	if (!pid)
	{
		if (redr_fds)
			(dup2(redr_fds[0], 0), dup2(redr_fds[1], 1));
		//prot
		prgm = is_vld_exc(prgm, vars_lst);
		if (!prgm)
			exit(127);
		execve(prgm, cmdtree->arg, envs);
	}
	pipe_close(redr_fds, limn);
	if(limn > 0 || limn == -2)
		waitpid(pid, &r_val, 0);
	g_flag = WEXITSTATUS(r_val);
	free_dblarr(envs, ft_lstsize(*vars_lst));
	return (WEXITSTATUS(r_val));
}

int	do_lqados(t_tree *cmdtree, int *redr_fds, int limn, t_list **vars_lst)
{
	int	lisr_fds[2];
	int	limn_fds[2];
	int	pipefd[2];
	int	r_val;


	lisr_fds[0] = redr_fds[0];
	lisr_fds[1] = 1;
	limn_fds[0] = 0;
	limn_fds[1] = redr_fds[1];
	if (!(cmdtree->tkn->type & PIPE))
		return (do_cmd(cmdtree, redr_fds, limn, vars_lst));
	pipe(pipefd);
	lisr_fds[1] = pipefd[1];
	limn_fds[0] = pipefd[0];
	if (cmdtree->redr && rslv_redr(cmdtree->redr, &lisr_fds[0], 0, 0))
		rslv_redr(cmdtree->redr, &limn_fds[0], 1, 0);
	if (cmdtree->lisr->tkn->type & (VAR | WORD))
		do_cmd(cmdtree->lisr, &lisr_fds[0], -1, vars_lst);
	else
		do_logops(cmdtree->lisr, &lisr_fds[0], 1, vars_lst);
	r_val = do_logops(cmdtree->limn, &limn_fds[0], 1, vars_lst);
	if (cmdtree->lisr->tkn->type & (VAR | WORD))
		waitpid(-1, NULL, 0);
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
