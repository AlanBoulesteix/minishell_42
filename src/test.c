#include "minishell.h"
#include <unistd.h>


int heredoc(char *str)
{
    int     end[2];
    int     count;
    char    *line;
    char    buffer[1];

    line = "start";
    count = 1;
    while (count && line && ft_streq(line, str))
    {
        count = read(STDIN_FILENO, buffer, 1);
        line = join_char(line, buffer);
    }
}