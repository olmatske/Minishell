### signals! the signals should be passed before the whole start of the loop.
	- [x] study signals!
	- [x] where should they be passed exactly?
	- [x] signal handling
		- [x] ctrl-C displays a new prompt on a new line - sigint
		- [x] ctrl-D exits the shell - NULL is passed
		- [x] ctrl-\ does nothing - sigquit
### quotes handling!
	- [x] if there are quotes the entire line inside trhe quoiotes shouold be a WORD - should be checked right after the quotes checking?
### validation:
	- [x] pipe cannot be at the start or at the end
	- [x] that there are no more than one pipe simultaneously
	- [x] pipe is between two commands - NOT VALID
	- [x] that there is an output or innput file after the redirection sign
	- [x] redirections should have either a filename or a word(that will be turned sowieso into a file name)
	- [x] heredoc should be followed by a delimiter word
### env handling! only after the quotes checking
	- [ ] $ sign
		- [x] if inside the signgle qotes - does nothing
		- [x] if inside double quotes - replaced by the corresponding data from the t_env list
		- [x] if it is a $? sign - replaced by the exit status oof the last executed command 
			- [x] add the initialisation for the variable $? (name = ?) as zero (value = "0").  - as a separate node at  the end of the t_env linked list
			- [x] the variable should be updated for every command! - to show if the status is changed - by execution (tell Olya)
			- [x] the list of the exits:
			0 a command was a success.
			1 a general error.
			2 a syntax error and for built-in commands.
			126 the command was found, but not executable or no permissions.
			127 the command was not found at all.
			130 the command was cancelled exactly when Ctrl+C (SIGINT) was pressed.
		- [x] check that the variable after the $ sign existst in the t_env list under name
			- [x] if it does not exist replace it with an emptry string ""
			- [x] if not inside the quotes - the node should be deleted . CHECK THE RESULT OF THE STRING OF NODES AFTER THE DELETION!
			- [x] if it was inside the quotes - the node is not deleted but contains only an empty string
			- [x] if this situation was after a redirect trhe error should be smth like "redirection error" - check with bash
	- [x] remove the quotes - after the quotes have been checked for correctness they can be safely removed from the WORD
### result!
	- [ ] each t_cmd_node will contain 
		- [x] a string (array) of arguments (like "echo" "-n" "hello" "NULL")
		- [x] redirection (like outfile: "outfile.txt", infile: "infile.txt", heredoc_delimeter:"whatever", out_type (append > or overwrite >> or none))
		- [x] builtin name like echo
	- [x] if there is a pipe in the input the node will be pointing to the next node. OTHERWISE THERE WILL BE ONLY ONE NODE FOR ONE COMMAND
### hleaks
	- [x] memory leaks at exit