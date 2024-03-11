/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:12:18 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/09 17:42:56 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	bresenham(t_data *data, double x1, double y1)
{
	int z_point;
	double z_step;
	data->u = data->x;
	data->v = data->y;
	data->z = data->map[data->y + (data->height / 2)] 
	[data->x + (data->width / 2)].z;
	data->z_copy = data->z;
	data->z1 = data->map[(int)y1 + (data->height / 2)] 
	[(int)x1 + (data->width / 2)].z;
	data->z1_copy = data->z1;
	data->color_default = data->map[data->y + (data->height / 2)] 
	[data->x + (data->width / 2)].color;
	rotation(data, &x1, &y1);
	zoom(&x1, &y1, data);
	map_move(&x1, &y1, data);
	data->x_step = x1 - data->u;
	data->y_step = y1 - data->v;
	data->max = max_step(positive(data->x_step), positive(data->y_step));
	data->x_step /= data->max;
	data->y_step /= data->max;
	z_point = data->z_copy;	
	z_step = (data->z1_copy - data->z_copy) / positive((x1 - data->u) / data->x_step);
	while ((int)(data->u - x1) || (int)(data->v - y1))
	{
	 	int color;
		color = 0;
		if (data->color_save > 1)
	 		color = roid_color(data, z_point);
		roid_build_img(data, color);
		z_point += z_step;
		data->u += data->x_step;
		data->v += data->y_step;
	}
}

int	build_img(t_data *data)
{
	char	*ptr;

	ptr = NULL;
	if (data->u < (WIDTH - 235) && data->u >= 0 \
	&& data->v < (HEIGHT) && data->v >= 0)
	{
		ptr = data->img.addr + (int)data->u * (data->img.bpp / 8) \
		+ ((int)data->v * data->img.line_len);
		*(unsigned int *)ptr = data->color_default;
	}
	return (0);
}

float	max_step(float x_step, float y_step)
{
	if (x_step > y_step)
		return (x_step);
	else
		return (y_step);
}

float	positive(float n)
{
	if (n < 0)
		return (n *= -1);
	return (n);
}
