/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:32:46 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/14 19:32:48 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	*allocate_this(char *buf, short name_len, t_vm *s)
{
	char	*dst;
	short	start;
	short	len;

	if (!buf || !s)
		error_exit(s, "allocate this - empty ptr found");
	start = 0;
	while (start < name_len && buf[start] == 0)
		start++;
	len = 0;
	while (start + len < name_len && buf[start])
		len++;
	if (!(dst = ft_strnew(len + 1)))
		error_exit(s, "allocate this - malloc returned null");
	ft_memcpy(dst, &(buf[start]), (size_t)len);
	return (dst);
}

void	extract_data(t_pl *player, char *buf, t_vm *s)
{
	if (!player || !s || !buf)
		error_exit(s, "extract data - empty ptr found");
	if (!(player->name = allocate_this(&(buf[4]), PROG_NAME_LENGTH, s)))
		error_exit(s, "extract data - allocating function returned null");
	if (!(player->comment = allocate_this(&(buf[8 + PROG_NAME_LENGTH + \
			CHAMP_EXEC_CODE_SIZE]), COMMENT_LENGTH, s)))
		error_exit(s, "extract data - allocating function returned null");
	if (!(player->code = allocate_this(&(buf[12 + PROG_NAME_LENGTH + \
			CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH]), player->codesize, s)))
		error_exit(s, "extract data - allocating function returned null");
}
