#include "../../inc/cub3d.h"
// #include <cub3d.h>

char	*join_s_till_c(char *s1, char *s2, char c)
{
	char	*out_s;
	int		i_in_s1;
	int		i_in_s2;
	int		i_out;

	i_in_s1 = 0;
	i_in_s2 = 0;
	i_out = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	out_s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (out_s == NULL)
		return (NULL);
	while (s1 && s1[i_in_s1] != c)
		out_s[i_out++] = s1[i_in_s1++];
	while (s2 && s2[i_in_s2] != c)
		out_s[i_out++] = s2[i_in_s2++];
	out_s[i_out] = '\0';
	return (out_s);
}

char	*join_s(char *st_s, char *buf)
{
	char	*new_line;

	new_line = join_s_till_c(st_s, buf, '\0');
	if (new_line == NULL)
		return (NULL);
	free(st_s);
	return (new_line);
}

char *file_to_str(int fd)
{
	char	buf[6];
	int		read_return;
	int		index;
	char	*result;
	read_return = 5;
	index = 0;
	result = malloc(sizeof(char) * 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	while (read_return == 5)
	{
		read_return = read(fd, buf, 5);
		buf[read_return] = '\0';
		result = join_s(result, buf);
	}
	return (result);
}


char *get_key_value(const char *key, char *file)
{
	int i;
	i = 0;
	ft_strcmp(file, key)
}









int main(void)
{
	t_total *total;
	total = (t_total *)ft_calloc(sizeof(t_total), 1);
	int fd = open("../../img/map.cub", O_RDONLY);
	char *file = file_to_str(fd);
	char *north_path = get_key_value("NO", file);
	char *south_path = get_key_value("SO", file);
	char *west_path = get_key_value("WE", file);
	char *east_path = get_key_value("EA", file);
	char *floor_color = get_key_value("F", file);
	char *ceiling_color = get_key_value("C", file);
	
	
	
	
	
	
	
	printf("%s\n", file);
	free(file);
	close(fd);
	return (0);
}