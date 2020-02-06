#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "map.h"

void print_block_energies(int** boostup_blocks, int num_boostup_blocks){
    printf("\n");
    for(int i=0; i<num_boostup_blocks; i++){
        printf("%d) x=%d, y=%d energy left=%d\n", i+1, boostup_blocks[i][0], boostup_blocks[i][1], boostup_blocks[i][2]);
    }
    printf("\n");
    return;
}


void print(int size_game, int**map_bin, int**game_board, int colors[6], int num_boostup_blocks, int** boostup_blocks){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int counter_khat=1;
    for(int i=size_game-1; i>=0; i--, counter_khat++){
        for(int j=0; j<size_game; j++){
            if(j%2==0){
                if(counter_khat%3==0){
                    SetConsoleTextAttribute(hConsole, 7);
                    printf("   ");
                    SetConsoleTextAttribute(hConsole, 7);
                    if(j==size_game-1){
                        counter_khat=1;
                    }
                    continue;
                }
                if(game_board[i][j]==0){
                    if(map_bin[i][j]==ENERGY){
                        int energy_left;
                        for(int k=0; k<num_boostup_blocks; k++){
                            if(boostup_blocks[k][0]==j && boostup_blocks[k][1]==i){
                                energy_left=boostup_blocks[k][2];
                            }                            
                        }
                        SetConsoleTextAttribute(hConsole, colors[1]*16);
                        if(energy_left>25){
                            printf("EE");
                        }
                        else if(energy_left>0){
                            printf("E ");
                        }
                        else{
                            printf("  ");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");

                    }
                    else if(map_bin[i][j]==MITOSIS){
                        SetConsoleTextAttribute(hConsole, colors[2]*17);
                        printf("MM");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==FORBIDDEN){
                        SetConsoleTextAttribute(hConsole, colors[3]*17);
                        printf("FF");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==NORMAL){
                        SetConsoleTextAttribute(hConsole, colors[4]*17);
                        printf("NN");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }else if(game_board[i][j]>0){//karbar aval
                    if(map_bin[i][j]==ENERGY){
                        SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                        if(game_board[i][j]>9){
                            printf("%d", game_board[i][j]);
                        }else{
                            printf("%d ", game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==2){
                        SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                        if(game_board[i][j]>9){
                            printf("%d", game_board[i][j]);
                        }else{
                            printf("%d ", game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==3){
                        SetConsoleTextAttribute(hConsole, (colors[3]*16)+colors[0]);
                        if(game_board[i][j]>9){
                            printf("%d", game_board[i][j]);
                        }else{
                            printf("%d ", game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==4){
                        SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                        if(game_board[i][j]>9){
                            printf("%d", game_board[i][j]);
                        }else{
                            printf("%d ", game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }else if(game_board[i][j]<0){//karbar dovom
                    if(map_bin[i][j]==1){
                        SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                        if((game_board[i][j]*-1)>9){
                            printf("%d", -1*game_board[i][j]);
                        }else{
                            printf("%d ", -1*game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==2){
                        SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                        if((game_board[i][j]*-1)>9){
                            printf("%d", -1*game_board[i][j]);
                        }
                        else{
                            printf("%d ", -1*game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==3){
                        SetConsoleTextAttribute(hConsole, (colors[3]*16)+colors[5]);
                        if((game_board[i][j]*-1)>9){
                            printf("%d", -1*game_board[i][j]);
                        }
                        else{
                            printf("%d ", -1*game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==4){
                        SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                        if((game_board[i][j]*-1)>9){
                            printf("%d", -1*game_board[i][j]);
                        }else{
                            printf("%d ", -1*game_board[i][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }
            }
            else if(j%2==1){
                if(i==size_game-1){
                    printf("   ");
                    continue;
                }
                if(game_board[i+1][j]==0){
                    if(map_bin[i+1][j]==ENERGY){
                        int energy_left;
                        for(int k=0; k<num_boostup_blocks; k++){
                            if(boostup_blocks[k][0]==j&&boostup_blocks[k][1]==i+1){
                                energy_left=boostup_blocks[k][2];
                            }                            
                        }
                        SetConsoleTextAttribute(hConsole, colors[1]*16);
                        if(energy_left>25){
                            printf("EE");
                        }
                        else if(energy_left>0){
                            printf("E ");
                        }
                        else{
                            printf("  ");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i+1][j]==MITOSIS){
                        SetConsoleTextAttribute(hConsole, colors[2]*17);
                        printf("MM");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i+1][j]==FORBIDDEN){
                        SetConsoleTextAttribute(hConsole, colors[3]*17);
                        printf("FF");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i+1][j]==NORMAL){
                        SetConsoleTextAttribute(hConsole, colors[4]*17);
                        printf("NN");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }else if(game_board[i+1][j]>0){//karbar aval
                    if(map_bin[i+1][j]==ENERGY){
                        SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                        if(game_board[i+1][j]>9){
                            printf("%d", game_board[i+1][j]);
                        }else{
                            printf("%d ", game_board[i+1][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i+1][j]==MITOSIS){
                        SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                        if(game_board[i+1][j]>9){
                            printf("%d", game_board[i+1][j]);
                        }else{
                            printf("%d ", game_board[i+1][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    
                    else if(map_bin[i+1][j]==NORMAL){
                        SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                        if(game_board[i+1][j]>9){
                            printf("%d", game_board[i+1][j]);
                        }else{
                            printf("%d ", game_board[i+1][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }else if(game_board[i+1][j]<0){
                    if(map_bin[i+1][j]==ENERGY){
                        SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                        if((game_board[i+1][j]*-1)>9){
                            printf("%d", -1*game_board[i+1][j]);
                        }else{
                            printf("%d ", -1*game_board[i+1][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i+1][j]==MITOSIS){
                        SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                        if((game_board[i+1][j]*-1)>9){
                            printf("%d", -1*game_board[i+1][j]);
                        }else{
                            printf("%d ", -1*game_board[i+1][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    
                    else if(map_bin[i+1][j]==NORMAL){
                        SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                        if((game_board[i+1][j]*-1)>9){
                            printf("%d", -1*game_board[i+1][j]);
                        }else{
                            printf("%d ", -1*game_board[i+1][j]);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
        counter_khat++;
        //khat dovom
        for(int j=0; j<size_game; j++){
            if(j%2==1 && counter_khat%3==1){
                SetConsoleTextAttribute(hConsole, 7);
                printf("   ");
                // continue;
                SetConsoleTextAttribute(hConsole, 7);
            }
            if(map_bin[i][j]==ENERGY){
                if(game_board[i][j]==0){
                   int energy_left;
                    for(int k=0; k<num_boostup_blocks; k++){
                        if(boostup_blocks[k][0]==j&&boostup_blocks[k][1]==i){
                            energy_left=boostup_blocks[k][2];
                        }                            
                    }
                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                    if(energy_left>75){
                        printf("EE");
                    }
                    else if(energy_left>50){
                        printf("E ");
                    }
                    else{
                        printf("  ");
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
                else if(game_board[i][j]>0){//karbar aval
                    SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                    printf("%d ", game_board[i][j]);                    
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }else if(game_board[i][j]<0){//karbar dovom
                    SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[1]);
                    printf("%d ", -1*game_board[i][j]);                    
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
            }
            else if(map_bin[i][j]==MITOSIS){
                if(game_board[i][j]==0){
                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                    printf("MM");
                }else if(game_board[i][j]>0){
                    SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                    if(game_board[i][j]>9){
                        printf("%d", game_board[i][j]);
                    }else{
                        printf("%d ", game_board[i][j]);
                    }
                }else if(game_board[i][j]<0){
                    SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                    if((-1*game_board[i][j])>9){
                        printf("%d", -1*game_board[i][j]);
                    }else{
                        printf("%d ", -1*game_board[i][j]);
                    }
                }
                SetConsoleTextAttribute(hConsole, 7);
                printf(" ");
            }
            else if(map_bin[i][j]==FORBIDDEN){
                if(game_board[i][j]==0){
                    SetConsoleTextAttribute(hConsole, colors[3]*17);
                    printf("FF");
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
            }
            else if(map_bin[i][j]==NORMAL){
                if(game_board[i][j]==0){
                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                    printf("NN");
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
                else if(game_board[i][j]>0){
                    SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                    if(game_board[i][j]>9){
                        printf("%d", game_board[i][j]);
                    }else{
                        printf("%d ", game_board[i][j]);
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }else if(game_board[i][j]<0){
                    SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                    if((-1*game_board[i][j])>9){
                        printf("%d", -1*game_board[i][j]);
                    }else{
                        printf("%d ", -1*game_board[i][j]);
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
            }
            
        }
        printf("\n");
    }
    int i=0;
    for(int j=0; j<size_game; j++){
        if(j%2==0){
            SetConsoleTextAttribute(hConsole, 7);
            printf("   ");
            SetConsoleTextAttribute(hConsole, 7);
        }else{
            if(map_bin[i][j]==ENERGY){
                if(game_board[i][j]==0){
                    int energy_left;
                    for(int k=0; k<num_boostup_blocks; k++){
                        if(boostup_blocks[k][0]==j && boostup_blocks[k][1]==i){
                            energy_left=boostup_blocks[k][2];
                        }                            
                    }
                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                    if(energy_left>75){
                        printf("EE");
                    }
                    else if(energy_left>50){
                        printf("E ");
                    }
                    else{
                        printf("  ");
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }else if(game_board[i][j]>0){
                    SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                    if(game_board[i][j]>9){
                        printf("%d", game_board[i][j]);
                    }else{
                        printf("%d ", game_board[i][j]);
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }else if(game_board[i][j]<0){
                    SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                    if(-1*game_board[i][j]>9){
                        printf("%d", -1*game_board[i][j]);
                    }else{
                        printf("%d ", -1*game_board[i][j]);
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
            }
            else if(map_bin[i][j]==MITOSIS){
                if(game_board[i][j]==0){
                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                    printf("MM");
                }else if(game_board[i][j]>0){
                    SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                    if(game_board[i][j]>9){
                        printf("%d", game_board[i][j]);
                    }else{
                        printf("%d ", game_board[i][j]);
                    }

                }else if(game_board[i][j]<0){
                    SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                    if(-1*game_board[i][j]>9){
                        printf("%d", -1*game_board[i][j]);
                    }else{
                        printf("%d ", -1*game_board[i][j]);
                    }

                }
                SetConsoleTextAttribute(hConsole, 7);
                printf(" ");
            }
            else if(map_bin[i][j]==FORBIDDEN){
                if(game_board[i][j]==0){
                    SetConsoleTextAttribute(hConsole, colors[3]*17);
                    printf("FF");
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(" ");
                }
            }
            else if(map_bin[i][j]==NORMAL){
                if(game_board[i][j]==0){
                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                    printf("NN");
                }else if(game_board[i][j]>0){
                    SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                    if(game_board[i][j]>9){
                        printf("%d", game_board[i][j]);
                    }else{
                        printf("%d ", game_board[i][j]);
                    }

                }else if(game_board[i][j]<0){
                    SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                    if(-1*game_board[i][j]>9){
                        printf("%d", -1*game_board[i][j]);
                    }else{
                        printf("%d ", -1*game_board[i][j]);
                    }

                }
                SetConsoleTextAttribute(hConsole, 7);
                printf(" ");
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 7);
    printf("\n");
    print_block_energies(boostup_blocks, num_boostup_blocks);
    return;

}


int millisleep(unsigned ms){
    SetLastError(0);
    Sleep(ms);
    return GetLastError() ?-1 :0;
}
