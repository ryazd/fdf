/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluthor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:30:51 by hluthor           #+#    #+#             */
/*   Updated: 2020/07/17 07:41:42 by hluthor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define MAX1(a, b) (a > b ? a : b)
# define MOD(a) ((a < 0) ? -a : a)
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdlib.h>
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

typedef	struct	s_fdf
{
	int			*width;
	int			height;
	int			**z_matrix;
	int			zoom;
	int			color;
	int			shift_x;
	int			shift_y;
	float		angle1;
	float		angle2;
	float		x[2];
	float		y[2];

	void		*mlx_ptr;
	void		*win_ptr;
}				t_fdf;

int				numstr(char *av);
void			isometric(float *x, float *y, int z, t_fdf *data);
void			draw(t_fdf *data);
int				read_file(char *file_name, t_fdf *data);
void			fill_matrix(int *z_line, char *line);
int				get_width(char *file_name, t_fdf *data);
int				get_height(char *file_name);
void			coord1(int x, int y, t_fdf *data);
void			coord(int x, int y, t_fdf *data);
void			zis(t_fdf *data);
void			bresenham(t_fdf *data);
int				deal_key(int key, t_fdf **data);
void			ft_freefull(t_fdf **data);
int				reterr();
int				ft_free(t_fdf **data);

#endif
