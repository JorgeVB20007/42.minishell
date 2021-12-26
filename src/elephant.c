#include "minishell.h"
#define MAXPIPES 64
#define WELCOME_EASTER "Oh sorry!...\r you may not find out the SEGFAULT you \
were looking for, but...\ryou discover our easter egg. Congratulations!!!...\r\
so, you asked for "

#define INTRO_SONG " elephan... I mean pipes right...\r let's get into it, \
in...\rFIVE   \rFOUR   \rTHREE   \rTWO   \rONE   \rBut first, let me ignore \
SIGINT & SIGQUIT...\rsorry for the inconveniences, now it's ok, enjoy...\r"
#define ELEPHANT " elephant"
#define ELEPHANT_SONG " went out to play...\r\
Upon a Spiders web one day...\rThey had such enormous fun...\r\
That they called for another elephant to come...\r"
#define ERASE_LINE "\033[K"
#define SLEEP_TIME 100000
#define MASK_COLOR_FOREGROUND "\033[3{0}m"
#define MASK_COLOR_BACKGROUND "\033[4{0}m"

static int get_another_rand_number(int number)
{
	int	new_number;

	new_number = rand() % 8;
	while (new_number == number)
		new_number = rand() % 8;
	return (new_number);
}

static void ramdon_colors()
{
	int		ramdon;
	char	*color;
	char	*mask;

	ramdon = rand() % 8;
	color =  ft_itoa(ramdon);
	mask = ft_strreplace(MASK_COLOR_FOREGROUND, "{0}", color);
	free(color);
	ft_putstr_fd(mask, STDOUT_FILENO);
	free(mask);
	color =  ft_itoa(get_another_rand_number(ramdon));
	mask = ft_strreplace(MASK_COLOR_BACKGROUND, "{0}", color);
	free(color);
	ft_putstr_fd(mask, STDOUT_FILENO);
	free(mask);
}

static void	troll_printing(const char *input)
{
	char	*str;

	str = (char *)input;
	while (*str != '\0')
	{
		ft_putchar_fd(*str, STDOUT_FILENO);
		if (*str  == '\r')
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
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	ft_putstr_fd("\033[?25l", STDOUT_FILENO);
	troll_printing(WELCOME_EASTER);
	ft_putnbr_fd(elephants, STDOUT_FILENO);
	troll_printing(INTRO_SONG);
	while (++i < elephants)
	{
		ft_putnbr_fd(i, STDOUT_FILENO);
		troll_printing(ELEPHANT);
		if (i != 1)
			troll_printing("s");
		troll_printing(ELEPHANT_SONG);
		ramdon_colors();
	}
	signal_handler_default();
}

void max_pipes_exceeded(const char *input)
{
	int		pipes;
	char	*str;

	pipes = 0;
	str = (char *) input;
	while (*str != '\0')
	{
		if (*str++ == '|')
			pipes++;
	}
	if (pipes >= MAXPIPES)
		easter_egg(pipes);
}
