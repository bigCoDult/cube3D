#include "../../inc/cub3d.h"
// #include <cub3d.h>

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

static int	find_i_key(char *file, const char *key)
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
			return (i);
		i++;
	}
	return (-1);
}

static char	*extract_value(const char *key, char *file)
{
	int	i_key;
	int	i_start;
	int	i_end;

	i_key = 0;
	i_key = find_i_key(file, key);
	if (i_key == -1 \
		|| (i_key != 0 && (!is_space(file[i_key - 1]))) \
		|| !is_space(file[i_key + ft_strlen(key)]))
		return (NULL);
	i_start = i_key + ft_strlen(key);
	if (count_space(file + i_key + ft_strlen(key)) == 0 \
		|| count_space(file + i_key + ft_strlen(key)) == -1)
		return (NULL);
	i_start += count_space(file + i_key + ft_strlen(key));
	i_end = i_start;
	while (file[i_end] && !is_space(file[i_end]))
		i_end++;
	return (ft_strndup(file + i_start, i_end - i_start));
}

static int	free_fail(char *file, t_extracted_str *extracted_str)
{
	if (!extracted_str->north || !extracted_str->south \
		|| !extracted_str->west || !extracted_str->east \
		|| !extracted_str->floor || !extracted_str->ceiling)
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
		free(extracted_str);
		free(file);
		return (-1);
	}
}

int	extract_str(int fd, t_total *total)
{
	char	*file;

	file = file_to_str(fd);
	if (!file)
	{
		free(total->parsed->extracted_str);
		free(total->parsed);
		return (-1);
	}
	total->parsed->extracted_str->north = extract_value("NO", file);
	total->parsed->extracted_str->south = extract_value("SO", file);
	total->parsed->extracted_str->west = extract_value("WE", file);
	total->parsed->extracted_str->east = extract_value("EA", file);
	total->parsed->extracted_str->floor = extract_value("F", file);
	total->parsed->extracted_str->ceiling = extract_value("C", file);
	free_fail(file, total->parsed->extracted_str);
	extract_map(file, total);
	free(file);
	return (0);
}
