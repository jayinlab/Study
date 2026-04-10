#define _CRT_SECURE_NO_WARNINGS
// 자 이동이 여러개다?
// version 1
// 1) 오른쪽 5
// 아래 4, 왼쪽 4
// 위로 3
// 2) 오른쪽 3
// 아래 2, 왼쪽 2
// 위로 1
// 3) 오른쪽 1

// - 시작 위치는 (r, c) = (1,0)
// - 우,하,좌,상 반복 이동
// - 한 방향 이동시 m번 이동
// - m의 초기값은 n.
// 오른쪽 이동하고 1감소
// 왼쪽 이동하고 1 감소
// 종료조건: n*n개를 다 채우면 종료

// version 2
/*
채우고 이동해서 4번 가고, 안채우고 멈추기
한바퀴 돌면 시작점임
그럼 안쪽으로 이동해. 2번만 돌아. 그러면 0000은 안가면 되고, m이 0이거나, n이 홀수면 중앙에 하나 채우기.
*/

#include <stdio.h>

int N;
int A[105][105];
// 이동했을때 변화량을 여기에 넣는 것
// 오른쪽은
int dr[] = {0,1,0,-1}; // 1이면 아래쪽, // 우, 하, 좌, 상
int dc[] = {1,0,-1,0}; // 1이면 오른쪽


void pro1() {
	int r = 1, c = 0, m = N, num = 1;
	// 방향은 반복
	for (int i = 0; ; i++) {
		// direction 방향인거
		int dir = i % 4;
		// dir = 0,1,2,3,0,1,2,3 ...

		// direction 방향 m번 이동.
		for (int j = 0; j < m; j++) {
			r += dr[dir];
			c += dc[dir];
			// 이동했으니까
			A[r][c] = num++;
			// 채울때마다 확인하라
			if (num > N * N) {
				// 다채웠네?
				return;
			}
		}

		// direction이 0이거나 2면 감소해라 (왼, 오면 감소)
		if (dir % 2 == 0) m--;
	}
	
}



void pro2() {

	int r = 1, c = 1, m = N - 1, num = 1;

	while (1) {
		// m이 0 이하면 종료해라. N이 1이면 처음부터 m이 0이다.
		if (m <= 0) break;
		//
		// 4개의 direction에 대해
		for (int dir = 0; dir < 4; dir++) {
			for (int i = 0; i < m; i++) {
				A[r][c] = num++;
				r += dr[dir];
				c += dc[dir];
			}
		}
		r++;
		c++;
		m -= 2;
	}
	if (N % 2) A[r][c] = num;
}

//// 이동이 가능하면 계속 반복한다
//// 범위가 벗어나는 조건을 추가한다
//// 이동 하고 삽입한다
//// dfs,bfs에서 할텐데 미리 해보자.


void pro3() {
	int r = 1, c = 0, num = 1;
	for (int i = 0; ; i++) {
		int dir = i % 4;
		while (1) {
			// 이동할 곳의...
			int nr = r + dr[dir];
			int nc = c + dc[dir];
			// 범위 먼저 확인해보기
			if (nr<1 || nr>N || nc<1 || nc >N) break;
			// 채워져 있는가?
			if (A[nr][nc]) break;

			// 그럼 여기
			r = nr;
			c = nc;
			//삽입
			A[r][c] = num++;
			// 종료?
			if (num > N * N) return;
		}
	}
}


//// 이동 가능하면 계속 반복한다
//// 주변을 0이 아닌 값으로 채워서 본다

void pro4() {

	// 처음에 테두리를 채웠을때 편할 때도 있기는 하더라.
	for (int i = 1; i <= N; i++) {
		A[0][i] = -1;
		A[N + 1][i] = -1;
		A[i][0] = -1;
		A[i][N + 1] = -1;
	}

	int r = 1, c = 0, num = 1;
	for (int i = 0; ; i++) {
		int dir = i % 4;
		while (1) {
			if (A[r + dr[dir]][c + dc[dir]]) break;
			r += dr[dir];
			c += dc[dir];
			// 삽입
			A[r][c] = num++;
			// 종료?
			if (num > N * N) return;
		}
	}
}


int main()
{
	auto tmp = freopen("input.txt", "r", stdin);
	auto temp = scanf("%d", &N);

	// pro1();
	// pro2();
	// pro3();
	pro4();

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}

	return 0;
}
