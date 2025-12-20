#include "generated_assets/vvirus_red4.asm";
#include "generated_assets/vvirus_blue4.asm";
#include "generated_assets/vvirus_yellow4.asm";
#include "generated_assets/bottle.asm";

void _macro_push(Arg *arg_reg) {	
	_instr_addi(sp, sp, 4);
	_instr_sw(arg_reg, _offset(0, sp));
}

void _macro_push_zero(Arg *arg_reg) {	
	_instr_addi(sp, sp, 4);
	_instr_sw(arg_reg, _offset(0, sp));
	_instr_li(arg_reg, 0);
}

void _macro_pop(Arg *arg_reg) {	
	_instr_lw(arg_reg, _offset(0, sp));
	_instr_addi(sp, sp, 4);
}

void _macro_set_color_w(Arg *arg_a1) {	
	
	_instr_lw(s7, _label_address(arg_a1));
}

void _macro_inner(Arg *arg_reg) {	
	_instr_lw(arg_reg, _offset(0, sp));
	_instr_addi(sp, sp, 4);
}

void main() {
	_instr_and(t5, t5, t7);
	syscall();
	_instr_and(t5, t5, t7);
	_instr_and(t5, t5, t7);
	syscall();
	_instr_and(t5, t5, t7);
	_instr_and(t5, t5, t7);
	syscall();
	_instr_and(t5, t5, t7);
}