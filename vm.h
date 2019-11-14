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
# define MAX_BUF	PROG_NAME_LENGTH + CHAMP_MAX_SIZE + COMMENT_LENGTH + 1200
# define CHAMP_EXEC_CODE_SIZE	4
# define FLAG_GRAF	(1 << 0)
# define FLAG_1		(1 << 1)
# define FLAG_2		(1 << 2)
# define GRAFIX		'n'
# define FL_1		'o'
# define FL_2		'p'
# include "libft/libft.h"
# include "op.h"

typedef struct	s_pl
{
	int		fd;
	char	*filename;
	char	*name;
	char	*comment;
	short	codesize;
}				t_pl;

typedef struct	s_vm
{
	t_pl	*player;
	short	max_pl;
	short	flags_exists;
	short	flag;
}				t_vm;

void			error_exit(t_vm *s, char *message);		// free_exit.c
void			free_exit(t_vm *s, char *message);		// free_exit.c

void			parse_flags(int ac, char **av, t_vm *s);// parse_flags.c

void			extract_data(t_pl *player, char *buf, t_vm *s);	// extract.c

void			read_files(t_vm *s);	// reader.c



#endif
