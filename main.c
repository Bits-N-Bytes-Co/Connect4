#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define row_num    6
#define col_num    7

typedef enum Token{
    EMPTY = 0,
    YELLOW = 1,
    RED = 2
}Token;

typedef struct Game{
    Token grid[row_num][col_num];
    char player1[50];
    char player2[50];
    bool gameover;
} Game;

//will check if 4 tokens connect
bool check_win_condition(){
    return false;
}

//will add the token, check the winning condition and return it
bool update_board(Game* game, int col, int current_player){
    return false;
}

void grid_init(Game* game){
    for (int i = 0; i < row_num; i++){
        for (int j = 0; j < col_num; j++){
              game->grid[i][j] = EMPTY;
        }
    }
}

void grid_show(Game* game){
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("| - + - + - + - + - + - + - |\n");
    for (int i = 0; i < row_num; i++){
        printf("|");
        for (int j = 0; j < col_num; j++){
              printf(" %d |",game->grid[i][j]);
        }
        printf("\n");
        printf("| - + - + - + - + - + - + - |\n");
    }
}

void game_init(Game* game){
    int current_player=1;
    int chosen_col=0;

    grid_init(game);
    
    printf("--------/Welcome to Connect 4/--------\n\n");
    printf("Player 1, please enter your name: ");
    scanf("%s", game->player1);
    printf("Player 2, please enter your name: ");
    scanf("%s", game->player2);
    printf("\n");

    grid_show(game);

    do{
        if(current_player==1){
            printf("%s, choose a column to drop your token in: ", game->player1);
            scanf("%d", &chosen_col);
            game->gameover=update_board(game, chosen_col-1, current_player);
            current_player=2;
            grid_show(game);
        }
        else{
            printf("%s, choose a column to drop your token in: ", game->player2);
            scanf("%d", &chosen_col);
            game->gameover=update_board(game, chosen_col-1, current_player);
            current_player=1;
            grid_show(game);
        }
    }while(!game->gameover);
    
}

int main(){
    Game* game=calloc(1, sizeof(Game));
    
    game_init(game);

    return 0;
}