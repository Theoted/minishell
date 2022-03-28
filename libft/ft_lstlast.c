/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:36:46 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/11 15:59:19 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	size_t	lstsize;
	size_t	i;

	lstsize = ft_lstsize(lst);
	i = -1;
	if (!lst)
		return (0);
	while (++i < lstsize - 1)
		lst = lst->next;
	return (lst);
}
