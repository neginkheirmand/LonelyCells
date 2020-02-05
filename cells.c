#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "cells.h"

int size_base=4;
// extern int size_game;
// extern int** map_bin;
// extern int** game_board;
// extern int num_boost_blocks;
// extern int** boostup_blocks;

static enum blocks{
 ENERGY = 1,
 MITOSIS,
 FORBIDDEN,
 NORMAL
};


char* give_name_rand(int size_name){
    char *str = malloc((size_name + 1) * sizeof(char)); 
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
 
    for (size_t i = 0; i < size_name; i++) {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }  
    str[size_name] = '\0'; 
    printf("the name choosen was: %s\n", str);
    return str;
}

char* give_your_name(int size_name){
    char *str = malloc((size_name + 1) * sizeof(char)); 
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

    for(int i=0; i<(sizeof(charset) / sizeof(char) - 1); i=i+5){
        if(i<10){
            printf("[%d]%c   ", i, charset[i]);
            printf("[%d]%c   ", i+1, charset[i+1]);
            printf("[%d]%c   ", i+2, charset[i+2]);
            printf("[%d]%c   ", i+3, charset[i+3]);
            printf("[%d]%c\n", i+4, charset[i+4]);
        }else{
            printf("[%d]%c  ", i, charset[i]);
            printf("[%d]%c  ", i+1, charset[i+1]);
            if(i==50){
                break;
            }
            printf("[%d]%c  ", i+2, charset[i+2]);
            printf("[%d]%c  ", i+3, charset[i+3]);
            printf("[%d]%c\n", i+4, charset[i+4]);

        }
    }
    printf("\nplease enter a %d char name by choosing the number corresponding to each one of his letters.\n", size_name);
    for(size_t i = 0; i < size_name; i++){
        int key;
        scanf("%d", &key);
        str[i] = charset[key];
    }  
    str[size_name] = '\0';
    printf("the name choosen was: %s\n", str);
    return str; 
}


void print_my_cells(struct cell* head_list, int player, int colors[6]){
    if(head_list==NULL){
        printf("NO cells to be showed");
        exit(0);
    }
    struct cell* temp=head_list;
    HANDLE hConsole;
    // printf("is here1\n");
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(player==1){
        
        while(temp!=NULL){
            // printf("\nis here2\n");
            SetConsoleTextAttribute(hConsole, 4);
            printf("[%d] ", temp->index);
            SetConsoleTextAttribute(hConsole, colors[0]);
            // printf("is here3\n");
            printf("%s ", temp->name);
            SetConsoleTextAttribute(hConsole, 4);
            // printf("is here4\n");
            printf("(");
            SetConsoleTextAttribute(hConsole, colors[0]);
            printf("%d , %d", temp->x, temp->y);
            SetConsoleTextAttribute(hConsole, 4);
            printf(")");
            printf("  glucose: %d", temp->glucose);
            SetConsoleTextAttribute(hConsole, 7);
            printf(" \n");
            // printf("\nis here5\n");
            temp=temp->next_cell;
        }
    }
    else{
        while(temp!=NULL){
        SetConsoleTextAttribute(hConsole, 4);
        printf("[%d] ", temp->index);
        SetConsoleTextAttribute(hConsole, colors[5]);
        printf("%s ", temp->name);
        SetConsoleTextAttribute(hConsole, 4);
        printf("(");
        SetConsoleTextAttribute(hConsole, colors[5]);
        printf("%d , %d", temp->x, temp->y);
        SetConsoleTextAttribute(hConsole, 4);
        printf(")");
        printf("  glucose: %d", temp->glucose);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" \n");
        temp=temp->next_cell;
        }
    }
    return;
}





struct cell* mitosis(){//in tabe gharare faghat besaze bayad badesh x va y ro set koni, dar zemn ba mitosis cell jadid mire tah list;
    struct cell* new_cell=malloc(sizeof(struct cell));
    new_cell->next_cell=NULL;
    new_cell->glucose=40;
    return new_cell;
}//in tabe ye esm dahande kam dare



struct cell* create_n_cells(int num_cells, int create_name, int player_num,int size_game,int**map_bin, int** game_board){
    srand(time(NULL));
    struct cell* Head;
    Head=mitosis();
    Head->glucose=0;
    Head->index=1;
    if(create_name==1){
        Head->name=give_your_name(size_base);
    }
    else{
        Head->name=give_name_rand(size_base);
    }
    int x_temp;
    int y_temp;
    x_temp=rand()%size_game;
    y_temp=rand()%size_game;
    while(map_bin[y_temp][x_temp]==FORBIDDEN||game_board[y_temp][x_temp]!=0){
        x_temp=rand()%size_game;
        y_temp=rand()%size_game;
    }
    Head->x=x_temp;
    Head->y=y_temp;
    game_board[y_temp][x_temp]=1;
    if(player_num==2){
        game_board[y_temp][x_temp]*=-1;
    }
    
