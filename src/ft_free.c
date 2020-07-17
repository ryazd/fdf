/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluthor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 07:09:08 by hluthor           #+#    #+#             */
/*   Updated: 2020/07/17 07:40:54 by hluthor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		reterr(void)
{
	write(2, "Error\n", 6);
	return (0);
}

int		ft_free(t_fdf **data)
{
	free((*data)->width);
	free(*data);
	return (reterr());
}

void	ft_freefull(t_fdf **data)
{
	int i;

	i = 0;
	free((*data)->width);
	while ((*data)->z_matrix[i])
	{
		free((*data)->z_matrix[i]);
		i++;
	}
	free((*data)->z_matrix);
	free(*data);
	exit(0);
}
