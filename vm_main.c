/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:16:17 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/23 17:13:41 by jmaynard         ###   ########.fr       */
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
	if (!(vm->arena = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
			MEM_SIZE)))
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
	unsigned int	value;

	if (ac < 2 || (ac < 3 && av[1][0] == '-') || ac > MAX_ARGS_NUMBER + 10)
	{
		fprint("Wrong number of parameters. ");
		fprint("Flags: [-grafix] [-dump nbr_cycles]\n");
		free_exit(NULL, "Use: ./corewar [-flags] [[-n number]champion] ...");
	}
	if (!(vm = create_vm_struct(preliminary_parse_flags(ac, av))))
		error_exit(vm, "main - null ptr returned");
	initialize_all(ac, av, vm);
	value = 0x70;
	set_bytes(&value, vm->arena, MEM_SIZE - 4, 1);
	print_all(vm);
	if (get_info(vm->arena[MEM_SIZE - 4], 1) == REG_CODE)
		fprint("This byte is register\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 1) == DIR_CODE)
		fprint("This byte is dir address\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 1) == IND_CODE)
		fprint("This byte is ind address\n");
	else
		fprint("Empty\n");
	if (get_info(vm->arena[MEM_SIZE - 4], 2) == REG_CODE)
		fprint("This byte is register\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 2) == DIR_CODE)
		fprint("This byte is dir address\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 2) == IND_CODE)
		fprint("This byte is ind address\n");
	else
		fprint("Empty\n");
	if (get_info(vm->arena[MEM_SIZE - 4], 3) == REG_CODE)
		fprint("This byte is register\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 3) == DIR_CODE)
		fprint("This byte is dir address\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 3) == IND_CODE)
		fprint("This byte is ind address\n");
	else
		fprint("Empty\n");
	if (get_info(vm->arena[MEM_SIZE - 4], 4) == REG_CODE)
		fprint("This byte is register\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 4) == DIR_CODE)
		fprint("This byte is dir address\n");
	else if (get_info(vm->arena[MEM_SIZE - 4], 4) == IND_CODE)
		fprint("This byte is ind address\n");
	else
		fprint("Empty\n");
	free_exit(vm, "its ok!");
	return (0);
}
