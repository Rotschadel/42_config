/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/25 13:30:03 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/02 18:36:39 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int		main(int argc, char **argv, char **environ)
{
	int		i;
	int		ret;
	char	**truc;
//	char	*str;

	i = 0;
/*	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
*/	truc = (char **)malloc(sizeof(char *) * 3);
	truc[0] = (char *)malloc(sizeof(char *) * 4);
	truc[0] = "pwd";
/*	truc[1] = (char *)malloc(sizeof(char *) * 3);
	truc[1][0] = '-';
	truc[1][1] = 'l';
	truc[1][2] = '\0';
*/	truc[1] = NULL;
	truc[2] = NULL;
//	str = ft_getenv(environ, "PWD");
//	str[43] = '\0';
//	environ[0][20] = '\0';
//	environ[0][58] = '\0';
	if (argc == 2)
	{
//		printf("%s\n", ft_getenv(environ, "PWD"));
//		printf("%s\n", ft_getenv(environ, "OLDPWD"));
		ret = chdir(argv[1]);
		printf("ret = %d\n", ret);
//		printf("%s\n", ft_getenv(environ, "PWD"));
//		printf("%s\n", ft_getenv(environ, "OLDPWD"));
		execve("/bin/pwd", truc, environ);
	}
	else if (argc == 1)
		printf("Which path ?\n");
	else
		printf("Too much path\n");
	return (0);
}
