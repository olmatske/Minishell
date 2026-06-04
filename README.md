*This project has been created as part of the 42 curriculum by anshuval, olmatske.*

# ✧･ﾟ: *✧･ﾟ:*🐚 Minishell 🐚*:･ﾟ✧*:･ﾟ✧ ...aka Bashtard

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


# Checklists and Roadmaps

### Parsing

### Execution

**Roadmap**


- [X] start with: echo hi (> hi.txt)
- [X] continue with built ins
- [X] anything without env vars
- [X] figure out env stuff
 - [X] files
	- [X] < "input" redirects input: cat < file.txt outputs file content to shell
	- [X] > "overwrite" redirects input into a file
		-> signals for exiting write mode!
	- [X] << "heredoc" should be given a delimiter, then read the input until a line containing the
			delimiter is seen. However, it doesn’t have to update the history!
	- [X] >> "append" should redirect output in append mode.
		-> [X] signals for exiting write mode!
- [X] externals
	- [X] absolute path
	- [X] relative path
	- [X] command
		-> search until :
		-> yoink the string
		-> append yoinked string + '/' + command
		-> check if it exists
			> if no iterate further and repeat process
			> if yes, return path
- [X] Pipes
- [X] PreZero (Garbage Collector)
- [X] heredoc last
- [X] link to main
	- [X] norm
- [X] change builtin.c
	- [X] envp to struct
	- [X] args
- [X] exit
- [X] add functions to header and clean up
- [X] increment and execute commands if pipes
- [X] norminette
- [X] garbage collecter
	-> cutsom mallox, mallocs and remembers in an array and frees at the end
	- [X] gc_malloc — allocates memory and registers it
	- [X] gc_free — frees a single pointer and removes it from the list
	- [X] gc_free_all — frees every tracked pointer (call on exit or error)
	- [X] gc_add — adds a pointer to the tracking list\
	- [X] gc_calloc - same as gc_malloc but fills space with NULL
- [X] execve are for external!!!!
- [X] grep hi <./test_files/infile_big <./test_files/infile
	-> LEAKS!!! was only the readline leaks
- [X] update $PWD when changing directories
- [X] leaks when doing just cd
- [X] Minishell$ pwd
- [X] Norminette
- [X] isatty(STDIN_FILENO) before readline, if it's not 0 you use readline, else gnl
- [X] file creation ->	"> text.txt" does not create file, but it should
- [X] Heredoc
- [X] remove fsanitizer from Makefile
