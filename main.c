#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "cells.h"
#include "map.h"


void map_handler(int***map_bin, int* num_forbiden_blocks, int* num_boost_blocks, int ***game_board, int ***boostup_blocks, int* size_game){
    FILE* fi=fopen("map.bin", "rb");
    unsigned int n;
    fread(&n, sizeof(unsigned int), 1, fi);
    *size_game=n;
    // printf("this is n: %d\n",n);

    *map_bin=(int**)malloc(n*sizeof(int*));
    char temp;
    for(int i=0; i<n; i++){
        (*map_bin)[i]=(int *)malloc(n*sizeof(int));
        for(int j=0; j<n; j++){
            fread(&temp, sizeof(char), 1, fi);
            (*map_bin)[i][j]=atoi(&temp);
            if((*map_bin)[i][j]==FORBIDDEN){
                (*num_forbiden_blocks)++;
            }
            if((*map_bin)[i][j]==ENERGY){
                (*num_boost_blocks)++;
            }
            // printf("this is temp: %c\n", temp);
            // printf("this is map_bin[%d][%d]= %d\n", i, j, map_bin[i][j]);
        }
    }
    fclose(fi);
    *game_board=(int **)malloc((*size_game)*sizeof(int*));
    for(int i=0; i<(*size_game); i++){
        (*game_board)[i]=(int *)malloc((*size_game)*sizeof(int));
        for(int j=0; j<(*size_game); j++){
            (*game_board)[i][j]=0;//khuneye khat i om va sotun j om ro 0 kon
        }
    }
    if(num_boost_blocks!=0){
        *boostup_blocks=(int**)malloc((*num_boost_blocks)*sizeof(int*));//gharare ye aray do boD beshe
        int** boostup_blocks1=*boostup_blocks;
        boostup_blocks1[0]=(int *)malloc(sizeof(int)*3);//avali x, dovomi y, sevomi point//har khat 3 ta sotun dare
        int counter_boost_blocks=0;
    //alan darim ye array dobodi ba 3 ta SOTUN dorost mikonim va numboostup_blocks ta khat
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if((*map_bin)[i][j]==ENERGY){
                    boostup_blocks1[counter_boost_blocks][0]=j;
                    boostup_blocks1[counter_boost_blocks][1]=i;
                    boostup_blocks1[counter_boost_blocks][2]=100;
                    millisleep(1000);
                    counter_boost_blocks++;
                    if(counter_boost_blocks==(*num_boost_blocks)){
                        break;
                    }
                    boostup_blocks1[counter_boost_blocks]=(int *)malloc(sizeof(int)*3);//sotun haye khate badi ro misazim
                }
                // printf("this is temp: %c\n", temp);
                // printf("this is map_bin[%d][%d]= %d\n", i, j, map_bin[i][j]);
            }
            if(counter_boost_blocks==(*num_boost_blocks)){
                break;
            }
        }
    }
    return ;
}//debuged but we cant put it in other file.c god knows why


int first_menu(){//menu aval bazi ro neshun mide va khurujish gharare ke entekhab karbar bashe

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    printf("[1]");
    SetConsoleTextAttribute(hConsole, 9);
    printf("Load \n");
    SetConsoleTextAttribute(hConsole, 4);
    printf(" if you changed the map in the step before you cannot choose the next option\n");
    printf("[2]");
    SetConsoleTextAttribute(hConsole, 9);
    printf("New single player game \n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[3]");
    SetConsoleTextAttribute(hConsole, 9);
    printf("New Multiplayer game \n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[4]");
    SetConsoleTextAttribute(hConsole, 9);
    printf("Exit\n");
    SetConsoleTextAttribute(hConsole, 7);
    int input;
    scanf("%d", &input);
    while(input>4||input<1){
        printf("Please enter a valid number\n");
        scanf("%d", &input);
    }
    return input;
}//debuged

int sec_menu1(){
    printf("Do you want to play with the program or alone?\n");
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    printf("[1]");
    SetConsoleTextAttribute(hConsole, 9);
    printf("Alone\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[2]");
    SetConsoleTextAttribute(hConsole, 9);
    printf("Smart program\n");
    SetConsoleTextAttribute(hConsole, 7);
    int choice2;
    scanf("%d", &choice2);

    while(choice2>2||choice2<1){
        printf("Please enter a valid number\n");
        scanf("%d", &choice2);
    }
}//debuged

