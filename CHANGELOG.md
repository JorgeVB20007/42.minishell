# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 2021-10-31 - Jorge

### Added

- Redirection '>' and '>>' should work fine for echo and pwd (pipes only act as ';' for now).
- Redirection '<' added, but hasn't been tested due to the current lack of uses for it.

### Comments

- Segfault when input starts with '>'*, '<'*.
- Pipes only serve as ';' for now. If '|' is the first parameter, an error should be returned, but it doesn't yet.

## 2021-10-31 - Edu

### Added

- pwd.c emulates bash pwd
- envutils.c include functions to work with enviroment list
- minishell.c introduce signal handling (CTRL+C, CTRL+D, CTRL+\) (miss work inside pipex)

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

