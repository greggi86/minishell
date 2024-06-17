# Minishell Project Documentation

## Introduction

Minishell is a project aimed at creating a simple shell, similar to Bash, providing insights into processes and file descriptors. This educational project is part of a coding school's curriculum, emphasizing hands-on learning in system programming by building a functional command line interpreter.

## Common Instructions

- **Language**: The project must be written in C.
- **Code Norms**: Compliance with specific coding standards (referred to as "Norm") is required. Any norm violation in bonus files/functions results in a zero score.
- **Memory Management**: No memory leaks will be tolerated. All heap allocated spaces must be freed appropriately.
- **Makefile**:
  - Must compile the project using `cc` with flags `-Wall`, `-Wextra`, and `-Werror`.
  - Must include rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
  - If `libft` is allowed, it must be compiled and included correctly.
- **Testing**: Creation of test programs is encouraged, although they are not graded.
- **Submission**: Code must be submitted through the assigned git repository, and the grading is based on the repository content post-peer evaluations.

## Mandatory Part

- **Program Name**: `minishell`
- **Files to Turn In**: `Makefile`, `*.h`, `*.c`
- **Functionality**:
  - Display a command prompt and handle command input with history.
  - Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
  - Implement signal handling with minimal global variables.
  - Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
  - Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
  - Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
  - Manage input/output redirection and piping.
  - Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
  - Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
  - Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
  - In interactive mode: ctrl-C displays a new prompt on a new line. ctrl-D exits the shell. ctrl-\ does nothing.
  - Implement built-in commands `echo`(with option -n), `cd` (with only a relative or absolute path), `pwd`, `export`, `unset`, `env`, and `exit`.
- **External Functions**:
  - `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`.

## Bonus Part

- Implementation of logical operators `&&` and `||` with prioritization.
- Support for wildcards (`*`) in the current working directory.
