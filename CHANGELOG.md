# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