    struct cell *temp=Head;
    for(int i=2; i<=num_cells; i++){
        temp->next_cell=mitosis();//next, glucose eshteb
        temp=temp->next_cell;
        temp->glucose=0;
        temp->index=i;
        if(create_name==1){
            temp->name=give_your_name(size_base);
        }
        else{
            temp->name=give_name_rand(size_base);
        }
        x_temp=rand()%size_game;
        y_temp=rand()%size_game;
        while(map_bin[y_temp][x_temp]==FORBIDDEN||game_board[y_temp][x_temp]!=0){
            x_temp=rand()%size_game;
            y_temp=rand()%size_game;
        }
        temp->x=x_temp;
        temp->y=y_temp;
        game_board[y_temp][x_temp]=i;
        if(player_num==2){
            game_board[y_temp][x_temp]*=-1;
        }
    }
    return Head;
}//need to be debuged


void check_move(int index_cell, struct cell* head_of_list, int direction, int player, int size_game,  int** game_board, int** map_bin){
//che zamani mituni beri tuye ye khune? forbidden nabashe va khali bashe, va az jadval nazane buirun
    struct cell* temp= head_of_list;
    while(temp->index!=index_cell && temp!=NULL){
        temp=temp->next_cell;
    }
    if(temp==NULL){
        printf("you are requestion to move something that doesent exist, need to debbug\n");
        exit(0);
    }
    int x, y;
    x=temp->x;
    y=temp->y; 
    
    if( (direction == 1) && (y==size_game-1||game_board[y+1][x]!=0||map_bin[y+1][x]==3)){
        printf("you just loosed your turn, the movement cannot be done\n");
        return;
    }
    else if(direction == 2  &&  (y==0||game_board[y-1][x]!=0||map_bin[y-1][x]==3) ){
        printf("you just loosed your turn, the movement cannot be done\n");
        return;
    }
    else if(direction == 3){
        if(x%2==0){
            if(y==size_game-1 || x==size_game-1||game_board[y+1][x+1]!=0||map_bin[y+1][x+1]==3 ){
                printf("you just loosed your turn, the movement cannot be done\n");
                return;
            }
        }
        else{
            if(x==size_game-1||game_board[y][x+1]!=0||map_bin[y][x+1]==3 ){
                printf("you just loosed your turn, the movement cannot be done\n");
                return;
            }
        }
    }
    else if(direction ==4){
        if(x%2==0 ){
            if(y==size_game-1||x==0||game_board[y+1][x-1]!=0||map_bin[y+1][x-1]==3){
                printf("you just loosed your turn, the movement cannot be done\n");
                return;
            }
        }
        else if((x%2==1)&& (x==0||game_board[y][x-1]!=0||map_bin[y][x-1]==3) ){
            printf("you just loosed your turn, the movement cannot be done\n");
            return;
        }
    }

    else if(direction ==5){
        if(x%2==0 &&(x==size_game-1||game_board[y][x+1]!=0||map_bin[y][x+1]==3)){
            printf("you just loosed your turn, the movement cannot be done\n");
            return;
        }
        else if(x%2==1&&(y==0||x==size_game-1||game_board[y-1][x+1]!=0||map_bin[y-1][x+1]==3)){
            printf("you just loosed your turn, the movement cannot be done\n");
            return;
        }
    }
    else if(direction == 6 ){
        if(x%2==0 && (x==0||game_board[y][x-1]!=0||map_bin[y][x-1]==3)){
            printf("you just loosed your turn, the movement cannot be done\n");
            return;
        }
        else if(x%2==1 && (y==0||x==0||game_board[y-1][x-1]!=0||map_bin[y-1][x-1]==3)){
            printf("you just loosed your turn, the movement cannot be done\n");
            return;
        }
    }

    if(direction==1){//chizaE ke bayad avaz koni:
    // game_board, x va y temp;
        game_board[y][x]=0;
        game_board[y+1][x]=(temp->index);
        if(player==2){
            game_board[y+1][x]*=-1;
        }
        (temp->y)=y+1;
    }
    else if(direction==2){//chizaE ke bayad avaz koni:
    // game_board, x va y temp;
        game_board[y][x]=0;
        game_board[y-1][x]=(temp->index);
        if(player==2){
            game_board[y-1][x]*=-1;
        }
        (temp->y)=y-1;
    }
    else if(direction==3){//chizaE ke bayad avaz koni:
    // game_board, x va y temp;
        if(x%2==1){
            game_board[y][x]=0;
            game_board[y][x+1]=(temp->index);
            if(player==2){
                game_board[y][x+1]*=-1;
            }
            (temp->x)=x+1;
        }
        else{
            game_board[y][x]=0;
            game_board[y+1][x+1]=(temp->index);
            if(player==2){
                game_board[y+1][x+1]*=-1;
            }
            (temp->x)=x+1;
            temp->y=y+1;
        }
    }
    else if(direction==4){
        if(x%2==0){
        game_board[y][x]=0;
        game_board[y+1][x-1]=(temp->index);
        if(player==2){
            game_board[y+1][x-1]*=-1;
        }
        temp->x=x-1;
        temp->y=y+1;
        }
        else{
        game_board[y][x]=0;
        game_board[y][x-1]=(temp->index);
        if(player==2){
            game_board[y][x-1]*=-1;
        }
        (temp->x)=x-1;
        }
    }
    else if(direction==5){
        if(x%2==0){
            game_board[y][x]=0;
            game_board[y][x+1]=(temp->index);
            if(player==2){
                game_board[y][x+1]*=-1;
            }
            temp->x=x+1;
        }
        else{    
            game_board[y][x]=0;
            game_board[y-1][x+1]=(temp->index);
            if(player==2){
                game_board[y-1][x+1]*=-1;
            }
            (temp->x)=x+1;
            (temp->y)=y-1;
        }
    }
    else if(direction==6){
        if(x%2==0){
            game_board[y][x]=0;
            game_board[y][x-1]=(temp->index);
            if(player==2){
                game_board[y][x-1]*=-1;
            }
            (temp->x)=x-1;
        }
        else{
            game_board[y][x]=0;
            game_board[y-1][x-1]=(temp->index);
            if(player==2){
                game_board[y-1][x-1]*=-1;
            }
            (temp->x)=x-1;
            (temp->y)=y-1;
        }
    }
    return;
}//debugged its


