/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:03 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/15 16:32:40 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_input(int argc, char **argv, t_display *display)
{
	char	**file_content;

	if (argc != 2 || !ft_strrchr(argv[1], '.')
		||ft_strncmp(".cub", ft_strrchr(argv[1], '.'), 5))
		(free_exit("Argument should be a.cub file", NULL, 1));
	file_content = read_file(argv[1]);
	store_validate(file_content, display);
}

char	**store_info(char *filename, int lines_count)
{
	int		fd;
	char	**file_content;
	int		i;

	fd = open(filename, O_RDONLY);
	file_content = malloc(sizeof(char *) * (lines_count + 1));
	if (!file_content)
		(ft_putendl_fd("❌ malloc failure", 2), exit(EXIT_FAILURE));
	i = 0;
	file_content[i] = get_next_line(fd);
	while (file_content[i++])
		file_content[i] = get_next_line(fd);
	close (fd);
	return (file_content);
}

int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

char	**read_file(char *file_name)
{
	int		fd;
	int		lines_count;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		(free_exit("File open failed", NULL, 1));
	lines_count = count_lines(fd);
	close(fd);
	return (store_info(file_name, lines_count));
}
