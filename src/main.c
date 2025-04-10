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

/*
mlx 오류 해결
	Syscall param writev(vector[0]) points to uninitialised byte(s)
		int	mlx_int_anti_resize_win() 함수안에
		memset(&hints, 0, sizeof(hints)); 추가
*/
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
	if (extract_str(fd, total) == -1)
		return (1);
	
	//str 검증
	if (validate(total))
	{
		// MLX 초기화
		init_about_mlx(total);
		// valid 경로를 기반으로 mlx_ptr에 img 로드
		extract_img(total);
		// 레이캐스팅 설정 및 시작
		start_raycast(total);
		
		// MLX 루프 실행
		mlx_loop(total->mlx->mlx_ptr);
	}
	else
	{
		// extract_str()의 메모리만 정리
		free_fail_case(total);
		close(fd);
		return (1);
	}
    
    // mlx_loop_end()에서 이어지는 메모리 정리
	free_success_case(total);
	
	close(fd);
    return (0);
}
