/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/09 12:44:48 by mdelage           #+#    #+#             */
/*   Updated: 2013/12/10 10:48:38 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "libft.h"

int		main(void)
{
	time_t	truc;
	char	*str;
	char	*time_ret;
	int		i;

	i = 0;
	truc = time(NULL);
	str = ft_strnew(12);
	ft_putnbr(truc);
	ft_putchar('\n');
	time_ret = ctime(&truc);
	while (i < 12)
	{
		str[i] = time_ret[i + 4];
		i++;
	}
	ft_putendl(str);
	ft_putendl(time_ret);
	return (0);
}
