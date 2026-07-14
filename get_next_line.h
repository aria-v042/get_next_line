/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:23:06 by frodrig2          #+#    #+#             */
/*   Updated: 2026/07/04 02:08:42 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

/* ==== STRUCTS ===== */

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}	t_list;

/* ==== CORE LOOP ======= */

char	*get_next_line(int fd);
int		read_into_list(t_list **list_ptr, int fd);
char	*extract_line(t_list *list);
int		trim_list(t_list **list_ptr);
int		get_remainder(t_list *lastnode, char **remainderptr);

/* ==== UTILS ============================================ */

int		find_newline(t_list *node);
size_t	len_to_newline(t_list *list);

t_list	*lst_append(t_list **list_ptr, char *buffer);
t_list	*lst_lastnode(t_list *list);
void	lst_freeuntil(t_list **list_ptr, t_list *limit);

#endif
