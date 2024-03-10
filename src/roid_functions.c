/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roid_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:11:05 by masoares          #+#    #+#             */
/*   Updated: 2024/03/10 21:33:04 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	roid_render_map(t_data *data)
{
	int	x;
	int	y;

	data->menu_img = mlx_xpm_file_to_image(data->mlx_ptr, data->menu_file, &x, &y);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH - 235, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, \
	&data->img.line_len, &data->img.endian);
	data->y = data->height / 2 * -1;
	if (data->height % 2 != 0 && data->width % 2 != 0)
		roid_map_impar(data);
	else if (data->height % 2 == 0 && data->width % 2 == 0)
		roid_map_par(data);
	else if (data->height % 2 != 0 && data->width % 2 == 0)
		roid_map_misto1(data);
	else
		roid_map_misto2(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->menu_img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 235, 0);
	menu_render(data);
	return (0);
}

void	roid_map_par(t_data *data)
{
	while (data->y < (data->height / 2))
	{
		data->x = data->width / 2 * -1;
		while (data->x < (data->width / 2))
		{
			if (data->x < (data->width / 2) - 1)
				roid_bresenham_colour(data, data->x + 1, data->y);
			if (data->y < (data->height / 2) - 1)
				roid_bresenham_colour(data, data->x, data->y + 1);
			data->x++;
		}
		data->y++;
	}
}

void	roid_map_impar(t_data *data)
{
	while (data->y <= (data->height / 2))
	{
		data->x = data->width / 2 * -1;
		while (data->x <= (data->width / 2))
		{
			if (data->x < (data->width / 2))
				roid_bresenham_colour(data, data->x + 1, data->y);
			if (data->y < (data->height / 2))
				roid_bresenham_colour(data, data->x, data->y + 1);
			data->x++;
		}
		data->y++;
	}
}

void	roid_map_misto1(t_data *data)
{
	if (data->height % 2 != 0)
	{
		while (data->y <= (data->height / 2))
		{
			data->x = data->width / 2 * -1;
			while (data->x < (data->width / 2))
			{
				if (data->x < (data->width / 2) - 1)
					roid_bresenham_colour(data, data->x + 1, data->y);
				if (data->y < (data->height / 2))
					roid_bresenham_colour(data, data->x, data->y + 1);
				data->x++;
			}
			data->y++;
		}
	}
}

void	roid_map_misto2(t_data *data)
{
	if (data->width % 2 != 0)
	{
		while (data->y < (data->height / 2))
		{
			data->x = data->width / 2 * -1;
			while (data->x <= (data->width / 2))
			{
				if (data->x < (data->width / 2))
					roid_bresenham_colour(data, data->x + 1, data->y);
				if (data->y < (data->height / 2) - 1)
					roid_bresenham_colour(data, data->x, data->y + 1);
				data->x++;
			}
			data->y++;
		}
	}
}

void	roid_bresenham_colour(t_data *data, double x1, double y1)
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
	roid_rotation(data, &x1, &y1);
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

int roid_color(t_data *data, double z_point)
{
	int color;
	if (data->color_save == 2)
	{
		if (z_point >= 0)
			color = roid_colors_above_2(data, z_point);
		if (z_point < 0)
			color = roid_colors_below_2(data, z_point);
	}
	if (data->color_save == 3)
	{
		if (z_point >= 0)
			color = roid_colors_above_3(data, z_point);
		if (z_point < 0)
			color = roid_colors_below_3(data, z_point);
	}
	if (data->color_save == 4)
	{
		if (z_point >= 0)
			color = roid_colors_above_4(data, z_point);
		if (z_point < 0)
			color = roid_colors_below_4(data, z_point);
	}
	if (data->color_save == 5)
	{
		if (z_point >= 0)
			color = roid_colors_above_5(data, z_point);
		if (z_point < 0)
			color = roid_colors_below_5(data, z_point);
	}
	return(color);
}
int	roid_colors_above_2(t_data *data, double z_point)
{
	int		red;
	int		green;
	int		blue;
	int		r;
	int		g;
	int		b;
	int 	trans;
	double	range;
	double	cur_max_z;
	double	cur_min_z;
	int		color;

	red = 86;
	green = 0;
	blue = 0;
	range = data->max_z / 8;
	cur_max_z = range;
	cur_min_z = 0;

	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 208 + (((108 - 208) / range) * (z_point - cur_min_z));
		g = 118 + (((149 - 118) / range) * (z_point - cur_min_z));
		b = 25 + ((59 - 25) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		trans = 0x00000000 + (0 << 24);
		
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 108 + (((0 - 108) / range) * (z_point - cur_min_z));
		g = 149 + ((213 - 149) / range) * (z_point - cur_min_z);
		b =  25 + ((25 - 25) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		trans = 0x00000000 + (0 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 108 + (((150 - 108) / range) * (z_point - cur_min_z));
		g = 181 + ((213 - 181) / range) * (z_point - cur_min_z);
		b =  25 + ((121 - 25) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		trans = 0x00000000 + (0 << 24);
		color = red + green + blue + trans;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0 + (((0 - 150) / range) * (z_point - cur_min_z));
		g = 213 + ((213 - 213) / range) * (z_point - cur_min_z);
		b =  121 + ((160 - 121) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 118 + (((118 - 118) / range) * (z_point - cur_min_z));
		g = 213 + ((213 - 213) / range) * (z_point - cur_min_z);
		b =  160 + ((220 - 160) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 118 + (((118 - 118) / range) * (z_point - cur_min_z));
		g = 255 + ((255 - 255) / range) * (z_point - cur_min_z);
		b =  220 + ((255 - 220) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 118 + (((255 - 118) / range) * (z_point - cur_min_z));
		g = 255 + ((255 - 255) / range) * (z_point - cur_min_z);
		b =  255 + ((255 - 255) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 255;
		g = 255 + ((255 - 255) / range) * (z_point - cur_min_z);
		b =  255 + ((255 - 255) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	return (0);
	
}

int	roid_colors_below_2(t_data *data, double z_point)
{
	int		red;
	int		green;
	int		blue;
	int		r;
	int		g;
	int		b;
	int		trans;
	double	range;
	double	cur_max_z;
	double	cur_min_z;
	int		color;

	red = 0;
	green = 29;
	blue = 29;
	range = -data->min_z / 7;
	cur_max_z = data->min_z + 1 * range;
	cur_min_z = data->min_z;

	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g = 29 + (((58 - 29) / range) * (z_point - cur_min_z));
		b =29 + (((58 - 29) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		trans = 0x00000000 + (255 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g = 29 + (((58 - 29) / range) * (z_point - cur_min_z));
		b =29 + (((58 - 29) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		trans = 0x00000000 + (255 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g =58 + ((93 - 58) / range) * (z_point - cur_min_z);
		b = 58 + ((96 - 58) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		trans = 0x00000000 + (255 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g = 96 + (((96 - 96) / range) * (z_point - cur_min_z));
		b = 93 + (((93 - 93) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		trans = 0x00000000 + (255 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r =0 +(((0 - 0) / range) * (z_point - cur_min_z));
		g = 96 +(((96 - 93) / range) * (z_point - cur_min_z));
		b = 93 +(((93 - 93) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		trans = 0x00000000 + (255 << 24);
		color = red + green + blue + trans;

		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0 + ((0 - 0) / range) * (z_point - cur_min_z);
		g = 96 + (((96 - 96) / range) * (z_point - cur_min_z));
		b = 93 + (((93 - 93) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		trans = 0x00000000 + (250 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 56 +(((104 - 56) / range) * (z_point - cur_min_z));
		g = 206 + (((206 - 206) / range) * (z_point - cur_min_z));
		b = 207 + (((207 - 207) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		trans = 0x00000000 + (250 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		
		r = 0 +(((56 - 0) / range) * (z_point - cur_min_z));
		g = 182 + (((206 - 182) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		b = 183 + (((207 - 183) / range) * (z_point - cur_min_z));
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		trans = 0x00000000 + (255 << 24);
		color = red + green + blue + trans;
		return (color);
	}
	return(0);
}

int	roid_colors_above_3(t_data *data, double z_point)
{
	int		red;
	int		green;
	int		blue;
	int	r;
	int	g;
	int	b;
	double	range;
	double	cur_max_z;
	double	cur_min_z;
	int		color;

	red = 86;
	green = 0;
	blue = 0;
	range = data->max_z / 8;
	cur_max_z = range;
	cur_min_z = 0;

	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 86 + (((117 - 86) / range) * (z_point - cur_min_z));
		g = 0 + (((33 - 0) / range) * (z_point - cur_min_z));
		b = 0 + ((8 - 0) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 117 + (((149 - 117) / range) * (z_point - cur_min_z));
		g = 33 + ((60 - 33) / range) * (z_point - cur_min_z);
		b =  8 + ((7 - 8) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 149 + (((182 - 149) / range) * (z_point - cur_min_z));
		g = 60 + ((88 - 60) / range) * (z_point - cur_min_z);
		b =  7 + ((4 - 7) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 182 + (((208 - 182) / range) * (z_point - cur_min_z));
		g = 88 + ((118 - 88) / range) * (z_point - cur_min_z);
		b =  4 + ((25 - 4) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 208 + (((225 - 208) / range) * (z_point - cur_min_z));
		g = 118 + ((149 - 118) / range) * (z_point - cur_min_z);
		b =  25 + ((59 - 25) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 225 + (((241 - 225) / range) * (z_point - cur_min_z));
		g = 149 + ((181 - 149) / range) * (z_point - cur_min_z);
		b =  59 + ((90 - 59) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 241 + (((255 - 241) / range) * (z_point - cur_min_z));
		g = 181 + ((213 - 181) / range) * (z_point - cur_min_z);
		b =  90 + ((121 - 90) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 255;
		g = 214 + ((255 - 213) / range) * (z_point - cur_min_z);
		b =  121 + ((255 - 121) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}

	return(0);
}

int	roid_colors_below_3(t_data *data, double z_point)
{
		int		red;
	int		green;
	int		blue;
	int	r;
	int	g;
	int	b;
	double	range;
	double	cur_max_z;
	double	cur_min_z;
	int		color;

	red = 0;
	green = 47;
	blue = 50;
	range = -data->min_z / 7;
	cur_max_z = data->min_z + 1 * range;
	cur_min_z = data->min_z;

	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g = 47 + (((93 - 47) / range) * (z_point - cur_min_z));
		b =50 + (((96 - 50) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g = 93 + (((122 - 93) / range) * (z_point - cur_min_z));
		b =96 + (((124 - 96) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g =122 + ((151 - 122) / range) * (z_point - cur_min_z);
		b = 124 + ((153 - 124) / range) * (z_point - cur_min_z);
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0;
		g = 151 + (((182 - 151) / range) * (z_point - cur_min_z));
		b = 153 + (((183 - 153) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r =0 +(((56 - 0) / range) * (z_point - cur_min_z));
		g = 182 +(((206 - 182) / range) * (z_point - cur_min_z));
		b = 183 +(((207 - 183) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 56 + (((104 - 56) / range) * (z_point - cur_min_z));
		g =206 + (((222 - 206) / range) * (z_point - cur_min_z));
		b = 207 + (((223 - 207) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 104 +(((141 - 104) / range) * (z_point - cur_min_z));
		g = 222 + (((239 - 222) / range) * (z_point - cur_min_z));
		b = 223 + (((239 - 223) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		
		r = 141 +(((174 - 141) / range) * (z_point - cur_min_z));
		g = 239 + (((255 - 239) / range) * (z_point - cur_min_z));
		red = 0x00000000 + (r <<16);
		b = 207 + (((255 - 207) / range) * (z_point - cur_min_z));
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 +b;
		color = red + green + blue;
		return (color);
	}
	return(0);
}
int	roid_colors_above_4(t_data *data, double z_point)
{
	int		red;
	int		green;
	int		blue;
	int	r;
	int	g;
	int	b;
	double	range;
	double	cur_min_z;
	int		color;

	red = 0;
	green = 0;
	blue = 0;
	range = data->max_z;
	cur_min_z = 0;

	r = 255 + (((74 - 255) / range) * (z_point - cur_min_z));
	g = 255 + (((255 - 255) / range) * (z_point - cur_min_z));
	b = 255 + ((0 - 255) / range) * (z_point - cur_min_z);
	red = 0x00000000 + (r << 16);
	green = 0x00000000 + (g << 8);
	blue = 0x00000000 + b;
	color = red + green + blue;
	return(color);
}

int	roid_colors_below_4(t_data *data, double z_point)
{
	int		red;
	int		green;
	int		blue;
	int	r;
	int	g;
	int	b;
	double	range;
	double	cur_min_z;
	int		color;

	red = 53;
	green = 17;
	blue = 65;
	range = -data->min_z;
	cur_min_z = data->min_z;
	r = 255 + (((140 - 255) / range) * (z_point - cur_min_z));
	g = 255 + (((0 - 255) / range) * (z_point - cur_min_z));
	b = 255 + (((255 - 255) / range) * (z_point - cur_min_z));
	red = 0x00000000 + (r << 16);
	green = 0x00000000 + (g << 8);
	blue = 0x00000000 + b;
	color = red + green + blue;
	return(color);
}

int	roid_colors_above_5(t_data *data, double z_point)
{
	int		red;
	int		green;
	int		blue;
	int	r;
	int	g;
	int	b;
	double	range;
	double	cur_max_z;
	double	cur_min_z;
	int		color;

	red = 0;
	green = 0;
	blue = 0;
	range = data->max_z / 8;
	cur_max_z = range;
	cur_min_z = 0;

	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 119 + ((135 - 119) / range) * (z_point - cur_min_z) + data->red;
		g = 119 + ((135 - 119) / range) * (z_point - cur_min_z) + data->green;
		b = 119 + ((135 - 119) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 135 + (((152 - 135) / range) * (z_point - cur_min_z)) + data->red;
		g = 135+ ((152 - 135) / range) * (z_point - cur_min_z) + data->green;
		b = 135 + ((152 - 135) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 152 + (((169 - 152) / range) * (z_point - cur_min_z)) + data->red;
		g = 152 + ((169 - 152) / range) * (z_point - cur_min_z) + data->green;
		b = 152 + ((169 - 152) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 169 + (((186 - 169) / range) * (z_point - cur_min_z)) + data->red;
		g = 169 + ((186 - 169) / range) * (z_point - cur_min_z) + data->green;
		b = 169 + ((186 - 169) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 186 + (((203 - 186) / range) * (z_point - cur_min_z)) + data->red;
		g = 186 + ((203 - 186) / range) * (z_point - cur_min_z) + data->green;
		b = 186 + ((203 - 186) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 203 + (((220 - 203) / range) * (z_point - cur_min_z)) + data->red;
		g = 203 + ((220 - 203) / range) * (z_point - cur_min_z) + data->green;
		b = 203 + ((220 - 203) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 220 + (((237 - 220) / range) * (z_point - cur_min_z)) + data->red;
		g = 220 + ((237 - 220) / range) * (z_point - cur_min_z) + data->green;
		b = 220 + ((237 - 220) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 237 + ((255 - 237) / range) * (z_point - cur_min_z) + data->red;
		g = 237 + ((255 - 237) / range) * (z_point - cur_min_z) + data->green;
		b = 237 + ((255 - 237) / range) * (z_point - cur_min_z) + data->blue;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}

	return(0);
}

int	roid_colors_below_5(t_data *data, double z_point)
{
		int		red;
	int		green;
	int		blue;
	int	r;
	int	g;
	int	b;
	double	range;
	double	cur_max_z;
	double	cur_min_z;
	int		color;

	red = 53;
	green = 17;
	blue = 65;
	range = -data->min_z / 7;
	cur_max_z = data->min_z + 1 * range;
	cur_min_z = data->min_z;

	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 0 + (((17- 0) / range) * (z_point - cur_min_z)) + data->red;
		g = 0 + (((17 - 0) / range) * (z_point - cur_min_z)) + data->green;
		b = 0 + ((17 - 0) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + b;
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 17 + (((34 - 17) / range) * (z_point - cur_min_z)) + data->red;
		g = 17 + ((34 - 17) / range) * (z_point - cur_min_z) + data->green;
		b =  17 + ((34 - 17) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 34 + (((51 - 34) / range) * (z_point - cur_min_z)) + data->red;
		g = 34 + ((51 - 34) / range) * (z_point - cur_min_z) + data->green;
		b =  34 + ((51 - 34) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 51 + (((68 - 51) / range) * (z_point - cur_min_z)) + data->red;
		g = 51 + ((68 - 51) / range) * (z_point - cur_min_z) + data->green;
		b = 51 + ((68 - 51) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 68 + (((85 - 68) / range) * (z_point - cur_min_z)) + data->red;
		g = 68 + ((85 - 68) / range) * (z_point - cur_min_z) + data->green;
		b =  68 + ((85 - 68) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 85 + (((102 - 85) / range) * (z_point - cur_min_z)) + data->red;
		g = 85 + ((102 - 85) / range) * (z_point - cur_min_z) + data->green;
		b =  85 + ((102 - 85) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}
	cur_min_z = cur_max_z;
	cur_max_z += range;
	if (z_point >= cur_min_z && z_point < cur_max_z)
	{
		r = 102 + (((119 - 102) / range) * (z_point - cur_min_z)) + data->red;
		g = 102 + ((119 - 102) / range) * (z_point - cur_min_z) + data->green;
		b =  102 + ((119 - 102) / range) * (z_point - cur_min_z) + data->blue;
		red = 0x00000000 + (r << 16);
		green = 0x00000000 + (g << 8);
		blue = 0x00000000 + (b);
		color = red + green + blue;
		return (color);
	}

	return(0);
}

int	roid_build_img(t_data *data, int color)
{
	char	*ptr;

	ptr = NULL;
	if (data->u < (WIDTH - 235) && data->u >= 0 
	&& data->v < (HEIGHT) && data->v >= 0)
	{
		if (color == 0)
		{
			ptr = data->img.addr + (int)data->u * (data->img.bpp / 8) 
			+ ((int)data->v * data->img.line_len);
			*(unsigned int *)ptr = data->color_default;
		}
		else
		{
			ptr = data->img.addr + (int)data->u * (data->img.bpp / 8) 
			+ ((int)data->v * data->img.line_len);
			*(unsigned int *)ptr = color;
		}
	}
	return (0);
}

// void	roid_bresenham_surfaces(t_data *data1, double x1, double y1, t_data *data2, double x2, double y2)
// {
// 	double m[4];
// 	double b[4];
// 	int max_u;
// 	int min_u;
// 	int max_b;
// 	int min_b;
	
// 	data1->u = data1->x;
// 	data1->v = data1->y;
// 	data2->u = data2->x;
// 	data2->v = data2->y;
// 	data1->z = data1->map[data1->y + (data1->height / 2)][data1->x + (data1->width / 2)].z;
// 	data1->z1 = data1->map[(int)y1 + (data1->height / 2)][(int)x1 + (data1->width / 2)].z;
// 	data2->z = data2->map[data1->y + (data2->height / 2)][data2->x + (data2->width / 2)].z;
// 	data2->z1 = data2->map[(int)y1 + (data2->height / 2)][(int)x1 + (data2->width / 2)].z;
// 	data1->color_default = data1->map[data1->y + (data1->height / 2)][data1->x + (data1->width / 2)].color;
// 	data2->color_default = data2->map[data1->y + (data2->height / 2)][data2->x + (data2->width / 2)].color;
// 	data1->z_copy = data1->z;
// 	data1->z1_copy = data1->z1;
// 	data2->z_copy = data2->z;
// 	data2->z1_copy = data2->z1;
// 	//colors_change(data);
// 	rotation(data1, &x1, &y1);
// 	zoom(&x1, &y1, data1);
// 	map_move(&x1, &y1, data1);
// 	rotation(data2, &x2, &y2);
// 	zoom(&x2, &y2, data2);
// 	map_move(&x2, &y2, data2);
// 	calc_m_b(&m, &b, data1, data2, x1, y1, x2, y2);
// 	calc_max_min();

// 	u = u_min;
// 	while (u <= u_max) 
// 	{
// 		v = v_min;
// 		while (v <= v_max)
// 		{
			 
// 			//checkar pelos m qual a posicao das retas e para decidir qual o quadrado a definir
// 		}
// 		build_img(data)
// 	}
// }

int	roid_rotation(t_data *data, double *x1, double *y1)
{
	double	latitude;
	double	longitude;
	double	latitude1;
	double	longitude1;
	double	R;
	double	max_z;
	double adj_z;

	max_z = (double) data->max_z;
	adj_z = max_z / 6.28;
	
	R = (data->width -1) /(6.28);
	longitude = (data->x)/ (R);
	latitude = 3.14/data->height * data->y;
	longitude1 = (*x1)/ R;
	latitude1 = 3.14/data->height * (*y1);
	if (data->y == (data->height/2))
		latitude = 3.14/2;
	else if (data->y == -(data->height/2))
		latitude = -3.14/2;
	if ((*y1) == (data->height/2))
		latitude1 = 3.14/2;
	else if ((*y1) == -(data->height/2))
		latitude1 = -3.14/2;
	data->v = (R + data->z/adj_z)* cos(latitude) *cos(longitude);
	data->u = -(R + data->z/adj_z) * cos(latitude) *sin(longitude);
	data->z = (R + data->z/adj_z) * sin(latitude);
	*y1= (R + data->z1/adj_z) * cos(latitude1) *cos(longitude1);
	*x1 = - (R + data->z1/adj_z) * cos(latitude1) *sin(longitude1);
	data->z1 = (R + data->z1/adj_z) * sin(latitude1);
	rotate_y_axis(data, &data->u, &data->z);
	rotate_y_axis(data, x1, &data->z1);
	rotate_z_axis(data, &data->u, &data->v);
	rotate_z_axis(data, x1, y1);
	rotate_x_axis(data, &data->v, &data->z);
	rotate_x_axis(data, y1, &data->z1);
	return (0);
}
