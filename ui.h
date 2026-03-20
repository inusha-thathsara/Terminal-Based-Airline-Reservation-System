#ifndef UI_H
#define UI_H

#include "types.h"

// ============================================================
//  SKYPORT TERMINAL — UI DECLARATIONS
// ============================================================

void clrscr();
void pressEnter();
void hline(char c);
void boxTop();
void boxBottom();
void boxDbl();
void boxTitle(const char* text);
void boxRow(const char* text);
void boxEmpty();
void boxSep();
void msgOK(const char* m);
void msgERR(const char* m);
void msgINFO(const char* m);
void msgWARN(const char* m);
void getCurrentTime(char* buf);
void getCurrentDate(char* buf);
void splashScreen();
void printHeader(const char* module);
void printFlightBoard(struct FlightList* list);

#endif
