/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_setters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/28 17:51:12 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	set bytes from unsigned integer variable (maximum 4 bytes) to the arena
*/

void	set_bytes(void *src, unsigned char *arena, short start, short len)
{
	short			i;
	short			position;
	unsigned int	*ptr;

	if (!arena || !src || len < 1 || len > 4)
		return ;
	ptr = src;
	i = -1;
	while (++i < len)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		arena[position] = (unsigned char)*ptr;
		*ptr = *ptr >> 8;
	}
}