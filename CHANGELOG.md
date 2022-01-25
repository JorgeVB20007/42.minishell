# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 2022-01-26 - Edu
### Added
- Added **ambiguos redirections** error for empty expand redirections
### Fixed
- Fixed posible empty expanses errors not retrieving those tokens

## 2022-01-25 - Jorge
### Added
- Files given with redirections are now checked to make sure they are suitable for each redirection.
	- New *static* functions: **outputting_redirs** and **inputting_redirs**. Found in **processes/process_redirection.c**. More info in a comment on top of each of them.

## 2022-01-25 - Edu
### Added
- Added **current_status** **last_status** to global to to handle error expansions
- Now single **builtins** uses **redirections**
- Added **tilde** expansion

## 2022-01-24 - Jorge
### Fixed
- Fixed bug where env variables were interpreted twice when usig **echo** (builtin).
- Minishell can now differentiate between commands and paths, and acts accordingly.

### Added
- function **is_it_path** in *is_it_path.c* returns 1 if the given text corresponds to a path and 0 if it's something else, such a command.

## 2022-01-24 - Edu
### Added
- **processes/process_redirections** Add redirections to process before executing
- **processes/run_processes** Added signal_handlers

### Changed
- **forks/close_quotes.c** Dinamyc CTRL+D error single double quotes open
- rename t_redir as t_redirection

## 2022-01-23 - Edu
### Added
- **libft/ft_free.c** frees a pointer & set as NULL
- **processes/run_processes** Add envp to run_processes
- **expansion/var_expansor** Added mode to expanse heredoc
- **processes/get_processes** Now expands heredoc (not working on get_processes at forks/heredoc_handler)

### Changed
- rename piped_process as process & t_pp as t_p
- create_forkedpipes renamed as **run_processes**
- single builtin process handled without forks
- **backslash** handled as open input on heredocs
- removed **env_list** from inputlist on **builtins**, **ft_getenv** & **var_expansor**

## 2022-01-22 - Edu
### Added
- **utils/error-handler** Added **count_pipes**
- **forks/run_processes** Added **create_forkedpipes** to run processes

## 2022-01-21 - Jorge
### Fixed
- The combination *cat | cat | (...) | cat | ls* now works as intended :D

