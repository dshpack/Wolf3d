/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:46:05 by dshpack           #+#    #+#             */
/*   Updated: 2018/09/27 18:47:14 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*find_fd_doubles(t_list *node, int fd)
{
	t_list	*current;

	if (!node)
		return (NULL);
	current = node;
	while (current)
	{
		if ((int)current->content_size == fd)
			return (current);
		current = current->next;
	}
	return (current);
}

int			ft_read_text(t_list *current, int *ret, int fd)
{
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	ft_memset(buf, 0, BUFF_SIZE + 1);
	if (!current->content)
	{
		*ret = read(fd, buf, BUFF_SIZE);
		if (*ret == 0)
			return (0);
		current->content = ft_strdup(buf);
	}
	else
	{
		if (ft_strchr(current->content, '\n'))
			return (1);
		*ret = read(fd, buf, BUFF_SIZE);
		if (*ret == 0)
			return (1);
		tmp = ft_strjoin(current->content, buf);
		ft_strdel((char**)&current->content);
		current->content = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	return (0);
}

int			ft_preparing_line(t_list *current, int ret, char **line, char *tmp)
{
	int		i;

	i = 0;
	*line = NULL;
	while (((char*)current->content)[i] && ((char*)current->content)[i] != '\n')
		i++;
	if ((!current->content && ret == 0) || ((char*)current->content)[0] == '\0')
		return (0);
	else if (((char*)current->content)[i] == '\n')
	{
		*line = ft_strncpy(ft_strnew((size_t)i), current->content, i);
		tmp = ft_strdup(current->content);
		ft_strdel((char**)&current->content);
		i++;
		current->content =
				ft_strcpy(ft_strnew((size_t)ft_strlen(tmp) - i), tmp + i);
		ft_strdel(&tmp);
	}
	else if (((char*)current->content)[i] != '\n' && ret == 0)
	{
		*line = ft_strncpy(ft_strnew((size_t)ft_strlen(current->content)),
			current->content, i);
		ft_strdel((char**)&current->content);
	}
	return (1);
}

t_list		*ft_file_upgrade(t_list **file, int fd)
{
	t_list			*current;

	if (!(*file))
	{
		*file = ft_lstnew(NULL, 0);
		current = *file;
	}
	else
	{
		current = find_fd_doubles(*file, fd);
		if (!current)
		{
			ft_lstadd(file, ft_lstnew(NULL, 0));
			current = *file;
		}
	}
	if (!current)
		return (NULL);
	current->content_size = fd;
	return (current);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	char			*tmp;
	static t_list	*file;
	t_list			*current;

	tmp = NULL;
	if (fd < 0 || fd > 4864 || !line || (int)read(fd, tmp, 0) < 0
		|| BUFF_SIZE <= 0 || BUFF_SIZE > 8000000)
		return (-1);
	if (!(current = ft_file_upgrade(&file, fd)))
		return (-1);
	while (1)
	{
		if (ft_read_text(current, &ret, fd))
			break ;
		else if (ret == 0)
			return (0);
		else if (!current->content)
			return (-1);
	}
	if (!ft_preparing_line(current, ret, line, tmp))
		return (0);
	if (!(*line))
		return (-1);
	return (1);
}
