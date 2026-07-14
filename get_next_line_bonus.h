/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 22:34:32 by frodrig2          #+#    #+#             */
/*   Updated: 2026/07/12 22:34:35 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
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
