# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


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

