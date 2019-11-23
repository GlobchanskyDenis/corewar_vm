/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:12:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/23 18:12:04 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	*get_bytes(void *dst, unsigned char *arena, short start, short len)
{
	short			i;
	short			position;
	unsigned int	*ptr;

	if (!arena || !dst)
		return (NULL);
	ptr = dst;
	*ptr = 0;
	i = -1;
	while (++i < len)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		*ptr = *ptr << 8;
		*ptr += (unsigned int)arena[position];
	}
	return (dst);
}
