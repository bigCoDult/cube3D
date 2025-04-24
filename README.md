# cube3D

**프로젝트 개요**
cube3D는 간단한 3D 레이캐스팅 엔진을 구현하여 `.cub` 맵 데이터를 시각화하는 교육용 프로젝트입니다.
Auxiliary library로 **libft**와 **MiniLibX**를 사용하여 실제 게임과 유사한 시점의 3D 환경을 렌더링합니다.

**프로젝트 의의**
- **레이캐스팅 알고리즘**: DDA(Digital Differential Analyzer) 방식을 통해 월드 좌표를 2D 평면에서 3D 투영으로 변환하는 원리를 학습합니다.
- **맵 파싱 및 검증**: 텍스처 경로, 바닥·천장 색상, 맵 형태(벽으로 둘러싸인지)를 파싱하고 검증하는 로직을 구현합니다.
- **그래픽 렌더링**: MiniLibX를 활용해 벽 텍스처 매핑, 어안 효과 보정, 바닥·천장 색상 칠하기, 미니맵 표시 등 기본 그래픽 기법을 실습합니다.
- **입력 처리 및 충돌 감지**: 키보드(WASD) 및 마우스 입력으로 플레이어 이동·회전을 구현하고, 벽 충돌을 방지하는 로직을 설계합니다.
- **모듈화 설계**: 파싱, 렌더링, 입력, 유틸리티 모듈을 분리하여 유지보수성과 확장성을 고려한 코드 구조를 경험합니다.

## 주요 디렉토리 구조
```
cube3D/
├── inc/                # 헤더 파일
├── src/                # 소스 파일 (파싱, 렌더링, 입력 등)
├── libft/              # 프로젝트 내장 라이브러리 (libft)
├── img/                # XPM 텍스처 리소스
├── cub3D/              # 예제 맵(.cub) 파일
├── Makefile            # 빌드 스크립트
├── .gitignore
└── README.md           # 이 파일
```

## 라이선스
이 프로젝트는 **Beerware License (Revision 42)**를 따릅니다.

```
THE BEER-WARE LICENSE (Revision 42)
As long as you retain this notice you can do anything with this stuff.
If we meet some day, and you think this stuff is worth it, you can buy me a beer in return.
```
