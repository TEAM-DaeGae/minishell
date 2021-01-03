// File Name: terminalio.c (다)
// Description: 터미널 상에서 입력 처리

#include "mysh.h"

void        show_prompt(char *curpath)
{
    ft_putstr_fd(userinfo->pw_name, 1);
    // ft_putstr_fd(" @ ", 1);
    // ft_putstr_fd(getcwd(curpath, MAXSIZE), 1);
    ft_putstr_fd("> ", 1);
}