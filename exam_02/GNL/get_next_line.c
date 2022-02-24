/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:02:13 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/24 18:12:54 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL.h"
#include <stdio.h>

void 	ft_free(char **str)
{
	if (!str)
		return ;
	else
	{
		free(*str);
		*str = NULL;
	}
	return ;
	
}

int		ft_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char *res;
	int	i = 0;
	
	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *res;
	int i = 0;
	int j = 0;
	
	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

int		new_line(char *str)
{
	int i = -1;

	while (str[++i])
	{
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

char *ft_copy_line(char *str)
{
	int i = 0;
	char *res;

	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i] && str[i - 1] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_copy_rest(char *str)
{
	int i = 0;
	int j = 0;
	char *remain;

	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	remain = (char *)malloc(sizeof(char) * ft_strlen(str) - i + 1);
	if (!remain)
		return (NULL);
	i += 1;
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	return (remain);
}

char	*returned_value(char **save)
{
	char *line;
	char *temp;
	
	if (!*save)
		return (NULL);
	if (new_line(*save))
	{
		line = ft_copy_line(*save);
		temp = ft_copy_rest(*save);
		ft_free(save);
		*save = temp;
		if ((*save)[0] == '\0')
			ft_free(save);
		return (line);
	}
	else
	{
		line = ft_strdup(*save);
		ft_free(save);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	static char	*save = NULL;
	int		ret = 0;
	char	*temp;

	if (fd < 1 || fd > OPEN_MAX)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(save, buf);
			ft_free(&save);
			save = temp;
		}
		if (new_line(buf))
		{
			break ;
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (returned_value(&save));
}
