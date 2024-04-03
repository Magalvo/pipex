/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:18:34 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/02 17:21:53 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


int	main(int argc, char **argv, char **envp)
{
	int	fd1[2];
	int	fd2[2];
	int arr[] = {1, 3 , 6, 9, 2, 4, 5, 7};
	int	arrSize = sizeof(arr) / sizeof(int);
	int	id1;
	int	id2;
	int	sum;
	int	i;
	int	partSize = arrSize / 3; 

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
		return (1);

	id1 = fork();
	if (id1 < 0)
		return (perror("Error:"), 1);
	if (id1 == 0)
	{
		close(fd1[0]);
		i = 0;
		sum = 0;
		while (i < partSize)
			sum += arr[i++];
		if(write(fd1[1], &sum, sizeof(sum)) == -1)
			return (2);
		close(fd1[1]); 
		exit(0);
	}
	
	id2 = fork();
	if (id2 < 0)
		return (perror("Error:"), 1);
	if (id2 == 0)
	{
		close(fd2[0]);
		i = partSize;
		sum = 0;
		while (i < partSize * 2)
			sum += arr[i++];
		if(write(fd2[1], &sum, sizeof(sum)) == -1)
			return (2);
		close(fd2[1]); 
		exit(0);
	}

	close(fd1[1]);
	close(fd1[1]);
	int	childSum1;
	int	childSum2;
	read(fd1[0], &childSum1, sizeof(childSum1));
	read(fd2[0], &childSum2, sizeof(childSum2));
	close(fd1[1]);
	close(fd2[1]);
	sum = 0;
	i = 2 *partSize;
	while (i < arrSize)
		sum += arr[i++];
	int totalSum = sum + childSum1 + childSum2;

	while(wait(NULL) != -1)
		printf("Waiting for the childs!\n");
		
	printf("Total Sum = %d\n", totalSum);
	
	return (0);
}

