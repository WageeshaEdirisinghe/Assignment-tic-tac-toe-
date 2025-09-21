// Online C compiler to run C program online
#include<stdio.h>
#include <stdlib.h>

char** initialize_the_Board(int N) {
    // initialize the board..............................................
    char** board = malloc(N * sizeof(char*));
    for (int i = 0; i < N; i++) {
        board[i] = malloc(N * sizeof(char));
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }
    return board;
}
// display the board......................................................
void display_the_board ( char** board, int N){
     for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
         printf("\n");

    if (i != N - 1) {
            for (int k = 0; k < N; k++) {
                printf("---\n");

                if (k != N - 1) printf("+\n");
            }
            printf("");
        }
    }
}

int checkWin(char** board, int N, char sym) {
    
    for (int i = 0; i < N; i++) {
        int row = 1, col = 1;
        for (int j = 0; j < N; j++) {
            if (board[i][j] != sym) row = 0;
            if (board[j][i] != sym) col = 0;
        }
        if (row || col) return 1;
    }
    //  diagonal...........................................................
    int d1 = 1, d2 = 1;
    for (int i = 0; i < N; i++) {
        if (board[i][i] != sym) d1 = 0;
        if (board[i][N - i - 1] != sym) d2 = 0;
    }
    if (d1 || d2) return 1;

    return 0;
}

// Check for draw
int isDraw(char** board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == '-') return 0; 
    }
    return 1; 
    }
}

int main() {
    int N;
    printf("Enter board size (3-10): ");
    scanf("%d", &N);

    if (N < 3 || N > 10) {
        printf("Invalid size!\n");
        return 1;
    }

    char **board = createBoard(N);

    int turn = 0; // 0 = X, 1 = O
    while (1) {
        showBoard(board, N);
        int r, c;
        char sym = (turn == 0) ? 'X' : 'O';

        printf("Player %c, enter row and column (1-%d): ", sym, N);
        scanf("%d %d", &r, &c);
        r--; c--; 
        if (r < 0 || r >= N || c < 0 || c >= N || board[r][c] != '-') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[r][c] = sym;

        if (checkWin(board, N, sym)) {
            showBoard(board, N);
            printf("Player %c wins!\n", sym);
            break;
        }
        if (isDraw(board, N)) {
            showBoard(board, N);
            printf("It's a draw!\n");
            break;
        }

        turn = 1 - turn; // switch player
    }

    // Free memory
    for (int i = 0; i < N; i++) free(board[i]);
    free(board);

    return 0;
}







