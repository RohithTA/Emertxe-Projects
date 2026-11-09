# Mini Shell (msh)

A minimal Linux shell written in C, built to practise process creation, signals and process synchronization.

> Developed as part of the Emertxe training program (Linux Internals module).

## Features
- Custom prompt, default `msh>`, changeable with `PS1=NEW_PROMPT`
- Runs external commands in a child process; the parent waits for completion
- Built-in commands, including `cd` and `exit`
- Special variables: `echo $?` (last exit status), `echo $$` (shell PID), `echo $SHELL`
- Signal handling: Ctrl-C sends SIGINT to the foreground program, Ctrl-Z sends SIGTSTP
- A list of known external commands is read from `external_commands.txt`

## Tech Stack
C, GCC, Make, Linux system calls (`fork`, `exec`, `wait`, `signal`)

## Project Structure
```
mini-shell/
├── src/                      # shell source files
├── external_commands.txt     # list of external commands the shell recognises
├── Makefile
└── README.md
```

## Build and Run
This project needs Linux (or WSL on Windows).
```bash
make
./msh
```
Run it from the project folder, because `external_commands.txt` is opened by relative path.

## What I Learned
- Process creation and synchronization with `fork`, `exec` and `wait`
- Signal handling and exit statuses
- Parsing and tokenizing user input

## Author
Rohith T A
