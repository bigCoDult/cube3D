/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:13:11 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/09 21:13:12 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endwith(char *str, char *end)
{
	char	*tmp;

	if (str == NULL || end == NULL)
		return (0);
	tmp = ft_strnstr(str, end, ft_strlen(str));
	if (tmp[ft_strlen(end) - 1] == '\0')
		return (1);
	else
		return (0);
}
