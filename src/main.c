/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:19:08 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/03 18:06:31 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include <signal.h>
#include <stdio.h>

extern int	g_flag[2];

void	action(int sig)
{
	if (sig == SIGQUIT)
	{
		if (!g_flag[1])
		{
			printf("Quit: \n");
			g_flag[0] = 131;
		}
		else
			set_term();
	}
	if (sig == SIGINT)
	{
		printf("\n");
		if (g_flag[1])
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_flag[0] = 130;
		return ;
	}
}

t_list	*get_vars(char **envp)
{
	t_var	*var;
	t_list	*vars_lst;
	int		i;
	int		equ;

	i = 0;
	vars_lst = NULL;
	while (envp[i])
	{
		var = ft_calloc(1, sizeof(t_var));
		if (!var)
			return (ft_lstclear(&vars_lst, free), NULL);
		equ = ft_strchrr(envp[i], '=');
		var->key = ft_substr(envp[i], 0, equ);
		var->val = ft_substr(envp[i], equ + 1, ft_strlen(envp[i]) - equ - 1);
		ft_lstadd_back(&vars_lst, ft_lstnew(var));
		i++;
	}
	return (vars_lst);
}

t_tkns	*prompt(char **cmd_buf, int *error)
{
	t_tkns	*tkns;

	*error = 0;
	*cmd_buf = readline("Nut-Shell> ");
	if (!*cmd_buf)
		do_exit(ft_itoa(g_flag[0]), 2);
	if (ft_strlen(*cmd_buf) > 0)
		add_history(*cmd_buf);
	tkns = tokenize(*cmd_buf, error);
	if (!tkns || *error)
	{
		free(*cmd_buf);
		if (*error)
			g_flag[0] = *error;
		return (NULL);
	}
	return (tkns);
}

void	freeall(t_tree *tree, t_tkns *tkns, char *cmd_buf)
{
	freetree(tree);
	freelst(&tkns);
	free(cmd_buf);
}

int	main(int ac, char **av, char **envp)
{
	t_tkns	*tkns;
	t_tree	*tree;
	int		error;
	char	*cmd_buf;
	t_list	*vars_lst;

	vars_lst = get_vars(envp);
	signal(SIGINT, action);
	signal(SIGQUIT, action);
	while (1)
	{
		tkns = prompt(&cmd_buf, &error);
		if (!tkns || error)
			continue ;
		tree = giv_tree(tkns, &error);
		if (error || !tree || !vars_lst)
		{
			g_flag[0] = 2;
			free(cmd_buf);
			continue ;
		}
		executor(tree, &vars_lst);
		freeall(tree, tkns, cmd_buf);
	}
	return ((void)ac, (void)av, 0);
}
