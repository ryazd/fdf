/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluthor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:53:49 by hluthor           #+#    #+#             */
/*   Updated: 2020/07/17 07:40:09 by hluthor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_height(char *file_name)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open(file_name, O_RDONLY, 0);
	while (get_next_line(fd, &line) > 0)
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int			get_width(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		i;
	int		c;

	i = 0;
	data->width = (int *)malloc(sizeof(int) * data->height + 1);
	fd = open(file_name, O_RDONLY, 0);
	while (get_next_line(fd, &line))
	{
		if ((c = numstr(line)) == 0)
		{
			close(fd);
			free(line);
			return (0);
		}
		data->width[i++] = c;
		free(line);
	}
	close(fd);
	return (1);
}

void		fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	i = 0;
	nums = ft_strsplit(line, ' ');
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

int			read_file(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	data->height = get_height(file_name);
	if (get_width(file_name, data) == 0)
		return (0);
	data->z_matrix = (int **)malloc(sizeof(int*) * (data->height + 1));
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * (data->width[i] + 1));
		i++;
	}
	data->z_matrix[i] = NULL;
	i = 0;
	fd = open(file_name, O_RDONLY, 0);
	while (get_next_line(fd, &line))
	{
		fill_matrix(data->z_matrix[i], line);
		free(line);
		i++;
	}
	close(fd);
	return (1);
}

void		isometric(float *x, float *y, int z, t_fdf *data)
{
	*x = (*x - *y) * cos(data->angle1);
	*y = (*x + *y) * sin(data->angle2) - z;
}
