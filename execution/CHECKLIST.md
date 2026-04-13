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
	- [X] env ([ ] need to increment SHLVL !!!)
	- [X] export ([ ] need to update the env file !!!)
	- [X] unset ([ ] need to update the env file !!!)
	- [X] exit
- [ ] expander
- [ ] external functions
- [ ] heredoc
--------------------------------------------------------------------------------
### Other
- [ ] structs
--------------------------------------------------------------------------------
### Library
- [ ] flags (heredoc, pipe, redicrection etc)
- [ ] struct for built in commands
- [ ] struct for argumnets
--------------------------------------------------------------------------------
### Roadmap
- [X] start with: echo hi (> hi.txt)
- [X] continue with built ins
- [X] anything without env vars
- [X] figure out env stuff
# - [ ] files
- [ ] PreZero (Garbage Collector)
- [ ] heredoc last

# - [ ] < should redirect input.
- [ ] > redirects input: cat < file.txt outputs whatever is in file.txt into the shell
- [ ] << should be given a delimiter, then read the input until a line containing the
		delimiter is seen. However, it doesn’t have to update the history!
- [ ] >> should redirect output in append mode.

- [ ] figure out files

- [ ] external command path lookup

- [ ] single command fork + execve

- [ ] basic redirections

- [ ] builtin detection

- [ ] parent-only builtins: cd, export, unset, exit

- [ ] pipelines

- [ ] heredoc

- [ ] signal handling

- [ ] exit-status propagation

- [ ] garbage collecter
	-> cutsom mallox, mallocs and remembers in an array and frees at the end

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