# M I N I S H E L L

### Questions
- [ ] what are built in commands?
- [ ] hwo do pipes work exactly?
--------------------------------------------------------------------------------
### Functions
- [ ] built ins
	- [X] cd
	- [X] echo
	- [X] echo -n (do not output the trailing newline)
	- [X] env ([ ] need to increment SHLVL !!!)
	- [ ] export
	- [ ] unset
	- [X] exit
- [ ] expander
- [ ] external
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
- [ ] continue with built ins
- [ ] anything without env vars
- [ ] figure out env stuff


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

, ,
, , ,
printf, malloc, free, write, , , read,
close, fork, wait, 
, , , ,
, , , kill, exit,
, , , , , , ,
, , , , , ,
, perror, , , , ,
, , , , ,
, , , 