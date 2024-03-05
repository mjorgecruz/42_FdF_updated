/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:20:08 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/05 12:04:39 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		creat_map(argv[1], &data);
		roid_open_window(&data);
	}
	else
		write(2, "Wrong format, please enter <./fdf ./path/file_map.fdf>\n", 55);
	exit (0);
}
