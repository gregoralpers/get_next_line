/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:48:53 by galpers           #+#    #+#             */
/*   Updated: 2022/03/28 12:01:10 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file_buffer(char *str, int fd)
{
	char	*buffer;
	int		r_value;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
		r_value = -1;
	while (!ft_strchr(str, '\n') && r_value != 0)
	{
		r_value = read(fd, buffer, BUFFER_SIZE);
		if (r_value == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[r_value] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
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

char	*remove_line(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 - i++));
	if (new == NULL)
		return (NULL);
	new[ft_strlen(str) - i] = '\0';
	j = 0;
	while (str[j + i] != '\0')
	{
		new[j] = str[j + i];
		j++;
	}
	free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	str = read_file_buffer(str, fd);
	if (str == NULL)
		return (NULL);
	result = get_line(str);
	str = remove_line(str);
	return (result);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/