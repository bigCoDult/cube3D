/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:20:40 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 05:03:34 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 메모리 추적 초기화
void	init_mem_tracker(t_total *total)
{
	total->mem_tracker = (t_mem_tracker *)malloc(sizeof(t_mem_tracker));
	if (!total->mem_tracker)
		return ;
	total->mem_tracker->head = NULL;
	total->mem_tracker->count = 0;
	total->mem_tracker->total_size = 0;
}

// 할당된 메모리 상태 출력 (디버깅용)
void	print_mem_status(t_total *total)
{
	t_mem_node	*current;
	int			i;

	if (!total || !total->mem_tracker)
		return ;
	printf("\n===== 메모리 할당 상태 =====\n");
	printf("할당된 블록 수: %d\n", total->mem_tracker->count);
	printf("총 할당 크기: %zu 바이트\n", total->mem_tracker->total_size);
	current = total->mem_tracker->head;
	i = 1;
	if (!current)
		printf("할당된 메모리가 없습니다.\n");
	while (current)
	{
		printf("\n블록 #%d:\n", i++);
		printf("  주소: %p\n", current->ptr);
		printf("  크기: %zu 바이트\n", current->size);
		if (current->label)
			printf("  설명: %s\n", current->label);
		else
			printf("  설명: 없음\n");
		current = current->next;
	}
	printf("\n============================\n");
}

// 모든 할당된 메모리 해제
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
	printf("총 %d개의 메모리 블록을 해제했습니다.\n", freed_count);
}
