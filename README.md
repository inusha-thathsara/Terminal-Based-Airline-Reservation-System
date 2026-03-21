# Baggage Management Documentation

------------------------------------------------------------------------

## File Overview

-   Implementation file: `baggage.c`\
-   Header file: `baggage.h`\
-   Module name: Baggage Services\
-   Purpose: Manage baggage records in the system

------------------------------------------------------------------------

## Purpose of the Module

The baggage management module handles all baggage-related operations in
the Airport Flight Management System. It allows the user to add, remove,
search, display, and analyze baggage records.

This module is accessed from the main menu through the Baggage Services
option.

------------------------------------------------------------------------

## Files in the Module

### `baggage.h`

This header file contains:

-   structure definitions (via `types.h`)\
-   function prototypes for the baggage operations module

------------------------------------------------------------------------

### `baggage.c`

This source file contains:

-   implementation of all baggage operations\
-   linked list management logic\
-   insertion, deletion, traversal, searching, and statistics

------------------------------------------------------------------------

## Data Structure Used

### Baggage List

The module stores baggage records using a doubly linked list.

``` c
struct BaggageList {
    struct BaggageNode* head;
    struct BaggageNode* tail;
};
```

The node structure is defined in `types.h` as `BaggageNode`.

------------------------------------------------------------------------

### BaggageNode Fields

Each node contains:

-   baggage ID\
-   passenger ID\
-   owner name\
-   weight\
-   tag (auto-generated)\
-   status\
-   next pointer\
-   prev pointer

------------------------------------------------------------------------

### Important Note About the Data Structure

The baggage module uses a doubly linked list, allowing:

-   forward traversal using `next`\
-   backward traversal using `prev`

------------------------------------------------------------------------

### Global Structure

``` c
struct BaggageList list;
```

**Purpose:**

-   stores all baggage records\
-   provides access to both head and tail

------------------------------------------------------------------------

## Functions in the Module

### 1. `initBaggageList(struct BaggageList* list)`

#### Purpose

Initializes the baggage list.

#### Method

-   sets head = NULL\
-   sets tail = NULL

#### Time Complexity

-   O(1)

------------------------------------------------------------------------

### 2. `createBaggageNode(...)`

#### Purpose

Creates a new baggage node.

#### Method

-   allocates memory using `malloc()`\
-   assigns all baggage details\
-   generates tag\
-   sets default status

#### Time Complexity

-   O(1)

------------------------------------------------------------------------

### 3. `baggageIDExists(struct BaggageList* list, int id)`

#### Purpose

Checks if a baggage ID already exists.

#### Method

-   traverses from head\
-   compares IDs

#### Algorithm Used

-   linear search

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 4. `addBaggage(struct BaggageList* list)`

#### Purpose

Adds a new baggage record.

#### Method

-   reads user input\
-   checks duplicate ID\
-   warns if weight \> 30kg\
-   inserts at tail

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 5. `removeBaggage(struct BaggageList* list)`

#### Purpose

Removes a baggage record by ID.

#### Method

-   searches node\
-   updates pointers\
-   frees memory

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 6. `displayForward(struct BaggageList* list)`

#### Purpose

Displays baggage from head to tail.

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 7. `displayBackward(struct BaggageList* list)`

#### Purpose

Displays baggage from tail to head.

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 8. `searchBaggage(struct BaggageList* list)`

#### Purpose

Searches baggage by passenger ID.

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 9. `baggageStatistics(struct BaggageList* list)`

#### Purpose

Generates baggage report.

#### Includes:

-   total bags\
-   total weight\
-   average weight\
-   heaviest bag

#### Time Complexity

-   O(n)

------------------------------------------------------------------------

### 10. `baggageMenu(struct BaggageList* list)`

#### Purpose

Menu system for baggage operations.

------------------------------------------------------------------------

## Algorithms Used

-   Linear Search\
-   Doubly Linked List Insertion\
-   Doubly Linked List Deletion\
-   Traversal

------------------------------------------------------------------------

## Memory Management

### Efficient Practices

-   uses `malloc()`\
-   frees memory on deletion\
-   prevents duplicates

------------------------------------------------------------------------

### Limitations

-   no full cleanup function\
-   memory not freed at program exit

------------------------------------------------------------------------

## Strengths

-   supports forward and reverse traversal\
-   modular design\
-   includes statistics

------------------------------------------------------------------------

## Weaknesses

-   limited input validation\
-   no data persistence

------------------------------------------------------------------------

## Suggested Improvements

-   add input validation\
-   implement full cleanup\
-   add file storage\
-   add sorting

------------------------------------------------------------------------

## Summary

The baggage management module uses a doubly linked list to efficiently
manage baggage records. It supports insertion, deletion, searching,
traversal, and reporting, making it a key part of the system.
