/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:17:46 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/02 12:54:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_PIPES 68
#define WELCOME_EASTER "Oh sorry!...\r you may not find out the SEGFAULT you \
were looking for, but...\ryou discover our \033[1mEaster Egg\033[0m. \
\033[1mCongratulations!!!\033[0m...\rso, you asked for "

#define INTRO_SONG " elephan... I mean pipes right...\r let's get into it, \
in...\rFIVE      \rFOUR      \rTHREE      \rTWO      \rONE      \rBut first, \
let me ignore SIGINT & SIGQUIT...\rsorry for the inconveniences, now it's ok, \
enjoy...\r"
#define ELEPHANT " elephant"
#define ELEPHANT_SONG " went out to play... \r\
\tupon a spiders web one day... \r\tthey had such enormous fun... \r\
\tthat they called for another elephant to come... \r"
#define EMOJIS " |🐘 |🎵 |🕷️ |🕸️ |🎉 |😤 |😛 |🤣 "
#define ERASE_LINE "\033[K"
#define SLEEP_TIME 50000
#define MASK_COLOR_FOREGROUND "\033[9{0}m"
#define MASK_COLOR_BACKGROUND "\033[10{0}m"
#define MASK_BLACK_FOREGROUND "\033[30m"
#define MASK_WHITE_FOREGROUND "\033[37m"
#define MASK_BLACK_BACKGROUND "\033[40m"
#define MASK_WHITE_BACKGROUND "\033[47m"
#define MASK_RESET "\033[0m"
#define HIDE_CURSOR "\033[?25l"
#define NUMBERS_DICTIONARY "\n\
0: zero\n\
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
	BACK,
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

	ramdon = rand() % 8;
	ft_putstr_fd(MASK_RESET, STDOUT_FILENO);
	color = ft_itoa(ramdon);
	if (ODD)
		mask = ft_strreplace(MASK_COLOR_FOREGROUND, "{0}", color);
	else
		mask = ft_strreplace(MASK_COLOR_BACKGROUND, "{0}", color);
	free(color);
	ft_putstr_fd(mask, STDOUT_FILENO);
	free(mask);
	if (ramdon == BACK && ODD)
		ft_putstr_fd(MASK_WHITE_BACKGROUND, STDOUT_FILENO);
	else if (ramdon == WHITE && ODD)
		ft_putstr_fd(MASK_BLACK_BACKGROUND, STDOUT_FILENO);
	if (!ODD && ramdon == BACK)
		ft_putstr_fd(MASK_WHITE_FOREGROUND, STDOUT_FILENO);
	else if (!ODD && ramdon != BACK)
		ft_putstr_fd(MASK_BLACK_FOREGROUND, STDOUT_FILENO);
}

static void	troll_printing(const char *input, char **emojis, int emojis_len)
{
	char	*str;
	int		tabs;

	str = (char *)input;
	while (*str != '\0')
	{
		tabs = 1;
		if (*str == '\t')
			tabs = rand() % 7;
		if (emojis && *str == '\r')
			ft_putstr_fd(emojis[rand() % emojis_len], STDOUT_FILENO);
		while (tabs--)
			ft_putchar_fd(*str, STDOUT_FILENO);
		if (emojis && *str == '\t')
			ft_putstr_fd(emojis[rand() % emojis_len], STDOUT_FILENO);
		if (*str == '\r')
		{
			usleep(SLEEP_TIME * 3);
			ft_putstr_fd(ERASE_LINE, STDOUT_FILENO);
		}
		usleep(SLEEP_TIME);
		str++;
	}
}

static void	easter_egg(int elephants)
{
	int		i;
	char	**emojis;
	int		emojis_len;

	i = 0;
	emojis = ft_split(EMOJIS, '|');
	emojis_len = array_str_get_size(emojis);
	troll_printing(WELCOME_EASTER, NULL, 0);
	translate_number(elephants);
	troll_printing(INTRO_SONG, NULL, 0);
	while (++i < elephants)
	{
		troll_printing("\t", emojis, emojis_len);
		translate_number(i);
		troll_printing(ELEPHANT, NULL, 0);
		if (i > 1)
			troll_printing("s", NULL, 0);
		troll_printing(ELEPHANT_SONG, emojis, emojis_len);
		ramdon_colors(i % 2);
	}
	megafree(&emojis);
}

int	max_pipes_exceeded(char **tokens)
{
	int		i;
	int		pipes;

	i = 0;
	pipes = 0;
	while (tokens[i] != NULL && pipes < INT_MAX)
		if (!strcmp(tokens[i++], "|"))
			pipes++;
	if (pipes >= MAX_PIPES)
	{
		signal(SIGINT, SIG_IGN);
		ft_putstr_fd(HIDE_CURSOR, STDOUT_FILENO);
		easter_egg(pipes);
		signal_handler_default();
		return (1);
	}
	return (0);
}

void	ft_search_word( char *to_find)
{
	char	*match;
	char	*print;

	match = ft_strnstr(NUMBERS_DICTIONARY, to_find, ULONG_MAX);
	if (match != NULL)
	{
		match = ft_strchr(match, ':');
		print = ft_substr(match, 2, ft_strchr(match, '\n') - match - 2);
		troll_printing(print, NULL, 0);
		free(print);
	}
}
