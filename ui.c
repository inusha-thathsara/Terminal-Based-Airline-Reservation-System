
// ============================================================
//  SKYPORT TERMINAL — UI HELPERS
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "ui.h"
#include "flights.h"

void clrscr() { system("cls"); }

void pressEnter() {
    printf("\n  Press ENTER to continue . . .");
    getchar(); getchar();
}

void hline(char c) {
    printf("  ");
    for (int i = 0; i < WIDTH; i++) printf("%c", c);
    printf("\n");
}

void boxTop()    { printf("  +"); for(int i=0;i<WIDTH-2;i++) printf("-"); printf("+\n"); }
void boxBottom() { printf("  +"); for(int i=0;i<WIDTH-2;i++) printf("-"); printf("+\n"); }
void boxDbl()    { printf("  +"); for(int i=0;i<WIDTH-2;i++) printf("="); printf("+\n"); }

void boxTitle(const char* text) {
    int len = strlen(text);
    int total = WIDTH - 4;
    int lpad = (total - len) / 2;
    int rpad = total - len - lpad;
    printf("  | ");
    for (int i = 0; i < lpad; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < rpad; i++) printf(" ");
    printf(" |\n");
}

void boxRow(const char* text) {
    int len = strlen(text);
    int pad = WIDTH - 4 - len;
    printf("  | %s", text);
    for (int i = 0; i < pad; i++) printf(" ");
    printf(" |\n");
}

void boxEmpty() {
    printf("  |");
    for (int i = 0; i < WIDTH-2; i++) printf(" ");
    printf("|\n");
}

void boxSep() {
    printf("  |");
    for (int i = 0; i < WIDTH-2; i++) printf("-");
    printf("|\n");
}

void msgOK(const char* m)   { printf("\n  [ OK ]  %s\n", m); }
void msgERR(const char* m)  { printf("\n  [FAIL]  %s\n", m); }
void msgINFO(const char* m) { printf("\n  [INFO]  %s\n", m); }
void msgWARN(const char* m) { printf("\n  [WARN]  %s\n", m); }

void getCurrentTime(char* buf) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buf, 20, "%H:%M:%S", tm_info);
}

void getCurrentDate(char* buf) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buf, 20, "%d %b %Y", tm_info);
}

void splashScreen() {
    clrscr();
    printf("\n\n\n");
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
    char date[20], time_str[20];
    getCurrentDate(date);
    getCurrentTime(time_str);
    printf("\n  Date     : %-30s\n", date);
    printf("  Time     : %-30s\n", time_str);
    printf("  Terminal : SKYPORT INTERNATIONAL AIRPORT\n");
    hline('-');
    printf("\n  Press ENTER to access the system . . .");
    getchar();
}

void printHeader(const char* module) {
    char time_str[20], date[20];
    getCurrentTime(time_str);
    getCurrentDate(date);
    clrscr();
    printf("\n");
    boxDbl();
    char left[60], right[60];
    sprintf(left,  "SKYPORT TERMINAL  |  %s", module);
    sprintf(right, "%s  %s", date, time_str);
    int llen = strlen(left);
    int rlen = strlen(right);
    int total = WIDTH - 4;
    int spaces = total - llen - rlen;
    if (spaces < 1) spaces = 1;
    printf("  | %s", left);
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s |\n", right);
    boxDbl();
    printf("\n");
}

void printFlightBoard() {
    extern FlightNode* flightHead;
    printf("\n");
    boxDbl();
    boxEmpty();
    boxTitle("~~  DEPARTURES / ARRIVALS BOARD  ~~");
    boxEmpty();
    boxDbl();
    if (!flightHead) {
        boxEmpty();
        boxTitle("-- NO FLIGHTS SCHEDULED --");
        boxEmpty();
        boxBottom();
        return;
    }
    printf("  | %-9s | %-14s | %-14s | %-7s | %-5s | %-7s |\n",
           "FLIGHT","FROM","TO","TIME","GATE","STATUS");
    boxSep();
    FlightNode* curr = flightHead;
    int count = 0;
    while (curr && count < 5) {
        printf("  | %-9s | %-14s | %-14s | %-7s | %-5s | %-7s |\n",
            curr->flightNumber, curr->origin, curr->destination,
            curr->departureTime, curr->gate, curr->status);
        curr = curr->next;
        count++;
    }
    boxBottom();
}
