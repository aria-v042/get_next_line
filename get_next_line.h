/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:23:06 by frodrig2          #+#    #+#             */
/*   Updated: 2026/06/28 00:21:44 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

/* ==== CORE ===== */

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	read_into_list(t_list **list_ptr, int fd);
char	*extract_line(t_list *list);
int		trim_list(t_list **list_ptr);

/* ==== UTILS ==== */

int		has_newline(t_list *node);
t_list	*lst_lastnode(t_list *list);
t_list	*lst_append(t_list **list_ptr, char *buffer);
size_t	len_to_newline(t_list *list);
void	lst_copyline(t_list *list, char *line);

#endif
