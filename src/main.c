#include "cub3d.h"
/* 변수 초기화 함수
// 맵 파싱 데이터를 활용한 플레이어 위치
// 방향 벡터 초기화
// 카메라 평면 초기화
*/

// int main()
// {
// 	// 맵 파싱
// 	// 변수 초기화
// 	// 화면 생성
// 	/* 게임 루프(반복문)
// 	// 프레임 그리기
// 	// 키 입력 받기
// 	*/
// }

int main(int argc, char **argv)
{
    t_total *total;
	int		fd;
	(void)argv;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d [map_file.cub]\n", 2);
		return (1);
	}

	// 맵파일 열기
	fd = open("./img/map.cub", O_RDONLY);
	if (fd == -1)
	{
		printf("file open error\n");
		return (-1);
	}

	// t_total 메모리 할당
    total = (t_total *)malloc(sizeof(t_total));

	// 메모리 추적 초기화
	init_mem_tracker(total);
	
	// 맵에서 str 추출
	extract_str(fd, total);
	
	//str 검증
	if (!validate(total))
	{
		// free_invalid_case(total);
		return (1);
	}
    
    // MLX 초기화
	init_about_mlx(total);
	// valid 경로를 기반으로 mlx_ptr에 img 로드
	extract_img(total);
    // 레이캐스팅 설정 및 시작
    start_raycast(total);
    
    // MLX 루프 실행
    mlx_loop(total->mlx->mlx_ptr);
    
    // 프로그램 종료 직전에 메모리 정리
    // print_mem_status(total); // 디버깅용, 정리 전 메모리 상태 출력
    free_all_memory(total); // 할당된 모든 메모리 해제
    free(total->mem_tracker); // 메모리 추적기 자체 해제
    free(total); // total 구조체 해제
    
    return (0);
}