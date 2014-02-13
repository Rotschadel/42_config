/* *************************************************************************** */
/*                                                                             */
/*                                                         :::      ::::::::   */
/*   enum.c                                              :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+     */
/*   by: mdelage <mdelage@student.42.fr>             +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 12:56:46 by mdelage            #+#    #+#             */
/*   Updated: 2014/01/06 19:02:31 by mdelage           ###   ########.fr       */
/*                                                                             */
/* *************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

/*
** Enter      = 10
/* Escape     = 27
** Space      = 32
** Backspace  = 127
** Uparrow    = 4283163
** Downarrow  = 4348699
** Rightarrow = 4414235
** Leftarrow  = 4479771
** Delete     = 2117294875
*/
/*
typedef enum e_test	t_test;

enum	e_test
{
	10, 27, 32, 127, 4283163, 4348699, 4414235, 4479771, 2117294875
};
*/

typedef enum	e_trinaire{
	Enter = 0,
    '1' = 10,
    '2' = 2
}				t_trinaire;
enum	qwerty
{
	CACA, BOUDIN, POUET
};

int		main()
{
//	u_int	rd;
	t_trinaire truc;
//	t_test	truc;

	printf("%i", Enter);

/*	rd = 1;
	truc = rd;
	printf("%d = %d\n", rd, truc);
	rd = 2;
	truc = rd;
	printf("%d = %d\n", rd, truc);
	rd = 10;
	truc = rd;
	printf("%d = %d\n", rd, truc);
*//*	while (rd != 27)
	{
		rd = 0;
		read(0, &rd, 4);
		truc = rd;
		printf("%c\n", rd);
	}
*/	return (0);
}
