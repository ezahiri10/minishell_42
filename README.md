# Minishell

Minishell is a simplified shell implementation designed as part of the 42 curriculum. This project aims to deepen understanding of system programming, process management, and Unix-like operating systems by recreating a basic shell.

---

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Builtin Commands](#builtin-commands)
- [Technical Details](#technical-details)
- [Project Structure](#project-structure)
- [Error Handling](#error-handling)
- [Contributing](#contributing)
- [License](#license)

---

## Features
Minishell includes the following features:

- Prompt displaying the current working directory.
- Execution of external commands using system paths.
- Implementation of builtin commands:
  - `cd`
  - `echo`
  - `env`
  - `export`
  - `unset`
  - `pwd`
  - `exit`
- Environment variable management and substitution (`$VARIABLE`).
- Support for input/output redirection:
  - `>`: Output redirection.
  - `<`: Input redirection.
  - `>>`: Append redirection.
- Support for pipes (`|`) for chaining commands.
- Signal handling for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.
- Proper error messages and memory management.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./minishell
   ```

---

## Usage

Start the shell by running the executable. Once inside, you can use it like a standard Unix shell to execute commands, manage files, or explore the implemented features.

### Example Commands:
```bash
$ pwd
/home/user/minishell

$ echo Hello, world!
Hello, world!

$ ls -l | grep minishell > output.txt

$ cat output.txt
```

---

## Builtin Commands

Minishell implements the following builtin commands:

- **`cd [directory]`**: Change the current directory.
- **`echo [arguments]`**: Print arguments to the terminal.
- **`env`**: Display all environment variables.
- **`export [name=value]`**: Set or update an environment variable.
- **`unset [name]`**: Remove an environment variable.
- **`pwd`**: Print the current working directory.
- **`exit [status]`**: Exit the shell with an optional exit status.

---

## Technical Details

- **Parsing:**
  - Tokenizes the user input into commands and arguments.
  - Handles special operators like `|`, `<`, `>`, and `>>`.

- **Process Management:**
  - Uses `fork()` to create child processes for external commands.
  - Executes commands with `execve()`.

- **Pipes and Redirections:**
  - Implements pipes using `pipe()` to redirect output between commands.
  - Manages file descriptors for input/output redirection.

- **Signal Handling:**
  - Overrides default behaviors for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` to ensure seamless operation.

---

## Project Structure

```
minishell/
├── src/
│   ├── main.c         # Entry point of the program.
│   ├── parser.c       # Command parsing logic.
│   ├── executor.c     # Command execution logic.
│   ├── builtins.c     # Builtin commands implementation.
│   ├── signals.c      # Signal handling functions.
│   └── utils.c        # Utility functions.
├── includes/
│   └── minishell.h    # Header file with prototypes and constants.
├── Makefile           # Build system.
└── README.md          # Project documentation.
```

---

## Error Handling

Minishell ensures robust error handling by:

- Printing meaningful error messages for invalid commands, syntax errors, or permission issues.
- Managing memory to avoid leaks (validated with tools like `valgrind`).
- Ensuring proper cleanup of file descriptors and child processes.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add feature-name"
   ```
4. Push to your branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

Happy coding! 🚀

