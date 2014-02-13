/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 20:01:04 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/25 20:29:33 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "libft.h"

typedef struct termios	t_term;

typedef struct	s_data
{
	char		**env;
	char		**tcap;
	u_int		col;
	u_int		lin;
	t_term		term;
	t_term		term_backup;
}				t_data;

#define NB_TCAP	10

t_term	*get_term(t_term *term)
{
	static t_term	*ptr = NULL;

	if (term != NULL)
		ptr = term;
	return (ptr);
}

int		tputs_putchar(int c)
{
	write(0, &c, 1);
	return (1);
}

char	*ft_getenv(char ***env, char *name)
{
	int		i;
	int		j;

	i = 0;
	if (*env != NULL)
	{
		while (*(*env + i) != NULL)
		{
			j = 0;
			while ((*env)[i][j] == name[j])
				j++;
			if ((*env)[i][j] == '=' && name[j] == '\0')
				return ((*env)[i] + j + 1);
			i++;
		}
	}
	return (NULL);
}

int		ft_get_size(t_data *data)
{
	char	buffer[2048];

	tgetent(buffer, ft_getenv(&(data->env), "TERM"));
	data->col = tgetnum("co");
	data->lin = tgetnum("li");
	ft_putnbr(tgetnum("lm"), 0);
	ft_putchar('\n');
	return (0);
}

int		ft_init_tcap(t_data *data)
{
	char	**tcap;

	tcap = (char **)malloc(sizeof(char *) * NB_TCAP);
	if (tcap != NULL)
	{
		if ((tcap[0] = tgetstr("le", NULL)) == NULL || \
			(tcap[1] = tgetstr("LE", NULL)) == NULL || \
			(tcap[2] = tgetstr("ti", NULL)) == NULL || \
			(tcap[3] = tgetstr("te", NULL)) == NULL || \
			(tcap[4] = tgetstr("nd", NULL)) == NULL || \
			(tcap[5] = tgetstr("cm", NULL)) == NULL || \
			(tcap[6] = tgetstr("am", NULL)) == NULL || \
			tgetnum("co") < 0 || tgetnum("li") < 0 || tgetnum("lm" < 0))
			return (-2);
		data->tcap = tcap;
	}
	return (-3);
}

int		ft_init_term(t_data *data)
{
	char	buffer[2048];

	if (tgetent(buffer, getenv("TERM")) < 1)
		return (-1);
	tcgetattr(0, &(data->term_backup));
	tcgetattr(0, &(data->term));
	(data->term).c_lflag &= ~(ICANON | ECHO);
	(data->term).c_lflag |= ISIG;
	tcsetattr(0, 0, &(data->term));
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	return (0);
}

int		ft_init(int ac, char **av, char **env, t_data *data)
{
	int		ret;

	(void)ac;
	(void)av;
	(void)env;
	if ((ret = ft_init_term(data)) < 0)
		return (ret);
	if ((ret = ft_init_tcap(data)) < 0)
		return (ret);
	ft_get_size(data);
	get_term(&(data->term_backup));
	return (0);
}

void	sigint(int sig)
{
	t_term	*term;

	(void)sig;
	term = get_term(NULL);
	tcsetattr(0, 0, term);
	exit(0);
}

int		ft_isalnumwh(u_int c)
{
	if (c >= 32 && c < 127)
		return (1);
	else
		return (0);
}

void	ft_insert(t_data *data, char *str, u_int *whereis, u_int rd)
{
	u_int	len;
	u_int	curs;

	len = 0;
	while (str[len])
		len++;
	curs = len;
	while (curs > *whereis - 1)
	{
		str[curs] = str[curs - 1];
		curs--;
	}
	str[curs] = (char)rd;
	write(0, str + curs, len - curs + 1);
	tputs(tgoto(tgetstr("cm", NULL), *whereis % data->col, \
				*whereis / data->col), 1, tputs_putchar);
	return ;
}

void	ft_backspace(t_data *data, char *str, u_int *whereis)
{
	u_int	len;
	u_int	curs;

	(*whereis)--;
	tputs(tgoto(tgetstr("cm", NULL), *whereis % data->col, \
				*whereis / data->col), 1, tputs_putchar);
	curs = *whereis - 1;
	while (str[++curs])
		str[curs] = str[curs + 1];
	len = 0;
	while (str[len + *whereis])
		len++;
	write(0, str + *whereis, len);
	write(0, " ", 1);
	tputs(tgoto(tgetstr("cm", NULL), *whereis % data->col, \
				*whereis / data->col), 1, tputs_putchar);
	return ;
}

void	ft_delete(t_data *data, char *str, u_int *whereis)
{
	u_int	len;
	u_int	curs;

	curs = *whereis - 1;
	while (str[++curs])
		str[curs] = str[curs + 1];
	len = 0;
	while (str[len + *whereis])
		len++;
	write(0, str + *whereis, len);
	write(0, " ", 1);
	tputs(tgoto(tgetstr("cm", NULL), *whereis % data->col, \
				*whereis / data->col), 1, tputs_putchar);
	return ;
}

int		main(int ac, char **av, char **env)
{
	u_int	whereis;
	u_int	rd;
	t_data	data;
	char	*str;

	signal(SIGINT, sigint);
	whereis = 0;
	ft_init(ac, av, env, &data);
	str = ft_strnew(2048);
	while (read(0, &rd, 4) > 0)
	{
		if (ft_isprint(rd) && whereis < 2048)
		{
			whereis++;
			if (str[whereis - 1] == '\0')
			{
				str[whereis - 1] = (char)rd;
				write(0, &rd, 1);
			}
			else
				ft_insert(&data, str, &whereis, rd);
		}
		else if (rd == 127 && whereis > 0)
		{
			ft_backspace(&data, str, &whereis);
		}
		else if (rd == 2117294875 && str[whereis] != '\0')
		{
			ft_delete(&data, str, &whereis);
		}
		else if (rd == 4479771 && whereis > 0)
		{
			whereis--;
			tputs(tgoto(tgetstr("cm", NULL), whereis % data.col, whereis / data.col), 1, tputs_putchar);
		}
		else if (rd == 4414235 && str[whereis] != '\0')
		{
			whereis++;
			tputs(tgoto(tgetstr("cm", NULL), whereis % data.col, whereis / data.col), 1, tputs_putchar);
		}
		else if (rd == 10 || rd == 27)
			break;
		rd = 0;
	}
	tputs(tgetstr("te", NULL), 1, tputs_putchar);
	ft_putendl(str);
	free(str);
	sigint(0);
	return (0);
}
