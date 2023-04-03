/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:27:09 by mnadir            #+#    #+#             */
/*   Updated: 2023/04/03 18:06:21 by alemsafi         ###   ########.fr       */
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
# include <sys/types.h>
# include <termios.h>
# include <limits.h>
# define READLINE_LIBRARY 1
# include "/Users/mnadir/goinfre/.brew/opt/readline/include/readline/history.h"
# include "/Users/mnadir/goinfre/.brew/opt/readline/include/readline/readline.h"
// # include <readline/history.h>
// # include <readline/readline.h>

typedef struct s_var
{
	char			*key;
	char			*val;
}					t_var;

int		do_logops(t_tree *cmdtree, int	*redr_fds, int limn, t_list **vars_lst);
int		*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd);
char	*is_vld_exc(char *path, t_list **vars_lst, \
		char	*ppath, char	**paths);
int		is_num(char *str);
void	set_term(void);
void	action(int sig);
int		dir_exists(const char *path);
void	executor(t_tree *cmdtree, t_list **vars_lst);
int		pipe_close(int *pipefd, int limn);
int		do_builtin(t_tree *cmdtree, int *redr_fds, \
		int *oredr_fds, t_list **vars_lst);
void	do_echo(t_tree *cmdtree, int *redr_fds);
void	do_pwd(char *pwd);
void	do_cd(t_tree *cmdtree, char *pwd, t_list **vars_lst);
void	do_unset(t_tree *cmdtree, t_list **vars_lst);
void	do_export(t_tree *cmdtree, t_list **vars_lst);
void	do_env(t_tree *cmdtree, t_list **vars_lst);
void	do_exit(char *arg, int args_count);
int		count_args(t_tree *cmdtree);
int		count_dir(void);
void	*reallocate(void *ptr, int oldsize, int size);
void	expand3(t_tree *cmdtree, int i);
void	expand2(t_tree *cmdtree, int i, int *j, t_list **vars_lst);
t_list	*get_vars(char **envp);
int		ft_strchrr(const char *s, int c);
char	*ft_getenv(char *key, t_list *vars);
char	**get_dblarr(t_list **vars_lst);
void	free_dblarr(char **arr, int i);
char	*ft_getenvi(char *key, t_list *vars, int *len);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	expand(t_tree *cmdtree, t_list **vars_lst);
void	file_close(int *redr_fds);
int		*here_doc(int *fds, char *file);

#endif
