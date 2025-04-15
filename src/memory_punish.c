/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_punish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 05:03:28 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:39:19 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_mem_node	*find_memory_node(t_mem_tracker *tracker, void *ptr)
{
	t_mem_node	*current;

	current = tracker->head;
	while (current)
	{
		if (current->ptr == ptr)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	remove_memory_node(
	t_mem_tracker *tracker, t_mem_node *node, t_mem_node *prev)
{
	if (prev)
		prev->next = node->next;
	else
		tracker->head = node->next;
	tracker->count--;
	tracker->total_size -= node->size;
}

static t_mem_node	*find_previous_node(
	t_mem_tracker *tracker, t_mem_node *target)
{
	t_mem_node	*current;

	if (tracker->head == target)
		return (NULL);
	current = tracker->head;
	while (current && current->next != target)
		current = current->next;
	return (current);
}

void	cleanup_memory_node(t_mem_node *node)
{
	free(node->label);
	free(node->ptr);
	free(node);
}

void	tracked_free(t_total *total, void *ptr)
{
	t_mem_node	*node;
	t_mem_node	*prev;

	if (!ptr || !total->mem_tracker)
		return ;
	node = find_memory_node(total->mem_tracker, ptr);
	if (node)
	{
		prev = find_previous_node(total->mem_tracker, node);
		remove_memory_node(total->mem_tracker, node, prev);
		cleanup_memory_node(node);
	}
	else
		free(ptr);
}
