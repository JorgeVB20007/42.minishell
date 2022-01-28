* Handle every instruction like execve (path, argv ,env) path is unnecesary in Builtins
* Log with errors and locations (function throwing them) 'd be great
* top | cat -> espera el enter de cat y mientras imprime cada poo tiempo TOP
* cat | cat | cat | ls/echo "hello world!" -> immprime hello world ! o ls espera 3 enters de cat
* system("lsof -c minishell"); to check unclosed elements
* apavel  suggestions se parte en
	cmd
	argv
	pipe input
	pipe output
	echo hola pepe; ls -s | wc

* redirecciones rules over pipe  ls-l >file | grep cw
* > file1  > file 2 echo hola >file3 mundo -> create files 1,2 & 3 and writes Hola mundo on 3 (ignore space, care with explamation)
* ~/ ->  replace for env's HOME if we want to handle this

tomartin jalvarad tips
* 1st handle errors not closed quotes
* jalvarad 2nd handle errors is last redirection
* tomartin 3rd tokenizes input
* jalvarad 3rd split by pipes

ToDo
- [x] Export should return list orderder
- [x] Export dont allow start with every char like number or symbols
- [x] Unificar entradas para Builtins
- [ ] Gestionar correctamente ERNO
- [x] Gestionar señales en procesos hijos (open heredocs)
- [x] Hacer Env global a todas las funciones
- [x] Sacar expandir variables de la entrada
- [x] Test redirection functions
- [ ] Use enumerables for status like philoforks ex(FREE, NOT_FREE, KO, OK) wacht out literas alredy in use like NEWLINE
- [x] Handle heredoc before everything else
- [x] Use forks and signals to handle heredocs and unclosed quotes
- [ ] Review exit_status on ft_exit -> test several arguments (1st Number)
- [ ] ft_exit return exit\n as exit
- [ ] control is directory on searching cmd
- [ ] rand into execve_random
- [ ] control if bash (sleep & rands) exits
- [ ] control \ on heredocs
- [ ] eval heredocs with hello $hi "$hi" '$hi'  & he""llo $hi "$hi" '$hi'

- [ ] expanse tilde (https://unix.stackexchange.com/questions/423962/what-is-a-tilde-when-used-as-a-prefix-to-a-path/423984?noredirect=1#comment763846_423984
 					https://www.gnu.org/software/bash/manual/html_node/Tilde-Expansion.html#:~:text=If%20a%20word%20begins%20with,are%20considered%20a%20tilde%2Dprefix%20.&text=If%20this%20login%20name%20is,of%20the%20HOME%20shell%20variable)
- [ ] create execve random
- [ ] create fallback for execve sleep & random
Test parser.c aas basfbaskfhbsajhb ||| <<< >>> as|da>sa<s>>asf<<asdfd
test ft_recursive_expand sasdfsad$USER fas'd$TE'RM fasdfsadfsdf

WIFSIGNALED() to set status error by signals
	https://brennan.io/2015/01/16/write-a-shell-in-c/
	https://www.geeksforgeeks.org/making-linux-shell-c/


