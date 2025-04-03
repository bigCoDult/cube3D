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

int main()
{
    t_total *total;
	int		fd;

	// 맵파일 열기
	fd = open("./img/map.cub", O_RDONLY);
	if (fd == -1)
	{
		printf("file open error\n");
		return (-1);
	}

	// t_total 메모리 할당
    total = (t_total *)malloc(sizeof(t_total));
	
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
    return (0);
}