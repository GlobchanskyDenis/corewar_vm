#include "../vm.h"

void	op_null(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage)
		error_exit(vm, "operation null - empty ptr found");
	fprint("operation null\n");
	carriage->step = 1;
}