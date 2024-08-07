#include "minishell.h"

void	copy_env(t_minishell *minishell, char **env)
{
	int			i;
	int 		j;
	t_list	*tmp_lst = NULL;
	t_env 	*tmp_var;
	
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		tmp_var = new_var(ft_substr(env[i], 0, j), 
			ft_substr(env[i], j + 1, (ft_strlen(env[i]) - j - 1)));
		tmp_lst = ft_lstnew(tmp_var);
		if (minishell->env)
			ft_lstadd_back_2(&minishell->env, tmp_lst);
		else
			minishell->env = tmp_lst;
		i++;
	}
}

t_env  *new_var(char *name, char *value)
{
	t_env *var;

	if (!name || !value)
        return (NULL);
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}

char    **env_to_tab(t_list *env)
{
    char    **tab;
    int     i;
    t_list  *tmp;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    tab = malloc(sizeof(char *) * (i + 1));
    if (!tab)
        return (NULL);
    i = 0;
    while (env)
    {
        tab[i] = ft_strjoin(((t_env *)env->content)->name, "=");
        tab[i] = ft_strjoin(tab[i], ((t_env *)env->content)->value);
        env = env->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

bool	var_exist(t_list *env, char *name)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_env *)tmp->content)->name, name))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}