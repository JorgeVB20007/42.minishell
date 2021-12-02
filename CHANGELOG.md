# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

