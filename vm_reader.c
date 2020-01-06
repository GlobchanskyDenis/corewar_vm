/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:57:35 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/06 17:35:01 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_size_errors(int ret, char *filename, t_vm *vm)
{
	if (!vm || !filename)
		error_exit(vm, "check size errors - empty ptr found");
	if (ret < 12 + PROG_NAME_LENGTH + CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH)
	{
		fprint("Error: file '%s' has too small size\n", filename);
		error_exit(vm, NULL);
	}
	if (ret > 12 + PROG_NAME_LENGTH + CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH + \
			CHAMP_MAX_SIZE)
	{
		fprint("Error: file '%s' has too large ", filename);
		fprint("a code (%d bytes > 682 bytes)\n", ret - 2182);
		error_exit(vm, NULL);
	}
}

static void	check_champ_size(t_pl *player, unsigned char *buf, \
		short codesize, t_vm *vm)
{
	short			i;
	size_t			nbr;

	if (!player || !player->filename || !buf || !vm)
		error_exit(vm, "check champ size - empty ptr found");
	nbr = 0;
	i = -1;
	while (++i < CHAMP_EXEC_CODE_SIZE)
		nbr = ((nbr << 8) + (size_t)buf[i]);
	if (nbr != (size_t)codesize)
	{
		fprint("%s codesize = %d, extracted champ size = %d\n", \
				player->filename, codesize, (int)nbr);
		error_exit(vm, "wrong data in champion size");
	}
	player->codesize = codesize;
}

static void	check_header_errors(int ret, t_pl *player, unsigned char *buf, \
		t_vm *vm)
{
	unsigned char	*null0;
	unsigned char	*null1;

	if (!vm || !player || !player->filename || !buf)
		error_exit(vm, "check header errors - empty ptr found");
	if (buf[0] != (unsigned char)0 || buf[1] != (unsigned char)0xEA || \
			buf[2] != (unsigned char)0x83 || buf[3] != (unsigned char)0xF3)
	{
		fprint("check header errors - file '%s' isn't binary!", \
				player->filename);
		error_exit(vm, NULL);
	}
	null0 = buf + 4 + PROG_NAME_LENGTH;
	null1 = null0 + 4 + CHAMP_EXEC_CODE_SIZE + COMMENT_LENGTH;
	if (null0[0] != 0 || null0[1] != 0 || null0[2] != 0 || null0[3] != 0 || \
			null1[0] != 0 || null1[1] != 0 || null1[2] != 0 || null1[3] != 0)
	{
		fprint("Error: check header errors - file '%s' format error\n", \
				player->filename);
		error_exit(vm, NULL);
	}
	check_champ_size(player, buf + 8 + PROG_NAME_LENGTH, \
			ret - 12 - PROG_NAME_LENGTH - CHAMP_EXEC_CODE_SIZE - \
			COMMENT_LENGTH, vm);
}

void		read_files(t_vm *vm)
{
	short			i;
	unsigned char	buf[MAX_BUF];
	int				ret;

	if (!vm)
		error_exit(vm, "reader - empty ptr found");
	i = -1;
	while (++i < vm->max_pl)
	{
		ret = read(vm->player[i].fd, buf, MAX_BUF);
		check_size_errors(ret, vm->player[i].filename, vm);
		check_header_errors(ret, &(vm->player[i]), buf, vm);
		extract_data(&(vm->player[i]), (char *)buf, vm);
	}
}
