/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_flags_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:49:20 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/15 18:49:37 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	carefully_open(t_pl *player, char **av, short i, t_vm *vm)
{
	if (!player || !av || !vm)
		free_exit(vm, "carefully open - empty ptr found");
	player->filename = av[i];
	if ((player->fd = open(player->filename, O_RDONLY)) < 3)
	{
		fprint("Warning: cannot open file '%s'\n", player->filename);
		free_exit(vm, NULL);
	}
	if (read(player->fd, NULL, 0) < 0)
	{
		fprint("Warning: cannot take access to '%s'\n", player->filename);
		free_exit(vm, NULL);
	}
}

/*
**	Function handles grafix and dump flags
*/

static void	check_other_flags(char **av, short i, t_vm *vm)
{
	if (!av || !vm)
		error_exit(vm, "check other flags - empty ptr found");
	if (vm->tab[i] == FLAG_GRAF)
	{
		if (vm->flag & FLAG_GRAF)
			free_exit(vm, "Warning: grafix flag double inclusion");
		vm->flag = vm->flag | FLAG_GRAF;
	}
	else if (vm->tab[i] == FLAG_ARG && vm->tab[i - 1] == FLAG_DUMP)
	{
		if (vm->flag & FLAG_DUMP)
			free_exit(vm, "Warning: dump flag double inclusion");
		vm->flag = vm->flag | FLAG_DUMP;
		if (extract_number(av[i], vm) == UINT_MAX)
			free_exit(vm, "Warning: dump number is too big");
		vm->dump = extract_number(av[i], vm);
	}
}

/*
**	vm->tab is array of flags, that fits in size with array of arguments **av
**	and explains, what data is each argument consists of.
**	Function handles every argument that marked as File and argument [-n .nbr.]
**	if it exists. Rest of arguments handles in check_other_flags function
*/

void		parse_flags(int ac, char **av, t_vm *vm)
{
	short	i;
	short	j;

	if (!vm || !vm->tab || !av)
		error_exit(vm, "fill vm struct - empty ptr found");
	j = 0;
	i = 0;
	while (++i < (short)ac)
	{
		if (vm->tab[i] == FLAG_FILE)
		{
			carefully_open(&(vm->player[j]), av, i, vm);
			if (i > 1 && vm->tab[i - 2] == FLAG_NBR && \
					vm->tab[i - 1] == FLAG_ARG)
			{
				if (extract_number(av[i - 1], vm) >= USHRT_MAX)
					free_exit(vm, "Warning: id is too big");
				if ((vm->player[j].id = extract_number(av[i - 1], vm)) < 1)
					free_exit(vm, "Warning: id must be bigger than 0");
				vm->flag = vm->flag | FLAG_NBR;
			}
			j++;
		}
		check_other_flags(av, i, vm);
	}
}
