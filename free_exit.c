/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
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
	}
	free(player);
}

void	error_exit(t_vm *s, char *message)
{
	if (s)
	{
		if (s->player)
			player_free(s->player, s->max_pl);
		free(s);
	}
	if (message)
		fprint("Error: %s\n", message);
	exit(1);
}

void	free_exit(t_vm *s, char *message)
{
	if (s)
	{
		if (s->player)
			player_free(s->player, s->max_pl);
		free(s);
	}
	if (message)
		fprint("%s\n", message);
	exit(0);
}
