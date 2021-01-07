/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/07 21:29:27 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_list		*init_envs(int argc, char **argv, char **envp)
{
	int		pos;
	t_env	*env;
	t_list	*envs;

	envs = 0;
	if (!argc && argv)
		exit(1);
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		pos = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, pos);
		env->value = ft_substr(*envp, pos + 1, ft_strlen(*envp) - pos - 1);
		ft_lstadd_back(&envs, ft_lstnew(env));
		envp++;
	}
	return (envs);
}

void        show_prompt()
{
    char    *curpath;
    //ft_putstr_fd(userinfo->pw_name, 1);
    ft_putstr_fd("@", 1);
    ft_putstr_fd(getcwd(curpath, 1024), 1);
    ft_putstr_fd(" > ", 1);
}

int		    main(int argc, char **argv, char **envp)
{
    char    *input;
    t_data  data;
    t_list  *envs;
    int     ret;
    
    g_envp = envp;
    //envs = init_envs(argc, argv, envp);
    ret = 1;
    while (ret)
    {
        show_prompt();
        ret = get_next_line(0, &input); //-1인 경우 에러메세지?
        //parsing(&data, input); //free(data, input)
        //printf("%zu\n", ft_strlen(input));
        // free(input);
        // input = NULL;
    }
	return (0);
}