*This project has been created as part of the 42 curriculum by anshuval, olmatske.*

# ✧･ﾟ: *✧･ﾟ:*🐚 Minishell 🐚*:･ﾟ✧*:･ﾟ✧
# aka Bashtard

## Description
Minishell is a compact and simplified version of the bash shell. It consists of:
- **Builtin commands**, such as echo, cd or env
- **External commands**, such as cat or grep
- **Redirections**, mainly input, output and heredoc
- **Pipes**, chaining commands by passing one command's output to the next command's input

The project was split up into two categories, namely **execution** and **parsing**.
Parsing reads the commands, validates the input and converts them into structs, which execution uses to execute commands, pipe and redirect input of the user.

You can see the progress and thought proccess in the marksown (md) files in the respective directories.

## Instructions
To start the shell, compile the shell using the following line of commands:

```bash
make
./bashtard
```

## Resources
- A lot of help from peers, especially in the start and with troubleshooting
- A huge help and guidance for the github repository by dreule and gzovkic (https://github.com/dreule28/minishell)
- [Mindmap] (https://github.com/zstenger93/minishell/blob/master/mindmap.png)
- [Terster] (https://github.com/LucasKuhn/minishell_tester/tree/main#)

### Parsing
- bash
- [Bash_tutorial] (https://www.w3schools.com/bash/)
- Gemini and Copilot - AI was used for research and explanation of complex bash behaviour, especially in edge cases.
No code or code logic was AI generated. 

### Execution
- Stak Overflow
- Perplexity and Qwen Studio
- **UNIX man pages:** pipe(2), fork(2), dup2(2), execve(2), waitpid(2)
- https://en.wikipedia.org/wiki/Everything_is_a_file
- https://en.wikipedia.org/wiki/Fork_(system_call)
- https://en.wikipedia.org/wiki/Pipeline_(Unix)
- https://en.wikipedia.org/wiki/Exec_(system_call)
- https://en.wikipedia.org/wiki/Dup_(system_call)
- https://en.wikipedia.org/wiki/Wait_(system_call)
- gitbook
- AI in execution was only used to help decode leaks, understand and sometimes find bugs and help fix up norminette. AI was mostly used for repetative tasks to speed up the progress. Every bit of logic has been thought through and written by olmatske, aka a human.
