/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 16:52:06 by mdelage           #+#    #+#             */
/*   Updated: 2013/12/10 18:11:42 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft.h"

int		main(int argc, char **argv)
{
	int			i;
	struct stat	stat_ret;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			lstat(argv[i], &stat_ret);
			ft_putstr(argv[i]);
			ft_putstr(" : ");
			ft_putstr((S_ISLNK(stat_ret.st_mode)) ? GREEN"Sym lk"NORMAL : "");
			ft_putstr((S_ISDIR(stat_ret.st_mode)) ? GREEN"Dir"NORMAL : "");
			ft_putstr((S_ISFIFO(stat_ret.st_mode)) ? GREEN"Fifo"NORMAL : "");
			ft_putstr((S_ISCHR(stat_ret.st_mode)) ? GREEN"Char spe"NORMAL : "");
			ft_putstr((S_ISBLK(stat_ret.st_mode)) ? GREEN"Block spe"NORMAL : "");
			ft_putstr((S_ISREG(stat_ret.st_mode)) ? GREEN"Regular"NORMAL : "");
			ft_putstr((S_ISSOCK(stat_ret.st_mode)) ? GREEN"Socket"NORMAL : "");
			ft_putstr((S_ISWHT(stat_ret.st_mode)) ? GREEN"Whiteout"NORMAL : "");
			ft_putchar('\n');
//			ft_putendl_c("test 3", RED);
//			free(stat_ret);
			ft_strclr((char *)&stat_ret);
			i++;
		}
	}
	ft_putendl_c("END", GREEN);
	return (0);
}
