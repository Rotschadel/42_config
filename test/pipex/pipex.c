/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 18:13:48 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/01 18:56:03 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int		main(int argc, char **argv, char **env)
{
	int		i;
	int		fd[2];
	char	**ls;
	char	**wc;
	pid_t	father;

	i = 1;
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	pipe(fd);
	ls = (char **)malloc(sizeof(char *) * 4);
	ls[0] = (char *)malloc(sizeof(char) * 3);
	ls[0] = "ls";
	ls[1] = (char *)malloc(sizeof(char) * 3);
	ls[1] = "-R";
	ls[2] = (char *)malloc(sizeof(char) * 10);
	ls[2] = "/bin";
	ls[3] = NULL;
	wc = (char **)malloc(sizeof(char *) * 3);
	wc[0] = (char *)malloc(sizeof(char) * 3);
	wc[0] = "wc";
	wc[1] = (char *)malloc(sizeof(char) * 3);
	wc[1] = "-l";
	wc[2] = NULL;
	if((father = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (father > 0)
	{
//		close(0);		// fermeture de l'entre standard
//		dup(fd[0]);		// ouverture de l'entre du pipe
//		close(fd[1]);	// fermeture de la sortie du pipe
//		waitpid(father, NULL, 0);
		execve("/usr/bin/wc", wc, env);
		/* Parent process closes up output side of pipe */
	}
	else if (father == 0)
	{
//		close(1);		// fermeture de la sortie standard
//		dup(fd[1]);		// ouverture de la sortie du pipe
//		close(fd[0]);	// fermeture de l'entre du pipe
		execve("/bin/ls", ls, env);
		/* Child process closes up input side of pipe */
	}
	return (0);
}
