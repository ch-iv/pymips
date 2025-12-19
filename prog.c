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


void _macro_draw_background() {	_macro_push_zero(t0);
	_macro_push_zero(t1);
	_macro_push(t2);
	_macro_push(t3);
	_macro_push(t4);
	_instr_li(t0, 31);
	_instr_li(t1, 27);
	_instr_li(t3, 8);
	draw_background_loop_y::
	_instr_mul(s1, t1, t3);
	_instr_li(t0, 31);
	draw_background_loop_x::
	_instr_xor(t4, t1, t0);
	
	_instr_andi(t4, t4, 1);
	
	_instr_beqz(t4, _label_address(draw_background_set_black));
	draw_background_set_white::
	_macro_set_color_w(color_black);
	_instr_j(draw_background_draw);
	draw_background_set_black::
	_macro_set_color_w(color_dark_purple);
	draw_background_draw::
	_instr_mul(s0, t0, t3);
	_macro_draw_square(t3);
	_instr_subi(t0, t0, 1);
	_instr_bgez(t0, _label_address(draw_background_loop_x));
	_instr_subi(t1, t1, 1);
	_instr_bgez(t1, _label_address(draw_background_loop_y));
	_macro_pop(t4);
	_macro_pop(t3);
	_macro_pop(t2);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_draw_square(Arg *arg_size_register) {	_macro_push_zero(s2);
	
	_macro_push_zero(s3);
	
	_macro_push(t0);
	_instr_li(t0, 7);
	draw_square_loop::
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_macro_draw();
	_instr_addi(s2, s2, 4);
	_instr_addi(s2, s2, 992);
	_instr_subi(t0, t0, 1);
	_instr_bgez(t0, _label_address(draw_square_loop));
	_macro_pop(t0);
	_macro_pop(s3);
	_macro_pop(s2);
}
