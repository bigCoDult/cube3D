/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_no_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:57:52 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 14:57:57 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_on_keylist(char *file, int i)
{
	if (file[i] == '\0' || file[i + 1] == '\0')
		return (0);
	else if (file[i] == 'N' && file[i + 1] == 'O')
		return (2);
	else if (file[i] == 'S' && file[i + 1] == 'O')
		return (2);
	else if (file[i] == 'E' && file[i + 1] == 'A')
		return (2);
	else if (file[i] == 'W' && file[i + 1] == 'E')
		return (2);
	else if (file[i] == 'F' && file[i + 1] == ' ')
		return (1);
	else if (file[i] == 'C' && file[i + 1] == ' ')
		return (1);
	else
		return (0);
}

static int	skip_value(char *file, int i)
{
	if (file[i] != ' ')
		return (0);
	while ((file[i]) == ' ')
		i++;
	if (is_whitespace(file[i]))
		return (0);
	while (!is_whitespace(file[i]))
		i++;
	return (i);
}

int	is_no_trash(t_total *total)
{
	char	*file;
	int		i;
	int		map_start_i;
	int		skip;

	file = total->parsed->extracted_str->file;
	i = 0;
	map_start_i = find_map_start(file, 0);
	while (i < map_start_i)
	{
		while (is_whitespace(file[i]))
			i++;
		if (i >= map_start_i)
			break ;
		if (is_on_keylist(file, i))
			i += is_on_keylist(file, i);
		else
			return (0);
		skip = skip_value(file, i);
		if (skip)
			i = skip;
		else
			return (0);
	}
	return (1);
}
