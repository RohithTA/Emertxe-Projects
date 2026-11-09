# Mini Shell (msh)

A minimal Linux shell written in C that reads commands, runs them in child processes and supports a few built-ins.

> Developed as part of the Emertxe training program (Linux Internals module).

## Features
- Interactive prompt (default `[msh]$`), customizable with `PS1=NEWPROMPT`
- External commands run in a forked child process; the parent waits for it to finish
- Allowed external commands are read from `external_commands.txt` (one per line, easy to extend)
- Built-in commands: `cd`, `pwd`, `exit`
- `echo $?` (last child status) and `echo $$` (shell PID)

## Tech Stack
C, GCC, Make, Linux system calls (`fork`, `wait`, `chdir`, `getpid`)

## Project Structure

    mini-shell/
    - src/                     shell source files
    - external_commands.txt    commands the shell treats as external
    - Makefile
    - README.md

## Build and Run
Requires Linux or WSL. Run it from the project folder, because `external_commands.txt` is opened by relative path.

    make
    ./msh

## Known Limitations and Future Work
- No signal handling (Ctrl-C / Ctrl-Z) and no background jobs yet
- `echo $?` shows the raw wait status rather than the exit code
- Input is limited to 24 characters
- External commands stop being recognised after `cd`, because the command list is opened by relative path

## What I Learned
- Process creation and synchronization with `fork` and `wait`
- Parsing and classifying user input
- Structuring a multi-file C program

## Author
Rohith T A
