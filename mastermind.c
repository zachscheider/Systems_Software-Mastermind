/*
Zach Scheider
CS0449
Plays the game mastermind
Compile with -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char color_list[] = {'r', 'o', 'y', 'g', 'b', 'p'};

void gen_colors(char *buff, int low, int high, int num);
int play_game();
void enter_guess(char *buff, int guess_num, int len);
void game_logic();
int check_colors(char guess[], char secret[], int len);
int get_color_index(char color, int len);


int main(){
    srand((unsigned int)time(NULL));

    while(play_game()){
        game_logic();
    }

    return 0;
}

// generates the colors
void gen_colors(char *buff, int low, int high, int len){
    int value, i;
    for(i = 0; i < len; i++){
        value = rand() % (high - low + 1) + low;
        buff[i] = color_list[value];
    }
}

// asks the user if they want to play the game
int play_game(){
    int response;
    char input[32];

    printf("Would you like to play? ");
    scanf("%s", input);
    printf("\n");
    
    if('y' == input[0]){
        response = 1;
    }else if('n' == input[0]){
        response = 0;
    }else{
        printf("Please enter \'yes\' or \'no\'.\n\n");
        play_game();
    }
    return response;
}

// prompts the user to enter a guess
void enter_guess(char *buff, int guess_num, int len){
    char input[32];
    int i;

    printf("Enter guess number %d: ", guess_num);
    scanf("%s", input);
    printf("\n");
    
    for(i = 0; i < len; i++){
        buff[i] = input[i];
    }
}

// the main logic of the game
void game_logic(){
    char secret[4], guess[4];
    int guess_num;

    gen_colors(secret, 0, 5, 4);
    guess_num = 1;

    while(guess_num <= 10){
        enter_guess(guess, guess_num, 4);
        guess_num++;
        if(check_colors(guess, secret, 4) >= 4){
            printf("\nCongratulations! You won the game!\n\n");
            break;
        }
    }

}

// lets the user know how correct they are
int check_colors(char guess[], char secret[], int len){
    int i, in_common, in_correct_pos;
    int secret_count[] = {0, 0, 0, 0, 0, 0};
    int guess_count[] = {0, 0, 0, 0, 0, 0};

    in_common = 0;
    in_correct_pos = 0;

    for(i = 0; i < len; i++){
        secret_count[get_color_index(secret[i], 6)]++;
        guess_count[get_color_index(guess[i], 6)]++;
    }

    for(i = 0; i < sizeof(secret_count)/sizeof(secret_count[0]); i++){
        in_common += (int) fmin(secret_count[i], guess_count[i]);
    }

    for(i = 0; i < len; i++){
        if(guess[i] == secret[i]){
            in_correct_pos++;
        }
    }

    printf("Colors in the correct place: %d\n", in_correct_pos);
    printf("Colors correct but in wrong position: %d\n\n", in_common - in_correct_pos);

    return in_correct_pos;
}

// gets the index of the color in the array
int get_color_index(char color, int len){
    int i;

    for(i = 0; i < len; i++){
        if(color == color_list[i]){
            return i;
        }
    }
    
    return -1;
}