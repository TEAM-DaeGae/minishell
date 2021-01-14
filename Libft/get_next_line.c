#include "libft.h"

static void	ft_strfree(char **s)
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

static int	put_str_into_line(char **s, int fd, char **line)
{
	int			len;
	char		*temp;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		if (len == 0)
			*line = ft_strdup("");
		else
			*line = ft_substr(s[fd], 0, len);
		temp = ft_strdup(&s[fd][len + 1]);
		ft_strfree(&s[fd]);
		s[fd] = temp;
		if (s[fd][0] == 0)
			ft_strfree(&s[fd]);
	}
	else
	{
		*line = ft_strdup(s[fd]);
		ft_strfree(&s[fd]);
		return (0);
	}
	return (1);
}

static int	return_value(char **s, int fd, int r_size, char **line)
{
	int			ret;

	ret = 0;
	if (r_size < 0)
		ret = -1;
	else if (r_size == 0 && s[fd] == 0)
	{
		*line = ft_strdup("");
		ft_strfree(&s[fd]);
		ret = 0;
	}
	else
		ret = put_str_into_line(s, fd, line);
	return (ret);
}

static int	find_enter(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*backup[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			r_size;
	char		*temp;

	if (fd < 0 || line == 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (-1);
	while ((r_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r_size] = '\0';
		if (backup[fd] == NULL)
			backup[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(backup[fd], buff);
			ft_strfree(&backup[fd]);
			backup[fd] = temp;
		}
		if (find_enter(backup[fd]) != 0)
			break ;
	}
	return (return_value(backup, fd, r_size, line));
}