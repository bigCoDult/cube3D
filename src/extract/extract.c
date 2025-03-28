#include "../../inc/cub3d.h"
// #include <cub3d.h>


static int	count_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int find_i_key(char *file, const char *key)
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

char *extract_value(const char *key, char *file)
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
	if(count_space(file + i_key + ft_strlen(key)) == 0 || count_space(file + i_key + ft_strlen(key)) == -1)
		return (NULL);
	i_start += count_space(file + i_key + ft_strlen(key));
	i_end = i_start;
	while (file[i_end] && !is_space(file[i_end]))
		i_end++;
	return (ft_strndup(file + i_start, i_end - i_start));
}









int main(void)
{
	t_total *total;
	total = (t_total *)ft_calloc(sizeof(t_total), 1);
	total->parsed = malloc(sizeof(t_parsed));
	total->parsed->extracted_str = malloc(sizeof(t_extracted_str));
	int fd = open("../../img/map.cub", O_RDONLY);
	char *file = file_to_str(fd);
	total->parsed->extracted_str->north = extract_value("NO", file);
	total->parsed->extracted_str->south = extract_value("SO", file);
	total->parsed->extracted_str->west = extract_value("WE", file);
	total->parsed->extracted_str->east = extract_value("EA", file);
	total->parsed->extracted_str->floor = extract_value("F", file);
	total->parsed->extracted_str->ceiling = extract_value("C", file);
	
	// printf("%s\n\n\n", file);


	printf("north: %s\n", total->parsed->extracted_str->north);
	printf("south: %s\n", total->parsed->extracted_str->south);
	printf("west: %s\n", total->parsed->extracted_str->west);
	printf("east: %s\n", total->parsed->extracted_str->east);
	printf("floor: %s\n", total->parsed->extracted_str->floor);
	printf("ceiling: %s\n", total->parsed->extracted_str->ceiling);
	
	
	
	
	free(file);
	free(total->parsed->extracted_str->north);
	free(total->parsed->extracted_str->south);
	free(total->parsed->extracted_str->west);
	free(total->parsed->extracted_str->east);
	free(total->parsed->extracted_str->floor);
	free(total->parsed->extracted_str->ceiling);
	free(total->parsed->extracted_str);
	free(total->parsed);
	free(total);
	close(fd);
	return (0);
}