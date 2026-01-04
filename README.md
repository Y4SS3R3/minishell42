# Minishell - As Beautiful as a Shell

*This project was created as part of the 42 curriculum by ymassiou and twin.*

## Description
[cite_start]Minishell is a minimalist implementation of a Bash-like command-line interpreter[cite: 4, 5]. [cite_start]The project focuses on core system programming concepts in C, including process creation, signal handling, and file descriptor manipulation[cite: 6, 20]. It transforms user input into an Abstract Syntax Tree (AST) to execute complex command pipelines.

## Features

### Mandatory Requirements
* [cite_start]**Command Execution:** Locates and executes binaries based on the `PATH` variable or absolute/relative paths[cite: 99].
* [cite_start]**Built-in Commands:** Fully implemented `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit` [cite: 126-133].
* [cite_start]**Redirections:** * `<` : Input redirection[cite: 113].
  * [cite_start]`>` : Output redirection (trunc)[cite: 114].
  * [cite_start]`>>` : Output redirection (append)[cite: 117].
  * [cite_start]`<<` : Heredoc with delimiter support[cite: 115].
* [cite_start]**Pipes:** Connects the output of one command to the input of the next using `|`[cite: 118].
* [cite_start]**Environment Variables:** Handles `$` expansions and the `$?` exit status of the last pipeline[cite: 119, 120].
* [cite_start]**Signal Handling:** Interactive management of `ctrl-C` (new prompt), `ctrl-D` (exit), and `ctrl-\` (do nothing) [cite: 121-125].

### Bonus Features
* [cite_start]**Logical Operators:** Supports `&&` and `||` with parenthesis for operation priority[cite: 146].
* [cite_start]**Wildcards:** Pattern matching using `*` for the current working directory[cite: 147].

## Usage

### Prerequisites
* [cite_start]GCC or CC compiler[cite: 26].
* Standard C libraries.
* [cite_start]Readline library[cite: 95].

### Compilation
The project includes a `Makefile` with the following rules:
```bash
make          # Compiles the mandatory part
make clean    # Removes object files
make fclean   # Removes object files and the executable
make re       # Recompiles the project
```

### Execution
Run the shell from your terminal:

```Bash
./minishell
```
### Technical Highlights
* **Abstract Syntax Tree (AST):** The parser builds a recursive tree structure to manage the execution priority of pipes, logical operators, and redirections.

* **Custom Garbage Collector:** A centralized memory management system (t_trash) tracks heap allocations to ensure all memory is freed upon exit or error, preventing leaks.

* **DDA-style Parsing:** Implements a robust lexer and parser that handles quotes (single and double) and special characters without interpreting unclosed sequences.

* **Process Management:** Uses fork and waitpid to manage foreground pipelines and ensure correct exit status reporting.

### Resources
* [42 Docs - Minishell](https://harm-smits.github.io/42docs/projects/minishell) — Reference for shell behavior and system calls.
* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/) — The industry standard used as the project's behavioral baseline.
