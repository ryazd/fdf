/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluthor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:28:20 by hluthor           #+#    #+#             */
/*   Updated: 2020/07/17 07:43:14 by hluthor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		zis(t_fdf *data)
{
	int		z;
	int		z1;

	z = data->z_matrix[(int)data->y[0]][(int)data->x[0]];
	z1 = data->z_matrix[(int)data->y[1]][(int)data->x[1]];
	data->x[0] *= data->zoom;
	data->y[0] *= data->zoom;
	data->x[1] *= data->zoom;
	data->y[1] *= data->zoom;
	data->color = (z || z1) > 0 ? 0xe80c0c : 0xffffff;
	isometric(&(data->x[0]), &(data->y[0]), z, data);
	isometric(&(data->x[1]), &(data->y[1]), z1, data);
	data->x[0] += data->shift_x;
	data->y[0] += data->shift_y;
	data->x[1] += data->shift_x;
	data->y[1] += data->shift_y;
}

void		bresenham(t_fdf *data)
{
	float	x_step;
	float	y_step;
	int		max;

	zis(data);
	x_step = data->x[1] - data->x[0];
	y_step = data->y[1] - data->y[0];
	max = MAX1(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(data->x[0] - data->x[1]) || (int)(data->y[0] - data->y[1]))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->x[0],
				data->y[0], data->color);
		data->x[0] += x_step;
		data->y[0] += y_step;
	}
}

int			deal_key(int key, t_fdf **data)
{
	if (key == 53)
		ft_freefull(data);
	if (key == 126)
		(*data)->shift_y -= 10;
	if (key == 125)
		(*data)->shift_y += 10;
	if (key == 123)
		(*data)->shift_x -= 10;
	if (key == 124)
		(*data)->shift_x += 10;
	if (key == 69)
		(*data)->zoom *= 1.2;
	if (key == 78)
		(*data)->zoom /= 1.2;
	if (key == 84)
		(*data)->angle1 -= 0.1;
	if (key == 91)
		(*data)->angle1 += 0.1;
	if (key == 86)
		(*data)->angle2 -= 0.1;
	if (key == 88)
		(*data)->angle2 += 0.1;
	mlx_clear_window((*data)->mlx_ptr, (*data)->win_ptr);
	draw(*data);
	return (0);
}

void		draw(t_fdf *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width[y])
		{
			if (x < data->width[y] - 1)
			{
				coord(x, y, data);
				bresenham(data);
			}
			if (y < data->height - 1)
			{
				coord1(x, y, data);
				bresenham(data);
			}
			x += 1;
		}
		y += 1;
	}
}

int			main(int argc, char **argv)
{
	t_fdf		*data;

	if (argc > 2 || argc < 2)
		return (reterr());
	if (ft_strstr(argv[1], ".fdf") == NULL)
		return (reterr());
	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (read_file(argv[argc - 1], data) == 0)
		return (ft_free(&data));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "fdf");
	data->zoom = 20;
	data->angle1 = 0.5;
	data->angle2 = 0.5;
	draw(data);
	mlx_key_hook(data->win_ptr, deal_key, &data);
	mlx_loop(data->mlx_ptr);
}
