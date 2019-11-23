/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initialize_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:25:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/23 16:25:03 by jmaynard         ###   ########.fr       */
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
	}
}

static void	assign_id_to_players(t_pl *player, short max_pl, t_vm *vm)
{
	short	i;
	short	j;
	short	id;

	if (!vm)
		error_exit(vm, "assign id to files - empty ptr found");
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

static void	check_invalid_flag_cases(int ac, t_vm *vm)
{
	short	i;

	if (vm->tab[ac - 1] != FLAG_FILE)
		free_exit(vm, "Warning: the last argument must be filename");
	i = 0;
	while (++i < (short)ac)
	{
		if (vm->tab[i] == FLAG_DUMP && i + 1 < ac && vm->tab[i + 1] != FLAG_ARG)
			free_exit(vm, "Warning: dump flag without argument");
		if (vm->tab[i] == FLAG_NBR && i + 1 < ac && vm->tab[i + 1] != FLAG_ARG)
			free_exit(vm, "Warning: number flag without argument");
		if (vm->tab[i] == FLAG_ARG && vm->tab[i - 1] != FLAG_DUMP && \
				vm->tab[i - 1] != FLAG_NBR)
			free_exit(vm, "Warning: argument without flag");
		if (vm->tab[i] == FLAG_ARG && vm->tab[i - 1] == FLAG_NBR && \
				(i + 1 >= ac || vm->tab[i + 1] != FLAG_FILE))
			free_exit(vm, "Warning: flag nbr and argument without file");
		if (vm->tab[i] == FLAG_DUMP && (i > 2 || \
				(i > 1 && vm->tab[1] != FLAG_GRAF)))
			free_exit(vm, "Warning: dump must be in the begining");
		if (vm->tab[i] == FLAG_GRAF && (i > 3 || \
				(i > 1 && vm->tab[1] != FLAG_DUMP)))
			free_exit(vm, "Warning: graf must be in the begining");
	}
	assign_id_to_players(vm->player, vm->max_pl, vm);
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
	sort_players_by_id(vm->player, vm->max_pl, vm);
	read_files(vm);
	init_command(vm);
	initialize_game(vm->arena, vm);
}
