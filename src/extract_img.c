#include "../inc/cub3d.h"

int ft_atohex(char *hex)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (hex[i] != '\0')
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			result = result * 16 + (hex[i] - '0');
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			result = result * 16 + (hex[i] - 'A' + 10);
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			result = result * 16 + (hex[i] - 'a' + 10);
		i++;
	}
	return (result);
}

char	*dec_to_hex(char *dec)
{
	int		n;
	char	*hex;
	hex = malloc(sizeof(char) * 3);

	n = ft_atoi(dec);
	hex[0] = "0123456789ABCDEF"[n / 16];
	hex[1] = "0123456789ABCDEF"[n % 16];
	hex[2] = '\0';
	return (ft_strdup(hex));
}
char	*convert_rgb_to_hex(char *str)
{
	char **rgb;
	char *hex;

	rgb = ft_split(str, ',');
	hex = ft_calloc(sizeof(char), 7);
	// hex = join_s(hex, "0x");
	hex = join_s(hex, dec_to_hex(rgb[0]));
	hex = join_s(hex, dec_to_hex(rgb[1]));
	hex = join_s(hex, dec_to_hex(rgb[2]));
	return (ft_strdup(hex));
}
void extract_img(t_total *total)
{
	int width;
	int height;
	printf("ceiling	: %s\n", total->parsed->extracted_str->ceiling);
	printf("floor		: %s\n", total->parsed->extracted_str->floor);
	total->parsed->image_info = malloc(sizeof(t_image_info));
	total->parsed->image_info->ceiling = malloc(sizeof(char) * 9);
	total->parsed->image_info->floor = malloc(sizeof(char) * 9);
	total->parsed->image_info->ceiling = convert_rgb_to_hex(total->parsed->extracted_str->ceiling);
	total->parsed->image_info->floor = convert_rgb_to_hex(total->parsed->extracted_str->floor);
	printf("ceiling : %s\n", total->parsed->image_info->ceiling);
	printf("floor : %s\n", total->parsed->image_info->floor);
	printf("%d\n", ft_atohex(total->parsed->image_info->ceiling));
	printf("%d\n", ft_atohex(total->parsed->image_info->floor));
	width = 64;
	height = 64;
	total->parsed->image_info->north = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->north, &width, &height);
	total->parsed->image_info->south = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->south, &width, &height);
	total->parsed->image_info->west = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->west, &width, &height);
	total->parsed->image_info->east = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->east, &width, &height);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->north, 0, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->south, 64, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->west, 0, 64);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->east, 64, 64);
}
