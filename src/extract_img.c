/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:32:34 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 17:46:06 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atohex(char *hex)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (hex[i] != '\0')
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			result = result * 16 + (hex[i] - '0');
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			result = result * 16 + (hex[i] - 'A' + 10);
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			result = result * 16 + (hex[i] - 'a' + 10);
		i++;
	}
	return (result);
}

static char	*dec_to_hex(char *dec)
{
	int		n;
	char	*hex;

	hex = malloc(sizeof(char) * 3);
	n = ft_atoi(dec);
	hex[0] = "0123456789ABCDEF"[n / 16];
	hex[1] = "0123456789ABCDEF"[n % 16];
	hex[2] = '\0';
	return (hex);
}

static char	*convert_rgb_to_hex(char *str)
{
	char	**rgb;
	char	*hex;
	char	*tmp;

	rgb = ft_split(str, ',');
	hex = ft_calloc(sizeof(char), 1);
	tmp = dec_to_hex(rgb[0]);
	hex = join_s(hex, tmp);
	free(tmp);
	tmp = dec_to_hex(rgb[1]);
	hex = join_s(hex, tmp);
	free(tmp);
	tmp = dec_to_hex(rgb[2]);
	hex = join_s(hex, tmp);
	free(tmp);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (hex);
}

void	extract_img(t_total *total)
{
	t_cordi	length;

	length = (t_cordi){64, 64};
	total->parsed->image_info = malloc(sizeof(t_image_info));
	total->parsed->image_info->ceiling = \
		convert_rgb_to_hex(total->parsed->extracted_str->ceiling);
	total->parsed->image_info->floor = \
		convert_rgb_to_hex(total->parsed->extracted_str->floor);
	total->parsed->image_info->north = mlx_xpm_file_to_image(total->mlx->\
		mlx_ptr, total->parsed->extracted_str->north, &length.col, &length.row);
	total->parsed->image_info->south = mlx_xpm_file_to_image(total->mlx->\
		mlx_ptr, total->parsed->extracted_str->south, &length.col, &length.row);
	total->parsed->image_info->west = mlx_xpm_file_to_image(total->mlx->\
		mlx_ptr, total->parsed->extracted_str->west, &length.col, &length.row);
	total->parsed->image_info->east = mlx_xpm_file_to_image(total->mlx->\
		mlx_ptr, total->parsed->extracted_str->east, &length.col, &length.row);
}

int	find_i_key(char *file, const char *key)
{
	int	i;
	int	k;

	i = 0;
	while (file[i])
	{
		k = 0;
		while (key[k] && key[k] == file[i + k])
			k++;
		if (key[k] == '\0')
		{
			if (i == 0 || (is_whitespace(file[i - 1]) && file[i + k] == ' '))
				return (i);
		}
		i++;
	}
	return (-1);
}
