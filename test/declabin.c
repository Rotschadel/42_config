/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declabin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 14:29:47 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/25 18:27:59 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>

int		main(void)
{
	u_int	truc;
	int		i;
	char	bidule[5] = "qwer";

	printf("1\n");
	printf("u_int = %u\n", (*(u_int *)bidule));
	printf("char0 = %c\n", (char)(*(u_int *)bidule & 0x000000FF));	
	printf("char1 = %c\n", (char)((*(u_int *)bidule & 0x0000FF00) / 0x100));
	printf("char2 = %c\n", (char)((*(u_int *)bidule & 0x00FF0000) / 0x10000));
	printf("char3 = %c\n", (char)((*(u_int *)bidule & 0xFF000000) / 0x1000000));
	printf("2\n");
	i = -1;
	truc = 1919252337;
	printf("int = %u\n", truc);
	while (++i < 4)
	{
		printf("char %i = %c\n", i, (char)(truc & 255));
		truc = truc >> 8;
	}
	return (0);
}
