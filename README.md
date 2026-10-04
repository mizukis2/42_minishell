*This project has been created as part of the 42 curriculum by mmatsu, zekhatib.*

# Minishell

## Description

Minishell is a small Unix shell developed as part of the 42 curriculum.

The goal of this project is to recreate the core behavior of a shell such as Bash while working directly with processes, file descriptors, pipes, signals, environment variables, redirections, and command execution.

Through this project, we implemented a command-line interface capable of reading user input, parsing commands, creating the required processes, connecting them through pipes, handling redirections, and executing both built-in and external commands.

The project focuses particularly on understanding:

* Processes and process creation
* File descriptors
* Pipes and inter-process communication
* Process execution with `execve`
* Input/output redirection
* Environment variables
* Signals
* Shell parsing and quoting
* Built-in commands
* Process exit status

## Features

### Interactive shell

Minishell provides an interactive prompt where users can enter commands and execute them.

It supports:

* Command history
* External commands
* Relative and absolute executable paths
* Commands found through `$PATH`
* Environment variable expansion
* Exit-status expansion with `$?`

### Quoting

The shell supports:

* Single quotes `'...'`
* Double quotes `"..."`

Single quotes prevent interpretation of meta-characters inside the quoted sequence.

Double quotes prevent interpretation of meta-characters except for environment variable expansion using `$`.

### Redirections

Minishell supports:

| Operator | Description                            |
| -------- | -------------------------------------- |
| `<`      | Redirect standard input                |
| `>`      | Redirect standard output               |
| `<<`     | Read input until a specified delimiter |
| `>>`     | Append output to a file                |

### Pipes

The `|` operator connects the output of one command to the input of the next command.

For example:

```bash
cat file.txt | grep "hello" | wc -l
```

### Environment variables

Minishell supports environment variable expansion:

```bash
echo $USER
echo $HOME
```

It also supports `$?` for accessing the exit status of the most recently executed foreground pipeline.

### Built-in commands

The mandatory part includes the following built-ins:

* `echo` with `-n`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

### Signals

Minishell handles the following keyboard signals in interactive mode:

* `Ctrl-C`
* `Ctrl-D`
* `Ctrl-\`

Their behavior is designed to match Bash as closely as required by the subject.

## Installation

### Requirements

* Unix-like operating system
* C compiler
* `make`
* GNU Readline library
* `libft`

### Clone the repository

```bash
git clone <repository-url>
cd 42_minishell
```

### Compile

```bash
make
```

The Makefile uses the required compiler flags:

```text
-Wall -Wextra -Werror
```

### Other Makefile commands

```bash
make clean
make fclean
make re
```

## Usage

Start Minishell with:

```bash
./minishell
```

You should then see the shell prompt and can enter commands interactively.

Examples:

```bash
./minishell
```

```bash
echo "Hello World"
```

```bash
ls -la
```

```bash
echo $HOME
```

```bash
cat file.txt | grep "hello"
```

```bash
cat < input.txt
```

```bash
echo "hello" > output.txt
```

```bash
echo "hello" >> output.txt
```

```bash
grep "hello" << EOF
hello
world
EOF
```

## Technical Overview

The shell follows a general pipeline from user input to command execution:

```text
User input
    │
    ▼
Readline
    │
    ▼
Parsing
    │
    ├── Quotes
    ├── Environment variables
    ├── Redirections
    └── Pipes
    │
    ▼
Command structure
    │
    ▼
Execution
    │
    ├── Built-ins
    └── External commands
            │
            ▼
          execve
```

For pipelines, processes are connected using Unix pipes:

```text
Command 1
    │
    │ stdout
    ▼
  pipe()
    │
    │ stdin
    ▼
Command 2
    │
    │ stdout
    ▼
  pipe()
    │
    ▼
Command 3
```

The implementation makes extensive use of Unix system calls and functions such as:

* `fork`
* `wait`
* `waitpid`
* `execve`
* `pipe`
* `dup`
* `dup2`
* `open`
* `close`
* `signal`
* `sigaction`
* `getcwd`
* `chdir`

## Project Structure

```text
minishell/
├── Makefile
├── README.md
├── include/
│   └── ...
├── src/
│   ├── ...
│   └── ...
├── libft/
│   └── ...
└── ...
```

## Testing

Testing was performed by comparing Minishell's behavior with Bash and by testing individual features and combinations of features.

Important areas to test include:

* Simple commands
* Arguments
* Absolute paths
* Relative paths
* `$PATH` command lookup
* Pipes
* Input/output redirections
* Heredocs
* Single and double quotes
* Environment variables
* `$?`
* Built-in commands
* Signals
* Invalid commands
* Invalid syntax
* Exit statuses
* Memory leaks

Example:

```bash
echo hello
echo "hello world"
echo 'hello $USER'
echo "$USER"
echo $?
ls | grep minishell
cat < input.txt
echo hello > output.txt
echo hello >> output.txt
```

## Resources
### Shell & POSIX

* [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) — Reference for shell syntax, quoting, token recognition, expansions, redirections, pipelines, and other shell behavior.
* [explainshell](https://explainshell.com/) — Interactive tool for breaking down shell commands and understanding their arguments and options.

### Minishell Development

* [Minishell: Building a mini-bash](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218) — Practical overview of building a Minishell, including parsing, execution, tokenization, syntax analysis, environment expansion, and project architecture.

### Shell History & Readline

* [GNU History Library Documentation](https://tiswww.case.edu/php/chet/readline/history.html) — Documentation for the GNU History library, including functions used for command history management.
* [How to Manipulate Linux Shell History](https://labex.io/tutorials/linux-how-to-manipulate-linux-shell-history-430972) — Practical introduction to shell history and history-related commands.

### Testing

* [LucasKuhn/minishell_tester](https://github.com/LucasKuhn/minishell_tester) — Community tester for the 42 Minishell project, with tests covering built-ins, pipes, redirections, syntax, signals, heredocs, and other cases.
* `man` pages — Used as references for system calls, library functions, shell commands, and Unix behavior throughout the project.


### AI Usage

AI tools were used as a learning and development aid during the project.

They were used for tasks such as:

* Understanding Unix processes and file descriptors
* Clarifying system calls and their behavior
* Discussing parsing and shell architecture
* Brainstorming test cases
* Reviewing explanations of unfamiliar concepts
* Identifying possible edge cases

AI-generated suggestions were reviewed, tested, and adapted by the team rather than being used blindly. The final implementation was developed and understood by the project members.

## Team

| Member   | Login   | Responsibilities   |
| -------- | ------- | ------------------ |
| Mizuki Matsui| mmatsui | https://github.com/mizukis2 |
| Zeki Khatibi | zekhatib |  |
