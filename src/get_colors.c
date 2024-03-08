/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:22:42 by ruiolive          #+#    #+#             */
/*   Updated: 2023/12/07 10:48:58 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	atoi_base(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] != ',')
		i++;
	i += 2;
	while (str[i])
	{
		num = num * 16 + get_pos(str[i]);
		i++;
	}
	return (num);
}

int	get_pos(char c)
{
	int		i;
	char	*str;
	char	*str1;

	i = 0;
	str = ft_strdup("0123456789abcdef");
	str1 = ft_strdup("0123456789ABCDEF");
	while (str[i] != c && str1[i] != c && str[i])
		i++;
	free(str);
	free(str1);
	return (i);
}

int	check_for_colors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			return (1);
		i++;
	}
	return (0);
}
