/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:46:09 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/16 10:27:40 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

char	*ft_join(char *buffer, char *buf);
char	*ft_clean(char *buffer);
char	*ft_line(char *buffer);
char	*read_file(int fd, char *res);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

#endif