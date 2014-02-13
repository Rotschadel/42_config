/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/17 17:11:53 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/25 14:26:18 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef unsigned char	u_char;
typedef unsigned int	u_int;

struct		s_get
{
	u_char	b;
	u_char	g;
	u_char	r;
};

typedef union		s_color
{
	u_int			c;
	struct s_get	get;
}					t_color;

int		main(void)
{
	t_color	test;

//	(test.get).b = 50;
//	(test.get).g = 80;
//	(test.get).r = 0;
	test.c = 23453657;
	printf("b = %d\tg = %d\tr = %d\tc  %u\n", (test.get).b, (test.get).g, (test.get).r, test.c);
	(test.get).b = 70;
	(test.get).g = 60;
	(test.get).r = 0;
	printf("b = %d\tg = %d\tr = %d\tc  %u\n", (test.get).b, (test.get).g, (test.get).r, test.c);
	(test.get).b = 90;
	(test.get).g = 40;
	(test.get).r = 0;
	printf("b = %d\tg = %d\tr = %d\tc  %u\n", (test.get).b, (test.get).g, (test.get).r, test.c);
	(test.get).b = 110;
	(test.get).g = 20;
	(test.get).r = 0;
	printf("b = %d\tg = %d\tr = %d\tc  %u\n", (test.get).b, (test.get).g, (test.get).r, test.c);
	return (0);
}
