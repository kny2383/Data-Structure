#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int findingPath(char** maze, int MAXROW, int MAXCOL);

typedef struct {
    short int vert;
    short int horiz;
} offsets;


offsets move[8] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;
element stack[10000];

void push(int* top, element curr) {
    stack[++(*top)] = curr;
}

element pop(int* top) {
    return stack[(*top)--];
}

int main() {
    int row, col;

    printf("행과 열을 입력하세요. : ");
    scanf("%d %d", &row, &col);

    FILE* pFile = fopen("maze.txt", "r");

    int ROW = row + 2;
    int COL = col + 2;

    char** maze = (char**)malloc(sizeof(char*) * ROW);
    for (int i = 0; i < ROW; i++) {
        maze[i] = (char*)malloc(sizeof(char) * (col + 2));


        if (i == 0 || i == ROW - 1) {
            for (int j = 0; j < COL; j++) {
                maze[i][j] = '1';
            }
            continue;
        }

        maze[i][0] = maze[i][COL - 1] = '1';
        for (int j = 1; j <= col; j++) {
            fscanf(pFile, " %c", &maze[i][j]);
        }
    }

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }

    return 0;
}

