# Inverted Search

A command-line search engine in C that builds an inverted index from text files and lets you search words across them.

> Developed as part of the Emertxe training program.

## Features
- Validates input files (must be `.txt`, exist, and not be empty; duplicates are skipped)
- Builds a database using a hash table (27 buckets, by first letter) with linked lists
- For each word, stores how many files contain it and the count in each file
- Menu: create, display, search, save and update (load) the database
- Save writes the database to a text file you name; update loads a saved file back

## Tech Stack
C, GCC, Make, Hash tables, Singly linked lists, File I/O

## Project Structure

    inverted-search/
    - src/        all .c files and invert_index.h
    - samples/    file1.txt, file2.txt, backup.txt (a saved database)
    - Makefile
    - README.md

## Build

    make

## Usage
Pass one or more `.txt` files, then choose from the menu:

    ./inverted_search samples/file1.txt samples/file2.txt

    1. Create database
    2. Display Database
    3. Search for a word
    4. Save the database     (asks for a .txt filename)
    5. Update to existing database   (loads a saved file; use it before creating)

To load the included sample database, choose option 5 first and enter `samples/backup.txt`.

## How It Works
1. Each input file is validated and added to a file list.
2. Words are hashed into buckets by their first letter.
3. Each word has a main node (the word) and sub nodes (one per file, with the count).
4. Searching a word walks its bucket and prints the files and counts.

## Known Limitations
- The save/load filename must contain a `.` (such as `db.txt`), otherwise the program crashes
- Loading a saved database is only allowed before creating one

## What I Learned
- Hash tables and chaining with linked lists
- Dynamic memory management in C
- Designing multi-file C programs and parsing text files

## Author
Rohith T A
