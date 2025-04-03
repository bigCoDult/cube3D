#include "../inc/cub3d.h"

void print_parsed(t_total *total)
{
	printf("------------str start------------\n");
	printf("north: %s\n", total->parsed->extracted_str->north);
	printf("south: %s\n", total->parsed->extracted_str->south);
	printf("west: %s\n", total->parsed->extracted_str->west);
	printf("east: %s\n", total->parsed->extracted_str->east);
	printf("floor: %s\n", total->parsed->extracted_str->floor);
	printf("ceiling: %s\n", total->parsed->extracted_str->ceiling);
	printf("------------str end------------\n");
	
	printf("\n");
	
	int col = 0;
	printf("------------map start------------\n");
	while (total->parsed->map[col] != NULL)
	{
		printf("%s\n", total->parsed->map[col]);
		col++;
	}
	printf("------------map end------------\n");
	
	
	printf("\n");
	if (total->parsed->player->col != 0)
		printf("player coordinate: %c %d, %d\n", total->parsed->map[total->parsed->player->col][total->parsed->player->row], total->parsed->player->col, total->parsed->player->row);
	else
		printf("player not found\n");
	printf("\n");
}