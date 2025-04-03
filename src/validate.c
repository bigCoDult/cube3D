// #include <cub3d.h>
#include "../inc/cub3d.h"

static int	check_8way(t_total *total, int col, int row)
{
	if (col == 0 || row == 0 || col == total->parsed->max.col -1 || row == total->parsed->max.row - 1)
		return (0);
	if (total->parsed->map[col - 1][row] == ' ' || total->parsed->map[col + 1][row] == ' ' \
	|| total->parsed->map[col][row - 1] == ' ' || total->parsed->map[col][row + 1] == ' ' \
	|| total->parsed->map[col - 1][row - 1] == ' ' || total->parsed->map[col - 1][row + 1] == ' ' \
	|| total->parsed->map[col + 1][row - 1] == ' ' || total->parsed->map[col + 1][row + 1] == ' ')
		return (0);
	return (1);
}

static int	is_closed(t_total *total)
{
	int col;
	int row;
	col = 0;
	row = 0;
	while (total->parsed->map[col])
	{
		if (total->parsed->map[col][row] == '1' || total->parsed->map[col][row] == ' ')
			row++;
		if (total->parsed->map[col][row] == '\0')
		{
			row = 0;
			col++;
			continue;
		}
		if (total->parsed->map[col][row] == '0' || total->parsed->map[col][row] == 'N' \
		|| total->parsed->map[col][row] == 'S' || total->parsed->map[col][row] == 'E' \
		|| total->parsed->map[col][row] == 'W')
		{
			if (!check_8way(total, col, row))
				return (0);
			row++;
		}
	}
	return (1);
}

static int is_path(t_total *total)
{
	int fd_north;
	int fd_south;
	int fd_east;
	int fd_west;

	fd_north = open(total->parsed->extracted_str->north, O_RDONLY);
	fd_south = open(total->parsed->extracted_str->south, O_RDONLY);
	fd_east = open(total->parsed->extracted_str->east, O_RDONLY);
	fd_west = open(total->parsed->extracted_str->west, O_RDONLY);
	if (fd_north != -1)
		close(fd_north);
	if (fd_south != -1)
		close(fd_south);
	if (fd_east != -1)
		close(fd_east);
	if (fd_west != -1)
		close(fd_west);
	if (fd_north == -1 || fd_south == -1 || fd_east == -1 || fd_west == -1)
	{
		printf("invalid img path\n");
		return (0);
	}
	else
		return (1);
}

int	validate(t_total *total)
{
	if (!is_closed(total))
		printf("\nmap XXXXX\n\n");
	else if (!is_path(total))
		printf("\nimg path XXXXX\n\n");
	else
		return (1);
	return (0);

}