int num_cells(int num_forbiden_blocks, int num_cells1, int num_cells2, int size_game){
    printf("Please enter the number of cells you want to play with\n");
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    printf("(Rules: 0<number of cells< 100\n");
    printf("they should fit in the board game wich has ");
    SetConsoleTextAttribute(hConsole, 9);
    printf("%d", size_game*size_game-num_forbiden_blocks-num_cells1-num_cells2);
    SetConsoleTextAttribute(hConsole, 4);
    printf(" blocks available)\n");
    SetConsoleTextAttribute(hConsole, 7);
    int num_cells;
    scanf("%d", &num_cells);
    while(num_cells>100||num_cells<1||num_cells>(size_game*size_game)-(num_forbiden_blocks)-(num_cells1)-(num_cells2)){
//inja ma saghf 100 ro baraye tedad cell haye karbar dar nazar gerfTm
        printf("please enter a valid number\n");
        scanf("%d", &num_cells);
    }
    return num_cells;
}//tedaD ke behet barmigardune ghabel ghabule hatmn

int choseName(){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("do you want to give them name yourself?\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("1)");
    SetConsoleTextAttribute(hConsole, 9);
    printf("yes  ");
    SetConsoleTextAttribute(hConsole, 4);
    printf("2)");
    SetConsoleTextAttribute(hConsole, 9);
    printf("no\n");
    SetConsoleTextAttribute(hConsole, 7);
    int choice;
    scanf("%d", &choice);
    while(choice>2||choice<1){
        printf("ENTER A VALID NUMBER\n");
        scanf("%d", &choice);
    }
    return choice;
}














int color(int num_player, int colors[6]){
    printf("Do you want to choose the colors of your player/s and the blocks?\n");
    printf("1)yes   2)no, use the default ones\n");
    int choice;
    scanf("%d", &choice);
    while(choice>2||choice<1){
        printf("ENTER A VALID NUMBER\n");
        scanf("%d", &choice);
    }
    if(choice==2){
        colors[0]=1;//code khode rang bedune pas zamine
        colors[1]=6;
        colors[2]=2;
        colors[3]=5;
        colors[4]=8;
        colors[5]=4;
        return choice;
    }
    else{
        if(num_player==1){
            printf("which color do you want for your player?\n");
            //choosing color
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // you can loop k higher to see more color choices
            for(int k = 1; k < 16; k++){
                SetConsoleTextAttribute(hConsole, k);
                printf("%d) This is the color i want\n", k);
            }
            scanf("%d", &colors[0]);
            colors[5]=0;
        }else{
            //choosing color
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // you can loop k higher to see more color choices
            for(int k = 1; k < 16; k++){
                SetConsoleTextAttribute(hConsole, k);
                printf("%d) This is the color i want\n", k);
            }
            SetConsoleTextAttribute(hConsole, 7);
            printf("enter the color you want for your player(player one): ");
            scanf("%d", &colors[0]);
            while(colors[0]>16||colors[0]<1){
                printf("ENTER A VALID NUMBER\n");
                scanf("%d", &colors[0]);
            }
            printf("enter the color you want for your player(player two): \n");
            SetConsoleTextAttribute(hConsole, 4);
            printf("should not be the same az the player one\nit is recommended not to choose alike colors\n");
            SetConsoleTextAttribute(hConsole, 7);
            scanf("%d", &colors[5]);
            while(colors[5]>16||colors[5]<1||colors[5]==colors[0]){
                printf("ENTER A VALID NUMBER\n");
                scanf("%d", &colors[5]);
            }
        }
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
        int k=1;
        for(int i=17; i<239; i+=17, k++){
            if(i==119){
                k--;
                continue;
            }
            SetConsoleTextAttribute(hConsole, 7);
            printf("%d)", k);
            SetConsoleTextAttribute(hConsole, i);
            printf("cc");
            SetConsoleTextAttribute(hConsole, 7);
            printf("\t");
            // if(i%5==0){
            //     SetConsoleTextAttribute(hConsole, 7);
            //     printf("\n");
            // }
        }
        SetConsoleTextAttribute(hConsole, 7);
        printf("\nshouldent be the same as the avatar/s \n");

        printf("which color do you want for the energy block? ");
        scanf("%d", &colors[1]);
        if(colors[1]>=7){
            colors[1]++;
        }
        while(colors[1]<0||colors[1]>13||colors[0]==colors[1]||colors[5]==colors[1]){
            printf("ENTER A VALID NUMBER\n");
            scanf("%d", &colors[1]);
            if(colors[1]>=7){
                colors[1]++;
            }
        }
        printf("which color do you want for the mitosis block? ");
        scanf("%d", &colors[2]);
        if(colors[2]>=7){
            colors[2]++;
        }
        while(colors[2]<0||colors[2]>13||colors[2]==colors[0]||colors[2]==colors[5]||colors[2]==colors[1]){
            printf("ENTER A VALID NUMBER\n");
            scanf("%d", &colors[2]);
            if(colors[2]>=7){
                colors[2]++;
            }
        }

        printf("which color do you want for the forbidden block? ");
        scanf("%d", &colors[3]);
        if(colors[3]>=7){
            colors[3]++;//az alan be bad har adadi ke in tu bud ro varmidari zarb dar 17 mikonish rang kham mishe
        }
        while(colors[3]<0||colors[3]>13||colors[3]==colors[1]||colors[3]==colors[0]||colors[3]==colors[2]||colors[3]==colors[5]){
            printf("ENTER A VALID NUMBER\n");
            scanf("%d", &colors[3]);
            if(colors[3]>=7){
                colors[3]++;//az alan be bad har adadi ke in tu bud ro varmidari zarb dar 17 mikonish rang kham mishe
            }
        }

        printf("which color do you want for the normal block? ");
        scanf("%d", &colors[4]);
        if(colors[4]>=7){
            colors[4]++;
        }
        while(colors[4]<0||colors[4]>15||colors[4]==colors[0]||colors[4]==colors[1]||colors[4]==colors[2]||colors[4]==colors[3]||colors[4]==colors[5]){
            printf("ENTER A VALID NUMBER\n");
            scanf("%d", &colors[4]);
            if(colors[4]>=7){
                colors[4]++;
            }
        }
    }
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
    printf("for example\n");
    SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
    printf("this");
    SetConsoleTextAttribute(hConsole, 7);
    printf("is player one in a block of energy\nand ");
    SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
    printf("this");
    SetConsoleTextAttribute(hConsole, 7);
    printf("is player two in a block of energy\n");
    // printf("alan tuye color()\n");
    // for(int i=0; i<6; i++){
    //     printf("colors[%d] is : %d\n", i, colors[i]);
    // }
}//works perfectly and its match with the print function



