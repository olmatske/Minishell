# M I N I S H E L L

### Questions
- [X] what are built in commands?
- [X] hwo do pipes work exactly?
--------------------------------------------------------------------------------
### Functions
- [X] built ins
	- [X] cd
	- [X] echo
		- [X] fix -n
	- [X] echo -n (do not output the trailing newline)
	- [X] env ([X] redo and only use the env struct)
	- [X] export
		- [X] fix updating variable if it exists
	- [X] unset
	- [X] exit
	- [X] externals paths etc
- [X] expander
- [X] external functions
- [X] heredoc
	-> cat << EOF
		hello
		world
		EOF
		-> printf until the delimiter
--------------------------------------------------------------------------------
### Other
- [X] structs
--------------------------------------------------------------------------------
### Header
- [X] flags (heredoc, pipe, redicrection etc)
- [X] struct for built in commands
-------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
### Errors
- [X] externals leak (example: ls)
- [X] when writing "exit" it prints exit again
	- [X] leaks
- [X] are args supposed to have the builtin in them??
	-> yes, kind of
- [X] wrong command doesn't work (example: rxiy)
	- [X] leaks
- [X] echo -n: -n is in args and not initialized
	 -> supposed to be this way, added checker in echo function
- [X] cd not working
- [X] env does not get updated and prints garbage like ?=0 -> that's the exit, not supposed to be printed, isn't garbage either
- [X] fix export behaviour: "declare -x "
- [X] bash export and minishell export differs
- [X] Minishell$ echo "hi hello hiii" | cat -e >>>>>>> LEAKS!!!
	-> idk what I did but I fixed it, exit leaks because of shell status
	- [X] exitting afterwards leaks too!!
- [X] exit leaks like crazy
	-> likely because of the uninitialized shell exit status
- [X] just cd does not rerout to $HOME
- [X] echo status must be 1 if cd nonexistentpath
- [X] export PATH -> declare -x PATH (no ="")
- [X] pipes don't work apparently (env | grep TEST) -> they do
- [X] fix export so that it sees the difference between export PATH and export PATH= !!
- [X] env gets permanently sorted after export
- [X] grep "NAME" goes into infinite loop
		~/42/Minishell (execution*) » ./minishell                                               oli@Olgas-MacBook-Air
		Minishell$ grep "NAME" Makefile
		NAME = minishell
		all: $(NAME)
		$(NAME): $(OBJECTS) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline
				$(RM) $(NAME) $(OBJECTS)
		Minishell$ 
- [X] why does the tester fail on exit codes when everythings fine>??
- [X] echo "overwrite" > test.txt -> no output
- [X] > doesn't appear to be working, doesn't make a new file
- [X] when doing echo and a pipe it still prints with echo
- [X] >> doesn't seem to be working
- [X] cat < nonexistent.txt goes into infinite loop
- [X] heredoc is missing
- [X] echo "first" > out.tct < in.txt   oli@Olgas-MacBook-Air zsh: no such file or directory: in.txt
- [X] > test.txt goes into infinite loop
		-> smth wrong with redirections...
- [X] echo "fail" > dev/full -> /dev/full: No space left on device 
- [X] cat > > -> syntax error near unexpected token '>'
- [X] exits!!!
- [X] update old pwd and new pwd in env after calling cd !!!
- [X] apparently storing exit code in env is wrong
- [X] Ctrl+\ doesn't work
- [X] echo "fail" > dev/full -> /dev/full: No space left on device 
- [X] cat > > -> syntax error near unexpected token '>'
- [X] exits!!!
- [X] update old pwd and new pwd in env after calling cd !!!
- [X] apparently storing exit code in env is wrong
- [X] Ctrl+\ doesn't work
- [X] print quotes in export!
- [X] add exit after exiting with a set number
- [X]  !!!doesnt work!!! running ctrl-\ after a blocking command (like grep b) should write 
		^\Quit (core dumped) on the line
		and give a prompt on a new line
- [X]  !! heredoc woks partially! without a command at the front it does not work
		the info after the delimeter should not be added to the history. adds only the main command. 
		check for the NULL at the beginning
		Minishell$ << EOF
		> lkjsd
		> sadkjf
		> EOF
		(null): command not found
		Minishell$ 

///////////////////////////////////////////////////////////////////////////////////////////////////////////

### Roadmap
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

minishell:
Minishell$ export PATH=""
Minishell$ $?
0: command not found
Minishell$ 

bash:
olmatske@3-F-4:~/Curriculum/Minishell/tt$ export PATH=""
olmatske@3-F-4:~/Curriculum/Minishell/tt$ $?
bash: sed: No such file or directory
bash: 0: No such file or directory






### Allowed functions
------------------------------------------------
readline
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
access
open
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
getcwd
chdir
stat
lstat
fstat
unlink
execve
dup
dup2
pipe
opendir
readdir
isatty
ttyname
ttyslot
ioctl
getenv
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
closedir
strerror

|||
|||
|||
|||
|||
|||
|||
|||
|||
|||

printf, malloc, free, write, read, close, fork, wait, kill, exit, perror