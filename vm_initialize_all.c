/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initialize_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:25:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/05 21:09:42 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	sort_players_by_id(t_pl *player, short max_pl, t_vm *vm)
{
	short	i;
	t_pl	tmp_player;

	if (!vm || !player)
		error_exit(vm, "sort players by id - empty ptr found");
	i = -1;
	while (++i < max_pl - 1)
	{
		if (player[i].id > player[i + 1].id)
		{
			tmp_player = player[i + 1];
			player[i + 1] = player[i];
			player[i] = tmp_player;
			i = -1;
		}
		else if (player[i].id == player[i + 1].id)
			free_exit(vm, "Warning: identical id numbers was found");
	}
}

static void	assign_id_to_players(t_pl *player, short max_pl, t_vm *vm)
{
	short	i;
	short	j;
	short	id;

	if (!vm)
		error_exit(vm, "assign id to players - empty ptr found");
	id = 1;
	i = -1;
	while (++i < max_pl)
	{
		j = -1;
		while (++j < max_pl)
		{
			if (id == player[j].id)
			{
				id++;
				j = 0;
			}
		}
		if (player[i].id == 0)
			player[i].id = id;
	}
}

static void	check_another_flag_cases(short i, t_vm *vm)
{
	short	j;

	if (vm->tab[i] == FLAG_LOG || vm->tab[i] == FLAG_AFF || \
			vm->tab[i] == FLAG_DUMP || vm->tab[i] == FLAG_GRAF)
	{
		j = i;
		while (--j != 0)
		{
			if (vm->tab[j] == FLAG_FILE)
			{
				ft_putstr("Warning: aff, log, dump and graf flags must be ");
				free_exit(vm, "before filenames");
			}
		}
	}
}

static void	check_invalid_flag_cases(int ac, t_vm *vm)
{
	short	i;

	i = 0;
	while (++i < (short)ac)
	{
		if (vm->tab[i] == FLAG_DUMP && i + 1 < ac && vm->tab[i + 1] != FLAG_ARG)
			free_exit(vm, "Warning: dump flag without argument");
		if (vm->tab[i] == FLAG_NBR && i + 1 < ac && vm->tab[i + 1] != FLAG_ARG)
			free_exit(vm, "Warning: number flag without argument");
		if (vm->tab[i] == FLAG_ARG && (i == 1 || \
				(vm->tab[i - 1] != FLAG_DUMP && vm->tab[i - 1] != FLAG_NBR)))
			free_exit(vm, "Warning: argument without flag");
		if (vm->tab[i] == FLAG_ARG && vm->tab[i - 1] == FLAG_NBR && \
				(i + 1 >= ac || vm->tab[i + 1] != FLAG_FILE))
			free_exit(vm, "Warning: flag nbr and argument without file");
		check_another_flag_cases(i, vm);
	}
	if (vm->tab[ac - 1] != FLAG_FILE)
		free_exit(vm, "Warning: the last argument must be filename");
}

/*
**	Настя, вызывай из этой функции всю инициализацию, которую напишешь
*/

void		initialize_all(int ac, char **av, t_vm *vm)
{
	if (!vm || !av)
		error_exit(vm, "initialize all - empty ptr found");
	parse_flags(ac, av, vm);
	check_invalid_flag_cases(ac, vm);
	assign_id_to_players(vm->player, vm->max_pl, vm);
	sort_players_by_id(vm->player, vm->max_pl, vm);
	read_files(vm);
	initialize_operations_array(vm);
	initialize_game(vm->arena, vm);
}
