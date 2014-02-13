/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 16:52:06 by mdelage           #+#    #+#             */
/*   Updated: 2013/12/26 15:56:10 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft.h"

int		main(int argc, char **argv)
{
	int			i;
	int			ok;
	struct stat	stat_ret;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			ok = 0;
			ft_putstr(argv[i]);
			ft_putstr(" : ");
			if (lstat(argv[i], &stat_ret) != -1)
			{
				ok = (stat_ret.st_mode & S_IFDIR ? 1 : 0);
				ok = (stat_ret.st_mode & S_IXUSR ? ok : 0);
				ft_strclr((char *)&stat_ret);
			}
			ft_putnbr(ok, 0);
			ft_putchar('\n');
			i++;
		}
	}
	ft_putendl_c("END", GREEN);
	return (0);
}
