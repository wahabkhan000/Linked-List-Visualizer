# Linked List Visualizer

A collection of C++ implementations for learning and practicing linked lists through interactive and practical examples.

The repository focuses mainly on doubly linked lists and circular doubly linked lists, along with applications that show how these structures can be used in real programs.

## Topics Covered

* Doubly Linked Lists

  * Forward and backward traversal
  * Insertion and deletion
  * Navigation using previous and next pointers

* Circular Doubly Linked Lists

  * Bidirectional traversal
  * Circular navigation
  * Insertion and deletion

* Hash Tables

  * Separate chaining
  * Insertion, deletion, searching, and updating
  * Hash table statistics

## Practical Implementations

The repository includes several examples that apply linked lists to practical problems:

* **Browser History Management**

  * Uses a doubly linked list for page navigation.

* **Music Playlist**

  * Uses a circular doubly linked list for moving between songs.

* **Text Editor**

  * Uses a doubly linked list for character insertion, deletion, and cursor movement.

* **Interactive Circular Linked List**

  * Allows forward and backward traversal through user interaction.

## Hash Table Implementations

The repository also contains several versions of a hash table using **separate chaining**.

These implementations demonstrate:

* Key-value insertion
* Searching
* Updating
* Deletion
* Collision handling
* Hash table statistics

Different versions show the development and refinement of the implementation.

## Technologies

* C++
* Standard C++ libraries
* Console-based programs
* Dynamic data structures

## Running the Programs

Each `.cpp` file can be compiled separately.

```bash
g++ filename.cpp -o program
./program
```

For example:

```bash
g++ Music_Playlist_using_a_Circular_Doubly_Linked_List.cpp -o playlist
./playlist
```

Most programs are interactive and require user input.

## Purpose

This repository is part of my practical data structures learning.

The goal is to understand how linked lists work internally and how they can be applied to problems such as browser history, playlists, text editing, and hash-table collision handling.
