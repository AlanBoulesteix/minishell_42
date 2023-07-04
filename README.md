# Minishell
```
 __   __  ___   __    _  ___   _______  __   __  _______  ___      ___     
|  |_|  ||   | |  |  | ||   | |       ||  | |  ||       ||   |    |   |    
|       ||   | |   |_| ||   | |  _____||  |_|  ||    ___||   |    |   |    
|       ||   | |       ||   | | |_____ |       ||   |___ |   |    |   |    
|       ||   | |  _    ||   | |_____  ||       ||    ___||   |___ |   |___ 
| ||_|| ||   | | | |   ||   |  _____| ||   _   ||   |___ |       ||       |
|_|   |_||___| |_|  |__||___| |_______||__| |__||_______||_______||_______|
```

Minishell is a project from the 42 school cursus. The goal is to code a shell with some basic functionalities.

## Installation

Use the makefile to compile the project

```bash
make
```

## Usage

```bash
./minishell
```

## Features

- Prompt display
- Executing commands with arguments and path
- Environment variables
- Exit built-in
- cd built-in
- pwd built-in
- export built-in
- unset built-in
- env built-in
- echo built-in
- redirections: <, >, >>
- heredoc like
- pipes: |
- signals: ctrl-C, ctrl-D, ctrl-\
- quotes: ", '
- exit status var: $?
- env variables: $ followed by characters