### Note
- The heredoc used in this version is the previous one (Jorge's).
	- Jorge's heredoc fails to show variables inside quotation marks ( "$test" --> "" ) when the ending keyword is not between QMs.

## 2022-01-21 - Edu
### Added
- **var_expansor** Added **ft_expand** to simplify expand without mallocing 1st
- **piped_processes** Added adv_qm_rem and ft_expand to prepare proceeses info
### Fixed
- **piped_processes** 1st process element hasn't to be cmd or builtin
- **utils/quote_mark_handler.c** Fix **adv_qm_rem** leaks for every FREE case

## 2022-01-16 - Edu
### Added
- **Makefile** add compiler flag
- **piped_processes.c** added heredoc management to **get_piped_processes**

### Fixed
- **forks/heredoc_handler.c** Fix segfault on empty heredocs
- **str_struct_filter.c** Fix leak on **new_get_command_path**
- **utils/lst_..._handler.c** nulling elements at free

## 2022-01-15 - Edu

### Added
- **piped_processes.c** prepare info needed for all process
- **utils/lst_process_handler.c**  Include basic functions to handle process list (new, add_front, add_back, free_list & print)
- **utils/lst_redir_handler.c**  Include basic functions to handle redir list (new, add_front, add_back, free_list & print)

### Changed
- **eval_token** just return token type, not path

## 2022-01-09 - Edu
## Changed
- **utils/error_handler.c** replace usleep with bash sleep through execve

## 2022-01-05 - Edu
## Added
- new folder **forks** to storage related files
- **forks/heredoc_handler.c** Add pipedforks to handle signals
- **forks/close_quotes.c** Add pipedforks to handle signals
- **libft/ft_strjoin_freedouble.c** ft_strjoin wich free both inputs
- **includes/constants.c** add pipe_fd enumerable & UNEXPECTED_EOF error for heredoc_handler & close_quotes

## Changed
- **heredoc_handler.c** split into **close_quotes.c** & **heredoc_handler.c**, both moved to **forks**
- **minishell1.c** changed main processline readability

## 2022-01-03 - Edu
## Added
- **utils/heredoc_handler.c** Added with functions to handle all heredocs and unclosed quotes
 at start of processline

## 2022-01-02 - Edu
## Added
- **utils/token_handler2.c** Added **eval_token** function to returns if token is PIPE, REDIR, CMD...

## Changed
- Replaced **strcmp** & **modstrcmp** by **libft 's ft_strcmp** (ft_modstrcmp.c to old)
- Rename **ms_parser.c** as **utils/token_handler.c**
- Moved  **has_pipe_redir_open** function to **utils/token_handler2.c**
- Grouped **qm_error_detector.c** & **qm_remover.c** into **utils/quote_mark_handler.c**

###	Fixed
- Fixing **max_pipes_exceeded** exits whithout leaks & also check actual number of pipes (after tokenize)

## 2021-12-31 - Edu
###	Added
- **builtins/exit.c** emulates bash exit
- **utils/megafree.c** added **array_str_get_size** to gets size of array of strings

### Changed
- **utils/error_handler2.c** & **utils/error_handler3.c** Refactor to clean code
- **utils/megafree.c** ft_array_str_print renamed as **array_str_print**

## 2021-12-27 - Edu
### Changed
- **utils/error_handler2.c** Animate Easter with ramdoness xD

### Fixed
- **utils/error_handler3.c** Fix rush02 conversor problems

## 2021-12-26 - Edu
### Added
- **utils/error_handler2.c** & **utils/error_handler3.c** Added Easter Egg to control max pipes allowed

### Fixed
- **new_redirections.c** Remove unused variables

## 2021-12-24 - Edu
### Added
- **minishell1.c** Added boolean **ignored_env** on **processline** to emulate bash CTRL hotkey(+d)(exit) depending on env was ignored at start of the program
- **minishell1.c** Added **disable_ctrl_c_hotkey** to disable CTRL hotkey(+c) from printing ^C following
	+ https://unix.stackexchange.com/questions/558694/why-do-terminals-sometimes-echo-special-characters-like-c
	+ https://stackoverflow.com/questions/68602211/forcing-a-terminal-not-to-print-ctrl-hotkeys-when-signals-are-caught
### Changed
- Remove unnecessary code to handle hotkey(+c) behaviour on signal_handler and constants.h
- **red_sttruct_filter.c** Save 127 exit status on 'Command not found', errors handled with **log_error** functions
- Move unique constants from constants.h to their files.

## 2021-12-20 - Edu
### Fixed
- **var_expansor.c** Fix expansions at start of string

## 2021-12-19 - Jorge
### Changed
- **new_exec_command** renamed to **command_sorter.c**
- **exec_command.c** and **interpreter.c** moved to **/old**
### Fixed
- **heredoc** should now work even with pipes.

## 2021-12-19 - Edu
### Changed
- **utils/signal_handler.c** Added missing definitions
### Fixed
- fix **MS_PROMPT_SIG_INT** to clean lines properly on SIG_INT

## 2021-12-18 - Jorge
### Added
- **utils/signal_handler.c** where the signal handles

## 2021-12-11 - Edu

### Fixed
- **builtins/cd.c** fix log error 'No such file or directory'
- **builtins/cd.c** & **builtins/pwd.c** getcwd doesn't check if current working directory exist anymore to emulate bash work

## 2021-11-30 - Jorge

### Changed
- **new_exec_command()** now checks if the redirection files are directories or files, and checks if they have the required permissions.
	- TO DO: Investigate in what cases an invalid file invalidates  the whole command and in what cases the command stills running.

### Added
- **ft_is_directory.c** file with command **int ft_is_directory(char *)**.
## 2021-11-28 - Jorge

### Changed

- **minishell.h** has been rearranged.
- redirections and pipes are back to normal. The test *cat | cat | cat | ls* still not working

## 2021-11-29 - Edu

### Changed

- **utils/error_handler.c** Added missing documentation

## 2021-11-28 - Edu

### Added

- **utils/error_handler.c** where the error handles
- add status_error to global
- **var_expansor.c** expands exit status of the last executed command

### Changed

- **builtins** errors logged now on STDERR_FILENO

## 2021-11-27 - Edu

### Changed

- **minishell.c** Refactor Stdin handling with new function **processline**

### Fixed

- **ms_parser.c** Protect readline from emptys with new function **has_token**

## 2021-11-27 - Jorge

### Fixed
- Pipes now work how they're supposed to work, but there's still some bugs to fix.
	- Builtins are already in use with these new pipes.

## 2021-11-24 - Edu

### Fixed

- **ms_parser.c** Protect get_tokens from empty inputs "\0"
- **megafree.c** Protect ft_array_str_print  from NULL input

## 2021-11-23 - Edu

### Changed

-  **ms_parser.c** & **var_expansor.c** rename function & variables meaningfull

### Fixed

- **ms_parser.c** free token list after used
- **var_expansor.c** remove uneeded code lines

## 2021-11-22 - Edu

### Added

- **ms_parser.c** added file to parses minishell's input into array of tokens
- **var_expansor.c** added function ft_recursive_expand Given str expand environment variables, input str should come malloc

### Changed

- **utils/lst_str_handler.c** rename ft_lst_str to lst_str
- **env_list_to_vector** rename into **lst_str_to_array** is reused for other purposes, and also moved to **utils/lst_str_handler.c**
- **ft_getenv** moved to **builtins/env.c**

## 2021-11-21 - Edu

### Added

- **includes/constants.c** add FREE/NOT_FREE status enumerable

### Fixed

- **qm_error_detector.c** fix has_pipe_redir_open to handle pipe &redir errors with ERNNO code
- **utils//lst_str_handler.c** fix ft_lst_str_free list should be NULL at free

## 2021-11-20 - Edu

### Added

- **utils/lst_red_handler.c**  Include basic functions to handle red list (new, add_front, add_back & free_list)
- **qm_error_detector.c** added functions ro check open redirections

### Changed

- **utils/lst_str_handler.c** ft_lst_str_delete modified now deletes every matched str of size len from list
- Replaced **libft/ft_strncmp** with **libft/ft_strcmp** is possible
- **var_expansor.c** improve performance dollarfound_getlen

### Fixed

- **builtins/export.c** Fix updating variables with and without equals

## 2021-11-14 - Edu

### Added

- **libft/ft_strcmp.c**  recreates the string.h funtion "strcmp"

### Fixed

- Fixed size_t MAX for str functions as limits.h ULONG_MAX
- **builtins/export.c** not allowing characters before '=' and handling \' \" combinations properly
- **libft/ft_strreplace.c** fix loop when newset chars contains oldset chars
- **src/minishell1.c** Remove some wrong functions (wrong previous commit)

## 2021-11-13 - Edu

### Added

- **utils/lst_str_handler2.c.c** added ft_getenv.c recreates the stdlib.h funtion "getenv"
- **libft/ft_strreplace.c** Returns a new string in which all occurrences of a specified string in the current instance are replaced with another specified string.
- **libft/ft_strreplaceat.c** Returns a new string in which occurrence at index (if found) of a specified string in the current instance are replaced with another specified string.

### Changed

- Now exit minishell write 'exit' at input level
- **builtins/cd.c** refactor to fullfill norm

## 2021-11-11 - Jorge

### Added

- **heredoc** works mostly fine (some rules need to be added to 100% emulate the real Bash).

## 2021-11-09 - Edu

### Added

- **megafree.c** add ft_array_str_print to print array of strings

### Changed

- **Contants.h** rename LITERAL -> LIT
- **pwd.c** get **argv as input like execve
- **interpreter.c** match builtins keywords without limit size, size to INT_MAX
### Fixed

- **libft/ft_strncmp.c** Fix ft_strncmp now check's at end of both str \0

## 2021-11-07 - Jorge

### Added

- *heredoc* started, but **readline** doesn't work insde the ft_heredoc() funtion.

### Fixed

- Other characters (such as '\t') considered spaces when parsing. **ft_isspace** was used for this.
- *fdin* and *fdout* in **redirection_finder()** were messed up. This has been fixed.

## 2021-11-07 - Edu

### Added

- **cd.c** emulates bash cd
- **env.c** & **export.c**  add their own functions to print env records

### Changed

- Replace several magic strings with constants
- **env.c** get **argv as input like execve
- **interpreter.c** added cd, export & unset

### Fixed

- **env.c** & **export.c** dont print same records and export mask them, Fixed!
- **lst_str_handler.c** remove innecesary printf logs & replace ft_strncmp MAX to compare
- **libft/ft_substr.c** Fix substr malloc

## 2021-11-07 - Jorge

### Added

- Added functional pipes. They can be stacked multiple times.
- Non-builtin functions are now executed using *minishell's* own **env**. Functions that take input from the stdin (*cat*, *wc*...) need some fixes.

### Changed

- Functions after **command_finder** don't need to return the parameters used anymore to *idx*, but a pointer to the first parameter is still suggested.
- **ft_echo** can now print parameters after a redirection.

## 2021-11-06 - Edu

### Added

- **lst_str_handlers.c** added ft_lst_str_add_sorted to add items sorted & lst_str_handlers2.c o increase functions to 10

### Changed

- **env.c** add items sorted to linked list
- **unset.c** get **argv as input like execve
- **export.c** get **argv as input like execve

### Fixed

- **env.c** fixed env_list_to_vector, now working properly!
- **unset.c** fixed, now working properly!
- **export.c** fixed, now working properly!

## 2021-11-04 - Edu

### Added

- **env.c** added env_list_to_vector to transform env linked list into vector as intended to work with execve
- **unset.c** emulates bash unset
- **export.c** emulates bash export

## 2021-11-03 - Edu

### Added

- **env.c** emulates bash env include functions to initialize env and shlvl (.src/buitins/env.c)
- **lst_str_handlers.c** handle linked str list (.src/utils/lst_str_handlers.c)

### Changed

- **constants.h** addedd MAX_INT constant
- Double linked str list to single linked list
- **interpreter.c** ft_env added & env_list as function argument in some functions(command_finder & interpreter)

## 2021-11-01 - Edu

### Added

- **buitins** directory added (.src/buitins)
- **utils** directory added (.src/utils)

### Changed

- **Makefile** work with new directorys
- Change path for echo.c, pwd.c & envutils.c

### Fixed

- **Makefile** include missing header constants.h to fix not handling relink
## 2021-10-31 - Jorge

### Added

- Redirection '>' and '>>' should work fine for echo and pwd (pipes only act as ';' for now).
- Redirection '<' added, but hasn't been tested due to the current lack of uses for it.

### Comments

- Segfault when input starts with '>'*, '<'*.
- Pipes only serve as ';' for now. If '|' is the first parameter, an error should be returned, but it doesn't yet.

## 2021-10-31 - Edu

### Added

- **pwd.c** emulates bash pwd
- **envutils.c** include functions to work with enviroment list
- **minishell.c** introduce signal handling (CTRL+C, CTRL+D, CTRL+\) (miss work inside pipex)
- **constants.h** to handle constants

## 2021-10-27 - Jorge

### Added

- N/A

### Changed

- Parser is now linked to readline, so we can test it multiple times without having to launch the program multiple times to check it.
- File "sarchandreplace.c" changed to "var_expansor.c"

## 2021-10-26 - Jorge

### Added

- Added searchandreplace.c (name might change). It's used to manage environment variables ($x) once detected.

### Changed

- N/A


## 2021-10-24 - Edu

### Added

- Add CHANGELOG.md, libft, Makefile,errors & minishell headers

### Changed

- Structure files in folders.

