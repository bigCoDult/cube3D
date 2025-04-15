/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:20:40 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:36:52 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_mem_tracker(t_total *total)
{
	total->mem_tracker = (t_mem_tracker *)malloc(sizeof(t_mem_tracker));
	if (!total->mem_tracker)
		return ;
	total->mem_tracker->head = NULL;
	total->mem_tracker->count = 0;
	total->mem_tracker->total_size = 0;
}

void	free_all_memory(t_total *total)
{
	t_mem_node	*current;
	t_mem_node	*next;
	int			freed_count;

	if (!total || !total->mem_tracker)
		return ;
	current = total->mem_tracker->head;
	freed_count = 0;
	while (current)
	{
		next = current->next;
		if (current->ptr)
		{
			free(current->ptr);
			freed_count++;
		}
		if (current->label)
			free(current->label);
		free(current);
		current = next;
	}
	total->mem_tracker->head = NULL;
	total->mem_tracker->count = 0;
	total->mem_tracker->total_size = 0;
}
