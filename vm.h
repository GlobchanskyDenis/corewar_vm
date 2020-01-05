/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:18:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/05 18:38:24 by bsabre-c         ###   ########.fr       */
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
# define FLAG_AFF				(1 << 5)
# define FLAG_LOG				(1 << 6)
# define FLAG_COLOR_DUMP		(1 << 7)
# define FLAG_INFO_DUMP			(1 << 8)
# define FLAG_FULL_DUMP			(1 << 9)
# define GRAFIX					"-graf"
# define DUMP					"-dump"
# define COLOR_DUMP				"-colordump"
# define INFO_DUMP				"-infodump"
# define FULL_DUMP				"-fulldump"
# define NBR					"-n"
# define AFF					"-aff"
# define LOG					"-v"
# define COMMAND_AMOUNT			17
# define UINT_MAX				4294967295

/*
**	OPERATION CODES
*/

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
	short			id;
	short			codesize;
	char			*filename;
	char			*name;
	char			*comment;
	char			*code;
	size_t			last_live_cycle;
}				t_pl;

typedef struct	s_car
{
	size_t			id;
	short			owner_id;
	short			carry;
	short			step;
	short			cycles_to_exe;
	short			command;
	short			position;
	int				reg[REG_NUMBER];
	struct s_car	*next;
	size_t			last_live_cycle;
}				t_car;

typedef struct	s_corewar
{
	short			dump_flag;
	size_t			dump;
	int				cycles_to_die;
	size_t			cycle;
	size_t			next_check;
	short			lives_for_cycle;
	short			last_alive;
}				t_corewar;

typedef struct	s_vm
{
	t_pl			*player;
	short			*tab;
	short			*arena_owner;
	unsigned char	*arena;
	t_car			*car;
	void			(*operation[17])(t_car *, struct s_vm *);
	short			max_pl;
	size_t			max_car_id;
	short			flag;
	short			checks;
	size_t			dump;
	t_corewar		*cw;
}				t_vm;

typedef struct	s_arg
{
	int				arg1;
	int				arg2;
	int				arg3;
	int				reg_num;
}				t_arg;

void			error_exit(t_vm *s, char *message);
void			free_exit(t_vm *s, char *message);
short			*preliminary_parse_flags(int ac, char **av);
void			parse_flags(int ac, char **av, t_vm *s);
void			extract_data(t_pl *player, char *buf, t_vm *s);
void			read_files(t_vm *s);
void			dump(t_vm *s);
size_t			extract_number(const char *str, t_vm *vm);
void			initialize_all(int ac, char **av, t_vm *vm);
void			initialize_game(unsigned char *arena, t_vm *vm);
void			initialize_operations_array(t_vm *vm);
t_car			*add_new_carriage_in_stack(t_vm *vm);
t_car			*carriage_duplicate(t_car *carriage, t_vm *vm);
void			carriage_read_command(t_car *carriage, t_vm *vm);
void			carriage_make_step(t_car *carriage, t_vm *vm);
void			find_n_del_carriage(t_car *carriage, t_vm *vm);
int				get_bytes(unsigned char *arena, short start, short len, \
		t_vm *vm);
void			set_bytes(void *src, unsigned char *arena, short start, \
		short len);
void			set_owner(short owner_id, short *arena_owner, short start, \
		short len);
short			get_arg_size(unsigned char byte, short operation_nbr);
short			get_execution_length(unsigned char command);
void			dump_arena(unsigned char *arena, t_vm *vm);
int				calc_ind_address(short position, int ind, t_vm *vm);
int				calc_long_ind_address(short position, int ind, t_vm *vm);
int				get_argument(int value, short type, t_car *carriage, t_vm *vm);
void			corewar(t_vm *vm);

void			operation_null(t_car *carriage, t_vm *vm);
void			operation_live(t_car *carriage, t_vm *vm);
void			operation_ld(t_car *carriage, t_vm *vm);
void			operation_st(t_car *carriage, t_vm *vm);
void			operation_add(t_car *carriage, t_vm *vm);
void			operation_sub(t_car *carriage, t_vm *vm);
void			operation_and(t_car *carriage, t_vm *vm);
void			operation_or(t_car *carriage, t_vm *vm);
void			operation_xor(t_car *carriage, t_vm *vm);
void			operation_zjmp(t_car *carriage, t_vm *vm);
void			operation_ldi(t_car *carriage, t_vm *vm);
void			operation_sti(t_car *carriage, t_vm *vm);
void			operation_fork(t_car *carriage, t_vm *vm);
void			operation_lld(t_car *carriage, t_vm *vm);
void			operation_lldi(t_car *carriage, t_vm *vm);
void			operation_lfork(t_car *carriage, t_vm *vm);
void			operation_aff(t_car *carriage, t_vm *vm);

short			g_flags;

#endif
