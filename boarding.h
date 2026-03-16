#ifndef BOARDING_H
#define BOARDING_H

#include "types.h"

// ============================================================
//  MEMBER 5 — BOARDING CONTROL
// ============================================================

extern StackNode* boardingTop;

int  isDuplicateBoarding(int id);
void pushBoarding();
void popBoarding();
void peekBoarding();
void displayBoardingList();
void undoBoarding();
void boardingMenu();

#endif
