
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ui.h"
#include "utils.h"

#define WIDTH 70

void clrscr() { system("cls"); }

void pressEnter() {
    printf("\n  Press ENTER to continue . . .");
    getchar(); getchar();
}

void boxDbl() {
    int i;
    printf("  +");
    for (i = 0; i < WIDTH-2; i++) printf("=");
    printf("+\n");
}

void boxLine() {
    int i;
    printf("  +");
    for (i = 0; i < WIDTH-2; i++) printf("-");
    printf("+\n");
}

void boxEmpty() {
    int i;
    printf("  |");
    for (i = 0; i < WIDTH-2; i++) printf(" ");
    printf("|\n");
}

void boxSep() {
    int i;
    printf("  |");
    for (i = 0; i < WIDTH-2; i++) printf("-");
    printf("|\n");
}

void boxTitle(const char* text) {
    int len = manualStrLen(text);
    int total = WIDTH - 4;
    int lpad = (total - len) / 2;
    int rpad = total - len - lpad;
    int i;
    printf("  | ");
    for (i = 0; i < lpad; i++) printf(" ");
    printf("%s", text);
    for (i = 0; i < rpad; i++) printf(" ");
    printf(" |\n");
}

void boxRow(const char* text) {
    int len = manualStrLen(text);
    int pad = WIDTH - 4 - len;
    int i;
    printf("  | %s", text);
    for (i = 0; i < pad; i++) printf(" ");
    printf(" |\n");
}

void msgOK(const char* m)   { printf("\n  [ OK ]  %s\n", m); }
void msgERR(const char* m)  { printf("\n  [FAIL]  %s\n", m); }
void msgINFO(const char* m) { printf("\n  [INFO]  %s\n", m); }
void msgWARN(const char* m) { printf("\n  [WARN]  %s\n", m); }

void printHeader(const char* module) {
    char time_str[20], date[20];
    char left[60], right[60];
    int  spaces, i;
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(time_str, 20, "%H:%M:%S", tm_info);
    strftime(date,     20, "%d %b %Y", tm_info);
    clrscr();
    printf("\n");
    boxDbl();
    sprintf(left,  "SKYPORT TERMINAL  |  %s", module);
    sprintf(right, "%s  %s", date, time_str);
    spaces = WIDTH - 4 - manualStrLen(left) - manualStrLen(right);
    if (spaces < 1) spaces = 1;
    printf("  | %s", left);
    for (i = 0; i < spaces; i++) printf(" ");
    printf("%s |\n", right);
    boxDbl();
    printf("\n");
}

void splashScreen() {
    clrscr();
    printf("\n\n");
    boxDbl();
    boxEmpty();
    boxTitle("S K Y P O R T   T E R M I N A L");
    boxEmpty();
    boxTitle("AIRPORT FLIGHT MANAGEMENT SYSTEM");
    boxEmpty();
    boxSep();
    boxEmpty();
    boxTitle("* * *   AUTHORIZED PERSONNEL ONLY   * * *");
    boxEmpty();
    boxDbl();
    printf("\n  Press ENTER to access the system . . .");
    getchar();
}
