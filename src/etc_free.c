/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:05:06 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 15:11:52 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	free_this_failed(t_total *total)
{
	free(total->parsed->extracted_str->file);
	free(total->parsed->extracted_str);
	free(total->parsed->player);
	free(total->parsed);
	return (1);
}

int	if_failed_free(t_total *total)
{
	t_extracted_str	*extracted_str;

	extracted_str = total->parsed->extracted_str;
	if (!extracted_str->north || !extracted_str->south || \
	!extracted_str->west || !extracted_str->east || \
	!extracted_str->floor || !extracted_str->ceiling)
	{
		if (extracted_str->north)
			free(extracted_str->north);
		if (extracted_str->south)
			free(extracted_str->south);
		if (extracted_str->west)
			free(extracted_str->west);
		if (extracted_str->east)
			free(extracted_str->east);
		if (extracted_str->floor)
			free(extracted_str->floor);
		if (extracted_str->ceiling)
			free(extracted_str->ceiling);
		free_this_failed(total);
		return (1);
	}
	return (0);
}
