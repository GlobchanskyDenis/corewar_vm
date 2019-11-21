/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:16:17 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/17 14:17:46 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*create_vm_struct(short *tab)
{
	t_vm	*vm;

	if (!tab)
		error_exit(NULL, "create_vm_struct - empty ptr found");
	if (!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		error_exit(NULL, "create_vm_struct - malloc (vm) returned null");
	if (!(vm->player = (t_pl *)ft_memalloc(sizeof(t_pl) * tab[0])))
		error_exit(vm, "create_vm_struct - malloc (player arr) returned null");
	if (!(vm->arena = (char *)ft_memalloc(sizeof(char) * MEM_SIZE)))
		error_exit(vm, "create_vm_struct - malloc (arena) returned null");
	if (!(vm->command_tab = (t_command *)ft_memalloc(sizeof(t_command) * \
			COMMAND_AMOUNT)))
		error_exit(vm, "create_vm_struct - malloc (command) returned null");
	vm->tab = tab;
	vm->max_pl = tab[0];
	return (vm);
}

/*
**	while (s->cycles_to_die > 0)
**	{
**		if (s->curr_cycle % s->cycles_to_die == 0)
**			ft_check(s);
**		// executes cursors codes
**		s->curr_cycle++;
**	}
*/

int			main(int ac, char **av)
{
	t_vm	*vm;

	if (ac < 2 || (ac < 3 && av[1][0] == '-') || ac > MAX_ARGS_NUMBER + 10)
	{
		fprint("Wrong number of parameters. ");
		fprint("Flags: [-grafix] [-dump nbr_cycles]\n");
		free_exit(NULL, "Use: ./corewar [-flags] [[-n number]champion] ...");
	}
	if (!(vm = create_vm_struct(preliminary_parse_flags(ac, av))))
		error_exit(vm, "main - null ptr returned");
	initialize_all(ac, av, vm);
	print_all(vm);
	free_exit(vm, "its ok!");
	return (0);
}
