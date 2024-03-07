/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:26:16 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/06 13:18:52 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	handle_mouse_move(int x, int y, t_data *data)
{
	if (data->button == 1 && x > 235)
	{
		data->hor += (x - data->prev_x);
		data->hey += (y - data->prev_y);
		data->prev_x = x;
		data->prev_y = y;
	}
	else if (data->button == 2 && x > 235)
	{
		data->angle_z -= (x - data->prev_x - (y - data->prev_y)) * 0.002;
		data->prev_x = x;
		data->prev_y = y;
	}
	else if (data->button == 3 && x > 235)
	{
		data->angle_x -= (y - data->prev_y) * 0.002;
		data->angle_y += (x - data->prev_x) * 0.002;
		data->prev_x = x;
		data->prev_y = y;
	}
	else if (x > 215 && x < 230 && y > 210 && y < 225 && strcmp(data->menu_file, "./sprites_xpm/x_right.xpm"))
		data->menu_file = "./sprites_xpm/x_right.xpm";
	else if (x > 170 && x < 185 && y > 210 && y < 225 && strcmp(data->menu_file, "./sprites_xpm/x_left.xpm"))
		data->menu_file = "./sprites_xpm/x_left.xpm";
	else if (x > 215 && x < 230 && y > 245 && y < 260 && strcmp(data->menu_file, "./sprites_xpm/y_right.xpm"))
		data->menu_file = "./sprites_xpm/y_right.xpm";
	else if (x > 170 && x < 185 && y > 245 && y < 260 && strcmp(data->menu_file, "./sprites_xpm/y_left.xpm"))
		data->menu_file = "./sprites_xpm/y_left.xpm";
	else if (x > 215 && x < 230 && y > 278 && y < 293 && strcmp(data->menu_file, "./sprites_xpm/z_right.xpm"))
		data->menu_file = "./sprites_xpm/z_right.xpm";
	else if (x > 170 && x < 185 && y > 278 && y < 293 && strcmp(data->menu_file, "./sprites_xpm/z_left.xpm"))
		data->menu_file = "./sprites_xpm/z_left.xpm";
	else if (x > 215 && x < 230 && y > 370 && y < 385 && strcmp(data->menu_file, "./sprites_xpm/zoom_right.xpm"))
		data->menu_file = "./sprites_xpm/zoom_right.xpm";
	else if (x > 170 && x < 185 && y > 370 && y < 385 && strcmp(data->menu_file, "./sprites_xpm/zoom_left.xpm"))
		data->menu_file = "./sprites_xpm/zoom_left.xpm";
	else if (x > 215 && x < 230 && y > 461 && y < 476 && strcmp(data->menu_file, "./sprites_xpm/height_right.xpm"))
		data->menu_file = "./sprites_xpm/height_right.xpm";
	else if (x > 170 && x < 185 && y > 461 && y < 476 && strcmp(data->menu_file, "./sprites_xpm/height_left.xpm"))
		data->menu_file = "./sprites_xpm/height_left.xpm";
	else if (x > 215 && x < 230 && y > 496 && y < 511 && strcmp(data->menu_file, "./sprites_xpm/move_x_right.xpm"))
		data->menu_file = "./sprites_xpm/move_x_right.xpm";
	else if (x > 170 && x < 185 && y > 496 && y < 511 && strcmp(data->menu_file, "./sprites_xpm/move_x_left.xpm"))
		data->menu_file = "./sprites_xpm/move_x_left.xpm";
	else if (x > 215 && x < 230 && y > 529 && y < 544 && strcmp(data->menu_file, "./sprites_xpm/move_y_right.xpm"))
		data->menu_file = "./sprites_xpm/move_y_right.xpm";
	else if (x > 170 && x < 185 && y > 529 && y < 544 && strcmp(data->menu_file, "./sprites_xpm/move_y_left.xpm"))
		data->menu_file = "./sprites_xpm/move_y_left.xpm";
	else if (x > 60 && x < 170 && y > 725 && y < 765 && strcmp(data->menu_file, "./sprites_xpm/menu_reset.xpm"))
		data->menu_file = "./sprites_xpm/menu_reset.xpm";
	else if (x > 60 && x < 170 && y > 775 && y < 805 && strcmp(data->menu_file, "./sprites_xpm/menu_exit.xpm"))
		data->menu_file = "./sprites_xpm/menu_exit.xpm";
	else if (strcmp(data->menu_file, "./sprites_xpm/menu.xpm"))
	{
		if ((check_if_between(60, 170, x) && (check_if_between(725, 765, y) || check_if_between(775, 805, y))) 
		|| ((check_if_between(170, 185, x) || check_if_between(215, 230, x)) && 
		(check_if_between(210, 225, y) || check_if_between(245, 260, y) || check_if_between(278, 293, y) 
		|| check_if_between(370, 385, y) || check_if_between(461, 476, y) || check_if_between(496, 511, y) 
		|| check_if_between(529, 544, y))))
			return (0);
		data->menu_file = "./sprites_xpm/menu.xpm";
	}
	else
		return (0);
	free_info(data);
	if (data->render_status == 2)
		roid_render_map(data);
	else
		render_map(data);
	return (0);
}

