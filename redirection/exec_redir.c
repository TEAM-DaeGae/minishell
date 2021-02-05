#include "minishell.h"

# define BREDIR	60
# define REDIR	62
# define DREDIR	6
// BREDIR = '<', REDIR = '>', DREDIR = >>

typedef struct	s_redir
{
	int			argc; // parse_redir 함수의 변수 j + 1?
	char		**argv;
	char		**cmds;
	char		*types;
}				t_redir;

// **[중요] 여름님과 우리코드의 큰 차이점은, 여름님네는 ';'를 기준으로 나눴고, 우리코드는 ';'와 '|'를 기준으로 나눴다.
// 또한 여름님네는 "echo hi\0" 이렇게 char *로 가져온다면, 우리코드는 "echo","hi",NULL 이렇게 char **로 가져온다.

// cmdline 인자 char * -> char ** 로 변경
void    exec_redir(char **cmdline, t_list *envs)
{
	int		i;
	int		ret;
	t_redir r;

    char    *one_cmdline;
    one_cmdline = change_from_double_to_single_cmdline(cmdline);

	init_redir(one_cmdline, &r);
	if ((ret = parse_redir(one_cmdline, &r)) <= 0)
	{
		if (ret < 0)
			ft_putendl_fd("syntax error near unexpected token `newline'", 1);
		return ;
	}
	i = -1;
	while (r.cmds[++i])
	{
		if (has_quote(r.cmds[i]))
			r.cmds[i] = modify_argv(r.cmds[i], envs);
	}
	open_unnecessary_files(&r);
	cmd_redir(&r, envs); // 실제 > < >> 처리하는 부분
}

int		is_single_redir(char *command, int i)
{
	if (command[i] == '>' && command[i - 1] != '>' && command[i + 1] != '>')
		return (1);
	return (0);
}

int		find_redir_type(char *command, int i)
{
	if (command[i] == '>' && command[i + 1] == '>')
		return (DREDIR);
	else if (is_single_redir(command, i))
		return (REDIR);
	return (BREDIR);
}

////////////////////////////////////////////////////////////
char    *ft_strjoin_c(char *s, char c)
{
	char    *p;
	int     i;

	i = 0;
	p = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = c;
	p[i + 1] = '\0';
    if (s)
	{
		free(s);
		s = NULL;
	}
	return (p);
}

char    *change_from_double_to_single_cmdline(char **cmdline)
{
    char    *new_line;
    char    *temp;
    int     i;

    if (!cmdline)
        return (NULL);
    
    new_line = ft_strdup("");
    i = 0;
    while (cmdline[i])
    {
        temp = ft_strjoin(new_line, cmdline[i]);
        free(new_line);
        new_line = temp;
        
        if (cmdline[i + 1] != NULL)
            new_line = ft_strjoin_c(new_line, ' ');

        i++;
    }
    new_line[ft_strlen(new_line)] = '\0';
    return (new_line);
}