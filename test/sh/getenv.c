/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/25 12:43:09 by mdelage           #+#    #+#             */
/*   Updated: 2013/12/25 13:16:41 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_getenv(char **environ, char *name);

int		main(int argc, char **argv, char **environ)
{
	int		i;
	char	*env;

	(void)argv;
	i = 1;
	while (i < argc)
	{
		env = ft_getenv(environ, argv[i]);
		if (env != NULL)
			printf("%s : %s\n", argv[i], env);
		i++;
	}
	return (0);
}

char	*ft_getenv(char **environ, char *name)
{
	int		i;
	int		j;

	i = 0;
	while (environ[i] != NULL)
	{
		j = 0;
		while (environ[i][j] != '=' && environ[i][j] == name[j])
			j++;
		if (environ[i][j] == '=')
			return (environ[i] + j + 1);
		i++;
	}
	return (NULL);
}
