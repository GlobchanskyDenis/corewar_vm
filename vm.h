/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:18:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/29 20:17:33 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H
# include "libft/libft.h"
# include "op.h"
# define MAX_BUF	PROG_NAME_LENGTH + CHAMP_MAX_SIZE + COMMENT_LENGTH + 1200
# define CHAMP_EXEC_CODE_SIZE	4
# define FLAG_GRAF				(1 << 0)
# define FLAG_DUMP				(1 << 1)
# define FLAG_NBR				(1 << 2)
# define FLAG_ARG				(1 << 3)
# define FLAG_FILE				(1 << 4)
# define GRAFIX					"-graf"
# define DUMP					"-dump"
# define NBR					"-n"
# define COMMAND_AMOUNT			17
# define USHRT_MAX				65535
# define UINT_MAX				4294967295
# define OP_LIVE				1
# define OP_LD					2
# define OP_ST					3
# define OP_ADD					4
# define OP_SUB					5
# define OP_AND					6
# define OP_OR					7
# define OP_XOR					8
# define OP_ZJMP				9
# define OP_LDI					10
# define OP_STI					11
# define OP_FORK				12
# define OP_LLD					13
# define OP_LLDI				14
# define OP_LFORK				15
# define OP_AFF					16

typedef struct	s_pl
{
	int				fd;
	unsigned short	id;
	short			codesize;
	char			*filename;
	char			*name;
	char			*comment;
	char			*code;
	size_t			last_live_cycle;
}				t_pl;

typedef struct	s_car
{
	short			carry;
	short			step;
	short			cycles_to_exe;
	short			command;
	short			position;
	unsigned int	*reg;
	struct s_car	*next;
	size_t			last_live_cycle;
}				t_car;

typedef struct	s_corewar
{
	short			dump_flag;
	size_t			dump;
	size_t			cycles_to_die;
	size_t			cycle;
	size_t			next_check;
	short			lives_for_cycle;
	short			last_alive;
}				t_corewar;


typedef struct	s_vm
{
	t_pl			*player;
	short			*tab;
	unsigned char	*arena;
	t_car			*car;
	void			(*operation[17])(t_car *, struct s_vm *);
	short			max_pl;
	short			flag;
	short			checks;
	size_t			dump;
	t_corewar		*cw;
}				t_vm;

void			error_exit(t_vm *s, char *message);
void			free_exit(t_vm *s, char *message);
short			*preliminary_parse_flags(int ac, char **av);
void			parse_flags(int ac, char **av, t_vm *s);
void			extract_data(t_pl *player, char *buf, t_vm *s);
void			read_files(t_vm *s);
void			print_all(t_vm *s);
size_t			extract_number(const char *str, t_vm *vm);
void			initialize_all(int ac, char **av, t_vm *vm);
void			initialize_game(unsigned char *arena, t_vm *vm);
void			initialize_operations_array(t_vm *vm);
t_car			*add_new_carriage_in_stack(t_vm *vm);
t_car			*carriage_duplicate(t_car *carriage, t_vm *vm);
void			carriage_read_command(t_car *carriage, t_vm *vm);
void			carriage_make_step(t_car *carriage, t_vm *vm);
void			find_n_del_carriage(t_car *carriage, t_vm *vm);
unsigned int	get_bytes(unsigned char *arena, short start, short len, \
		t_vm *vm);
void			set_bytes(void *src, unsigned char *arena, short start, \
		short len);
short			get_arg_size(unsigned char byte, short operation_nbr);
short			get_info(unsigned char byte, short arg_nbr);
short			get_execution_length(unsigned char command);
//int				get_args_types(unsigned char *byte);///
//int				get_arg(t_car *c, t_vm *vm, short type, int dir_size);///

void			op_add(t_car *carriage, t_vm *vm);
void			op_aff(t_car *carriage, t_vm *vm);
void			op_and(t_car *carriage, t_vm *vm);
void			op_fork(t_car *carriage, t_vm *vm);
void			operation_ld(t_car *carriage, t_vm *vm);
void			op_ldi(t_car *carriage, t_vm *vm);
void			op_lfork(t_car *carriage, t_vm *vm);
void			operation_live(t_car *carriage, t_vm *vm);
void			op_lld(t_car *carriage, t_vm *vm);
void			op_lldi(t_car *carriage, t_vm *vm);
void			op_or(t_car *carriage, t_vm *vm);
void			op_st(t_car *carriage, t_vm *vm);
void			operation_sti(t_car *carriage, t_vm *vm);
void			op_sub(t_car *carriage, t_vm *vm);
void			op_xor(t_car *carriage, t_vm *vm);
void			op_zjmp(t_car *carriage, t_vm *vm);
void			op_null(t_car *carriage, t_vm *vm);
void			check(t_vm *vm);
void			corewar(t_vm *vm);

#endif
