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
	free(buffer);
	return (join);
}

//It does the same as current_line but with the next ones.
char	*ft_next_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	//find the size of the line
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	//res alocate the remaining data after the new line cheracter
	//plus 1 for the null terminator
	res = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	i++;
	//and then its copied
	while (buffer[i])
		res[j++] = buffer[i++];
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
	//checks the size of the string
	while (buffer[i] && buffer[i] != '\n')
		i++;
	//Does calloc + 2 for  the new line '\n' character and the NULL
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	//copies the current buffer chunk to line var
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	//adding the '\n'
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	//and the null terminator
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	//if theres no information in the buffer we just put 0 on it (empty string)
	if (!res)
		res = ft_calloc(1, 1);
	//we initialize the buffer with calloc
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	//The loop keeps reading the file untill buffer_size or a new line is reached
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		//if an error occurs, rad returns -1 and we return NULL
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		//instead of having a null terminator we need to put 0 so
		//the line doesnt end there.
		buffer[byte_read] = 0;
		//adding buffer to res
		res = ft_joinnfree(res, buffer);
		//since we only read till a new line if we find one, the loop
		//breaks, ensuring only one line is read.
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	//fd < 0 ensures the file descriptor is valid, 
	//BUff_size <= ensures the buffer size is positive and 
	//the last one checks if the file descriptor is invalid
	//by readiing it with 0 bytes, which does not change the 
	//file pointer or data but will return -1 if the descriptor
	// is invalid.
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	//reads the data from the file and updates the buffer.
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	//extracts line from the buffer
	line = ft_current_line(buffer);
	//updates buffer so it contains only the data from the
	//extrated line.
	buffer = ft_next_line(buffer);
	return (line);
}

/*#include <stdio.h>

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
}*/
