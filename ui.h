/* ui.h - User Interface Functions Header */
#ifndef UI_H
#define UI_H

void clrscr(void);
void pressEnter(void);
void boxDbl(void);
void boxLine(void);
void boxEmpty(void);
void boxSep(void);
void boxTitle(const char* text);
void boxRow(const char* text);
void msgOK(const char* m);
void msgERR(const char* m);
void msgINFO(const char* m);
void msgWARN(const char* m);
void printHeader(const char* module);
void splashScreen(void);

#endif