void map_editor(int ***map_bin, int* size_game,int* num_boost_blocks, int* num_forbiden_blocks, int*** game_board, int*** boostup_blocks){
//bayad tuye marhaleye ghabli be karbar gofte beshe ke gharare bazi kolan reseat beshe va tamam etelat ghabli az dast khahad raft
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE* save_binary_map=fopen("map.bin", "wb");
    printf("how many rows/columns do you want in the new map?\n");
    unsigned int n;
    scanf("%d", &n);
    while(n<1){
        printf("must be: rows>=1\n");
        scanf("%d", &n);
    }
    *size_game=n;
    fwrite(&n, sizeof(unsigned int), 1, save_binary_map);
    //boostup_blocks ye array do boDe ke sotun avelsh x, sotune dovomesh y va sotune sevomesh emtiaz, va be tedade num_boostup_blocks khate dare
    
    *num_boost_blocks=0;
    //meghdare ghablish ro barey free kardn bayad negah darim
    *num_forbiden_blocks=0;

    printf("the states of a block are:\n");
    SetConsoleTextAttribute(hConsole, 14);
    printf("1)ENERGY\n");
    SetConsoleTextAttribute(hConsole, 2);
    printf("2)MITOSIS\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("3)FORBIDDEN\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("4)NORMAL\n");
    SetConsoleTextAttribute(hConsole, 7);
    
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<n; j++){
            if(j%2==1){
                printf("        ");
                continue;
            }
            else if(j%2==0){
                printf("(%2d,%2d) ", j, i);
            }
        }
        printf("\n");
        for(int j=0; j<n; j++){
            if(j%2==0){
                printf("        ");
            }
            else if(j%2==1){
                printf("(%2d,%2d) ", j, i);
            }
        }
        printf("\n");
    }
    int state;
    *map_bin=(int**)malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++){
        (*map_bin)[i]=(int*)malloc(sizeof(int)*n);
        for(int j=0; j<n; j++){
            printf("enter the state of block: (%d, %d): ", j, i);
            scanf("%d", &state);
            while(state>4||state<1){
                printf("ENTER A VALID NUMBER\n");
                scanf("%d", &state);
            }
            (*map_bin)[i][j]=state;
            char a;
            itoa(state, &a, 10);
            fwrite(&a, sizeof(char), 1, save_binary_map);
        }
    }
    fclose(save_binary_map);
    int** map_bin1=*map_bin;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(map_bin1[i][j]==FORBIDDEN){
                (*num_forbiden_blocks)++;
            }
            if(map_bin1[i][j]==ENERGY){
                (*num_boost_blocks)++;
            }
        }
    }
    *game_board=(int**)malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++){
        (*game_board)[i]=(int *)malloc(n*sizeof(int));
        for(int j=0; j<n;j++){
            (*game_board)[i][j]=0;
        }
    }

    *boostup_blocks=malloc( (*num_boost_blocks)*sizeof(int*));//hala hame khunehayi ke ghabln gerefte budim ro khali mikonim
    (*boostup_blocks)[0]=malloc( 3*sizeof(int));
    int counter_boostup=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(map_bin1[i][j]==ENERGY){
                (*boostup_blocks)[counter_boostup][0]=j;
                (*boostup_blocks)[counter_boostup][1]=i;
                (*boostup_blocks)[counter_boostup][2]=100;
                counter_boostup++;
                if(counter_boostup==(*num_boost_blocks)){
                    break;
                }
                (*boostup_blocks)[counter_boostup]=malloc(3*sizeof(int));
            }
        }
        if(counter_boostup==(*num_boost_blocks)){
            break;
        }
    }
    return;
}//deghat shavad in tabe ro nemishe vasat bazi estefade kard chon hich kari ba x va y cell ha nadre 
//darzemn inja farz shode ke aval bazie va emtiaz manabe 100 set mishe
//tuye khodesh seda mishe print() va be karbar neshun dade mishe taghirat anjam shode

