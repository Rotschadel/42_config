/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 17:25:29 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/29 17:37:22 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef enum	e_bool
{
				ft_false,
				ft_true
}				t_bool;

typedef enum	e_type
{
	empty,
	cmd,
	pipe,
	and,
	or
}				t_type;

void	ft_type(int i)
{
	if (i == empty)
		printf("empty");
	else if (i == cmd)
		printf("cmd");
	else if (i == pipe)
		printf("pipe");
	else if (i == and)
		printf("and");
	else if (i == or)
		printf("or");
	printf("\n");
}

int		main(void)
{
	int		i;

	i = 0;
	if (i == ft_true)
		printf("true\n");
	else if (i == ft_false)
		printf("false\n");
	else
		printf("idk\n");
	while (i < 5)
		ft_type(i++);
	return (0);
}
