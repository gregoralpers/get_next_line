/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:41:48 by galpers           #+#    #+#             */
/*   Updated: 2022/03/28 12:15:40 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	read_file_buffer(char *str[], int fd)
{
	char	*buffer;
	int		r_value;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return ;
		r_value = -1;
	while (!ft_strchr(str[fd], '\n') && r_value != 0)
	{
		r_value = read(fd, buffer, BUFFER_SIZE);
		if (r_value == -1)
		{
			free(buffer);
			str[fd] = NULL;
			return ;
		}
		buffer[r_value] = '\0';
		str[fd] = ft_strjoin(str[fd], buffer);
	}
	free(buffer);
}

char	*get_line(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (result == NULL)
		return (NULL);
	result[i + 1] = '\0';
	while (i != -1)
	{
		result[i] = str[i];
		i--;
	}
	return (result);
}

void	remove_line(char *str[], int fd)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (str[fd][i] != '\0' && str[fd][i] != '\n')
		i++;
	if (str[fd][i] == '\0')
	{
		free(str[fd]);
		str[fd] = NULL;
		return ;
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str[fd]) + 1 - i++));
	if (new == NULL)
		return ;
	new[ft_strlen(str[fd]) - i] = '\0';
	j = 0;
	while (str[fd][j + i] != '\0')
	{
		new[j] = str[fd][j + i];
		j++;
	}
	free(str[fd]);
	str[fd] = new;
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	read_file_buffer(str, fd);
	if (str[fd] == NULL)
		return (NULL);
	result = get_line(str[fd]);
	remove_line(str, fd);
	return (result);
}