int Load(struct cell** head_1, struct cell** head_2, int***map_bin, int* num_forbiden_blocks, int* num_boost_blocks, int ***game_board, int ***boostup_blocks, int* size_game){
    //if returns 0 wasnt able to load it, else gives the number of players in the game
    FILE* save_file_cells=fopen("save_cells.txt", "r");
    if(save_file_cells==NULL){
        printf("Nothing was saved in the games before\n");
        return 0;
    }   
    int num_players;
    fscanf(save_file_cells, "%d\n", &num_players);
    fscanf(save_file_cells, "1\n");
    int num_cells1;

    fscanf(save_file_cells, "%d\n", &num_cells1);
    *head_1=mitosis();
    struct cell* temp=*head_1;
    int size_name;
    fscanf(save_file_cells,"%d-%d-%d-%d-", &temp->x, &temp->y, &temp->glucose, &size_name);
    char* name1=malloc(sizeof(char)*size_name+3);
    fgets(name1, size_name+3, save_file_cells);
    name1[size_name]='\0';
    temp->name=name1;
    temp->index=1;
    for(int i=2; i<=num_cells1; i++){
        temp->next_cell=mitosis();
        temp=temp->next_cell;
        fscanf(save_file_cells,"%d-%d-%d-%d-", &temp->x, &temp->y, &temp->glucose, &size_name);
        name1=malloc(sizeof(char)*size_name+3);
        fgets(name1,size_name+3, save_file_cells);
        name1[size_name]='\0';
        temp->name=name1;
        temp->index=i;
    }
    if(num_players==2){
        fscanf(save_file_cells, "2\n");
        int num_cells2;
        fscanf(save_file_cells, "%d\n", &num_cells2);
        *head_2=mitosis();
        temp=*head_2;
        fscanf(save_file_cells,"%d-%d-%d-%d-", &temp->x, &temp->y, &temp->glucose, &size_name);
        name1=malloc(sizeof(char)*size_name+3);
        fgets(name1, size_name+3, save_file_cells);
        name1[size_name]='\0';
        temp->name=name1;
        temp->index=1;
        for(int i=2; i<=num_cells1; i++){
            temp->next_cell=mitosis();
            temp=temp->next_cell;
            name1=malloc(sizeof(char)*size_name+3);
            fscanf(save_file_cells,"%d-%d-%d-%d-", &temp->x, &temp->y, &temp->glucose, &size_name);
            fgets(name1, size_name+3, save_file_cells);
            name1[size_name]='\0';
            temp->name=name1;
            temp->index=i;
            temp=temp->next_cell;
        }
    }
    //ta inja ma etelaat bazikon haro bazyabi karDm
    //alan bayad etelaat naghshe ro bayabi konim
    map_handler(map_bin,  num_forbiden_blocks,  num_boost_blocks, game_board, boostup_blocks, size_game);
    temp=*head_1;
    while(temp!=NULL){
        (*game_board)[temp->y][temp->x]=temp->index;
        temp=temp->next_cell;
    }

    if(head_2!=NULL){
        temp=*head_2;
        while(temp!=NULL){
            (*game_board)[temp->y][temp->x]=temp->index*-1;
            temp=temp->next_cell;
        }
    }
    FILE* save_file_naghshe=fopen("save_map_points.txt", "r");
    if(save_file_naghshe==NULL){
        printf("there is an error");
        exit(0);
    }
    int N_boostup;
    fscanf(save_file_naghshe,"%d\n", &N_boostup);
    *num_boost_blocks=N_boostup;
    *boostup_blocks=(int **)malloc(sizeof(int*)*N_boostup);
    for(int i=0; i<N_boostup; i++){
        (*boostup_blocks)[i]=(int*)malloc(sizeof(int)*3);
    }
    for(int i=0; i<N_boostup; i++){
        fscanf(save_file_naghshe,"%d-%d-%d\n",&((*boostup_blocks)[i][0]), &((*boostup_blocks)[i][1]), &((*boostup_blocks)[i][2]));//x-y-energy  
    }
    fclose(save_file_naghshe);
    fclose(save_file_cells);
    return num_players;
    
}

