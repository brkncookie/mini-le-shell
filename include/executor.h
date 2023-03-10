/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:27:09 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/10 12:28:00 by saltysushi       ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_var
{
	char			*key;
	char			*val;
}					t_var;

int		do_logops(t_tree *cmdtree, int	*redr_fds, int limn, t_list **vars_lst);
int		*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd);
char	*is_vld_exc(char *path);
void	executor(t_tree *cmdtree, t_list **vars_lst);
void	pipe_close(int *pipefd, int limn);
void	do_echo(t_tree *cmdtree);
void	do_pwd(t_tree *cmdtree);
void	do_cd(t_tree *cmdtree);
void	do_unset(t_tree *cmdtree, t_list **vars_lst);
void	do_export(t_tree *cmdtree, t_list **vars_lst);
void	do_env(t_tree *cmdtree, t_list **vars_lst);
void	do_exit(char *arg, int args_count);
int		count_args(t_tree *cmdtree);
int		count_dir(void);
void	*reallocate(void *ptr, int oldsize, int size);
void	expand(t_tree *cmdtree, int i);
t_list	*get_vars(char **envp);
int		ft_strchrr(const char *s, int c);
char	*ft_getenv(char *key, t_list *vars);
char	**get_dblarr(t_list **vars_lst);
void	free_dblarr(char **arr, int i);

int		g_flag;

#endif
