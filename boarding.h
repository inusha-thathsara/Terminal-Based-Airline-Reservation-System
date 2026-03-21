#ifndef BOARDING_H
#define BOARDING_H

#include "types.h"

// ============================================================
//  MEMBER 5 — BOARDING CONTROL (STACK)
// ============================================================

void initStack(struct Stack* stack);
struct StackNode* createStackNode(int passengerID, char* passengerName,
                                   char* seatNumber);
int  isDuplicateBoarding(struct Stack* stack, int id);
void pushBoarding(struct Stack* stack);
void popBoarding(struct Stack* stack);
void peekBoarding(struct Stack* stack);
void displayBoardingList(struct Stack* stack);
void undoBoarding(struct Stack* stack);
void boardingMenu(struct Stack* stack);

#endif
