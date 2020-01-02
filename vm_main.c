/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:16:17 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/02 15:34:00 by bsabre-c         ###   ########.fr       */
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
	vm->max_pl = tab[0];
	if (!(vm->player = (t_pl *)ft_memalloc(sizeof(t_pl) * vm->max_pl)))
		error_exit(vm, "create_vm_struct - malloc (player arr) returned null");
	if (!(vm->arena = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
			MEM_SIZE)))
		error_exit(vm, "create_vm_struct - malloc (arena) returned null");
	if (!(vm->arena_owner = (short *)ft_memalloc(sizeof(short) * MEM_SIZE)))
		error_exit(vm, "create_vm_struct - malloc (arena owner) returned null");
	vm->tab = tab;
	return (vm);
}

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
	//print_all(vm);
	corewar(vm);
	free_exit(vm, NULL);
	return (0);
}
