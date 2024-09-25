# Minishell - As Beautiful as a Shell 🌟

## Minishell: A Simple, Custom Bash-like Shell in C

**Minishell** is a custom shell project written in C that mimics the functionality of a basic Unix shell like Bash. This project will teach you about process handling, file descriptors, and system calls, while adhering to strict coding standards. 

This shell supports command execution, redirections, pipelines, built-in commands, and signal handling.

## Features
- Customizable command prompt
- Command execution based on `$PATH`
- Support for piping (`|`), input/output redirections (`<`, `>`, `>>`, `<<`)
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable expansion and history management
- Proper handling of special characters and signals (e.g., Ctrl-C, Ctrl-D)

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/ivotints/minishell.git
   cd minishell
   make re run
