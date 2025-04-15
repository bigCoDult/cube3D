/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_atoitoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:11:20 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 14:11:20 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	cmp_atoitoa(char *origin)
{
	int		n;
	char	*str;
	int		result;

	n = ft_atoi(origin);
	str = ft_itoa(n);
	if (ft_strcmp(str, origin))
		result = 1;
	else
		result = 0;
	free(str);
	return (result);
}