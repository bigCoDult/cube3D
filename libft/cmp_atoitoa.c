/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_atoitoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:11:20 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 14:28:25 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	cmp_atoitoa(char *origin)
{
	int		n;
	char	*str;
	int		result;

	n = ft_atoi(origin);
	str = ft_itoa(n);
	if (ft_strcmp(str, origin) == 0)
		result = 1;
	else
		result = 0;
	free(str);
	return (result);
}
