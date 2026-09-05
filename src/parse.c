/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 22:55:59 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/05 19:04:49 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * checks that a token is a valid signed number and returns it as int
 */
static int	parse_map_token(t_fdf *fdf, char *tok)
{
	int	i;

	i = 0;
	if (tok[i] == '-' || tok[i] == '+')
		i++;
	if (!tok[i])
		ft_error(fdf, "fdf: invalid altitude in map\n", ERR_USER);
	while (tok[i])
	{
		if (!ft_isdigit(tok[i]))
			ft_error(fdf, "fdf: invalid altitude in map\n", ERR_USER);
		i++;
	}
	return (ft_atoi(tok));
}

/**
 * splits one row into tokens, allocates the map on the first row
 * and stores the altitudes of that row in the grid
 */
static void	parse_row_content(t_fdf *fdf, char *line, int y)
{
	int	width;
	int	x;

	fdf->map_tokens = ft_split(line, ' ');
	if (!fdf->map_tokens)
		ft_error(fdf, "malloc failed in parse_row_content\n", ERR_SYS);
	width = ft_strarray_len(fdf->map_tokens);
	if (y == 0)
		allocate_map(fdf, width, ft_lstsize(fdf->map_rows));
	else if (width != fdf->map.width)
		ft_error(fdf, "fdf: map rows have different widths\n", ERR_USER);
	x = -1;
	while (++x < fdf->map.width)
	{
		fdf->map.points[y * fdf->map.width + x]
			= parse_map_token(fdf, fdf->map_tokens[x]);
	}
	ft_free_strarray(fdf->map_tokens);
	fdf->map_tokens = NULL;
}

/**
 * reads the file line by line, trims the whitespace
 * and stores every non empty line in map_rows
 */
static void	read_them_lines(t_fdf *fdf, int fd)
{
	char	*line;
	char	*trimmed;
	t_list	*node;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\r\v\f");
		free(line);
		if (!trimmed)
			ft_error(fdf, "malloc failed in read_them_lines", ERR_SYS);
		if (!trimmed[0])
			free(trimmed);
		else
		{
			node = ft_lstnew(trimmed);
			if (!node)
				ft_error(fdf, "malloc failed in read_lines", ERR_SYS);
			ft_lstadd_back(&fdf->map_rows, node);
		}
		line = get_next_line(fd);
	}
}

/**
 * opens the map file, reads all rows, fills the point grid
 * and sets the z bounds
 */
void	parse_map(t_fdf *fdf, char *map_path)
{
	t_list	*cur;
	int		fd;
	int		y;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error(fdf, map_path, ERR_SYS);
	read_them_lines(fdf, fd);
	close(fd);
	if (!fdf->map_rows)
		ft_error(fdf, "fdf: map is empty\n", ERR_USER);
	cur = fdf->map_rows;
	y = 0;
	while (cur)
	{
		parse_row_content(fdf, cur->content, y++);
		cur = cur->next;
	}
	ft_lstclear(&fdf->map_rows, free);
	set_map_bounds(&fdf->map);
}
