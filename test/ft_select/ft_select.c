/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 13:34:46 by mdelage           #+#    #+#             */
/*   Updated: 2014/02/10 20:22:57 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include <unistd.h> /* write */
#include <stdlib.h> /* getenv */
#include <stdio.h> /* printf */

struct		s_rchar
{
	char	c0;
	char	c1;
	char	c2;
	char	c3;
};

typedef union		u_read
{
	unsigned int	rint;
	struct s_rchar	rchar;
}					t_read;

#define TABSIZE 12

int		tputs_putchar(int c)
{
	write(0, &c, 1);
	return (1);
}

int		aff_truc(char tab[TABSIZE][20], size_t tab_size, size_t which_one, int select[TABSIZE])
{
	size_t	i;

	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	tputs(tgetstr("do", NULL), 1, tputs_putchar);
	i = 0;
	while (i < tab_size)
	{
		tputs(tgoto(tgetstr("cm", NULL), i / 4 * 6, i % 4), 1, tputs_putchar);
		if (select[i])
			tputs(tgetstr("mr", NULL), 1, tputs_putchar);
		if (i == which_one)
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
		write(0, tab[i], 20);
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
		if (i == which_one)
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
		i++;
	}
	return (1);
}

int		main(void)
{
	size_t			which_one;
	char			tab[TABSIZE][20] = {"test1", "test2", "test3", "test4", "test5", "test6", "test7", "test8", "test9", "test10", "test11", "test12"};
	int				select[TABSIZE] = {0};
	t_read			rd;
	struct termios	term;

	if (tgetent(NULL, getenv("TERM")) < 1)
		return (-1);
	printf("%d %d %s\n", isatty(0), ttyslot(), ttyname(0));
	printf("col = %d\tlin = %d\n", tgetnum("co"), tgetnum("li"));
	printf("ku : %s\tkd : %s\tkr : %s\tkl : %s\n", tgetstr("ku", NULL), tgetstr("kd", NULL), tgetstr("kr", NULL), tgetstr("kl", NULL));
	which_one = 0;
	rd.rint = 0;
	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ISIG;
	tcsetattr(0, 0, &term);
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	aff_truc(tab, TABSIZE, which_one, select);
//	tputs(tgetstr("vi", NULL), 1, tputs_putchar);
	while (!(rd.rint == 27 || rd.rint == 10))
	{
		rd.rint = 0;
		read(0, &(rd.rint), 4);
		if (rd.rint == 32)
			select[which_one] = !select[which_one];
		if (rd.rint == 4283163)
			which_one = (which_one - 1) % TABSIZE;
		else if (rd.rint == 4348699)
			which_one = (which_one + 1) % TABSIZE;
		else if (rd.rint== 4414235)
			which_one = (which_one + 4) % TABSIZE;
		else if (rd.rint == 4479771)
			which_one = (which_one - 4) % TABSIZE;
//		printf("%u\n", rd.rint);
		aff_truc(tab, TABSIZE, which_one, select);
		printf("\n");
		if (rd.rint == 32)
		{
			printf("espace = ");
			printf("%u", rd.rint);
		}
		if (rd.rint >> 16 == 65)
			printf("fhaut = ");
		else if (rd.rint >> 16 == 66)
			printf("fbas = ");
		else if (rd.rint >> 16 == 67)
			printf("fdroite = ");
		else if (rd.rint >> 16 == 68)
			printf("fgauche = ");
		if ((rd.rint & 2843) == 2843)
			printf("%u", rd.rint >> 16);
		printf("\n%u", rd.rint);
		printf("\n%d %d %d %d %u\n", rd.rchar.c0, rd.rchar.c1, rd.rchar.c2, rd.rchar.c3, (unsigned int)which_one);
	}
	tputs(tgetstr("te", NULL), 1, tputs_putchar);
	printf("%d %d %d %d %u\n", rd.rchar.c0, rd.rchar.c1, rd.rchar.c2, rd.rchar.c3, (unsigned int)which_one);
	if (rd.rint == 10)
	{
		which_one = 0;
		while (which_one < TABSIZE)
		{
			if (select[which_one])
			{
				write(1, tab[which_one], 5);
				write(1, " ", 1);
			}
			which_one++;
		}
	}
//	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	term.c_lflag |= ISIG;
	tcsetattr(0, 0, &term);
	return (0);
}
