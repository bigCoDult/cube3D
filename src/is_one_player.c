
#include "cub3d.h"

int is_one_player(t_total *total)
{
	int i;
	int k;
	int player_count;

	i = 0;
	player_count = 0;
	while (total->parsed->map[i])
	{
		k = 0;
		while (total->parsed->map[i][k])
		{
			if (total->parsed->map[i][k] == 'N' || total->parsed->map[i][k] == 'S' ||
			total->parsed->map[i][k] == 'E' || total->parsed->map[i][k] == 'W')
				player_count++;
			k++;
		}
		i++;
	}
	return (player_count == 1);
}
