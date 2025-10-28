# 🐚 Minishell

![minishell](https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExZ3h3NDVzdWN0dmFlZnpid2o5eXhkcWwwMGh2b3FkZjEwZnZ5MmRnciZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/jUhpOyPjtyiDLuL8ZX/giphy.gif)


### 🧾 About the Project

Minishell is a simplified version of the Unix shell, built entirely in C.
The goal of this project is to recreate the core behavior of Bash — including command parsing, environment management, redirections, and pipes — while learning how processes, file descriptors, and signals work at a low level in Unix systems.

### 💬 What I Learned

Building Minishell was one of the most challenging and eye-opening experiences in my journey at 42.
I learned how a real shell works behind the scenes — from parsing user input and handling environment variables to creating processes, managing pipes, and dealing with signals.
This project taught me a lot about system programming, memory management, and how to design clean, modular C code that behaves just like a real Unix shell.

```

├── Makefile
├── README.md
├── include
│   ├── builtin.h
│   ├── cleanup.h
│   ├── env.h
│   ├── exec.h
│   ├── expansion.h
│   ├── input.h
│   ├── minishell.h
│   ├── parser.h
│   ├── quotes.h
│   ├── redir.h
│   ├── signals.h
│   ├── tokenizer.h
│   └── utils.h
└── src
    ├── builtin
    │   ├── cd.c
    │   ├── dispatcher.c
    │   ├── echo.c
    │   ├── env.c
    │   ├── exit.c
    │   ├── exit_utils.c
    │   ├── export.c
    │   ├── export_utils.c
    │   ├── pwd.c
    │   └── unset.c
    ├── cleanup
    │   ├── cleanup.c
    │   └── exit.c
    ├── env
    │   ├── env_free.c
    │   ├── env_get.c
    │   ├── env_helpers.c
    │   ├── env_init.c
    │   ├── env_set.c
    │   ├── env_to_str_array.c
    │   ├── env_unset.c
    │   └── env_utils.c
    ├── exec
    │   ├── exec_errors.c
    │   ├── exec_fork.c
    │   ├── exec_path.c
    │   ├── exec_pipeline.c
    │   ├── exec_pipeline_helpers.c
    │   ├── exec_single.c
    │   ├── exec_utils.c
    │   ├── pipes.c
    │   ├── wait.c
    │   └── wait_utils.c
    ├── expansion
    │   ├── expand_char_helpers.c
    │   ├── expand_dollar_helpers.c
    │   ├── expand_env.c
    │   ├── expand_exit.c
    │   ├── expand_loop.c
    │   ├── expand_main.c
    │   └── expand_utils.c
    ├── input
    │   ├── prompt_free.c
    │   ├── prompt_init.c
    │   ├── prompt_state.c
    │   ├── prompt_utils.c
    │   ├── read_input.c
    │   └── readline_config.c
    ├── libft
    │   ├── Makefile
    │   ├── ft_*.c
    │   └── libft.h
    ├── main
    │   ├── main.c
    │   ├── shell_loop.c
    │   └── shell_loop_utils.c
    ├── parser
    │   ├── ft_add_arg.c
    │   ├── parser_cmd.c
    │   ├── parser_main.c
    │   ├── parser_main_utils.c
    │   ├── parser_split.c
    │   ├── parser_syntax.c
    │   └── parser_utils.c
    ├── quotes
    │   ├── quote_check.c
    │   ├── quote_strip.c
    │   └── quote_type.c
    ├── redir
    │   ├── heredoc.c
    │   ├── redir_apply.c
    │   ├── redir_error.c
    │   ├── redir_input.c
    │   ├── redir_main.c
    │   └── redir_output.c
    ├── signals
    │   ├── signal_echoctl.c
    │   ├── signal_global.c
    │   ├── signal_handlers.c
    │   └── signal_init.c
    ├── tokenizer
    │   ├── token_free.c
    │   ├── token_type.c
    │   ├── token_utils.c
    │   └── tokenizer.c
    └── utils
        ├── cd_utils.c
        ├── error.c
        ├── free_utils.c
        ├── malloc_helpers.c
        ├── str_join.c
        └── str_utils.c

```

### Skills Developed

- Process creation and synchronization (fork, execve, wait)
- File descriptors and inter-process communication using pipe and dup2
- Parsing and tokenization of complex user input
- Quote and environment variable handling ($HOME, $USER, $?)
- Built-in command implementation (cd, echo, export, etc.)
- Signal handling (SIGINT, SIGQUIT, SIGTERM)
- Clean and modular C architecture design
- Memory management and debugging with Valgrind


### ⚙️ How to Run
#### 1. Clone the repository

```
git clone https://github.com/doglaswicht/minishell_42
cd minishell

```


#### 2. Compile the project
```
make
``` 
#### 3. Run Minishell

```
./minishell
```

#### 4. Clean compiled files
```
make clean
make fclean
```

#### Example Usage

```
minishell$ echo "Hello $USER"
Hello doglas

ls | grep minishell > result.txt
cat result.txt
pwd

```
[Go to website(AllUp)](https://www.allup.ch/projects.html)
