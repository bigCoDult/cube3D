/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_track.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:59:43 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:36:48 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_mem_node	*create_mem_node(void *ptr, size_t size, char *label)
{
	t_mem_node	*new_node;

	new_node = (t_mem_node *)malloc(sizeof(t_mem_node));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->size = size;
	new_node->label = ft_strdup(label);
	new_node->next = NULL;
	return (new_node);
}

static void	add_node_to_tracker(t_mem_tracker *tracker, t_mem_node *node)
{
	if (!tracker->head)
		tracker->head = node;
	else
	{
		node->next = tracker->head;
		tracker->head = node;
	}
	tracker->count++;
	tracker->total_size += node->size;
}

static void	*handle_allocation_failure(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	*tracked_malloc(t_total *total, size_t size, char *label)
{
	void		*ptr;
	t_mem_node	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = create_mem_node(ptr, size, label);
	if (!new_node)
		return (handle_allocation_failure(ptr));
	add_node_to_tracker(total->mem_tracker, new_node);
	return (ptr);
}
