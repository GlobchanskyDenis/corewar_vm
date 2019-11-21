/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:16:09 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/13 12:16:11 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	player_free(t_pl *player, short max_pl)
{
	short	i;

	if (!player)
		return ;
	i = -1;
	while (++i < max_pl)
	{
		if (player[i].name)
			free(player[i].name);
		if (player[i].comment)
			free(player[i].comment);
		if (player[i].code)
			free(player[i].code);
		if (player[i].fd)
			close(player[i].fd);
	}
	free(player);
}

static void	carriage_free(t_car *carriage)
{
	t_car	*tmp;

	if (!carriage)
		return ;
	while (carriage)
	{
		tmp = carriage;
		carriage = carriage->next;
		if (tmp->reg)
			free(tmp->reg);
		free(tmp);
	}
}

void		error_exit(t_vm *vm, char *message)
{
	if (vm)
	{
		if (vm->player)
			player_free(vm->player, vm->max_pl);
		if (vm->car)
			carriage_free(vm->car);
		if (vm->tab)
			free(vm->tab);
		if (vm->arena)
			free(vm->arena);
		if (vm->command_tab)
			free(vm->command_tab);
		free(vm);
	}
	if (message)
		fprint("Error: %s\n", message);
	exit(1);
}

void		free_exit(t_vm *vm, char *message)
{
	if (vm)
	{
		if (vm->player)
			player_free(vm->player, vm->max_pl);
		if (vm->car)
			carriage_free(vm->car);
		if (vm->tab)
			free(vm->tab);
		if (vm->arena)
			free(vm->arena);
		if (vm->command_tab)
			free(vm->command_tab);
		free(vm);
	}
	if (message)
		fprint("%s\n", message);
	exit(0);
}
