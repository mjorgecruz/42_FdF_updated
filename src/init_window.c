/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:57:29 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/06 12:03:30 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	open_window(t_data *data)
{
		render_menu(data);
		mlx_hook(data->win_ptr, DestroyNotify, NoEventMask, &handle_menu_close, data);
		mlx_hook(data->win_ptr, 4, 1L << 2, &handle_entry_mouse_down, data);
		mlx_hook(data->win_ptr, 5, 1L << 3, &handle_entry_mouse_up, data);
		mlx_hook(data->win_ptr, 6, 1L << 6, &handle_entry_mouse_move, data);
		mlx_loop(data->mlx_ptr);
}

int	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FdF");
	if (!data->win_ptr)
	{
		free(data->win_ptr);
		exit (2);
	}
	data->menu_entry_file = "./sprites_xpm/menu_start.xpm";
	data->choose_file = "./sprites_xpm/choose_map.xpm";
	return (1);
}

void	init_data(t_data *data)
{
	creat_map(data->map_to_render, data);
	data->zoom = 20;
	data->hor = (WIDTH - 200) / 2;
	data->hey = HEIGHT / 2;
	data->button = 0;
	data->angle_x = 0.567890;
	data->angle_y = -0.012300;
	data->angle_z = 0.743534;
	data->menu_color = 0x444444;
	data->color_save = 0;
	data->add_color = 1;
	data->render_status = 1;
	data->menu_file = "./sprites_xpm/menu.xpm";
	get_max_z(data);
	get_min_z(data);
}

int	render_menu(t_data *data)
{
	int x;
	int y;

	data->entry_img = mlx_xpm_file_to_image(data->mlx_ptr, data->menu_entry_file, &x, &y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->entry_img, 0, 0);
	return (1);
}

int	render_choose_menu(t_data *data)
{
	int x;
	int y;

	data->choose_img = mlx_xpm_file_to_image(data->mlx_ptr, data->choose_file, &x, &y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->choose_img, 0, 0);
	return (1);
}