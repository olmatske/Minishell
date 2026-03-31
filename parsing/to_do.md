- signals! the signals should be passed before the whole start of the loop.
	- [ ] study signals!
	- [ ] where should they be passed exactly?
	- [ ] signal handling
		- [ ] ctrl-C displays a new prompt on a new line - sigint
		- [ ] ctrl-D exits the shell - NULL is passed
		- [ ] ctrl-\ does nothing - sigquit
- quotes handling!
	- [ ] if there are quotes the entire line inside trhe quoiotes shouold be a WORD - should be checked right after the quotes checking?
- env handling! only after the quotes checking
	- [ ] $ sign
		- [ ] if inside the signgle qotes - does nothing
		- [ ] if inside double quotes - replaced by the corresponding data from the t_env list
		- [ ] if it is a $? sign - replaced by the exit status oof the last executed command 
			- [ ] add the initialisation for the variable $? (name = ?) as zero (value = "0").  - as a separate node at  the end of the t_env linked list
			- [ ] the variable should be updated for every command! - to show if the status is changed - by execution (tell Olya)
			- [ ] the list of trhe exits:
			0 a command was a success.
			1 a general error.
			2 a syntax error for built-in commands.
			126 the command was found, but not executable or no permissions.
			127 the command was not found at all.
			130 the command was cancelled exactly when Ctrl+C (SIGINT) was pressed.
		- [ ] check that the variable after the $ sign existst in the t_env list under name
			- [ ] if it does not exist replace it with an emptry string ""
			- [ ] if not inside the qotes - the node should be deleted . CHECK THE RESULT OF THE STRING OF NODES AFTER THE DELETION!
			- [ ] if it was inside the quotes - the node is not deleted but contains only an empty string
			- [ ] if this situation was after a redirect trhe error should be smth like "redirection error" - check with bash
	- [ ] remove the quotes - after the quotes have been checked for correctness they can be safely removed from the WORD
- validation:
	- [ ] pipe cannot be at the start or at the end
	- [ ] that there are no more than one pipe simultaneously
	- [ ] pipe is between two commands
	- [ ] that there is an output file after the redirection sign
	- [ ] redirections should have either a filename or a word(that will be turned sowieso into a file name)
	- [ ] heredoc should be followed by a delimiter word
- result!
	- [ ] each t_cmd_node will contain 
		- [ ] a string (array) of arguments (like "echo" "-n" "hello" "NULL")
		- [ ] redirection (like outfile: "outfile.txt", infile: "infile.txt", heredoc_delimeter:"whatever", out_type (append > or overwrite >> or none))
		- [ ] builtin name like echo
	- [ ] if there is a pipe in the input the node will be pointing to the next node. OTHERWISE THERE WILL BE ONLY ONE NODE FOR ONE COMMAND
- heredoc handling!!! to be studied and added later