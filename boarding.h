/* boarding.h - Boarding Control Header (Stack) */
#ifndef BOARDING_H
#define BOARDING_H

#include "types.h"

extern struct Stack boardingStack;

void initStack(void);
int isStackEmpty(void);
int isStackFull(void);
int alreadyBoarded(int id);
void boardPassenger(void);
void deboardPassenger(void);
void viewLastBoarded(void);
void displayBoardingList(void);
void boardingMenu(void);

#endif
