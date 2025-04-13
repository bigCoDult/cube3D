/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:13:11 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/11 19:19:04 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endwith(char *str, char *end)
{
	int	len;
	int	str_i;
	int	end_i;

	if (str == NULL || end == NULL)
		return (0);
	len = ft_strlen(end);
	str_i = ft_strlen(str) - len;
	end_i = 0;
	if (str_i < 0)
		return (0);
	while (end[end_i])
	{
		if (str[str_i++] != end[end_i++])
			return (0);
	}
	return (1);
}
