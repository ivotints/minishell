# Minishell - As Beautiful as a Shell 🌟

## Minishell: A Simple, Custom Bash-like Shell in C

**Minishell** is a custom shell project written in C that mimics the functionality of a basic Unix shell like Bash. It is part of the curriculum at **42 School**, a renowned coding academy known for its peer-to-peer learning approach and project-based education. By completing this project, you will gain hands-on experience with process handling, file descriptors, and system calls, all while adhering to strict coding standards and conventions.

This shell supports essential features like command execution, redirections, pipelines, built-in commands, and signal handling, making it a valuable learning experience for understanding the inner workings of Unix-like systems.

## Features
- Customizable command prompt
- Command execution based on `$PATH`
- Support for piping (`|`), input/output redirections (`<`, `>`, `>>`, `<<`)
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable expansion and history management
- Proper handling of special characters and signals (e.g., Ctrl-C, Ctrl-D)

## Installation
To set up and run **Minishell**, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/ivotints/minishell.git
   ```

2. Navigate into the project directory:
   ```bash
   cd minishell
   ```

3. Compile the project and run the shell:
   ```bash
   make re run
   ```

## About the Project

This project is a key part of the 42 School curriculum, aimed at developing a deep understanding of **Unix-based shell behavior** and **low-level programming in C**. Through **Minishell**, you'll explore process creation, input/output redirection, signal handling, and command parsing. You'll also implement basic shell functionalities like built-in commands (`cd`, `echo`, `env`, etc.) and gain experience in managing memory, handling system calls, and creating an interactive command-line interface.

At 42, projects like **Minishell** are designed to encourage students to solve problems creatively, learn through collaboration, and write maintainable, error-free code. This hands-on project simulates a real-world environment, preparing students for advanced topics in system programming and beyond.
