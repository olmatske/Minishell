# M I N I S H E L L

### Questions
- [ ] what are built in commands?
- [ ] hwo do pipes work exactly?
--------------------------------------------------------------------------------
### Functions
- [X] built ins
	- [X] cd
	- [X] echo
		- [X] fix -n
	- [X] echo -n (do not output the trailing newline)
	- [X] env ([ ] redo and only use the env struct)
#	- [X] export
#		- [X] fix updating variable if it exists
	- [X] unset
	- [X] exit
#	- [ ] externals paths etc
- [ ] expander
- [ ] external functions
- [ ] heredoc
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
- [] export PATH -> declare -x PATH (no ="")
- [X] pipes don't work apparently (env | grep TEST) -> they do
- [] fix export so that it sees the difference between export PATH and export PATH= !!
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
- [ ] heredoc is missing
- [ ] echo "first" > out.tct < in.txt   oli@Olgas-MacBook-Air zsh: no such file or directory: in.txt
- [ ] > test.txt goes into infinite loop
		-> smth wrong with redirections...
# - [ ] echo "fail" > dev/full -> /dev/full: No space left on device 
- [ ] cat > > -> syntax error near unexpected token '>'
- [ ] exits!!!
- [ ] update old pwd and new pwd in env after calling cd !!!
- [ ] apparently storing exit code in env is wrong
- [ ] Ctrl+\ doesn't work

# - [ ] update $PWD when changing directories
# - [ ] Heredoc
# - [ ] Minishell$ pwd
				/Users/oli/42/Minishell
				curr status: 0
				shell status: 0
				Minishell$ $?
				0: Command not found
				curr status: 0
				shell status: 0
				Minishell$ Minishell$  <------ !!! when pressing down key
				Minishell$ 

- [ ] open fd nach signals bei heredoc
		-> close the fd if a signal comes throgh during heredoc!!!
- [ ] open fd im child proccess is not supposed to happen!!


///////////////////////////////////////////////////////////////////////////////////////////////////////////

### Roadmap
- [X] start with: echo hi (> hi.txt)
- [X] continue with built ins
- [X] anything without env vars
- [X] figure out env stuff
 - [ ] files
	- [X] < "input" redirects input: cat < file.txt outputs file content to shell
	- [X] > "overwrite" redirects input into a file
		-> signals for exiting write mode!
	- [ ] << "heredoc" should be given a delimiter, then read the input until a line containing the
			delimiter is seen. However, it doesn’t have to update the history!
	- [X] >> "append" should redirect output in append mode.
		-> [ ] signals for exiting write mode!

- [ ] externals
	- [ ] absolute path
	- [ ] relative path
	- [ ] command
		-> search until :
		-> yoink the string
		-> append yoinked string + '/' + command
		-> check if it exists
			> if no iterate further and repeat process
			> if yes, return path
- [X] Pipes
- [X] PreZero (Garbage Collector)
- [ ] heredoc last
- [X] link to main
	- [X] norm
- [X] change builtin.c
	- [X] envp to struct
	- [X] args
- [ ] exit signals
- [ ] add functions to header and clean up
- [ ] increment and execute commands if pipes
- [ ] norminette


- [X] garbage collecter
	-> cutsom mallox, mallocs and remembers in an array and frees at the end
	- [X] gc_malloc — allocates memory and registers it
	- [X] gc_free — frees a single pointer and removes it from the list
	- [X] gc_free_all — frees every tracked pointer (call on exit or error)
	- [X] gc_add — adds a pointer to the tracking list\
	- [X] gc_calloc - same as gc_malloc but fills space with NULL

- [ ] execve are for external!!!!

- [ ] grep hi <./test_files/infile_big <./test_files/infile
	-> LEAKS!!!

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