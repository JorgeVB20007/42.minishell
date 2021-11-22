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
- [ ] Unificar entradas para Builtins
- [ ] Gestionar correctamente ERNO
- [ ] Gestionar señales en procesos hijos (open heredocs)
- [ ] Hacer Env global a todas las funciones
- [ ] Sacar expandir variables de la entrada
- [x] Test redirection functions
- [ ] Use enumerables for status like philoforks ex(FREE, NOT_FREE, KO, OK) wacht out literas alredy in use like NEWLINE

Test parser.c aas basfbaskfhbsajhb ||| <<< >>> as|da>sa<s>>asf<<asdfd
test ft_recursive_expand sasdfsad$USER fas'd$TE'RM fasdfsadfsdf
