#include "minishell.h"

void    print_env(t_minishell *minishell)
{
    t_list  *tmp;

    tmp = (t_list *)minishell->env;
    while (tmp)
    {
        printf("%s=%s\n", ((t_env *)tmp->content)->name, ((t_env *)tmp->content)->value);
        tmp = tmp->next;
    }
}