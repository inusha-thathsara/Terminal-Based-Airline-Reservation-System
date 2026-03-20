// ============================================================
//  SKYPORT TERMINAL — UI HELPERS
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "ui.h"

void clrscr() { system("cls"); }

void pressEnter() {
    printf("\n  Press ENTER to continue . . .");
    getchar(); getchar();
}

void hline(char c) {
    int i;
    printf("  ");
    for (i = 0; i < WIDTH; i++) printf("%c", c);
    printf("\n");
}

void boxTop()    { int i; printf("  +"); for(i=0;i<WIDTH-2;i++) printf("-"); printf("+\n"); }
void boxBottom() { int i; printf("  +"); for(i=0;i<WIDTH-2;i++) printf("-"); printf("+\n"); }
void boxDbl()    { int i; printf("  +"); for(i=0;i<WIDTH-2;i++) printf("="); printf("+\n"); }

void boxTitle(const char* text) {
    int len = strlen(text);
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
    int len = strlen(text);
    int pad = WIDTH - 4 - len;
    int i;
    printf("  | %s", text);
    for (i = 0; i < pad; i++) printf(" ");
    printf(" |\n");
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
    char left[60], right[60];
    int llen, rlen, total, spaces, i;

    getCurrentTime(time_str);
    getCurrentDate(date);
    clrscr();
    printf("\n");
    boxDbl();
    sprintf(left,  "SKYPORT TERMINAL  |  %s", module);
    sprintf(right, "%s  %s", date, time_str);
    llen   = strlen(left);
    rlen   = strlen(right);
    total  = WIDTH - 4;
    spaces = total - llen - rlen;
    if (spaces < 1) spaces = 1;
    printf("  | %s", left);
    for (i = 0; i < spaces; i++) printf(" ");
    printf("%s |\n", right);
    boxDbl();
    printf("\n");
}

void printFlightBoard(struct FlightList* list) {
    struct FlightNode* curr;
    int count = 0;

    printf("\n");
    boxDbl();
    boxEmpty();
    boxTitle("~~  DEPARTURES / ARRIVALS BOARD  ~~");
    boxEmpty();
    boxDbl();

    if (list->head == NULL) {
        boxEmpty();
        boxTitle("-- NO FLIGHTS SCHEDULED --");
        boxEmpty();
        boxBottom();
        return;
    }

    printf("  | %-9s | %-14s | %-14s | %-7s | %-5s | %-7s |\n",
           "FLIGHT","FROM","TO","TIME","GATE","STATUS");
    boxSep();

    curr = list->head;
    while (curr != NULL && count < 5) {
        printf("  | %-9s | %-14s | %-14s | %-7s | %-5s | %-7s |\n",
            curr->flightNumber, curr->origin, curr->destination,
            curr->departureTime, curr->gate, curr->status);
        curr = curr->next;
        count++;
    }
    boxBottom();
}