void Save(int num_players, struct cell* head_of_list1, struct cell* head_of_list2, int size_game, int num_boost_blocks, int** boostup_blocks){
    FILE* save_file_cells=fopen("save_cells.txt", "w");
    if(save_file_cells==NULL){
        printf("cannot save it\n");
        return;
    }
    
    struct cell* temp=head_of_list1;
    fprintf(save_file_cells,"%d\n", num_players);
    ///
    fprintf(save_file_cells,"%d\n", 1);
    int num_cells;
    for(num_cells=1; temp->next_cell!=NULL; num_cells++){
        temp=temp->next_cell;
    }//check shavad
    temp=head_of_list1;
    fprintf(save_file_cells,"%d\n", num_cells);
    while(temp!=NULL){
        int size_name=strlen(temp->name);
        fprintf(save_file_cells,"%d-%d-%d-%d-%s\n", temp->x, temp->y, temp->glucose, size_name, temp->name);
        temp=temp->next_cell;
    }
    if(num_players==2){
        temp=head_of_list2;
        fprintf(save_file_cells,"%d\n", 2);
        for(num_cells=1; temp->next_cell!=NULL; num_cells++){
            temp=temp->next_cell;
        }
        temp=head_of_list2;
        fprintf(save_file_cells,"%d\n", num_cells);
        while(temp!=NULL){
            int size_name=0;
            char* name_temp=temp->name;
            size_name=strlen(name_temp);
            fprintf(save_file_cells,"%d-%d-%d-%d-%s\n", temp->x, temp->y, temp->glucose,size_name, temp->name);
            temp=temp->next_cell;
        }   
    }
    fclose(save_file_cells);
    FILE* save_file_naghshe=fopen("save_map_points.txt", "w");
    if(save_file_naghshe==NULL){
        printf("cannot save the file\n");
        return;
    }
    fprintf(save_file_naghshe,"%d\n",num_boost_blocks);
    for(int i=0; i<num_boost_blocks; i++){
        fprintf(save_file_naghshe,"%d-%d-%d\n",boostup_blocks[i][0], boostup_blocks[i][1], boostup_blocks[i][2]);//x-y-energy  
    }
    fclose(save_file_naghshe);
}

void point_printer(struct cell* head_1, struct cell* head_2){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    printf("sum glucoses of the cells(player one):\n");
    int sum=0;
    while(head_1!=NULL){
        sum+=head_1->glucose;
        head_1=head_1->next_cell;
    }
    printf("%d\n", sum);
    SetConsoleTextAttribute(hConsole, 7);
    if(head_2!=NULL){
        sum=0;
        SetConsoleTextAttribute(hConsole, 11);
        printf("sum glucoses of the cells(player two):\n");
        while(head_2!=NULL){
            sum+=head_2->glucose;
            head_2=head_2->next_cell;
        }
        printf("%d\n", sum);
        SetConsoleTextAttribute(hConsole, 7);
    }
    return;
}


