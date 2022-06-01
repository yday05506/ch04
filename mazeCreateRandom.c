//8����(��,����,��,����,��,�»�,��,���) �� �� �������� �̵� ����
//0�� ��, 1�� �̵� ������ ���

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 20
#define C 30
int cnt = 0;
int chk = 0;

//�ʱ�� ��� 0���� ����
int maze[R][C] = { 0 };

enum Bool { False, True };

struct direction {
	int r;
	int c;
};
struct direction move[8] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

enum Bool nextCheck(int maze_r, int maze_c, int next_r, int next_c) {
	int i;

	for (i = 0; i < 8; i++) {
		if (next_r + move[i].r < 0 || next_c + move[i].c < 0 || next_r + move[i].r >= R || next_c + move[i].c >= C) continue;
		if (next_r + move[i].r == maze_r && next_c + move[i].c == maze_c)continue;
		if (maze[next_r + move[i].r][next_c + move[i].c] >= 1) return False;
	}
	return True;
}

void mazeCreateStart(int maze_r, int maze_c) {
	int dir, next_r, next_c;

	while (maze[maze_r][maze_c] < 255) { //8���� ��� ���� �� ������ �ݺ�
		do {
			dir = rand() % 8; //8���� �� ������ ����
		} while ((maze[maze_r][maze_c] & (1 << dir)) == 1);

		//�̵� ������ ǥ����. dir�� 3�̸� �����ʿ��� �� ��°�� 1�� �ǰ� ��. 000...000000100
		//8���� ��� ���캸�Ҵٸ� 000...011111111 => 255
		maze[maze_r][maze_c] |= (1 << dir);
		next_r = maze_r + move[dir].r;
		next_c = maze_c + move[dir].c;

		if (next_r >= 0 && next_c >= 0 && next_r < R && next_c < C)
			if (maze[next_r][next_c] == 0 && nextCheck(maze_r, maze_c, next_r, next_c)) {
				maze[next_r][next_c] = 1;
				mazeCreateStart(next_r, next_c);
			}
	}
}

void mazeCreateEnd(int maze_r, int maze_c) {
	int dir, next_r, next_c, chk = 0;

	do {

		dir = rand() % 8; //8���� �� ������ ����

		next_r = maze_r + move[dir].r;
		next_c = maze_c + move[dir].c;

		if (next_r >= 0 && next_c >= 0 && next_r < R && next_c < C) {
			if (nextCheck(maze_r, maze_c, next_r, next_c)) {
				maze[next_r][next_c] = 1;
				maze_r = next_r;
				maze_c = next_c;
			}
			else break;
		}

	} while (1);

	maze[next_r][next_c] = 1;
}

void mazePrint(void) {
	int i, j;

	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (maze[i][j] >= 1)printf("%2d", 1);
			else printf("%2d", 0);
		}
		printf("\n");
	}

}

int main(void) {
	int start_r, start_c;
	int end_r, end_c;

	srand((unsigned int)time(NULL));

	printf("�̷� �� ũ��� 20, �� ũ��� 30\n\n");
	printf("������� �� ��ȣ(0~%d): ", R - 1);
	scanf_s("%d", &start_r);
	printf("������� �� ��ȣ(0~%d): ", C - 1);
	scanf_s("%d", &start_c);

	printf("\n�������� �� ��ȣ(0~%d): ", R - 1);
	scanf_s("%d", &end_r);
	printf("�������� �� ��ȣ(0~%d): ", C - 1);
	scanf_s("%d", &end_c);

	maze[end_r][end_c] = 256;

	printf("\n");
	//��������� �̷� ����
	mazeCreateStart(start_r, start_c);

	//���������� �̷� ����
	mazeCreateEnd(end_r, end_c);

	//�̷� ���
	mazePrint();
	printf("\n");

	return 0;
}