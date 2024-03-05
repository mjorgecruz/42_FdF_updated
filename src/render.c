/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:05:50 by ruiolive          #+#    #+#             */
/*   Updated: 2023/12/07 10:39:47 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	render_map(t_data *data)
{
	int	x;
	int	y;

	data->menu_img = mlx_xpm_file_to_image(data->mlx_ptr, data->menu, &x, &y);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH - 235, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, \
	&data->img.line_len, &data->img.endian);
	data->y = data->height / 2 * -1;
	if (data->height % 2 != 0 && data->width % 2 != 0)
		map_impar(data);
	else if (data->height % 2 == 0 && data->width % 2 == 0)
		map_par(data);
	else if (data->height % 2 != 0 && data->width % 2 == 0)
		map_misto1(data);
	else
		map_misto2(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->menu_img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 235, 0);
	menu_render(data);
	return (0);
}

int	menu_render(t_data *data)
{
	render_strings1(data);
	return (0);
}

void	render_strings1(t_data *data)
{
	data->info.angle_x = ft_calloc(sizeof(char),  20);
	data->info.angle_y = ft_calloc(sizeof(char),  20);
	data->info.angle_z = ft_calloc(sizeof(char),  20);
	data->info.zoom = ft_calloc(sizeof(char),  20);
	data->info.high = NULL;
	data->info.horizontal = NULL;
	data->info.Vertical = NULL;
	data->info.color_rad = NULL;

	ftoa(data->angle_x, data->info.angle_x, 2);
	ftoa(data->angle_y, data->info.angle_y, 2);
	ftoa(data->angle_z, data->info.angle_z, 2);
	ftoa((float)data->zoom, data->info.zoom, 2);
	data->info.high = ft_itoa(data->max_z);
	data->info.horizontal =  ft_itoa(data->hor);
	data->info.Vertical =  ft_itoa(data->hey);
	data->info.color_rad = ft_itoa(data->add_color);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 194,
	221, 0x000000, data->info.angle_x);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 194,
	256, 0x000000, data->info.angle_y);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 194,
	289, 0x000000, data->info.angle_z);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 190,
	381, 0x000000, data->info.zoom);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 196,
	472, 0x000000, data->info.high);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 194,
	507, 0x000000, data->info.horizontal);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 194,
	540, 0x000000, data->info.Vertical);
}
