/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneiva-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:15:46 by aneiva-d          #+#    #+#             */
/*   Updated: 2024/07/15 15:51:38 by aneiva-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static void	set_zero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	set_zero(ptr, nmemb * size);
	return (ptr);
}

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	
	str = (char *)s;
	//searches for the character stored in the c variable
	while (*str != c && *str != 0)
		str++;
	//then returns the pointer to that character.
	if (*str == c)
		return (str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	c;
	size_t	size;
	char	*newstr;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = ft_calloc(size, sizeof(char));
	if (!newstr || !s1 || !s2)
		return (NULL);
	i = 0;
	c = 0;
	//puts the info of the first string in the new string
	while (s1[i] != 0)
	{
		newstr[i] = s1[i];
		i++;
	}
	//puts the info of the second string in the new string
	while ((i + c) < size - 1)
	{
		newstr[i + c] = s2[c];
		c++;
	}
	newstr[i + c] = 0;
	return (newstr);
}