void play_menu(int index_cell, struct cell** head_of_list1, struct cell** head_of_list2, int player, int num_player, int size_game, int** map_bin, int** game_board, int num_boost_blocks, int** boostup_blocks){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    printf("[1] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Move\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[2] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Split a cell\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[3] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Boost energy\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[4] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Save\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[5] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Exit\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("[6] ");
    SetConsoleTextAttribute(hConsole, 7);
    printf(" Show the sum of points\n");
    int choice;
    scanf("%d", &choice);
    while(choice>5||choice<1){
        printf("ENTER A VALID NUMBER\n");
        scanf("%d", &choice);
    }
    if(choice==1){
        printf("pay attantion to where you move you move your cell, if cannot go that way, you lose your turn\n");
        if(player==1){
            Move(index_cell, *head_of_list1, 1, size_game, game_board, map_bin);//player mitune 1 ya 2 bashe
        }
        else{
            Move(index_cell, *head_of_list2, 2, size_game, game_board, map_bin);//player mitune 1 ya 2 bashe
        }
        return;
    }else if(choice==2){
        if(player==1){
            Split(index_cell, head_of_list1, 1, map_bin, size_game, game_board);
        }
        else{
            Split(index_cell, head_of_list2, 2, map_bin, size_game, game_board);
        }
        if(num_player==1){
            refresh_game_board(*head_of_list1, NULL, game_board, size_game);
        }
        else{
            refresh_game_board(*head_of_list1, *head_of_list2, game_board, size_game);
        }
        return;
    }else if(choice==3){
        if(player==1){
            BoostEnergy(index_cell, *head_of_list1, 1, map_bin, game_board, num_boost_blocks, boostup_blocks);
        }
        else{
            BoostEnergy(index_cell, *head_of_list2, 2, map_bin, game_board, num_boost_blocks, boostup_blocks);
        }
    }else if(choice==4){
        if(head_of_list1!=NULL&&head_of_list2!=NULL){
            Save(num_player, *head_of_list1, *head_of_list2, size_game, num_boost_blocks, boostup_blocks);
        }else if(head_of_list1!=NULL&&head_of_list2==NULL){
            Save(num_player, *head_of_list1, NULL, size_game, num_boost_blocks, boostup_blocks);
        }else if(head_of_list1==NULL&& head_of_list2==NULL){
            printf("nothing to be saved\n");
            return;
        }
    }else if(choice==5){
        if(head_of_list1!=NULL&&head_of_list2!=NULL){
            point_printer(*head_of_list1, *head_of_list2);
        }
        else if(head_of_list1!=NULL&&head_of_list2==NULL){
            point_printer(*head_of_list1, NULL);
        }
        printf("thnx for playing");
        exit(0);
    }else{
        if(head_of_list1!=NULL&&head_of_list2!=NULL){
            point_printer(*head_of_list1, *head_of_list2);
        }
        else if(head_of_list1!=NULL&&head_of_list2==NULL){
            point_printer(*head_of_list1, NULL);
        }
    }
    return;
}


int main(){
    time_t t=time(NULL);
    srand(t);
    int size_game;//vaghT naghshe ro mikhuni bare aval set mishe, faghat havaset bashe agar map_editor badan ke neveshTsh bayad dobare set beshe
    int num_cells1=0;
    int num_cells2=0;
    int** map_bin;//naghsheye bazi, yadet bashe ke ino set koni tuye map_editor
    int** game_board;
    int num_forbiden_blocks=0;//in 3 ta ro bayad local main bokoni
    int** boostup_blocks;
    int num_boost_blocks=0;//khate aval->X khate dovom->Y khate sevom->energy  
    int colors[6];
    //[0]=player1
    //[1]=blocks of energy raw
    //[2]=blocks of mitosis raw
    //[3]=forbidden blocks raw
    //[4]=normal blocks raw
    //[5]=player2

    printf("Do you want to play with your own map or the by-default one?\n");
    int map=0;
    printf("1)i want my own map\n2) by-default\n");
    scanf("%d", &map);
    if(map==1){
        map_editor( &map_bin, &size_game, &num_boost_blocks, &num_forbiden_blocks, &game_board, &boostup_blocks);
    }else{
        map_handler(&map_bin, &num_forbiden_blocks, &num_boost_blocks, &game_board, &boostup_blocks, &size_game);
    }

    if(size_game*size_game==num_forbiden_blocks){
        printf("there is no place\nsize_game*size_game==num_forbiden_blocks");
        return 0;
    }


    int choice_first_menu=first_menu();
    // print_block_energies(boostup_blocks, num_boost_blocks);
    struct cell* Head_Player_one=NULL;
    struct cell* Head_Player_two=NULL;
    int loaded=0;
    if(choice_first_menu==1){
        loaded=1;
        printf("if the last saved game was one of two players, this one will become one too.\nsame case for single player game\n");
        choice_first_menu=1+Load(&Head_Player_one, &Head_Player_two, &map_bin, &num_forbiden_blocks, &num_boost_blocks, &game_board, &boostup_blocks, &size_game);
    }

    if(choice_first_menu==2){
        int sec_choice=sec_menu1();
        color(1, colors);
        if(sec_choice==1){
            if(loaded==0){
                print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
                num_cells1=num_cells(num_forbiden_blocks, num_cells1, num_cells2, size_game);
                int choose_name=choseName();//agar 1 bale
                millisleep(1000);
                // system("cls");
                Head_Player_one=create_n_cells(num_cells1, choose_name, 1, size_game, map_bin, game_board);
            }
            print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
            millisleep(1000);
            // system("cls");
            print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
            while(2>1){
                printf("\nPlease choose one of your cells:\n");
                print_my_cells(Head_Player_one, 1, colors);
                int choosen_cell;
                scanf("%d", &choosen_cell);
                play_menu(choosen_cell, &Head_Player_one, NULL, 1, 1, size_game, map_bin, game_board, num_boost_blocks, boostup_blocks);//1 chon player one bazi mikone
                millisleep(1000);
                // system("cls");
                print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
            }
        }
        else if(sec_choice==2){//smart program XD
            // colors[5]=0;//bayad handle koni rang taraf moghabel

            printf("in ghesmat hanuz dayer nist :D\n");
        }
    }

    if(choice_first_menu==3){//new multiplayer game//inja farz shode ke faghat bazi mitune 2 nafare bashe
        color(2, colors);
        // printf("alan tuye main()\n");
        // for(int i=0; i<6; i++){
        //     printf("colors[%d] is : %d\n", i, colors[i]);
        // }
        printf("player one answer:\n");
        num_cells1=num_cells(num_forbiden_blocks, num_cells1, num_cells2, size_game);
        int choose_name1=choseName();//agar 1 bale
        Head_Player_one=create_n_cells(num_cells1, choose_name1, 1, size_game, map_bin, game_board);
        printf("player two answer:\n");
        num_cells2=num_cells(num_forbiden_blocks, num_cells1, num_cells2, size_game);
        int choose_name2=choseName();//agar 1 bale
        Head_Player_two=create_n_cells(num_cells2, choose_name2, 2, size_game, map_bin, game_board);
        // system("cls");
        print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
        // millisleep(1000);
        // system("cls");
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
        while(2>1){
            SetConsoleTextAttribute(hConsole, colors[0]);
            printf("player one answer:\n");
            SetConsoleTextAttribute(hConsole, 7);
            printf("Please choose one of your cells:\n");
            print_my_cells(Head_Player_one, 1, colors);
            int choosen_cell;
            scanf("%d", &choosen_cell);
            play_menu(choosen_cell, &Head_Player_one, &Head_Player_two, 1, 2, size_game, map_bin, game_board, num_boost_blocks, boostup_blocks);//1 chon player one bazi mikone
            // system("cls");
            print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
            millisleep(500);
            SetConsoleTextAttribute(hConsole, colors[5]);
            printf("player two answer:\n");
            SetConsoleTextAttribute(hConsole, 7);
            printf("Please choose one of your cells:\n");
            print_my_cells(Head_Player_two, 2, colors);
            scanf("%d", &choosen_cell);
            //inja farz mishavad ke karbar adad dorost vared karde.
            play_menu(choosen_cell, &Head_Player_one, &Head_Player_two, 2, 2, size_game, map_bin, game_board, num_boost_blocks, boostup_blocks);
            // system("cls");
            print(size_game, map_bin, game_board, colors, num_boost_blocks, boostup_blocks);
            millisleep(1000);
        }
    }
    else{
        return 0;
    }
}