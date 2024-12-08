/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbusom-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:24:44 by jbusom-r          #+#    #+#             */
/*   Updated: 2024/12/02 14:04:35 by jbusom-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = NULL;
	i = 0;
	len = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	len = ft_strlen(stash) - i;
	tmp = ft_substr(stash, i, len + 1);
	if (!tmp)
		ft_free(&tmp);
	ft_free(&stash);
	return (tmp);
}

char	*fill_line(char *stash)
{
	int		len;
	char	*result;

	len = 0;
	while (stash[len])
	{
		if (stash[len] == '\n')
		{
			if (len == 0)
				len = 1;
			else
				len++;
			break ;
		}
		len++;
	}
	result = ft_substr(stash, 0, len);
	if (!result || len == 0)
		return (ft_free(&result));
	return (result);
}

char	*read_buf(int fd, char *stash)
{
	int		read_bytes;
	char	*buf;

	read_bytes = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free(&stash));
	buf[0] = '\0';
	while (read_bytes > 0 && !ft_strchr(buf, '\n'))
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buf[read_bytes] = '\0';
			stash = ft_strjoin_free(stash, buf);
		}
	}
	free(buf);
	if (read_bytes == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	if ((stash[fd] && !ft_strchr(stash[fd], '\n')) || !stash[fd])
		stash[fd] = read_buf(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = fill_line(stash[fd]);
	if (!line)
		return (ft_free(&stash[fd]));
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
