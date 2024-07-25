#include "minishell.h"

char    **get_path(t_list *env)
{
    t_list  *tmp;
    char    **path;
    int     i;

    i = 0;
    tmp = env;
    while (tmp)
    {
        if (!ft_strncmp(((t_env *)tmp->content)->name, "PATH", 4))
            break ;
        tmp = tmp->next;
    }
    if (!tmp)
        return (NULL);
    path = ft_split(((t_env *)tmp->content)->value, ':');
    return (path);
}