void Move(int index_cell, struct cell* head_of_list, int player, int size_game, int** game_board,int** map_bin){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    printf("[1] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" North\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[2] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" South \n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[3] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Northeast\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[4] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Northwest \n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[5] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Southeast \n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[6] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Southwest\n");
    int choice;
    scanf("%d", &choice);
    while(choice>6||choice<1){
        printf("cant you just enter a reasonable number? \n");
        scanf("%d", &choice);
    }
    check_move(index_cell,head_of_list, choice, player,size_game, game_board, map_bin);
    return;
}//reviewed

void delete(struct cell** pointer_head, struct cell* be_remove){//tabeye refresh ham tu khodeshe 
    if(*pointer_head==be_remove){
        (*pointer_head)=(*pointer_head)->next_cell;
        free(be_remove);
        return;
    }
    struct cell* temp=*pointer_head;
    while(temp->next_cell!=be_remove && temp->next_cell!=NULL){
        temp=temp->next_cell;
    }
    if(temp->next_cell==NULL){
        printf("NEED TO BE DEBUGED\n");
        exit(0);
    }
    if(temp->next_cell==be_remove){
        temp->next_cell=be_remove->next_cell;
        free(be_remove);
    }
    //hala bayad kole list ro refresh konim;
    temp=*pointer_head;
    for(int i=1; temp!=NULL; i++){
        temp->index=i;
        temp=temp->next_cell;
    }
    return;
}


void refresh_game_board(struct cell* head1, struct cell* head2, int** game_board, int size_game){
    for(int i=0; i<size_game; i++){
        for(int j=0; j<size_game; j++){
            game_board[i][j]=0;
        }
    }
    while(head1!=NULL){
        game_board[head1->y][head1->x]=head1->index;
        head1=head1->next_cell;
    }
    while(head2!=NULL){
        game_board[head2->y][head2->x]=(head2->index)*-1;
        head2=head2->next_cell;
    }
    return;
}

void refresh_indexes(struct cell* head){
    if(head==NULL){
        printf("why is there no cells in the list??\n");
        return;
    }
    for(int i=1; head!=NULL; i++){
        head->index=i;
        head=head->next_cell;
    }
    return;
}

