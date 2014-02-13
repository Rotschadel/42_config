/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/25 17:30:31 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/02 19:32:20 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int		main(int argc, char **argv)
{
	int		i;
	char	*str;

	i = 1;
	while (i < argc)
	{
		str = ft_strjoin("/nfs/zfs-student-3/users/2013/mdelage/test/sh/", argv[i]);
		str = argv[i];
		if (str != NULL)
		{
			if (access(str, F_OK) == 0)
			{
				printf("%s F_OK", argv[i]);
				if (access(str, R_OK) == 0)
					printf(" R_OK");
				if (access(str, W_OK) == 0)
					printf(" W_OK");
				if (access(str, X_OK) == 0)
					printf(" X_OK");
				printf("\n");
			}
			else
				perror(str);
//			free(str);
			str = NULL;
		}
		i++;
	}
	return (0);
}
