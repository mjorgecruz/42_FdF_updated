/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roid_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:11:05 by masoares          #+#    #+#             */
/*   Updated: 2024/03/05 12:06:14 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	roid_open_window(t_data *data)
{
	init_window(data);
	roid_render_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &roid_handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, NoEventMask, &handle_close, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, &roid_handle_mouse_down, data);
	mlx_hook(data->win_ptr, 5, 1L << 3, &handle_mouse_up, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, &roid_handle_mouse_move, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free (data->mlx_ptr);
}
int	roid_render_map(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH - 200, HEIGHT);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 200, 0);
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
				roid_bresenham(data, data->x + 1, data->y);
			if (data->y < (data->height / 2) - 1)
				roid_bresenham(data, data->x, data->y + 1);
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
				roid_bresenham(data, data->x + 1, data->y);
			if (data->y < (data->height / 2))
				roid_bresenham(data, data->x, data->y + 1);
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
					roid_bresenham(data, data->x + 1, data->y);
				if (data->y < (data->height / 2))
					roid_bresenham(data, data->x, data->y + 1);
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
					roid_bresenham(data, data->x + 1, data->y);
				if (data->y < (data->height / 2) - 1)
					roid_bresenham(data, data->x, data->y + 1);
				data->x++;
			}
			data->y++;
		}
	}
}

void	roid_bresenham(t_data *data, double x1, double y1)
{
	data->u = data->x;
	data->v = data->y;
	data->z = data->map[data->y + (data->height / 2)] \
	[data->x + (data->width / 2)].z;
	data->z1 = data->map[(int)y1 + (data->height / 2)] \
	[(int)x1 + (data->width / 2)].z;
	data->color_default = data->map[data->y + (data->height / 2)] \
	[data->x + (data->width / 2)].color;
	colors_change(data);
	roid_rotation(data, &x1, &y1);
	zoom(&x1, &y1, data);
	map_move(&x1, &y1, data);
	data->x_step = x1 - data->u;
	data->y_step = y1 - data->v;
	data->max = max_step(positive(data->x_step), positive(data->y_step));
	data->x_step /= data->max;
	data->y_step /= data->max;
	while ((int)(data->u - x1) || (int)(data->v - y1))
	{
		build_img(data);
		data->u += data->x_step;
		data->v += data->y_step;
	}
}

int	roid_rotation(t_data *data, double *x1, double *y1)
{
	double	latitude;
	double	longitude;
	double	latitude1;
	double	longitude1;
	double	R;
	
	R = data->width /(6.28); 
	longitude = (data->x)/ (R);
	latitude = 2 *atan(exp(data->y/(R))) - 3.14/2;
	longitude1 = (*x1)/ R;
	latitude1 = 2 *atan(exp(*y1/(R))) - 3.14/2;
	data->v = (R + data->z/25)* cos(latitude) *cos(longitude);
	data->u = (R + data->z/25) * cos(latitude) *sin(longitude);
	data->z = (R + data->z/25) * sin(latitude);
	*y1= (R + data->z1/25) * cos(latitude1) *cos(longitude1);
	*x1 = (R + data->z1/25) * cos(latitude1) *sin(longitude1);
	data->z1 = (R + data->z1/25) * sin(latitude1);
	rotate_y_axis(data, &data->u, &data->z);
	rotate_y_axis(data, x1, &data->z1);
	rotate_z_axis(data, &data->u, &data->v);
	rotate_z_axis(data, x1, y1);
	rotate_x_axis(data, &data->v, &data->z);
	rotate_x_axis(data, y1, &data->z1);
	return (0);
}

int	roid_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_close(data);
	else if (keysym == XK_Right || keysym == XK_Left || \
	keysym == XK_Up || keysym == XK_Down || keysym == XK_r)
		move_handle(keysym, data);
	else if (keysym == XK_q || keysym == XK_w || keysym == XK_a \
	|| keysym == XK_s || keysym == XK_z || keysym == XK_x)
		angle_handle(keysym, data);
	else if (keysym == XK_1 || keysym == XK_2 || keysym == XK_3 \
	|| keysym == XK_4)
		projection_handle(keysym, data);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract)
		z_handle(keysym, data);
	else if (keysym == XK_F1 || keysym == XK_F2 || keysym == XK_F3 \
	|| keysym == XK_p)
		color_handler(keysym, data);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	roid_render_map(data);
	return (0);
}

int	roid_handle_mouse_move(int x, int y, t_data *data)
{
	if (data->button == 1)
	{
		data->hor += (x - data->prev_x);
		data->hey += (y - data->prev_y);
		data->prev_x = x;
		data->prev_y = y;
	}
	else if (data->button == 2)
	{
		data->angle_z -= (x - data->prev_x - (y - data->prev_y)) * 0.002;
		data->prev_x = x;
		data->prev_y = y;
	}
	else if (data->button == 3)
	{
		data->angle_x -= (y - data->prev_y) * 0.002;
		data->angle_y += (x - data->prev_x) * 0.002;
		data->prev_x = x;
		data->prev_y = y;
	}
	else
		return (0);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	roid_render_map(data);
	return (0);
}

int	roid_handle_mouse_down(int button, int x, int y, t_data *data)
{
	if (button == 1 || button == 2 || button == 3)
	{
		data->prev_x = x;
		data->prev_y = y;
		data->button = button;
	}
	else if (button == 4)
	{
		if (data->zoom < 150)
			data->zoom *= 1.5;
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		roid_render_map(data);
	}
	else if (button == 5)
	{
		if (data->zoom > 3)
			data->zoom /= 1.5;
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		roid_render_map(data);
	}
	return (0);
}