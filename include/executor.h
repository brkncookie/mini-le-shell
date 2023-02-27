/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:27:09 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/27 15:22:37 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

int		do_logops(t_tree *cmdtree, int	*redr_fds, int limn, char **envp);
int		*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd);
char	*is_vld_exc(char *path);
void	executor(t_tree *cmdtree, char **envp);
void	pipe_close(int *pipefd, int limn);
int		do_echo(t_tree *cmdtree, int *redr_fds);
int		do_pwd(t_tree *cmdtree, int *redr_fds);
int		do_cd(t_tree *cmdtree, int *redr_fds);
int		do_env(t_tree *cmdtree, int *redr_fds, char **envp);

#endif
