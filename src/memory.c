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

// 메모리 할당 및 추적 함수
void	*tracked_malloc(t_total *total, size_t size, char *label)
{
	void		*ptr;
	t_mem_node	*new_node;

	// 일반 malloc으로 메모리 할당
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	// 메모리 추적 노드 생성
	new_node = (t_mem_node *)malloc(sizeof(t_mem_node));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	// 노드 정보 설정
	new_node->ptr = ptr;
	new_node->size = size;
	new_node->label = ft_strdup(label); // 레이블 복사
	new_node->next = NULL;
	// 연결 리스트에 노드 추가
	if (!total->mem_tracker->head)
		total->mem_tracker->head = new_node;
	else
	{
		new_node->next = total->mem_tracker->head;
		total->mem_tracker->head = new_node;
	}
	// 통계 업데이트
	total->mem_tracker->count++;
	total->mem_tracker->total_size += size;
	return (ptr);
}

// 메모리 해제 함수
void	tracked_free(t_total *total, void *ptr)
{
	t_mem_node	*current;
	t_mem_node	*prev;

	if (!ptr || !total->mem_tracker)
		return ;
	current = total->mem_tracker->head;
	prev = NULL;
	// 리스트에서 노드 찾기
	while (current)
	{
		if (current->ptr == ptr)
		{
			// 노드 연결 리스트에서 제거
			if (prev)
				prev->next = current->next;
			else
				total->mem_tracker->head = current->next;
			// 통계 업데이트
			total->mem_tracker->count--;
			total->mem_tracker->total_size -= current->size;
			// 메모리 해제
			free(current->label);
			free(ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	// 추적되지 않은 메모리 해제 시도 (경고 출력 가능)
	free(ptr);
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
	// 모든 노드를 순회하며 메모리 해제
	while (current)
	{
		next = current->next;
		// 할당된 메모리 해제
		if (current->ptr)
		{
			free(current->ptr);
			freed_count++;
		}
		// 레이블 해제
		if (current->label)
			free(current->label);
		// 노드 자체 해제
		free(current);
		current = next;
	}
	// 메모리 추적기 초기화
	total->mem_tracker->head = NULL;
	total->mem_tracker->count = 0;
	total->mem_tracker->total_size = 0;
	printf("총 %d개의 메모리 블록을 해제했습니다.\n", freed_count);
}
