/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:27:09 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/28 18:52:20 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "dirent.h"
# include <sys/errno.h>

typedef struct s_var
{
	char			*key;
	char			*val;
}					t_var;

int		do_logops(t_tree *cmdtree, int	*redr_fds, int limn, char **envp);
int		*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd);
char	*is_vld_exc(char *path);
void	executor(t_tree *cmdtree, char **envp);
void	pipe_close(int *pipefd, int limn);
void	do_echo(t_tree *cmdtree);
void	do_pwd(t_tree *cmdtree);
void	do_cd(t_tree *cmdtree);
void	do_unset(t_tree *cmdtree, char **envp);
void	do_export(t_tree *cmdtree, char **envp);
void	do_env(t_tree *cmdtree, char **envp);
void	do_exit(char *arg, int args_count);
int		count_args(t_tree *cmdtree);
int		count_dir(void);
void	*reallocate(void *ptr, int oldsize, int size);
void	expand(t_tree *cmdtree, int i);
t_list	*get_vars(char **envp);

#endif