int	handle_entry_mouse_move(int x, int y, t_data *data)
{
	if (x > 790 && x < 1128 && y > 750 && y < 820 && strcmp(data->menu_entry_file, "./sprites_xpm/menu_start_exit.xpm"))
		data->menu_entry_file = "./sprites_xpm/menu_start_exit.xpm";
	else if (x > 790 && x < 1128 && y > 650 && y < 712 && strcmp(data->menu_entry_file, "./sprites_xpm/menu_start_choose.xpm"))
		data->menu_entry_file = "./sprites_xpm/menu_start_choose.xpm";
	else if (strcmp(data->menu_entry_file, "./sprites_xpm/menu_start.xpm"))
	{
		if (check_if_between(790, 1128, x) && (check_if_between(750, 820, y) || check_if_between(650, 712, y)))
			return (0);
		data->menu_entry_file = "./sprites_xpm/menu_start.xpm";
	}
	else
		return (0);
	mlx_destroy_image(data->mlx_ptr, data->entry_img);
	render_menu(data);
	return (0);
}

int	handle_choose_map_mouse_move(int x, int y, t_data *data)
{
	if (x > 790 && x < 1128 && y > 868 && y < 933 && strcmp(data->choose_file, "./sprites_xpm/choose_map_back.xpm"))
		data->choose_file = "./sprites_xpm/choose_map_back.xpm";
	else if (x > 145 && x < 480 && y > 373 && y < 432 && strcmp(data->choose_file, "./sprites_xpm/42_map.xpm"))
		data->choose_file = "./sprites_xpm/42_map.xpm";
	else if (x > 585 && x < 920 && y > 373 && y < 432 && strcmp(data->choose_file, "./sprites_xpm/t1_map.xpm"))
		data->choose_file = "./sprites_xpm/t1_map.xpm";
	else if (x > 1025 && x < 1360 && y > 373 && y < 432 && strcmp(data->choose_file, "./sprites_xpm/t2_map.xpm"))
		data->choose_file = "./sprites_xpm/t2_map.xpm";
	else if (x > 1465 && x < 1800 && y > 373 && y < 432 && strcmp(data->choose_file, "./sprites_xpm/pyramid_map.xpm"))
		data->choose_file = "./sprites_xpm/pyramid_map.xpm";
	else if (x > 145 && x < 480 && y > 513 && y < 572 && strcmp(data->choose_file, "./sprites_xpm/fractal_map.xpm"))
		data->choose_file = "./sprites_xpm/fractal_map.xpm";
	else if (x > 585 && x < 920 && y > 513 && y < 572 && strcmp(data->choose_file, "./sprites_xpm/world_map.xpm"))
		data->choose_file = "./sprites_xpm/world_map.xpm";
	else if (x > 1025 && x < 1360 && y > 513 && y < 572 && strcmp(data->choose_file, "./sprites_xpm/julia_map.xpm"))
		data->choose_file = "./sprites_xpm/julia_map.xpm";
	else if (x > 1465 && x < 1800 && y > 513 && y < 572 && strcmp(data->choose_file, "./sprites_xpm/mars_map.xpm"))
		data->choose_file = "./sprites_xpm/mars_map.xpm";
	else if (strcmp(data->choose_file, "./sprites_xpm/choose_map.xpm"))
	{
		if((check_if_between(790, 1128, x) && check_if_between(868, 933, y)) || 
		((check_if_between(145, 480, x) || check_if_between(585, 920, x) || check_if_between(1025, 1360, x) || check_if_between(1465, 1800, x)) 
		&& (check_if_between(373, 432, y) || check_if_between(513, 572, y))))
			return (0);
		data->choose_file = "./sprites_xpm/choose_map.xpm";
	}
	else
		return (0);
	mlx_destroy_image(data->mlx_ptr, data->choose_img);
	render_choose_menu(data);
	return (0);
}

