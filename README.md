# Flight Management Documentation

## File Overview

- Implementation file: `flights.c`
- Header file: `flights.h`
- Module name: Flight Operations
- Purpose: Manage flight records in the system

## Purpose of the Module

The flight management module handles all flight-related operations in the Airport Flight Management System. It allows the user to add, remove, search, display, and update flight records. It also provides a summary of flight statuses.

This module is accessed from the main menu through the Flight Operations option.

## Files in the Module

### `flights.h`

This header file contains:

- the external declaration of the flight list head pointer
- function prototypes for the flight operations module

### `flights.c`

This source file contains:

- the actual implementation of all flight operations
- the global flight list head pointer
- list traversal, insertion, deletion, searching, and counting logic

## Data Structure Used

### Flight List

The module stores flights using a linked list whose head pointer is:

```c
FlightNode* flightHead = NULL;
```

The node structure is defined in `types.h` as `FlightNode`.

### FlightNode Fields

Each node stores:

- flight number
- destination
- origin
- departure time
- arrival time
- gate
- total seats
- available seats
- status
- aircraft type
- next pointer
- prev pointer

### Important Note About the Data Structure

The comment in `flights.c` says the module uses a singly linked list. However, the implementation also uses a `prev` pointer during insertion and deletion.

That means the real implementation behaves more like a doubly linked list, even though most traversal operations move forward using `next`.

## Global Variable

```c
FlightNode* flightHead = NULL;
```

Purpose:

- stores the first node of the flight list
- allows all flight functions in the module to access the list

## Functions in the Module

### 1. `flightExists(const char* fn)`

#### Purpose

Checks whether a flight number already exists in the linked list.

#### Parameters

- `fn`: flight number to search for

#### Return Value

- `1` if the flight exists
- `0` if the flight does not exist

#### Method

- starts from `flightHead`
- traverses node by node
- compares each node's flight number with the target value

#### Algorithm Used

- linear search

#### Time Complexity

- O(n)

### 2. `addFlight()`

#### Purpose

Adds a new flight record into the list.

#### Method

1. Allocates memory for a new `FlightNode`
2. Reads flight information from the user
3. Checks for duplicate flight numbers using `flightExists()`
4. Sets default values such as status and available seats
5. Inserts the node at the end of the list

#### Algorithm Used

- linear search for duplicate detection
- tail insertion into linked list

#### Time Complexity

- O(n)

#### Memory Behavior

- uses `malloc()` to allocate a new node
- frees memory immediately if a duplicate flight number is entered

### 3. `removeFlight()`

#### Purpose

Removes a flight from the linked list using its flight number.

#### Method

1. Reads the target flight number
2. Traverses the list to find a matching node
3. Re-links neighboring nodes
4. Frees the removed node from memory

#### Algorithm Used

- linear search
- linked list deletion

#### Time Complexity

- O(n)

### 4. `searchFlight()`

#### Purpose

Searches for flights by flight number or destination.

#### Method

1. Reads a user query
2. Traverses the entire list
3. Uses substring matching to compare the query against flight number and destination
4. Displays all matches

#### Algorithm Used

- linear search
- substring matching using `strstr()`

#### Time Complexity

- O(n)

### 5. `displayAllFlights()`

#### Purpose

Displays all stored flights in tabular form.

#### Method

- traverses the linked list from head to tail
- prints each flight row
- counts total records while traversing

#### Algorithm Used

- full list traversal

#### Time Complexity

- O(n)

### 6. `updateFlightStatus()`

#### Purpose

Updates the status of a selected flight.

#### Method

1. Reads a flight number
2. Traverses the list to find the matching flight
3. Accepts a new status from the user
4. Updates the `status` field

#### Algorithm Used

- linear search

#### Time Complexity

- O(n)

### 7. `countFlights()`

#### Purpose

Counts flights by status and prints a summary.

#### Method

- traverses the full list once
- increments counters for:
  - total flights
  - on-time flights
  - delayed flights
  - cancelled flights

#### Algorithm Used

- single-pass counting traversal

#### Time Complexity

- O(n)

### 8. `flightMenu()`

#### Purpose

Displays the flight operations menu and routes user commands to the correct function.

#### Operations Available

- schedule new flight
- cancel or remove flight
- search flight
- view all flights
- update flight status
- show flight summary
- return to main terminal

#### Control Structures Used

- `do-while` loop
- `switch-case`

## Algorithms Used in the Module

The module mainly uses the following algorithms:

### 1. Linear Search

Used in:

- `flightExists()`
- `removeFlight()`
- `searchFlight()`
- `updateFlightStatus()`

### 2. Linked List Insertion

Used in:

- `addFlight()`

The new node is inserted at the end of the list after traversing to the last node.

### 3. Linked List Deletion

Used in:

- `removeFlight()`

The node is removed by adjusting pointers and freeing the node.

### 4. Counting Traversal

Used in:

- `countFlights()`
- `displayAllFlights()`

## Memory Management

### Efficient Practices Present

- memory is allocated only when a new flight is created
- duplicate entries are rejected before insertion is completed
- deleted flights are properly freed from memory

### Limitations

- there is no cleanup function to free all remaining flight nodes when the program exits
- memory is released only when individual flights are removed
- if many flights remain at exit, the operating system reclaims memory, but the program does not explicitly clean it up

## Strengths of the Module

- clear separation of flight operations from other modules
- straightforward list-based design
- supports all essential flight management operations
- easy to expand with extra flight fields or validations
- good reuse of UI helper functions for consistent display

## Weaknesses and Limitations

1. Input validation is limited
2. Flight status input accepts any string, not only valid predefined statuses
3. Tail insertion takes O(n) time because there is no tail pointer
4. The code comment says singly linked list, but the implementation also uses `prev`
5. No full cleanup routine exists for all remaining nodes

## Suggested Improvements

1. Add input validation for seat counts and status values
2. Restrict flight status to a valid set of options
3. Add a tail pointer to make insertion O(1)
4. Decide clearly whether the list should be singly or doubly linked and keep the implementation consistent
5. Add a `freeAllFlights()` cleanup function before program termination

## Summary

The flight management module is an important part of the system. It stores flight information in a linked-list-based structure and provides operations to insert, remove, search, display, and summarize flight data. The implementation is suitable for a coursework project and demonstrates linked list traversal and node management clearly, although it can be improved further in consistency, validation, and cleanup.
