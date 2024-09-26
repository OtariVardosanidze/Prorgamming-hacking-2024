#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MILSEC 1000
/*
Небольшой хэдер, при помощи которого вывод можно сделать похожим на то, 
что кто - то вводит данные с клавиатуры в реальном времени.
А ЕЩЁ СДЕЛАТЬ РАДУЖНЫМ!!!
СПЛОШНОЙ КАЙФ, СМЕЮ ВАС ЗАВЕРИТЬ

Русские буквы почему - то не становятся радужными Ж8-(
*/
int randLower(int max){
    return rand() % (max + 1);
}

void lRPrint(char* input){
    int i = 0;
    while(input[i]){
        putchar(input[i]);
        fflush(stdout);
        i++;
        usleep((randLower(5) + 50) * MILSEC);
    }
}

void lRPrintRainbow(char* input){
    int i = 0;
    int color = 0;
    while(input[i]){
        color = 31 + i % 7;
        printf("\033[%dm", color);
        putchar(input[i]);
        fflush(stdout);
        i++;
        usleep((randLower(5) + 50) * MILSEC);
    }
    printf("\033[0m");
}

void lRPrintFromFile(char* filename){
    FILE* fp = fopen(filename, "r");
    char buffer[1024];
    if(fp){
        while(fgets(buffer, 1024, fp) != NULL){
            lRPrint(buffer);
        }
    }
    fclose(fp);
}

void lRPrintFromFileRainbow(char* filename){
    FILE* fp = fopen(filename, "r");
    char buffer[1024];
    if(fp){
        while(fgets(buffer, 1024, fp) != NULL){
            lRPrintRainbow(buffer);
        }
    }
    fclose(fp);
}
