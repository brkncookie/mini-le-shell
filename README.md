# Minishell

Minishell is a project focused on creating a Unix-like shell in the C programming language. The goal of this project is to develop a command-line interpreter similar to Bash, enabling users to interact with their operating system through a shell interface.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Concepts Learned](#concepts-learned)
  - [Abstract Syntax Tree (AST)](#abstract-syntax-tree-ast)
  - [Interpreted Programming Language and Interpreter](#interpreted-programming-language-and-interpreter)
  - [Binary Tree](#binary-tree)
  - [Child Process Creation in Linux](#child-process-creation-in-linux)
  - [Execution of Commands](#execution-of-commands)
  - [Output Redirection in Commands](#output-redirection-in-commands)
  - [Interprocess Communication with Linux Signals and Pipes](#interprocess-communication-with-linux-signals-and-pipes)
- [Examples](#examples)
  - [Running Commands](#running-commands)
  - [Output Redirection](#output-redirection)
  - [Pipes](#pipes)
  - [Logical Operators](#logical-operators)

## Introduction

Minishell is a comprehensive project that provides developers with insights into systems programming and command-line interfaces. By implementing a basic shell, developers can understand the intricacies of process management, input/output handling, and command execution in Unix-like operating systems.

## Features

- Command-line interface similar to Bash.
- Support for executing commands, including built-in commands and external executables.
- Output redirection to files and pipes.
- Basic error handling and signal management.

## Concepts Learned

### Abstract Syntax Tree (AST)

Minishell involves parsing user input and constructing an abstract syntax tree (AST). The AST represents the syntactic structure of the input command, facilitating easier analysis and execution.

### Interpreted Programming Language and the role of an Interpreter

Minishell acts as an interpreter for the commands provided by the user. It parses and executes commands in real-time, mimicking the behavior of an interpreter for an interpreted programming language.

### Binary Tree

The construction of the abstract syntax tree in Minishell often utilizes a binary tree structure. Understanding binary trees aids in efficient traversal and manipulation of the command syntax tree.

### Child Process Creation in Linux

Minishell creates child processes in Linux to execute commands. This involves utilizing system calls such as `fork()` to spawn new processes, managing parent-child relationships, and ensuring proper execution of commands.

### Execution of Commands

Executing commands in Minishell involves parsing arguments, searching for executables in the system's PATH, and executing the command within the shell's context.

### Output Redirection in Commands

Minishell supports output redirection, allowing users to control the input and output streams of commands. Techniques for redirecting standard input, output, and error streams to and from files or other processes are explored.

### Interprocess Communication with Linux Signals and Pipes

Interprocess communication is facilitated through Linux signals and pipes in Minishell. Signals enable communication between processes, while pipes facilitate the transfer of data between processes, allowing for more complex command executions.

## Examples

### Running Commands

To run a command in Minishell, simply type the command followed by its arguments:

```bash
$ ls -l
```

### Output Redirection

Redirecting output allows you to save the output of a command to a file:

```bash
$ ls > file.txt
```

### Pipes

Pipes enable the output of one command to be used as the input for another command:

```bash
$ ps aux | grep minishell
```

### Logical Operators

Logical operators `||` and `&&` provide conditional execution of commands based on the success or failure of previous commands.

#### Logical OR (||)

The `||` operator executes the second command only if the first command fails (returns a non-zero exit status).

```bash
$ rm non_existent_file || echo "File does not exist"
```

In this example, if the `rm` command fails because the file does not exist, the `echo` command will be executed, printing "File does not exist".

#### Logical AND (&&)

The `&&` operator executes the second command only if the first command succeeds (returns a zero exit status).

```bash
$ ./configure && make && make install
```

In this example, the `configure` script is executed first. If it succeeds, the `make` command is executed. If `make` succeeds, the `make install` command is executed. If any of the commands fail, subsequent commands will not be executed.

These logical operators provide flexibility in command execution and are commonly used in shell scripting to handle conditional execution flows.
