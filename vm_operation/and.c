/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:52:31 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/01 21:31:08 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static short	is_invalid_parameters(unsigned char types, int arg1, int arg2, \
		int reg)
{	
	if ((types & 3) != 0 || (types >> 2 & 3) != REG_CODE || \
			(types >> 4 & 3) == 0 || (types >> 6) == 0)
	{
		// fprint("wrong argument type, skip the command\n");
		//fprint("types = %d\tshould be %d\n", types, (REG_CODE << 6) | (REG_CODE << 4) | (REG_CODE << 2));
		return (1);
	}
	if (reg > REG_NUMBER || reg < 1)
	{
		// fprint("wrong reg number, skip the command\n");
		// fprint("reg1 %d\n", reg);
		return (1);
	}
	if ((types >> 6) == REG_CODE && (arg1 > REG_NUMBER || arg1 < 1))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);
	return (0);
}

static void	log_and(short carriage_id, int arg1, int arg2, int reg_nbr)
{
	if (!DEBUG_LOG)
		return ;
	fprint("P ");
	if (carriage_id < 1000)
		ft_putchar(' ');
	if (carriage_id < 100)
		ft_putchar(' ');
	if (carriage_id < 10)
		ft_putchar(' ');
	fprint("%d | and %d %d r%d\n", carriage_id, arg1, arg2, reg_nbr);
}

/*
**	OPERATION	AND (bitwise AND)
**	OPCODE		ARGUMENT_1			ARGUMENT_2			ARGUMENT_3
**	6			T_REG/T_DIR/T_IND	T_REG/T_DIR/T_IND	T_REG
**
**	Записывает в регистр заданный аргументом 3 результат побитового И
**	аргументов 1 и 2. Меняет carry.
*/

void	operation_and(t_car *carriage, t_vm *vm)
{
	int		types;
	int		arg1;
	int		arg2;
	int		reg_nbr;

	if (!vm || !carriage)
		error_exit(vm, "operation and - empty ptr found");
	// fprint("cycle %d\tposition %d  operation and\t", (int)carriage->position, (int)vm->cw->cycle);
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];

	carriage->step = 2 + get_arg_size(types >> 6, 6) + \
			get_arg_size(types >> 4 & 3, 6) + \
			get_arg_size(types >> 2 & 3, 6);

	reg_nbr = vm->arena[(carriage->position + 2 + get_arg_size(types >> 6, 6) + \
			get_arg_size(types >> 4 & 3, 6)) % MEM_SIZE];

	arg1 = get_bytes(vm->arena, carriage->position + 2, \
			get_arg_size(types >> 6, 6), vm);
	arg2 = get_bytes(vm->arena, carriage->position + 2 + \
			get_arg_size(types >> 6, 6), get_arg_size(types >> 4 & 3, 6), vm);

	if (is_invalid_parameters(types, arg1, arg2, reg_nbr))
		return ;

	carriage->reg[reg_nbr - 1] = get_argument(arg1, types >> 6, carriage, vm) \
			& get_argument(arg2, types >> 4 & 3, carriage, vm);
	
	// fprint("arg1 %d\t", get_argument(arg1, types >> 6, carriage, vm));
	// fprint("arg2 %d\t", get_argument(arg1, types >> 4 & 3, carriage, vm));
	// fprint("return %d\n", carriage->reg[reg - 1]);

	carriage->carry = (carriage->reg[reg_nbr - 1]) ? 0 : 1;

	//fprint("arg %d  arg %d r%d\n", arg1, arg2, reg - 1);
	log_and(carriage->id, arg1, arg2, reg_nbr);
}
