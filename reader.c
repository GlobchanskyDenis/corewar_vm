/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:57:35 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/13 20:57:38 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_size_errors(int ret, char *filename, t_vm *s)
{
	if (!s || !filename)
		error_exit(s, "check size errors - empty ptr found");
	// 2192
	if (ret < 12 + PROG_NAME_LENGTH + CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH)
	{
		fprint("Error: file '%s' has too small size\n", filename);
		error_exit(s, NULL);
	}
	// 2874
	if (ret > 12 + PROG_NAME_LENGTH + CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH +\
			CHAMP_MAX_SIZE)
	{
		fprint("Error: file '%s' has too large ", filename);
		fprint("a code (%d bytes > 682 bytes)\n", ret - 2182);
		error_exit(s, NULL);
	}
}

static void	check_champ_size(t_pl *player, char *buf, int codesize, t_vm *s)
{
	short	i;
	size_t	nbr;

	if (!player || !player->filename || !buf || !s)
		error_exit(s, "check champ size - empty ptr found");
	nbr = 0;
	i = -1;
	while (++i < CHAMP_EXEC_CODE_SIZE)
		nbr = (nbr << 8) + (size_t)buf[i];
	if (nbr != (size_t)codesize)
	{
		fprint("%s codesize = %d, extracted champ size = %d\n", \
				player->filename, codesize, (int)nbr);
		error_exit(s, "wrong data in champion size");
	}
	player->codesize = codesize;
}

static void	check_header_errors(int ret, t_pl *player, char *buf, t_vm *s)
{
	char	*null0;
	char	*null1;

	if (!s || !player || !player->filename || !buf)
		error_exit(s, "check header errors - empty ptr found");
	if (buf[0] != 0 || buf[1] != (char)0xEA || \
			buf[2] != (char)0x83 || buf[3] != (char)0xF3)
	{
		fprint("check header errors - file '%s' isn't binary!", \
				player->filename);
		error_exit(s, NULL);
	}
	null0 = buf + 4 + PROG_NAME_LENGTH;
	null1 = null0 + 4 + CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH;
	if (null0[0] != 0 || null0[1] != 0 || null0[2] != 0 || null0[3] != 0 || \
			null1[0] != 0 || null1[1] != 0 || null1[2] != 0 || null1[3] != 0)
	{
		fprint("Error: check header errors - file '%s' format error\n", \
				player->filename);
		error_exit(s, NULL);
	}
	check_champ_size(player, buf + 8 + PROG_NAME_LENGTH, \
			ret - 12 - PROG_NAME_LENGTH - CHAMP_EXEC_CODE_SIZE - \
			COMMENT_LENGTH, s);
}

void		read_files(t_vm *s)
{
	short	i;
	char	buf[MAX_BUF];
	int		ret;

	if (!s)
		error_exit(s, "reader - empty ptr found");
	i = -1;
	while (++i < s->max_pl)
	{
		ret = read(s->player[i].fd, buf, MAX_BUF);
		check_size_errors(ret, s->player[i].filename, s);
		check_header_errors(ret, &(s->player[i]), buf, s);
		extract_data(&(s->player[i]), buf, s);
	}
}