int	handle_mouse_down(int button, int x, int y, t_data *data)
{
	if (x > 60 && x < 170 && y > 775 && y < 805 && button == 1)
	{
		free_info(data);
		ft_free_map(data);
		data->menu_entry_file = "./sprites_xpm/menu_start.xpm";
		data->choose_file = "./sprites_xpm/choose_map.xpm";
		open_window(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 210 && y < 225)
	{
		free_info(data);
		data->angle_x += 0.1;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 210 && y < 225)
	{
		free_info(data);
		data->angle_x -= 0.1;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 245 && y < 260)
	{
		free_info(data);
		data->angle_y += 0.1;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 245 && y < 260)
	{
		free_info(data);
		data->angle_y -= 0.1;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 278 && y < 293)
	{
		free_info(data);
		data->angle_z += 0.1;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 278 && y < 293)
	{
		free_info(data);
		data->angle_z -= 0.1;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 370 && y < 385)
	{
		free_info(data);
		if (data->zoom < 150)
			data->zoom *= 1.2;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 370 && y < 385)
	{
		free_info(data);
		if (data->zoom > 3)
			data->zoom /= 1.2;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 461 && y < 476)
	{
		free_info(data);
		increase_z(data);
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 461 && y < 476)
	{
		free_info(data);
		decrease_z(data);
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 496 && y < 511)
	{
		free_info(data);
		data->hor += 5;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 496 && y < 511)
	{
		free_info(data);
		data->hor -= 5;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 215 && x < 230 && y > 529 && y < 544)
	{
		free_info(data);
		data->hey += 5;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 170 && x < 185 && y > 529 && y < 544)
	{
		free_info(data);
		data->hey -= 5;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 && x > 60 && x < 170 && y > 725 && y < 765)
	{
		free_info(data);
		data->zoom = 20;
		data->hor = (WIDTH - 200) / 2;
		data->hey = HEIGHT / 2;
		data->angle_x = 0.567890;
		data->angle_y = -0.012300;
		data->angle_z = 0.743534;
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 4 && x > 235)
	{
		if (data->zoom < 150)
			data->zoom *= 1.5;
		free_info(data);
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 5 && x > 235)
	{
		if (data->zoom > 3)
			data->zoom /= 1.5;
		free_info(data);
		if (data->render_status == 2)
			roid_render_map(data);
		else
			render_map(data);
	}
	else if (button == 1 || button == 2 || button == 3)
	{
		data->prev_x = x;
		data->prev_y = y;
		data->button = button;
	}
	return (0);
}

int	handle_entry_mouse_down(int button, int x, int y, t_data *data)
{
	if (x > 790 && x < 1128 && y > 750 && y < 820 && button == 1)
	{
		mlx_destroy_image(data->mlx_ptr, data->entry_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
		exit(1);
	}
	else if (x > 790 && x < 1128 && y > 650 && y < 712 && button == 1)
	{
		mlx_destroy_image(data->mlx_ptr, data->entry_img);
		render_choose_menu(data);
		mlx_hook(data->win_ptr, DestroyNotify, NoEventMask, &handle_menu_choose_close, data);
		mlx_hook(data->win_ptr, 4, 1L << 2, &handle_choose_map_mouse_down, data);
		mlx_hook(data->win_ptr, 5, 1L << 3, &handle_choose_map_mouse_up, data);
		mlx_hook(data->win_ptr, 6, 1L << 6, &handle_choose_map_mouse_move, data);
		mlx_loop(data->mlx_ptr);
	}
	return (0);
}

int	handle_choose_map_mouse_down(int button, int x, int y, t_data *data)
{
	if (x > 790 && x < 1128 && y > 868 && y < 933 && button == 1)
	{
		mlx_destroy_image(data->mlx_ptr, data->choose_img);
		data->menu_entry_file = "./sprites_xpm/menu_start.xpm";
		data->choose_file = "./sprites_xpm/choose_map.xpm";
		open_window(data);
	}
	else if (x > 145 && x < 480 && y > 373 && y < 432 && button == 1)
		data->map_to_render = "./maps/42.fdf";
	else if (x > 585 && x < 920 && y > 373 && y < 432 && button == 1)
		data->map_to_render = "./maps/t1.fdf";
	else if (x > 1025 && x < 1360 && y > 373 && y < 432 && button == 1)
		data->map_to_render = "./maps/t2.fdf";
	else if (x > 1465 && x < 1800 && y > 373 && y < 432 && button == 1)
		data->map_to_render = "./maps/pyramide.fdf";
	else if (x > 145 && x < 480 && y > 513 && y < 572 && button == 1)
		data->map_to_render = "./maps/fractal.fdf";
	else if (x > 585 && x < 920 && y > 513 && y < 572 && button == 1)
		data->map_to_render = "./maps/world.fdf";
	else if (x > 1025 && x < 1360 && y > 513 && y < 572 && button == 1)
		data->map_to_render = "./maps/julia.fdf";
	else if (x > 1465 && x < 1800 && y > 513 && y < 572 && button == 1)
		data->map_to_render = "./maps/mars.fdf";
	else
		return (0);
	init_data(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->choose_img);
	render_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, NoEventMask, &handle_close, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, &handle_mouse_down, data);
	mlx_hook(data->win_ptr, 5, 1L << 3, &handle_mouse_up, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, &handle_mouse_move, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	handle_mouse_up(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1 || button == 2 || button == 3)
		data->button = 0;
	return (0);
}

int	handle_entry_mouse_up(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1 || button == 2 || button == 3)
		data->button = 0;
	return (0);
}

int	handle_choose_map_mouse_up(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1 || button == 2 || button == 3)
		data->button = 0;
	return (0);
}

void	free_info(t_data *data)
{
	free(data->info.angle_x);
	free(data->info.angle_y);
	free(data->info.angle_z);
	free(data->info.zoom);
	free(data->info.high);
	free(data->info.horizontal);
	free(data->info.Vertical);
	free(data->info.color_rad);
	mlx_destroy_image(data->mlx_ptr, data->menu_img);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
}

int	check_if_between(int begin, int end, int num_to_check)
{
	if (num_to_check > begin && num_to_check < end)
		return (1);
	return (0);
}
