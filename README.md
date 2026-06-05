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
./minishell
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

**Roadmap**

- [X] signals! the signals should be passed before the whole start of the loop.
	- [X] study signals!
	- [X] where should they be passed exactly?
	- [X] signal handling
		- [X] ctrl-C displays a new prompt on a new line - sigint
		- [X] ctrl-D exits the shell - NULL is passed
		- [X] ctrl-\ does nothing - sigquit
- [X] quotes handling!
	- [X] if there are quotes the entire line inside trhe quoiotes shouold be a WORD - should be checked right after the quotes checking?
validation:
	- [X] pipe cannot be at the start or at the end
	- [X] that there are no more than one pipe simultaneously
	- [X] pipe is between two commands - NOT VALID
	- [X] that there is an output or innput file after the redirection sign
	- [X] redirections should have either a filename or a word(that will be turned sowieso into a file name)
	- [X] heredoc should be followed by a delimiter word
- [X] env handling! only after the quotes checking
	- [X] $ sign
		- [X] if inside the signgle qotes - does nothing
		- [X] if inside double quotes - replaced by the corresponding data from the t_env list
		- [X] if it is a $? sign - replaced by the exit status oof the last executed command 
			- [X] add the initialisation for the variable $? (name = ?) as zero (value = "0").  - as a separate node at  the end of the t_env linked list
			- [X] the variable should be updated for every command! - to show if the status is changed - by execution (tell Olya)
			- [X] the list of the exits:
				0 a command was a success.
				1 a general error.
				2 a syntax error and for built-in commands.
				126 the command was found, but not executable or no permissions.
				127 the command was not found at all.
				130 the command was cancelled exactly when Ctrl+C (SIGINT) was pressed.
		- [X] check that the variable after the $ sign existst in the t_env list under name
			- [X] if it does not exist replace it with an emptry string ""
			- [X] if not inside the quotes - the node should be deleted . CHECK THE RESULT OF THE STRING OF NODES AFTER THE DELETION!
			- [X] if it was inside the quotes - the node is not deleted but contains only an empty string
			- [X] if this situation was after a redirect trhe error should be smth like "redirection error" - check with bash
	- [X] remove the quotes - after the quotes have been checked for correctness they can be safely removed from the WORD
- [X] result!
	- [X] each t_cmd_node will contain 
		- [X] a string (array) of arguments (like "echo" "-n" "hello" "NULL")
		- [X] redirection (like outfile: "outfile.txt", infile: "infile.txt", heredoc_delimeter:"whatever", out_type (append > or overwrite >> or none))
		- [X] builtin name like echo
	- [X] if there is a pipe in the input the node will be pointing to the next node. OTHERWISE THERE WILL BE ONLY ONE NODE FOR ONE COMMAND
- [X] leaks
	- [X] memory leaks at exit

**Checklist**
- [X]  heredoc should ignore ctrl + z !!! doesnt ignore and aborts. ctrl+z aborts minishell in all the cases.
		is it correct?
		Minishell$ cat << EOF
		> ^Z
		[1]+  Stopped                 ./minishell
		Minishell$ /bin/echo """""""'"$USER"'""""""
		> "
- [X]  """""""'"$USER"'"""""" double free
- [X]  /bin/echo """""""'"$USER"'"""""" 
		should wait for the quotes to be closed then write out the user name with
		anything put after the > prompt on a new line 
		!!! leaks
- [X]  echo "" "" "" -n -n -n !!! prints out reversed before the minishell prompt, without spaces and 
		only two -n
		solved it by tracking the quotation marks - if there were quotation marks than the node was not deleted
		should just print out    -n -n -n
- [X]  cd ~/Desktop/ !!! cd: ~/Desktop/: No such file or directory
		should return to the folder under Desktop. ;ook up the tilda replacement with HOME from env
- [X]  /bin/echo '"'$USER'"'
		should return "username"
- [X]  /bin/echo "'"'$USER'"'"
		should return '$USER'
- [X]  env
		should print out the env without the ? node at thhe end 
- [X]  export
		should print out the env list in alphabetical order without the ? 
		node at thhe beginning and with prefix declare -x and all the values after the = sign are in
		quotation marks
		!!! prints out with ? on top and without quotation marks
- [X]  +echo "" "" "" -n -n -n -n
		command not found 127
- [X]  heredoc should ignore ctrl + z !!! doesnt ignore and aborts. ctrl+z aborts minishell in all the cases.
		is it correct?
		Minishell$ cat << EOF
		> ^Z
		[1]+  Stopped                 ./minishell
		Minishell$ /bin/echo """""""'"$USER"'""""""
		> "
- [X]  !! heredoc woks partially! without a command at the front it does not work
		the info after the delimeter should not be added to the history. adds only the main command. 
		check for the NULL at the beginning
		Minishell$ << EOF
		> lkjsd
		> sadkjf
		> EOF
		(null): command not found
		Minishell$ 
- [X]  ~ expansion during the substitution phase!!!!!!!!!!!!!
- [X]  exit code 0 should be substituted by the exit code in any case - 
		the main returns 0. should be returning the actual exit code
- [X]  if there is nothing in cmd list then it should return an exit code
- [X]  the $"..." should be discarding the $ sign and should only read smth in the "" - $"HOME" should be just HOME
		- [-]  nshuval@2-C-2:~/Documents/Minishell$ cat << EOF				-> not possible with minishell instructions!
			in bash $$USER expands to shell pid!!!!!!!!!!!!!!!! and i do not have an allowed function for it!!! 
- [X]  check exits for ft_error!!!! especially for redirections
- [X]  the unclosed quotes are not interrupted by ctrl C
- [X]  cat << "$US"E"R” !!! delimiter $USER does not work. ctrl+c does not end the heredoc as expected.
		ctrl+d does
		delimiter is $USER. - all the quotes should be deleted,
		but as $US is not set it should not print out any user name 
		and the bash does not expand the delimiter to anything else!!! just deleted the quotation marks!!
		Minishell$ cat << "$US"E"R"
		> $USER
		> USER
		> US
		> $USER
		> ^C
		> 
- [X]  cat << "EOF”
		> $USER
		EOF
		should not substitute the $USER and give out 
		anshuval@3-F-3:~/Documents/Minishell$ cat << "EOF"
		> $USER
		> EOF
		$USER
		ours is still expanding to $USER substitution
- [X]  heredoc should respond to ctrl + c
- [X]  heredoc should give out a comment on the ctrl + d 
		bash: warning: here-document at line 42 delimited by end-of-file (wanted `EOF')
		check that this is a standard warning. if yes should pass the delimiter and - how to count the lines
- [X]  when closing echo "hello with the ctrl d does not give out the bash notification
		anshuval@3-G-10:~/Documents/Minishell$ echo "hello
		> 
		bash: unexpected EOF while looking for matching `"'
		bash: syntax error: unexpected end of file

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
