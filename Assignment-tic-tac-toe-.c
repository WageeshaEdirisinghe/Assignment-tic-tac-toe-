#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize the board...........................................................................
char** initialize_the_Board(int N) {
    char** board = malloc(N * sizeof(char*));
    for (int i = 0; i < N; i++) {
        board[i] = malloc(N * sizeof(char));
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }
    return board;
}

// Display the board........................................................................
void display_the_board(char** board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");
    }
}

// win condition..............................................................................
int checkWin(char** board, int N, char sym) {
    for (int i = 0; i < N; i++) {
        int row = 1, col = 1;
        for (int j = 0; j < N; j++) {
            if (board[i][j] != sym) row = 0;
            if (board[j][i] != sym) col = 0;
        }
        if (row || col) return 1;
    }
    int d1 = 1, d2 = 1;
    for (int i = 0; i < N; i++) {
        if (board[i][i] != sym) d1 = 0;
        if (board[i][N - i - 1] != sym) d2 = 0;
    }
    return d1 || d2;
}

// draw condition.........................................................................
int isDraw(char** board, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == '-') return 0;
    return 1;
}

// Computer move logic........................................................................
void computerMove(char** board, int N, char sym) {
    int r, c;
    do {
        r = rand() % N;
        c = rand() % N;
    } while (board[r][c] != '-');
    board[r][c] = sym;
    printf("Computer %c placed at (%d, %d)\n", sym, r + 1, c + 1);
}

int main() {
    int N, mode, numPlayers;

    printf("Enter board size (3-10): ");//.......................................................
    scanf("%d", &N);
    if (N < 3 || N > 10) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("\nSelect Game Mode:\n");//.................................................
    printf("1 - Player vs Player\n");//................................................
    printf("2 - Player vs Computer\n");//..............................................
    printf("3 - Multiplayer\n");//.....................................................
    printf("Enter your choice: ");
    scanf("%d", &mode);

    if (mode == 1 || mode == 2) {
        numPlayers = 2;
    } else if (mode == 3) {
        printf("Enter number of players (2–10): ");
        scanf("%d", &numPlayers);
        if (numPlayers < 2 || numPlayers > 10) {
            printf("Invalid number of players!\n");
            return 1;
        }
    } else {
        printf("Invalid mode!\n");
        return 1;
    }

    // Allocate memory for symbols and roles.................................................................
    char* symbols = malloc(numPlayers * sizeof(char));
    int* roles = malloc(numPlayers * sizeof(int)); // 0 = human, 1 = computer...................................

    //symbols: A, B, C, ...................................................................................
    for (int i = 0; i < numPlayers; i++) {
        symbols[i] = 'A' + i;
    }

    // Configure roles................................................................
    printf("\nConfigure player roles:\n");
    for (int i = 0; i < numPlayers; i++) {
        if (mode == 2 && i == 1) {
            roles[i] = 1; // Player 2 is computer in PvC
            printf("Player %d (%c) is set as Computer.\n", i + 1, symbols[i]);
        } else {
            printf("Is Player %d (%c) a computer? (0 = No, 1 = Yes): ", i + 1, symbols[i]);
            scanf("%d", &roles[i]);
        }
    }

    char** board = initialize_the_Board(N);
    srand(time(NULL));

    int turn = 0;
    while (1) {
        display_the_board(board, N);
        char sym = symbols[turn];
        int r, c;

        if (roles[turn] == 0) {
            // Human move.........................................................
            printf("Player %c, enter row and column (1-%d): ", sym, N);
            scanf("%d %d", &r, &c);
            r--; c--;
            if (r < 0 || r >= N || c < 0 || c >= N || board[r][c] != '-') {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[r][c] = sym;
        } else {
            // Computer move.............................................................
            computerMove(board, N, sym);
        }

        if (checkWin(board, N, sym)) {
            display_the_board(board, N);
            printf("Player %c wins!\n", sym);
            break;
        }
        if (isDraw(board, N)) {
            display_the_board(board, N);
            printf("It's a draw!\n");
            break;
        }

        turn = (turn + 1) % numPlayers;
    }

    // Free memory............................................................................
    for (int i = 0; i < N; i++) free(board[i]);
    free(board);
    free(symbols);
    free(roles);

    return 0;
}

