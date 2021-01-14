# include <stdio.h>
# include <stdlib.h>

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
}				t_cmd;

typedef struct	s_data
{
	t_list	*lst;
	t_cmd	*cmd;
	char	*buff;
	int		i;
	int		j;
	int		k;
}				t_data;
