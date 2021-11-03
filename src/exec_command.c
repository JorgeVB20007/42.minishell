# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	char	**hello;
	int		pip[2];
	int		old;

	old = dup(1);
	pipe(pip);
	dup2(pip[0], STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	write(1, "Hello\n\n\n", 8);
	argc = 0;
	argv = NULL;
	close(pip[1]);
	hello = calloc(sizeof(char *), 3);
	hello[0] = calloc(sizeof(char), 4);
	hello[0][0] = 'c';
	hello[0][1] = 'a';
	hello[0][2] = 't';
	hello[0][3] = 0;
	hello[1] = calloc(sizeof(char), 3);
	hello[1][0] = '-';
	hello[1][1] = 'e';
	hello[1][2] = 0;
/*	hello[2] = calloc(sizeof(char), 3);
	hello[2][0] = 'M';
	hello[2][1] = 'a';
	hello[2][2] = 'k';
	hello[2][3] = 'e';
	hello[2][4] = 'f';
	hello[2][5] = 'i';
	hello[2][6] = 'l';
	hello[2][7] = 'e';
	hello[2][8] = 0;*/
	hello[2] = NULL;
	dup2(old, 1);
	execve("/bin/cat", hello, envp);
	close(pip[0]);
	write(1, "Hiiii", 5);
}
