#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>


int map[18][32],selected_map[18][32],select_pos[2],map_width,map_height,random_array[480];
int mine_num,checker,flag_num,mineflag_num;
int i,j,selec,rand_num,lose,color,c=1;
time_t start,end;
//PART 1--------
void Levelselect(){//主畫面選單
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(i=1;i<=3;i++){
        if(selec==i){
            SetConsoleTextAttribute(hConsole,10);
            printf(">");
        }else{
            SetConsoleTextAttribute(hConsole,7);
            printf(" ");
        }
        switch(i){ //選擇關卡 -輸出
        case 1:
            printf("初級\n");
            break;
        case 2:
            printf("中級\n");
            break;
        case 3:
            printf("高級\n");
            break;
        }
    }
    SetConsoleTextAttribute(hConsole,7);
    printf("\n↑↓:選擇選項 Space:確定 \n\n");

    switch(getch()){ //選擇關卡 -控制
        case 0xE0:
            switch(getch()){
                case 72:                //UP
                    if(selec > 1){selec--;}
                    system("cls");
                    Levelselect();
                    break;
                case 80:                //DOWN
                    if(selec < 3){selec++;}
                    system("cls");
                    Levelselect();
                    break;
                default:
                    system("cls");
                    Levelselect();
            }
            break;
        case ' ':
            system("cls");
            Load_level();
            break;
        default:
            system("cls");
            Levelselect();
    }
}

void Load_level(){//設定計算地圖
    switch(selec){
        case 1://9x9 10mines
            mine_num=10;
            map_width=9;
            map_height=9;
            break;
        case 2://16x16 40mines
            mine_num=40;
            map_width=16;
            map_height=16;
            break;
        case 3://30x16 99mines
            mine_num=99;
            map_width=30;
            map_height=16;
            break;
    }

    //隨機地雷New
    /*int tmp;
    for(i=0;i<map_width*map_height;i++){
        rand_num=rand()%(map_width*map_height);

        tmp=random_array[i];
        random_array[i]=random_array[rand_num];
        random_array[rand_num]=tmp;
    }
    for(i=0;i<mine_num;i++){
        map[random_array[i]/map_width+1][random_array[i]%map_width+1]=-1;
    }*/
    // 隨機地雷Old
    for(i=0;i<mine_num;i++){
        rand_num=rand()%(map_width*map_height);
        while(map[rand_num/map_width+1][rand_num%map_width+1]==1){
            rand_num=rand()%(map_width*map_height);
        }
        map[rand_num/map_width+1][rand_num%map_width+1]=-1;
    }

    int a,b;
    for(i=1;i<=map_height;i++){         //地雷計算
        for(j=1;j<=map_width;j++){
            if(map[i][j]!=-1){
                for(a=i-1;a<=i+1;a++){
                    for(b=j-1;b<=j+1;b++){
                        if(map[a][b]==-1){
                            map[i][j]++;
                        }
                    }
                }

                //counting_map[i][j]=map[i-1][j-1]+map[i-1][j]+map[i-1][j+1]+map[i][j-1]+map[i][j+1]+map[i+1][j-1]+map[i+1][j]+map[i+1][j+1];
            }
        }
    }
    Output_Level();
}
//PART 2--------
void Output_Level(){//輸出地圖
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    checker=0;
    flag_num=0;
    mineflag_num=0;

    for(i=1;i<=map_height;i++){
        for(j=1;j<=map_width;j++){
            //紀錄
            if(selected_map[i][j]!=1){
                checker++;
                if(selected_map[i][j]==2){
                    flag_num++;
                    if(map[i][j]==-1){
                        mineflag_num++;
                    }
                }
            }

            //選取位置標示
            if(i==select_pos[0]&&j==select_pos[1]){
                color=240;
                SetConsoleTextAttribute(hConsole,color);
            }else{
                color=0;
            }

            //地圖輸出
            if(selected_map[i][j]==0){
                printf("■");
            }else if(selected_map[i][j]==2){
                SetConsoleTextAttribute(hConsole,color+14);
                printf("★");
            }else if(map[i][j]==-1){
                printf("※");
            }else if(map[i][j]==0){
                printf("　");
            }else{
                switch(map[i][j]){
                case 1:
                    SetConsoleTextAttribute(hConsole,color+9);
                    printf("１");
                    break;
                case 2:
                    SetConsoleTextAttribute(hConsole,color+10);
                    printf("２");
                    break;
                case 3:
                    SetConsoleTextAttribute(hConsole,color+12);
                    printf("３");
                    break;
                case 4:
                    SetConsoleTextAttribute(hConsole,color+1);
                    printf("４");
                    break;
                case 5:
                    SetConsoleTextAttribute(hConsole,color+4);
                    printf("５");
                    break;
                case 6:
                    SetConsoleTextAttribute(hConsole,color+3);
                    printf("６");
                    break;
                case 7:
                    SetConsoleTextAttribute(hConsole,color+5);
                    printf("７");
                    break;
                case 8:
                    SetConsoleTextAttribute(hConsole,color+8);
                    printf("８");
                    break;
                }

            }
            SetConsoleTextAttribute(hConsole,7);
        }
        printf("\n");
    }

    printf("\n★:%d ※:%d\n",flag_num,mine_num);

    printf("\n↑↓←→:移動目標 Space:確定 X:插旗\n\n");
    //printf("選擇座標:(%d,%d)",select_pos[0],select_pos[1]);

    if(checker==mine_num || (mineflag_num==mine_num && flag_num==mine_num)){//勝利條件
        system("cls");
        Gameover();
    }else{
        Control();
    }
}

