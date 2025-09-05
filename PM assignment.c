#include<stdio.h>
#include <stdlib.h>

char** initialize_the_Board(int N) {
    // initialize the board..............................................
    char** board = malloc(N * sizeof(char*));
    for (int i = 0; i <= N; i++) {
        board[i] = malloc(N * sizeof(char));
        for (int j = 0; j <= N; j++) {
            board[i][j] = '-';
        }
    }
    return board;
}
// display the board......................................................
void display_the_board ( char** board, int N){
     for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            printf(" %c ", board[i][j]);
            if (j != N - 1) printf("|");
        }
    }
}

if(i != N - 1) {
            for (int k = 0; k < N; k++) {
                printf("---\n");

                if (k != N - 1) printf("+\n");
            }
        }




int main() {
    int N;
    printf("Enter board size N (N <=10 OR N>=3 ): ");
    scanf("%d", &N);

