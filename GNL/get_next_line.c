/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:00:22 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/11 12:55:04 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_line(char *line, int fd)
{
	char	*buf;
	ssize_t	status;
	char	*temp;

	buf = ft_gnlcalloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_gnlstrchr(line, '\n'))
	{
		status = read(fd, buf, BUFFER_SIZE);
		if (status <= 0)
		{
			if (status < 0 && line)
				return (free(line), free(buf), NULL);
			return (free(buf), line);
		}
		buf[status] = '\0';
		temp = line;
		line = ft_gnlstrjoin(line, buf);
		if (temp)
			free(temp);
		if (!line)
			return (free(buf), NULL);
	}
	return (free(buf), line);
}

char	*exact_line(char *line)
{
	char	*next_line;
	int		nl_len;

	nl_len = len_to_char(line, '\n');
	if (line[nl_len - 1] != '\n' && !line[nl_len])
		nl_len++;
	next_line = malloc (nl_len);
	if (!next_line)
		return (NULL);
	ft_copy(next_line, line, nl_len);
	return (next_line);
}

char	*remaining_of_line(char *line)
{
	char		*remaining;
	int			remaining_len;

	remaining_len = len_to_char(line, '\0') - (len_to_char(line, '\n'));
	if (remaining_len == 0)
		return (free(line), NULL);
	remaining = malloc (remaining_len + 1);
	if (!remaining)
		return (NULL);
	ft_copy(remaining, line + len_to_char(line, '\n'), remaining_len + 1);
	free(line);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	line = read_to_line(line, fd);
	if (!line)
		return (NULL);
	next_line = exact_line(line);
	line = remaining_of_line(line);
	return (next_line);
}