void Split(int index_cell, struct cell** head_of_list, int player, int** map_bin, int size_game, int**game_board){
//bayad haminja game_board ro ham refresh koni
//sharayet split: tuye khune mitosis, energy kafi, khunehaye baghali hadaghal yekishun ja bashe
    struct cell* temp=*head_of_list;
    while(temp!=NULL){
        if(temp->index==index_cell){
            break;
        }
        temp=temp->next_cell;
    }
    if(temp==NULL){
        printf("wait whaattttt!!\n");
        exit(0);
    }
        // printf("right here1\n");
    if(temp->index==index_cell){
        int x=temp->x;
        int y=temp->y;
        // printf("right here2\n");
        if(temp->glucose>=80 && map_bin[y][x]==MITOSIS){//ta inja check karDm ke energu kafi ro dashte bashe va tuye khuneye mitosis bashe
        //hala bayad check konim ke aslan khuneye dovomi hast ke beshe tush cell dovom ro berizim
            int blank_block=0;
            int x_2,y_2;
            // printf("right here3\n");
            if(x%2==1){
                for(int i=y-1; i<=y; i++){
                    if(i>=0){
                        for(int j=x-1; j<=x+1 && j<size_game; j++){
                            if(j>=0){
                                if(game_board[i][j]==0){
                                    // printf("right here4\n");
                                    x_2=j;
                                    y_2=i;
                                    blank_block=1;
                                    break;
                                }
                            }else{
                                continue;
                            }
                        }
                        if(blank_block==1){
                            break;
                        }
                    }else{
                        continue;
                    }
                }
                // printf("right here5\n");
                if(game_board[y+1][x]==0&&y+1<size_game){//harekat 1 ro ham check mikonim
                    blank_block=1;
                    x_2=x;
                    y_2=y+1;
                }
            }
            else if(x%2==0){
                // printf("right here6\n");
                for(int i=y; i<=y+1&&i<size_game; i++){
                    for(int j=x-1; j<=x+1 && j<size_game; j++){
                        if(j>=0){
                            if(game_board[i][j]==0){
                                x_2=j;
                                y_2=i;
                                blank_block=1;
                                break;
                            }
                        }else{
                            continue;
                        }
                    }
                    if(blank_block==1){
                        break;
                    }
                }
                // printf("right here7\n");
                if(game_board[y-1][x]==0&&y>0){//harekat 1 ro ham check mikonim
                    blank_block=1;
                    x_2=x;
                    y_2=y-1;
                }
            }
            // printf("right here8\n");
            if(blank_block==0){
                // printf("right here9\n");
                printf("there is not space for the child cell\n");
                return;
            }
            //inja bayad ye cell jadid besazi.
            //yani bayad ghablie ro delet koni, khodesho va bachasho bezari tahe list va index hameye cell haye tuye jadval ro update koni 
            // printf("right here10\n");
            char* name1 = temp->name;
            // printf("right here11\n");
            delete(head_of_list, temp);
            // printf("right here12\n");
            temp=*head_of_list;//alan temp be avalin khuneye liste jadid eshare mikone
            int i;
            for(i=1; temp->next_cell!=NULL; i++){
                temp=temp->next_cell;
            }
            // printf("right here13\n");
            i++;
            temp->next_cell=mitosis();
            temp=temp->next_cell;
            temp->x=x;
            temp->y=y;
            temp->name=name1;
            // printf("right here14\n");
            // temp->name="eyba";
            // printf("right here15\n");
            refresh_indexes(*head_of_list);
            // printf("right here15\n");
            temp->next_cell=mitosis();
            // printf("right here16\n");
            temp=temp->next_cell;
            temp->x=x_2;
            temp->y=y_2;
            temp->name=give_name_rand(size_base);
            refresh_indexes(*head_of_list);
            // printf("i am the bug in split:D\n");

            return;
            // mitosis
        }else{
            // printf("right here17\n");
            printf(" cannot split cause the cell\n");
            return;
        }
    }
}


void BoostEnergy(int index_cell, struct cell* head_of_list, int player, int**map_bin, int** game_board, int num_boost_blocks, int** boostup_blocks){
//sharatyet boostup: tuye khuneye boost up budn, ja dashtn, chon saghfe energy momken 100
    struct cell* temp=head_of_list;
    while(temp!=NULL){
        if(temp->index==index_cell){
            break;
        }
        temp=temp->next_cell;
    }
    if(temp==NULL){
        printf("cannot find such a cell!\n");
        return;
    }
    int x, y;
    if(temp->index==index_cell){
        x=temp->x;
        y=temp->y;
    }
    if(temp->glucose==100||map_bin[y][x]!=ENERGY){
        printf("cannot bust up the energy of the cell\n");
        return;
    }
    int index_boostup_block;
    for(int i=0; i<num_boost_blocks; i++){
        if(boostup_blocks[i][0]==x && boostup_blocks[i][1]==y){
            index_boostup_block=i;
            break;
        }
    }
    int block_energy=boostup_blocks[index_boostup_block][2];
    if(block_energy==0){
        printf("the block doesnt have any energy left\n");
        return;
    }
    if(temp->glucose>=85){
        if(100-temp->glucose>block_energy){
            boostup_blocks[index_boostup_block][2]=0;
            temp->glucose=(temp->glucose)+block_energy;
            return;
        }
        else if(100-temp->glucose<=block_energy){
            boostup_blocks[index_boostup_block][2]=block_energy-(100-temp->glucose);
            temp->glucose=100;
            return;
        }
    }
    if(block_energy>=15){
        
        boostup_blocks[index_boostup_block][2]-=15;
        (temp->glucose)+=15;
        return;
    }
    else{
        boostup_blocks[index_boostup_block][2]=0;
        (temp->glucose)+=block_energy;
        return;
    }
}
