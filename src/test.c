/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:19:08 by alemsafi          #+#    #+#             */
/*   Updated: 2023/02/28 18:51:16 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

int		g_flag = 0;

void	action(int sig)
{
	char	*pwd;

	pwd = getcwd(0, 500);
	ft_strlcat(pwd, "> ", ft_strlen(pwd) + 3);
	if (sig == SIGQUIT)
	{
		g_flag = 127;
		return ;
	}
	if (sig == SIGINT)
	{
		printf("\n%s", pwd);
		g_flag = 1;
		return ;
	}
}

int	ft_strchrr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (0);
}

t_list	*get_vars(char **envp)
{
	t_var	*var;
	t_list	*vars_lst;
	int		i;
	int		equ;

	i = 0;
	while (envp[i])
	{
		var = malloc(sizeof(t_var));
		// if (!var)
		// 	return (freelst(vars_lst), NULL);
		equ = ft_strchrr(envp[i], '=');
		var->key = ft_substr(envp[i], 0, equ);
		var->val = ft_substr(envp[i], equ + 1, ft_strlen(envp[i]) - equ - 1);
		ft_lstadd_back(&vars_lst, ft_lstnew(var));
		i++;
	}
	return (vars_lst);
}

void	prompt(char **cmd_buf, int *error)
{
	char	*pwd;

	pwd = getcwd(0, 500);
	ft_strlcat(pwd, "> ", ft_strlen(pwd) + 3);
	*error = 0;
	*cmd_buf = readline(pwd);
	free(pwd);
}

int	main(int ac, char **av, char **envp)
{
	t_tkns	*tkns;
	t_tree	*tree;
	int		error;
	char	*cmd_buf;

	signal(SIGQUIT, action);
	signal(SIGINT, action);
	(void)ac;
	(void)av;
	while (1)
	{
		prompt(&cmd_buf, &error);
		if (!cmd_buf)
			do_exit("0", 1);
		if (ft_strlen(cmd_buf) > 0)
			add_history(cmd_buf);
		tkns = tokenize(cmd_buf);
		if (!tkns)
			continue ;
		tree = giv_tree(tkns, &error);
		executor(tree, envp);
		free(cmd_buf);
	}
	return (0);
}
