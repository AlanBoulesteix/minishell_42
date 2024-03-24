# Minishell
Minishell is a simple Unix shell implemented in C, designed as a project for 42 school. It provides basic shell functionalities similar to bash, including command execution, path handling, environment variable management, and built-in functions.

## Features
- **Command Execution**: Execute external commands with arguments.
- **Command Execution**: Execute external commands with arguments.
- **Path Handling**: Support for both relative and absolute paths.
- **Quoting**: Handle single and double quotes similar to bash.
- **Redirections**: Support redirection operations such as >, <, <<, >>.
- **Environment Variables**: Manage environment variables like in a standard Unix shell.
- **Signal Handling**: Support interrupting processes with `Ctrl-C`, quitting programs with `Ctrl-\`, and throwing EOF with `Ctrl-D`.
- **Built-in Functions**:
- - `echo`: with support for the `-n` option.
- - `pwd`: print working directory.
- - `cd`: change directory.
- - `env`: display environment variables.
- - `export`: set an environment variable.
- - `exit`: exit the shell.

## Getting Started
To compile the minishell, simply run:
```bash
make
```
This will generate the minishell executable.

## Usage
To start the minishell, run:
```bash
./minishell
```
Once inside the minishell, you can use it just like a regular Unix shell, executing commands, using built-in functions, and managing environment variables.

## Credits
This project was developed by [valentinValep](https://github.com/valentinValep) and [Alan Boulesteix](https://github.com/AlanBoulesteix) as part of the curriculum at École 42.
