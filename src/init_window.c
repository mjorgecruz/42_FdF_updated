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

int	handle_entry_menu_keypress(int keysym, t_data *data);
int	render_menu(t_data *data);

void	open_window(t_data *data)
{
	init_window(data);
	render_menu(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_entry_menu_keypress, data);
	mlx_loop(data->mlx_ptr);
}

int	init_window(t_data *data)
{
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
	data->menu = "./sprites_xpm/menu.xpm";
	get_max_z(data);
	get_min_z(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FdF");
	if (!data->win_ptr)
	{
		free(data->win_ptr);
		exit (2);
	}
	return (1);
}

int	handle_entry_menu_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->entry_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
		ft_free_map(data);
		exit(1);
	}
	else if (keysym)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_image(data->mlx_ptr, data->entry_img);
		render_map(data);
		mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
		mlx_hook(data->win_ptr, DestroyNotify, NoEventMask, &handle_close, data);
		mlx_hook(data->win_ptr, 4, 1L << 2, &handle_mouse_down, data);
		mlx_hook(data->win_ptr, 5, 1L << 3, &handle_mouse_up, data);
		mlx_hook(data->win_ptr, 6, 1L << 6, &handle_mouse_move, data);
		mlx_loop(data->mlx_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
	}
	return (1);
}

int	render_menu(t_data *data)
{
	int x;
	int y;

	data->entry_img = mlx_xpm_file_to_image(data->mlx_ptr, "./sprites_xpm/jorge_gay.xpm", &x, &y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->entry_img, 0, 0);
	return (1);
}