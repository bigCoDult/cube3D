#include "../../inc/cub3d.h"

int	main(void)
{
	t_total	*total;
	int		fd;

	fd = open("../../img/map.cub", O_RDONLY);
	total = (t_total *)ft_calloc(sizeof(t_total), 1);
	total->parsed = malloc(sizeof(t_parsed));
	total->parsed->extracted_str = malloc(sizeof(t_extracted_str));
	if (extract_str(fd, total) == -1)
	{
		// free(total->parsed->extracted_str);
		free(total->parsed);
		free(total);
		close(fd);
		return (-1);
	}
	printf("------------str start------------\n");
	printf("north: %s\n", total->parsed->extracted_str->north);
	printf("south: %s\n", total->parsed->extracted_str->south);
	printf("west: %s\n", total->parsed->extracted_str->west);
	printf("east: %s\n", total->parsed->extracted_str->east);
	printf("floor: %s\n", total->parsed->extracted_str->floor);
	printf("ceiling: %s\n", total->parsed->extracted_str->ceiling);
	printf("------------str end------------\n");
	
	printf("\n\n\n");
	
	int row = 0;
	int col = 0;
	printf("------------map start------------\n");
	while (total->parsed->map[col] != NULL)
	{
		printf("%s\n", total->parsed->map[col]);
		col++;
	}
	printf("------------map end------------\n");
	col = 0;
	while (total->parsed->map[col] != NULL)
	{
		free(total->parsed->map[col]);
		col++;
	}
	free(total->parsed->map);
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
