* Handle every instruction like execve (path, argv ,env) path is unnecesary in Builtins
* Log with errors and locations (function throwing them) 'd be great
* top | cat -> espera el enter de cat y mientras imprime cada poo tiempo TOP
* cat | cat | cat | ls/echo "hello world!" -> immprime hello world ! o ls espera 3 enters de cat
* apavel  suggestions se parte en 
	cmd
	argv
	pipe input
	pipe output
	echo hola pepe; ls -s | wc 

* redirecciones rules over pipe  ls-l >file | grep cw 
* > file1  > file 2 echo hola >file3 mundo -> create files 1,2 & 3 and writes Hola mundo on 3 (ignore space, care with explamation)

ToDo
- [x] Export should return list orderder 
- [] export dont allow start with every char like number or symbols 