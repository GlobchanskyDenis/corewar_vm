/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:18:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/13 12:21:44 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H
# include "libft/libft.h"
# include "op.h"

typedef struct	s_vm
{
	int		*fd;
}				t_vm;

void			error_exit(t_vm *s, char *message);		// free_exit.c
void			free_exit(t_vm *s, char *message);		// free_exit.c

#endif
