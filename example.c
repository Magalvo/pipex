

#include "./includes/pipex.h"

int ft_strlengnl(char *str)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	return (i);
}

char *ft_strjoingnl(char *s1, char *s2)
{
	char *new;
	int i;
	int j;

	new = (char *)malloc(ft_strlengnl(s1) + ft_strlengnl(s2) + 1);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = -1;
	while ((++j >= 0) && s2[j] != '\n' && s2[j])
		new[i + j] = s2[j];
	if (s2[j] == '\n')
		new[i + j++] = '\n';
	new[i + j] = '\0';
	free(s1);
	return (new);
}

void ft_clean_buf(char *buffer)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < BUFFER_SIZE && buffer[i] != '\n')
	{
		buffer[i] = '\0';
		i++;
	}
	if (buffer[i] == '\n')
	{
		buffer[i] = '\0';
		i++;
		while (i < BUFFER_SIZE)
		{
			buffer[j] = buffer[i];
			buffer[i] = '\0';
			i++;
			j++;
		}
	}
}

char *get_next_line(int fd)
{
	static char buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char *line;
	int i;

	i = 0;
	if (read(fd, buffer, 0) < 0 || FOPEN_MAX <= fd || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < FOPEN_MAX)
		{
			while (buffer[fd][i])
			{
				buffer[fd][i++] = '\0';
			}
		}
		return (NULL);
	}
	line = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoingnl(line, buffer[fd]);
		ft_clean_buf(buffer[fd]);
		if (line && line[ft_strlengnl(line) - 1] == '\n')
			return (line);
	}
	return (line);
}

int main(int argc, char **av, char **env)
{
	int *pids;

	int fd1[2]; 
	int fd2[2]; 
	int i;
	i = 0;
	int out;

	pids = calloc(sizeof(int), 3);
	pipe(fd1);
	pipe(fd2);
	while (i != 3)
	{
		pids[i] = fork();

		if (i == 1)
			out = fd1[1];
		if (i == 2)
			out = fd2[1];
		if (pids[i] == 0)
		{
			if (i == 1)
				write(out, "Ola", 3);
			if (i == 2)
				write(out, "Boa", 3);
			close(out);
			exit(EXIT_SUCCESS);
		}
		close(out);
		i++;
	}
	int firstin = fd1[0];
	int firstout = fd2[0];
	pids[i] = fork();
	if (pids[i] == 0)
	{
		printf("%s primeiro firstin\n", get_next_line(firstin));
		close(firstin);
		printf("%s segundo firstout\n", get_next_line(firstout));
		close(firstout);
		exit(EXIT_SUCCESS);
	}
	close(firstin);
	close(firstout);
	waitpid(pids[i], &i, 0);
}
