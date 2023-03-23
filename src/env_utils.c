#include "../include/executor.h"

extern int	g_flag;

char	**get_dblarr(t_list **vars_lst)
{
	char	**envs;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *vars_lst;
	envs = ft_calloc(sizeof(char *), ft_lstsize(*vars_lst) + 1);
	if (!envs)
		return (NULL);
	while (tmp)
	{
		envs[i] = ft_calloc(sizeof(char),
				ft_strlen(((t_var *)tmp->content)->key)
				+ ft_strlen(((t_var *)tmp->content)->val) + 2);
		if (!envs[i])
			return (free_dblarr(envs, ft_lstsize(*vars_lst)), NULL);
		ft_strlcat(envs[i], ((t_var *)tmp->content)->key,
			ft_strlen(((t_var *)tmp->content)->key) + 1);
		ft_strlcat(envs[i], "=", ft_strlen(envs[i]) + 2);
		ft_strlcat(envs[i], ((t_var *)tmp->content)->val, ft_strlen(envs[i])
			+ ft_strlen(((t_var *)tmp->content)->val) + 1);
		i++;
		tmp = tmp->next;
	}
	return (envs);
}

void	free_dblarr(char **arr, int i)
{
	while (i >= 0)
	{
		if (arr[i])
			free(arr[i]);
		i--;
	}
	if (arr)
		free(arr);
}

char	*ft_getenv(char *key, t_list *vars)
{
	int	len;

	while (vars)
	{
		len = ft_strlen(((t_var *)vars->content)->key);
		if (!ft_strncmp(key, ((t_var *)vars->content)->key, len))
			if (!key[len] || (key[len] == '$' || key[len] == '"'
					|| key[len] == '\'' || key[len] == ' '))
				return (((t_var *)vars->content)->val);
		vars = vars->next;
	}
	return (NULL);
}

char	*ft_getenvi(char *key, t_list *vars, int *len)
{
	while (vars)
	{
		*len = ft_strlen(((t_var *)vars->content)->key) + 1;
		if (!ft_strncmp(key, ((t_var *)vars->content)->key, *len - 1))
		{
			if (!key[*len - 1] || key[*len - 1] == '$' || key[*len - 1] == '"'
				|| key[*len - 1] == '\'' || key[*len - 1] == ' ')
				return (ft_strndup(((t_var *)vars->content)->val,
						ft_strlen(((t_var *)vars->content)->val)));
		}
		vars = vars->next;
	}
	*len = 1;
	while (key[*len - 1] && key[*len - 1] != '$' && key[*len - 1] != '"'
		&& key[*len - 1] != '\'' && key[*len - 1] != ' ')
		*len = *len + 1;
	return (ft_strndup("", 1));
}
