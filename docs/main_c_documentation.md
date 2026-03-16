# Main Controller Documentation

## File Overview

- File: `main.c`
- Role: Entry point of the Skyport Terminal system
- Purpose: Initializes the program, displays the main terminal menu, and routes the user to each subsystem

## Purpose of the File

The `main.c` file acts as the central controller of the Airport Flight Management System. It is responsible for starting the program, showing the splash screen, displaying the main menu, reading the user's choice, and calling the correct module menu based on that selection.

This file does not store business data directly. Instead, it connects all modules together and controls the overall program flow.

## Header Files Included

- `stdio.h`: used for standard input and output
- `types.h`: shared data type definitions used across the project
- `ui.h`: user interface helper functions for formatting the terminal display
- `passengers.h`: passenger services module interface
- `flights.h`: flight operations module interface
- `baggage.h`: baggage services module interface
- `gates.h`: gate control module interface
- `boarding.h`: boarding control module interface
- `runway.h`: runway control module interface
- `schedule.h`: flight schedule module interface

## Main Function

### Function Signature

```c
int main()
```

### Responsibilities

The `main()` function performs the following tasks:

1. Initializes the runway queue by calling `initQueue()`.
2. Displays the system splash screen using `splashScreen()`.
3. Repeatedly displays the main terminal interface.
4. Reads the user's menu selection.
5. Uses a `switch` statement to route control to the correct module.
6. Displays a logout message when the user selects exit.
7. Terminates the program by returning `0`.

## Program Flow

The overall control flow of `main.c` is:

1. Start program
2. Initialize runway queue
3. Show splash screen
4. Enter menu loop
5. Display main terminal header and flight board
6. Display list of modules
7. Read user input
8. Call selected module menu
9. Return to main menu after module finishes
10. Exit when the user enters `0`

## Main Menu Options

The main menu routes the user to the following modules:

- `1`: Passenger Services
- `2`: Flight Operations
- `3`: Baggage Services
- `4`: Gate Control
- `5`: Boarding Control
- `6`: Runway Control
- `7`: Flight Schedule
- `0`: Exit system

## Control Structure Used

### 1. Do-While Loop

The file uses a `do-while` loop to keep the main terminal running until the user chooses to exit.

Why it is used:

- Ensures the menu is shown at least once
- Repeats the interface until `choice == 0`

### 2. Switch-Case Statement

The file uses a `switch` statement to route the program to the correct subsystem.

Why it is used:

- Makes menu handling simple and organized
- Improves readability compared to many `if-else` statements

## Functions Called from Other Modules

The file depends on these external functions:

- `initQueue()`
- `splashScreen()`
- `printHeader()`
- `printFlightBoard()`
- `boxDbl()`
- `boxEmpty()`
- `boxTitle()`
- `boxSep()`
- `boxRow()`
- `clrscr()`
- `msgERR()`
- `pressEnter()`
- `passengerMenu()`
- `flightMenu()`
- `baggageMenu()`
- `gateMenu()`
- `boardingMenu()`
- `runwayMenu()`
- `scheduleMenu()`

## Data Structures Used in This File

The `main.c` file does not define or manage any major data structure directly. Its role is control and navigation.

However, it indirectly accesses project data structures by calling each module. For example:

- Flights are shown through the flight linked list in `printFlightBoard()`
- Runway queue is initialized through `initQueue()`

## Algorithms Used in This File

The file does not implement advanced algorithms such as sorting or recursion.

It mainly uses:

- Iterative repetition through a `do-while` loop
- Decision-making through a `switch-case` statement

## Strengths

- Clean and simple program entry point
- Good separation of responsibilities
- Easy to understand menu routing
- Centralized navigation for all modules

## Limitations

- Uses `scanf("%d", &choice)` without checking whether the input is valid
- If the user enters non-numeric input, input handling may become inconsistent
- No final cleanup functions are called before exiting for dynamically allocated modules

## Suggested Improvements

1. Validate `scanf()` return values before using `choice`
2. Clear invalid input from the buffer when incorrect input is entered
3. Add cleanup functions for dynamically allocated structures before program exit
4. Consider splitting menu rendering into a helper function if the file grows larger

## Summary

The `main.c` file is the main controller of the project. It is responsible for starting the system, displaying the terminal interface, and connecting all functional modules together. It does not implement core data handling itself, but it is essential because it coordinates the whole Airport Flight Management System.
