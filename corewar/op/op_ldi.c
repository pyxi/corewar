#include	"operation.h"

void	debug_ldi(t_process *proc, int *val, int reg)
{
  my_putstr(proc->associated_champ->header.prog_name, 1, -1);
  my_putstr("\t", 1 , 1);
  my_putstr(" ldi (i@*(pc+", 1 , -1);
  my_put_nbr(val[0] - val[1], 1);
  my_putstr(")+", 1 , 2);
  my_put_nbr(val[1], 1);
  my_putstr("=", 1, 1);
  my_put_nbr(proc->reg[reg], 1);
  my_putstr(" -> reg", 1, -1);
  my_put_nbr(reg, 1);
  my_putstr(") carry = ", 1 , -1);
  my_put_nbr(proc->carry, 1);
  my_putstr("\n", 1, 1);
}

int	get_value_ldi_at_adrr(t_process *proc, t_vm *vm, int adrr)
{
  int	value;
  char	*tmp;

  value = 0;
  tmp = (char*)(&(value));
  tmp[0] = vm->mem[MOD_MEM(proc->pc + (adrr % IDX_MOD) + 0)];
  tmp[1] = vm->mem[MOD_MEM(proc->pc + (adrr % IDX_MOD) + 1)];
  tmp[2] = vm->mem[MOD_MEM(proc->pc + (adrr % IDX_MOD) + 2)];
  tmp[3] = vm->mem[MOD_MEM(proc->pc + (adrr % IDX_MOD) + 3)];
  switch_endian(tmp, sizeof(int));
  return (value);
}

short	get_value_ldi_b_adrr(t_process *proc, t_vm *vm)
{
  short	adrr;
  short	valat;
  char	*tmp;

  tmp = (char*)(&(adrr));
  tmp[0] = proc->params_next_instr.params[1];
  tmp[1] = proc->params_next_instr.params[2];
  switch_endian(tmp, sizeof(short));
  tmp = (char*)(&(valat));
  tmp[0] = vm->mem[MOD_MEM(proc->pc + (adrr % IDX_MOD) + 0)];
  tmp[1] = vm->mem[MOD_MEM(proc->pc + (adrr % IDX_MOD) + 1)];
  return (valat);
}

int	op_ldi(t_process *proc, t_vm *vm)
{
  int	reg;
  int	val[2];
  char	*tmp;

  val[0] = 0;
  val[1] = 0;
  reg = proc->params_next_instr.params[5] - 1;
  if (reg >= 0 && reg < REG_NUMBER)
    {
      val[0] = get_value_ldi_b_adrr(proc, vm);
      tmp = (char*)(&(val[1]));
      tmp[0] = proc->params_next_instr.params[NBPBYTE(PARAMBYTE, 1) + 1];
      tmp[0] = proc->params_next_instr.params[NBPBYTE(PARAMBYTE, 1) + 2];
      val[0] += val[1] % IDX_MOD;
      proc->reg[reg] = get_value_ldi_at_adrr(proc, vm, val[0]);
      proc->carry = is_byte_zero((char*)(&(proc->reg[reg])), sizeof(int));
      DEBUGCALL(ISDEBUGMODE, debug_ldi(proc, val, reg));
    }
  return (7);
}
