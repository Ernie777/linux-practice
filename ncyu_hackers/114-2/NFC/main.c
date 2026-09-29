#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// 產生 4 位數答案，數字不重複
void generateAnswer(char answer[]) {
    int used[10] = {0};
    
    for (int i = 0; i < 4; i++) {
        int digit;
        
        do {
            digit = rand() % 10;
        } while (used[digit]);
        
        used[digit] = 1;
        answer[i] = digit + '0';
    }
    
    answer[4] = '\0';
}

// 檢查輸入是否為「剛好四位數字」
int isValidInput(char input[]) {
    int len = strlen(input);

    // 一定要剛好 4 個字
    if (len != 4) {
        return 0;
    }

    // 每一個字元都必須是數字
    for (int i = 0; i < 4; i++) {
        if (!isdigit((unsigned char)input[i])) {
            return 0;
        }
    }

    return 1;
}

// 計算幾A幾B
void calculateAB(char answer[], char guess[], int *A, int *B) {
    int answerCount[10] = {0};
    int guessCount[10] = {0};

    *A = 0;
    *B = 0;

    // 先計算 A
    for (int i = 0; i < 4; i++) {
        if (answer[i] == guess[i]) {
            (*A)++;
        }
    }

    // 統計兩邊各數字出現次數
    for (int i = 0; i < 4; i++) {
        answerCount[answer[i] - '0']++;
        guessCount[guess[i] - '0']++;
    }

    // 計算總共有幾個數字相同
    for (int i = 0; i < 10; i++) {
        *B += (answerCount[i] < guessCount[i])
             ? answerCount[i]
             : guessCount[i];
    }

    // A 不算在 B 裡
    *B -= *A;
}

int main() {
    char answer[5];
    char guess[100];
    int A, B;
    int count = 0;

    srand((unsigned int)time(NULL));

    generateAnswer(answer);

    printf("===== 幾A幾B =====\n");
    printf("請輸入 4 位數字\n\n");

    while (1) {
        printf("請輸入答案：");

        fgets(guess, sizeof(guess), stdin);

        // 移除最後的換行
        guess[strcspn(guess, "\n")] = '\0';

        // 防呆
        if (!isValidInput(guess)) {
            printf("輸入錯誤！請輸入「剛好 4 個數字」。\n\n");
            continue;
        }

        count++;

        calculateAB(answer, guess, &A, &B);

        printf("%dA%dB\n\n", A, B);

        if (A == 4) {
            printf("恭喜你答對了！\n");
            printf("總共猜了 %d 次。\n", count);
            break;
        }
    }

    return 0;
}
