/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:17:46 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/31 15:29:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_PIPES 68
#define WELCOME_EASTER "Oh sorry!...\r you may not find out the SEGFAULT you \
were looking for, but...\ryou 've discovered our \033[1mEaster Egg\033[0m. \
\033[1mCongratulations!!!\033[0m...\rso, you asked for "

#define INTRO_SONG " elephan... I mean pipes right...\r let's get into it, \
in...\rFIVE      \rFOUR      \rTHREE      \rTWO      \rONE      \rBut first, \
let me ignore SIGINT & SIGQUIT...\rsorry for the inconveniences, now it's ok, \
enjoy...\r"
#define ELEPHANT " elephant"
#define ELEPHANT_SONG " went out to play... \r\
\tupon a spiders web one day... \r\tthey had such enormous fun... \r\
\tthat they called for another elephant to come... \r"
#define SLEEP_ARGS "/bin/sleep|sleep|0.006"
#define EMOJIS " |🐘 |🎵 |🕷️ |🕸️ |🎉 |😛 |🤣 "
#define ERASE_LINE "\033[K"
#define MASK_COLOR_FOREGROUND "\033[9{0}m"
#define MASK_COLOR_BACKGROUND "\033[10{0}m"
#define MASK_BLACK_FOREGROUND "\033[30m"
#define MASK_WHITE_FOREGROUND "\033[37m"
#define MASK_BLACK_BACKGROUND "\033[40m"
#define MASK_WHITE_BACKGROUND "\033[47m"
#define MASK_RESET "\033[0m"
#define END_SIMULATION "\033[0m\033[K\033[?25h\n"
#define HIDE_CURSOR "\033[?25l"
#define NUMBERS_DICTIONARY "\n\
0: \n\
1: one\n\
2: two\n\
3: three\n\
4: four\n\
5: five\n\
6: six\n\
7: seven\n\
8: eight\n\
9: nine\n\
10: ten\n\
11: eleven\n\
12: twelve\n\
13: thirteen\n\
14: fourteen\n\
15: fifteen\n\
16: sixteen\n\
17: seventeen\n\
18: eighteen\n\
19: nineteen\n\
20: twenty\n\
30: thirty\n\
40: forty\n\
50: fifty\n\
60: sixty\n\
70: seventy\n\
80: eighty\n\
90: ninety\n\
100: hundred\n\
1000: thousand\n\
1000000: million\n\
1000000000: billion\n\
1000000000000: trillion\n\
1000000000000000: quadrillion\n\
1000000000000000000: quintillion\n\
1000000000000000000000: sextillion\n\
1000000000000000000000000: septillion\n\
1000000000000000000000000000: octillion\n\
1000000000000000000000000000000: nonillion\n\
1000000000000000000000000000000000: decillion\n\
1000000000000000000000000000000000000: undecillion\n\
"

enum e_colors{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

static void	ramdon_colors(int ODD)
{
	int		ramdon;
	char	*color;
	char	*mask;

	ramdon = ft_rand_eight_module(NULL);
	ft_putstr_fd(MASK_RESET, STDOUT_FILENO);
	color = ft_itoa(ramdon);
	if (ODD)
		mask = ft_strreplace(MASK_COLOR_FOREGROUND, "{0}", color);
	else
		mask = ft_strreplace(MASK_COLOR_BACKGROUND, "{0}", color);
	free(color);
	ft_putstr_fd(mask, STDOUT_FILENO);
	free(mask);
	if (ramdon == BLACK && ODD)
		ft_putstr_fd(MASK_WHITE_BACKGROUND, STDOUT_FILENO);
	else if (ramdon == WHITE && ODD)
		ft_putstr_fd(MASK_BLACK_BACKGROUND, STDOUT_FILENO);
	if (!ODD && ramdon == BLACK)
		ft_putstr_fd(MASK_WHITE_FOREGROUND, STDOUT_FILENO);
	else if (!ODD && ramdon != BLACK)
		ft_putstr_fd(MASK_BLACK_FOREGROUND, STDOUT_FILENO);
}

static void	troll_printing(const char *input, char **emojis, char **sleep_argv)
{
	char	*str;
	int		tabs;
	int		times;

	str = (char *)input;
	while (*str != '\0' && g_var.elephants == PLAYING)
	{
		tabs = 1;
		if (*str == '\t')
			tabs = ft_rand_eight_module(NULL);
		if (emojis && *str == '\r')
			ft_putstr_fd(emojis[ft_rand_eight_module(NULL)], STDOUT_FILENO);
		while (tabs--)
			ft_putchar_fd(*str, STDOUT_FILENO);
		if (emojis && *str == '\t')
			ft_putstr_fd(emojis[ft_rand_eight_module(NULL)], STDOUT_FILENO);
		times = 6;
		while (*str == '\r' && times--)
			execve_sleep(sleep_argv);
		if (*str == '\r')
			ft_putstr_fd(ERASE_LINE, STDOUT_FILENO);
		execve_sleep(sleep_argv);
		str++;
	}
}

static void	easter_egg(int elephants)
{
	int		i;
	char	**emojis;
	char	**sleep_argv;

	i = 0;
	emojis = ft_split(EMOJIS, '|');
	sleep_argv = ft_split(SLEEP_ARGS, '|');
	troll_printing(WELCOME_EASTER, NULL, sleep_argv);
	translate_number(elephants, sleep_argv);
	troll_printing(INTRO_SONG, NULL, sleep_argv);
	while (++i < elephants && g_var.elephants == PLAYING)
	{
		troll_printing("\t", emojis, sleep_argv);
		translate_number(i, sleep_argv);
		troll_printing(ELEPHANT, NULL, sleep_argv);
		if (i > 1)
			troll_printing("s", NULL, sleep_argv);
		troll_printing(ELEPHANT_SONG, emojis, sleep_argv);
		ramdon_colors(i % 2);
	}
	execve_sleep(sleep_argv);
	megafree(&sleep_argv);
	megafree(&emojis);
}

int	max_pipes_exceeded(char **tokens)
{
	int		pipes;

	pipes = count_pipes(tokens);
	if (pipes >= MAX_PIPES)
	{
		signal(SIGINT, &signal_handler_elephants_sigint);
		ft_putstr_fd(HIDE_CURSOR, STDOUT_FILENO);
		easter_egg(pipes);
		signal_handler_default();
		ft_putstr_fd(END_SIMULATION, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	ft_search_word(char *to_find, char **sleep_argv)
{
	char	*match;
	char	*print;

	match = ft_strnstr(NUMBERS_DICTIONARY, to_find, ULONG_MAX);
	if (match != NULL)
	{
		match = ft_strchr(match, ':');
		print = ft_substr(match, 2, ft_strchr(match, '\n') - match - 2);
		troll_printing(print, NULL, sleep_argv);
		free(print);
	}
}
