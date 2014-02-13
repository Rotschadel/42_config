/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 16:22:55 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/09 16:38:27 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	u_int	cor;
	u_int	nb_col;
	u_int	nb_lin;
	u_int	len_max;
	u_int	nb_select;
	u_int	nb_aff;

	if (ac == 5)
	{
		nb_col = atoi(av[1]);
		nb_lin = atoi(av[2]);
		len_max = atoi(av[3]);
		nb_select = atoi(av[4]);
		cor = (nb_select % nb_lin == 0) ? 0 : 1;
		if ((nb_select / nb_lin + cor) * (len_max + 2) - 2 <= nb_col)
		{
//			curs = aff_from + curs;
//			curs = 0;
			nb_aff = nb_select;
//			aff_from = 0;
		}
		else
		{
			if (nb_col / (len_max + 2) * len_max >= nb_col)
				nb_aff = ((nb_col / (len_max + 2) + 1) * nb_lin);
			else
				nb_aff = (nb_col / (len_max + 2) * nb_lin);

//			aff_from = 0;
//			curs = 0;
		}
		printf("nb_col    : %d\n", nb_col);
		printf("nb_lin    : %d\n", nb_lin);
		printf("len_max   : %d\n", len_max);
		printf("nb_select : %d\n", nb_select);
		printf("nb_aff    : %d\n", nb_aff);
	}
	return (0);
}