void Control(){//遊戲控制


    switch(getch()){
    case 0xE0:

        switch(getch()){ //方向鍵操作控制
        case 72:                //UP
            if(select_pos[0]!=1){
                select_pos[0]-=1;
            }
            break;
        case 80:                //DOWN
            if(select_pos[0]!=map_height){
                select_pos[0]+=1;
            }
            break;
        case 75:                //LEFT
            if(select_pos[1]!=1){
                select_pos[1]-=1;
            }
            break;
        case 77:                //RIGHT
            if(select_pos[1]!=map_width){
                select_pos[1]+=1;
            }
            break;
        }
        break;
    case ' ': //選取
        if(c==1){//開始計時
            start=time(NULL);
            c=0;
        }

        if(selected_map[select_pos[0]][select_pos[1]]==0){
            selected_map[select_pos[0]][select_pos[1]]=1;
            if(map[select_pos[0]][select_pos[1]]==-1){//失敗條件
                lose=1;
            }else if(map[select_pos[0]][select_pos[1]]==0){
                Safe_sweeper(select_pos[0],select_pos[1]);//邏輯運算(空格排除)
            }
            break;
        }else{
            system("cls");
            Output_Level();
        }
    case 'x'://插旗
        if(selected_map[select_pos[0]][select_pos[1]]==0){
            selected_map[select_pos[0]][select_pos[1]]=2;
        }else if(selected_map[select_pos[0]][select_pos[1]]==2){
            selected_map[select_pos[0]][select_pos[1]]=0;
        }
        break;
    /*default:
        system("cls");
        Output_Level();*/
    }

    system("cls");
    if(lose==1){
        Gameover();
    }else{
        Output_Level();
    }
}

void Safe_sweeper(int y,int x){ //進階邏輯運算(空格排除)
    int n,m;
    for(n=y-1;n<=y+1;n++){
        for(m=x-1;m<=x+1;m++){
            if(n==0 || n>map_height || m==0 || m>map_width ||(n==y &&m==x)){ //排除邊界與自身
                continue;
            }

            if(selected_map[n][m]!=1 && map[n][m]==0){
                selected_map[n][m]=1;
                Safe_sweeper(n,m);
            }else{
                selected_map[n][m]=1;
            }
        }
    }

}

void Gameover(){ //遊戲結束
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    end=time(NULL);
    for(i=1;i<=map_height;i++){
        for(j=1;j<=map_width;j++){
            if(i==select_pos[0]&&j==select_pos[1]){
                color=240;
                SetConsoleTextAttribute(hConsole,color);
            }else if(selected_map[i][j]==2){
                color=64;
            }else{
                color=0;
            }

            if(map[i][j]==-1){
                if(selected_map[i][j]==2){
                    SetConsoleTextAttribute(hConsole,14);
                }
                printf("※");
                SetConsoleTextAttribute(hConsole,7);
            }else if(selected_map[i][j]==0){
                printf("■");
            }else if(map[i][j]==0){
                printf("　");
            }else{
                switch(map[i][j]){
                case 1:
                    SetConsoleTextAttribute(hConsole,color+9);
                    printf("１");
                    break;
                case 2:
                    SetConsoleTextAttribute(hConsole,color+10);
                    printf("２");
                    break;
                case 3:
                    SetConsoleTextAttribute(hConsole,color+12);
                    printf("３");
                    break;
                case 4:
                    SetConsoleTextAttribute(hConsole,color+1);
                    printf("４");
                    break;
                case 5:
                    SetConsoleTextAttribute(hConsole,color+4);
                    printf("５");
                    break;
                case 6:
                    SetConsoleTextAttribute(hConsole,color+3);
                    printf("６");
                    break;
                case 7:
                    SetConsoleTextAttribute(hConsole,color+5);
                    printf("７");
                    break;
                case 8:
                    SetConsoleTextAttribute(hConsole,color+8);
                    printf("８");
                    break;
                }
            }
            SetConsoleTextAttribute(hConsole,7);
        }
        printf("\n");
    }
    if(lose == 1){
        printf("\n你踩到地雷了!\n");
    }else{
        printf("\n你清光地雷了! 耗時:%d秒\n", (int) difftime(end,start));
    }
}


int main(){
    //初始化
    selec=1;
    memset(map,0,sizeof(map));
    select_pos[0]=1;
    select_pos[1]=1;
    memset(selected_map,0,sizeof(selected_map));
    for(i=0;i<480;i++){
        random_array[i]=i;
    }

    lose=0;


    //初始隨機值
    srand(time(NULL));
    rand();

    Levelselect();

    return 0;
}
