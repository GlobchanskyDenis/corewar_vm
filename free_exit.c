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

void	error_exit(t_vm *s, char *message)
{
	if (s)
	{
		if (s->player)
		{
			/// free name comment!!!
			free(s->player);
		}
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
		{
			/// free name comment!!!
			free(s->player);
		}
		free(s);
	}
	if (message)
		fprint("%s\n", message);
	exit(0);
}
