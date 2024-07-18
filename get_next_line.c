/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneiva-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:33:11 by aneiva-d          #+#    #+#             */
/*   Updated: 2024/07/16 17:11:04 by aneiva-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

char	*ft_joinnfree(char *buffer, char *buff)
{
	char	*join;
	
	join = ft_strjoin(buffer, buff);
	if (join == NULL)
		return (NULL);		
	free(buffer);
	return (join);
}

//It does the same as cuurent_line but with the next ones.
char	*ft_next_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	res = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	while (buffer[i])
	{
		res[j++] = buffer[i++];
	}
	free(buffer);
	return (res);
}

//it returns null if the buffer is empty. it also does calloc* to the var
//that will be returned (line) with the size of the line and will copy
//the current line. *I need to make my own ft_calloc.
char	*ft_current_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_file(int fd, char *buffer)
{
	char	*buff;
	int	bytes_read;

	//if buffer doesnt exist, allocates 1 byte and initializes it to 0
	if (!buffer)
		buffer = ft_calloc(1,1);
	//allocates memory for buffer 1, leavinf a space for the null
	//the buffer is used to read chunks of data from the file
	buff = ft_calloc(BUFFER_SIZE, sizeof(char));
	//initialized to 1 to enter the loop
	bytes_read = 1;
	while (bytes_read > 0)
	{
		//if the end of the file is in the buffer, it will skip this function
		if (ft_strchr(buffer, '\n'))
			break ;
		//reads up to BUFFER_SIZE bytes from the file into the buf1
		bytes_read = read(fd, buff, BUFFER_SIZE);
		//if read returns -1 an error has ocurred
		//frees the allocated buffer and returns NULL
		if (bytes_read == -1)
		{
			free(buff);
			return (NULL);
		}
		//0 terminating the buffer cause we're gonna place the null
		//later ourselves
		buff[bytes_read] = '\0';
		buffer = ft_joinnfree(buffer, buff);
	}
	free(buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*line;

	//error handling
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_current_line(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}

#include <stdio.h>

int	main()
{
	int	fd;
	//int	i;
	char	*string;

	fd = open("test.txt", O_RDONLY);
	//i = 1;
	string = get_next_line(fd);
	while (string)
	{
		printf("line: %s", string);
		free(string);
		string = get_next_line(fd);
		//printf("line: %s", string);
		//i++;
	}
	close(fd);
	free(string);
	return (0);
}
