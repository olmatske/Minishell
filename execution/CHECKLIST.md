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
#		- [ ] fix updating variable if it exists
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

### Errors
- [X] externals leak (example: ls)
- [X] when writing "exit" it prints exit again
	- [X] leaks
- [X] are args supposed to have the builtin in them??
	-> yes, kind of
- [X] wrong command doesn't work (example: rxiy)
	- [X] leaks
- [X] echo -n: -n is in args and not initialized
	 -[X] supposed to be this way, added checker in echo function


~/Curriculum/Minishell (execution*) » ./minishell                                                                                                                                                                                                                                                                                       olmatske@3-F-12
Minishell$ echo hi hello
hi hello
Minishell$ echo -n hi hello
-n hi hello
Minishell$ exit

=================================================================
==229973==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x49a23d in malloc (/home/olmatske/Curriculum/Minishell/minishell+0x49a23d)
    #1 0x4cb6be in minishell_loop /home/olmatske/Curriculum/Minishell/minishell.c:35:10
    #2 0x4cb548 in main /home/olmatske/Curriculum/Minishell/minishell.c:73:2
    #3 0x77288c229d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: 24 byte(s) leaked in 1 allocation(s).





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