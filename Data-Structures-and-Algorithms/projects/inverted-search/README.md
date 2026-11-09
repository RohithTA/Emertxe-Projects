# Inverted Search

A command-line search engine in C that builds an inverted index from text files and lets you search words across them.

> Developed as part of the Emertxe training program.

## Features
- Validates input files (must be `.txt`, exist, and not be empty; duplicates are skipped)
- Builds a database of words using a hash table (27 buckets) with linked lists
- Stores, for each word, how many files contain it, and the count in each file
- Display, search, update and save the database
- Saves the database to a backup file and can load it back

## Tech Stack
C, GCC, Make, Hash tables, Singly linked lists, File I/O

## Project Structure
```
inverted-search/
├── src/        # all .c files and invert_index.h
├── samples/    # file1.txt, file2.txt, backup.txt
├── Makefile
└── README.md
```

## Build
```bash
make
```

## Usage
Pass one or more `.txt` files as arguments, then use the menu:
```bash
./inverted_search samples/file1.txt samples/file2.txt
```

## How It Works
1. Each input file is validated and added to a file list.
2. Words are hashed into buckets by their first letter (27 buckets).
3. Each word has a main node (the word) and sub nodes (one per file, with the count).
4. Searching a word walks its bucket and prints the files and counts.

## What I Learned
- Hash tables and collision handling with linked lists
- Dynamic memory management in C
- Designing multi-file C programs and parsing text files

## Author
Rohith T A
