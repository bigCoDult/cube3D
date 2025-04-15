/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:41:21 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 15:49:40 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	count_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i]) == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
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

static char	*extract_value(const char *key, char *file)
{
	int	i_key;
	int	i_start;
	int	i_end;
	int	i_dup;

	i_key = find_i_key(file, key);
	if (i_key == -1)
		return (NULL);
	i_start = i_key + ft_strlen(key);
	i_dup = find_i_key(file + i_start, key);
	if (i_dup != -1)
	{
		write(2, "Error\nkeyvalue duplicated\n", 26);
		return (NULL);
	}
	if (count_space(file + i_key + ft_strlen(key)) == 0 || \
	count_space(file + i_key + ft_strlen(key)) == -1)
		return (NULL);
	i_start += count_space(file + i_key + ft_strlen(key));
	i_end = i_start;
	while (file[i_end] && !is_whitespace(file[i_end]))
		i_end++;
	return (ft_strndup(file + i_start, i_end - i_start));
}

static void	do_extract_nsew(char *file, t_total *total)
{
	total->parsed->extracted_str->north = extract_value("NO", file);
	total->parsed->extracted_str->south = extract_value("SO", file);
	total->parsed->extracted_str->west = extract_value("WE", file);
	total->parsed->extracted_str->east = extract_value("EA", file);
	total->parsed->extracted_str->floor = extract_value("F", file);
	total->parsed->extracted_str->ceiling = extract_value("C", file);
}

int	extract_str(int fd, t_total *total)
{
	char	*file;

	total->parsed = (t_parsed *)malloc(sizeof(t_parsed));
	total->parsed->extracted_str = malloc(sizeof(t_extracted_str));
	total->parsed->player = (t_cordi *)ft_calloc(sizeof(t_cordi), 1);
	total->parsed->extracted_str->file = file_to_str(fd);
	file = total->parsed->extracted_str->file;
	if (!file)
	{
		free(total->parsed->extracted_str);
		free(total->parsed);
		return (-1);
	}
	do_extract_nsew(file, total);
	if (if_failed_free(total))
	{
		free(total->mem_tracker);
		free(total);
		return (-1);
	}
	extract_map(file, total);
	return (1);
}
