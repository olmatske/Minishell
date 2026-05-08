# M I N I S H E L L

### Questions
- [ ] what are built in commands?
- [ ] hwo do pipes work exactly?
--------------------------------------------------------------------------------
### Functions
- [X] built ins
	- [X] cd
	- [X] echo
	- [X] echo -n (do not output the trailing newline)
	- [X] env ([ ] redo and only use the env struct)
	- [X] export ([ ] need to update the env file !!!)
	- [X] unset ([ ] need to update the env file !!!)
	- [ ] exit
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
--------------------------------------------------------------------------------
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
- [ ] Pipes
- [X] PreZero (Garbage Collector)
- [ ] heredoc last
# - [X] link to main
#	- [ ] norm
- [ ] change builtin.c
	- [ ] envp to struct
	- [ ] args
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