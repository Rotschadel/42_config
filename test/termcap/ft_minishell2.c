/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 20:01:04 by mdelage           #+#    #+#             */
/*   Updated: 2014/02/13 17:04:51 by mdelage          ###   ########.fr       */
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
	u_int		term_isnt_dumb;
	u_int		col;
	u_int		lin;
	t_term		term;
	t_term		term_backup;
}				t_data;

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
	char			buffer[2048];
	struct winsize	w;

	tgetent(buffer, ft_getenv(&(data->env), "TERM"));
	if (data->term_isnt_dumb)
	{
		data->col = tgetnum("co");
		data->lin = tgetnum("li");
	}
	else
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		data->col = w.ws_col;
		data->lin = w.ws_row;
	}
	return (0);
}

void	my_tputs(char *str)
{
	tputs(str, 1, tputs_putchar);
	return ;
}

char	*my_tgetstr(char *str)
{
	return (tgetstr(str, NULL));
}
int		ft_init_termcap(void)
{
	char	buffer[2048];

	if (tgetent(buffer, getenv("TERM")) < 1)
		return (-1);
	if (my_tgetstr("le") == NULL || my_tgetstr("LE") == NULL \
		|| my_tgetstr("ti") == NULL || my_tgetstr("te") == NULL \
		|| my_tgetstr("nd") == NULL || my_tgetstr("cm") == NULL \
		|| tgetnum("co") < 0 || tgetnum("li") < 0)
		return (-2);
	return (0);
}

int		ft_init_term(t_data *data)
{
	tcgetattr(0, &(data->term_backup));
	tcgetattr(0, &(data->term));
	(data->term).c_lflag &= ~(ICANON | ECHO);
	(data->term).c_lflag |= ISIG;
	(data->term).c_oflag &= ~(OPOST);
	tcsetattr(0, 0, &(data->term));
	return (0);
}

int		ft_init(int ac, char **av, char **env, t_data *data)
{
	int		ret;

	(void)ac;
	(void)av;
	(void)env;
	if ((ret = ft_init_termcap()) < 0)
		data->term_isnt_dumb = 0;
	ft_get_size(data);
	ft_init_term(data);
	ft_printf("col = %d\t", data->col);
	ft_printf("lin = %d\n\r", data->lin);
	ft_printf("lin = %d\n\r", tgetnum("lm"));
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

void	ft_moveleft(t_data *data, u_int *whereis)
{
	u_int	i;

	(void)data;
	(void)whereis;
	i = -1;
	if (data->term_isnt_dumb)
	{
		if (*whereis % data->col == data->col - 1)
		{
			my_tputs(my_tgetstr("up"));
			while (++i < data->col)
				my_tputs(my_tgetstr("nd"));
		}
		else
			my_tputs(my_tgetstr("le"));
	}
	else
		ft_putstr("\033[1D");
	usleep(5000);
	return ;
}

void	ft_moveright(t_data *data, u_int *whereis)
{
	if (data->term_isnt_dumb)
	{
		if (*whereis % data->col == 0)
			ft_putstr("\n\r");
		else
			my_tputs(my_tgetstr("nd"));
	}
	else
		ft_putstr("\033[1C");
	usleep(5000);
	return ;
}

void	ft_backtopos(t_data *data, char *str, u_int *whereis)
{
	u_int	curs;

	curs = ft_strlen(str);
	while (curs-- > 0)
		ft_moveleft(data, &curs);
	while (++curs < *whereis + 1)
		ft_moveright(data, &curs);
	return ;
}

void	ft_insert(t_data *data, char *str, u_int *whereis, u_int rd)
{
	u_int	len;
	u_int	curs;

	(void)data;
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
	my_tputs(my_tgetstr("sc"));	
	write(1, str + curs, len - curs + 1);
	my_tputs(my_tgetstr("rc"));	
	ft_moveright(data, whereis);
	return ;
}

void	ft_delete(t_data *data, char *str, u_int *whereis)
{
	u_int	len;
	u_int	curs;

	(void)data;
	curs = *whereis - 1;
	while (str[++curs])
		str[curs] = str[curs + 1];
	len = 0;
	while (str[len + *whereis])
		len++;
	my_tputs(my_tgetstr("sc"));	
	write(1, str + *whereis, len);
	write(1, " ", 1);
	my_tputs(my_tgetstr("rc"));
	return ;
}

void	ft_backspace(t_data *data, char *str, u_int *whereis)
{
	(*whereis)--;
	my_tputs(my_tgetstr("le"));
	ft_delete(data, str, whereis);
	return ;
}

int		main(int ac, char **av, char **env)
{
	u_int	whereis;
	u_int	rd;
	t_data	data;
	char	*str;

	data.term_isnt_dumb = 1;
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
				write(1, &rd, 1);
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
			ft_moveleft(&data, &whereis);
		}
		else if (rd == 4414235 && str[whereis] != '\0')
		{
			whereis++;
			ft_moveright(&data, &whereis);
		}
		else if (rd == 10 || rd == 27)
		{
			break;
		}
		else if (rd == 1)
		{
			while (whereis > 0)
			{
				whereis--;
				ft_moveleft(&data, &whereis);
			}
		}
		else if (rd == 5)
		{
			while (str[whereis] != '\0')
			{
				whereis++;
				ft_moveright(&data, &whereis);
			}
		}
		rd = 0;
	}
	while (str[whereis] != '\0')
	{
		whereis++;
		ft_moveright(&data, &whereis);
		usleep(5000);
	}
	ft_putstr("\n\r");
	ft_putstr(str);
	ft_putstr("\n\r");
	free(str);
	sigint(0);
	return (0);
}
