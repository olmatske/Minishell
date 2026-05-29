*This project has been created as part of the 42 curriculum by anshuval, olmatske.*

# ✧･ﾟ: *✧･ﾟ:*🐚 Minishell 🐚*:･ﾟ✧*:･ﾟ✧

## Description
Minishell is a compact and simplified version of the bash shell. It consists of:
- **Builtin commands**, such as echo, cd or env
- **External commands**, such as cat or grep
- **Redirections**, mainly input, output and heredoc

The project was split up into two categories, namely **execution** and **parsing**.
Parsing reads the commands, validates the input and converts them into structs, which execution uses to execute commands, pipe and redirect input of the user.

You can see the progress and thought proccess in the marksown (md) files in the respective directories.

## Instructions
To start the shell, compile the shell using the following line of commands:

```bash
make
./minishell
```

## Resources

### Parsing

### Execution
- A lot of help from peers, especially in the start
- [Terster](https://github.com/LucasKuhn/minishell_tester/tree/main#)
- Stak Overflow
- Perplexity and Qwen Studio
- AI in execution was only used to help decode leaks, understand and sometimes find bugs and help fix up norminette. AI was mostly used for repetative tasks to speed up the progress. Every bit of logic has been thought through and written by olmatske, aka a human.
