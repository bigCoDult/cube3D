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

int	validate(t_total *total)
{
	if (!is_closed(total))
	{
		printf("\nmap XXXXX\n\n");
		return (0);
	}
	printf("\nmap OOOOO\n\n");
	return (1);

}