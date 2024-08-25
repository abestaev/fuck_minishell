#include "minishell.h"

bool is_builtin(char *command)
{   
    if (ft_strcmp(command, "env") == 0)
        return (TRUE);
    return (FALSE);
}