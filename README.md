Airline Reservation System

Baggage Services Module Documentation

File Overview

Implementation File: baggage.c
Header File: baggage.h
Module Name: Baggage Services
Data Structure Used: Doubly Linked List

Purpose of the Module

The Baggage Services module is responsible for managing all baggage-related operations in the Airport Flight Management System.

It allows users to:

Check-in baggage
Remove baggage
Search baggage by passenger
View baggage records (forward & reverse)
Generate baggage statistics

This module is accessed through the Baggage Services Menu in the system.

Data Structure Used

Doubly Linked List

The baggage records are stored using a doubly linked list, which allows traversal in both directions.

Each node contains:

Baggage ID
Passenger ID
Owner Name
Weight
Tag (auto-generated)
Status
Pointer to next node
Pointer to previous node
Structure Behavior
head → points to the first baggage
tail → points to the last baggage

Functions in the Module
1. initBaggageList()

Initializes the baggage list by setting head and tail to NULL.

2. createBaggageNode()

Creates and initializes a new baggage node.

Features:

Allocates memory dynamically
Generates tag automatically (TAG-XXXX)
Sets default status to Checked-In
3. baggageIDExists()

Checks if a baggage ID already exists.

Algorithm: Linear Search
Time Complexity: O(n)

4. addBaggage()

Adds a new baggage record to the system.

Steps:

Takes user input
Checks for duplicate ID
Displays warning if weight > 30kg
Inserts node at the end (tail insertion)

Time Complexity: O(n)

5. removeBaggage()

Removes baggage using its ID.

Steps:

Searches for the node
Updates both next and prev pointers
Frees memory

Time Complexity: O(n)

6. displayForward()

Displays baggage records from head → tail.

7. displayBackward()

Displays baggage records from tail → head.

This is only possible because of the doubly linked list.

8. searchBaggage()

Searches baggage by Passenger ID.

Algorithm: Linear Search
Time Complexity: O(n)

9. baggageStatistics()

Generates a report including:

Total number of bags
Total weight
Average weight
Heaviest baggage
10. baggageMenu()

Provides a user interface for all baggage operations.

Uses:

do-while loop
switch-case for menu selection

Algorithms Used
1. Linear Search

Used in:

Checking duplicate IDs
Removing baggage
Searching baggage
2. Doubly Linked List Insertion
New nodes are added at the tail
3. Doubly Linked List Deletion
Updates both previous and next pointers
4. Traversal
Forward traversal → using next
Backward traversal → using prev

Memory Management

Good Practices
Uses malloc() for dynamic allocation
Frees memory when removing nodes
Prevents duplicate entries
Limitations
No full cleanup function to free all nodes at program exit

Strengths of the Module

Efficient forward and backward traversal
Clean modular design
Realistic baggage handling simulation
Automatic tag generation
Supports statistical analysis

Limitations

Limited input validation
No global cleanup function
Weight limit only gives warning (not enforced)

Suggested Improvements

Add input validation for all fields
Restrict valid weight ranges
Add function to free entire list
Add sorting (by weight or passenger ID)
Store data in file for persistence

Summary

The Baggage Services module demonstrates a practical implementation of a doubly linked list in a real-world scenario. It efficiently manages baggage records with insertion, deletion, searching, and reporting functionalities, making it a strong component of the Airport Flight Management System.
