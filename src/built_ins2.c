#include "../include/executor.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(char *arg, int args_num)
{
	if (args_num == 1)
	{
		printf("exit");
		exit(0);
	}
	else if (args_num == 2 && is_num(arg))
		exit(ft_atoi(arg));
	else if (args_num > 2 && is_num(arg))
		printf("exit: too many arguments");
	else
	{
		printf("exit: numeric argument required");
		exit(2);
	}
}

void	do_export(t_tree *cmdtree, char **envp)
{

}

void	do_unset(t_tree *cmdtree, char **envp)
{

}
