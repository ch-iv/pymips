#include "generated_assets/board.asm";
#include "generated_assets/pill_red_left.asm";
#include "generated_assets/pill_red_right.asm";
#include "generated_assets/pill_red_top.asm";
#include "generated_assets/pill_red_bottom.asm";
#include "generated_assets/pill_red_single.asm";
#include "generated_assets/pill_red_empty.asm";
#include "generated_assets/pill_blue_left.asm";
#include "generated_assets/pill_blue_right.asm";
#include "generated_assets/pill_blue_top.asm";
#include "generated_assets/pill_blue_bottom.asm";
#include "generated_assets/pill_blue_single.asm";
#include "generated_assets/pill_blue_empty.asm";
#include "generated_assets/pill_yellow_left.asm";
#include "generated_assets/pill_yellow_right.asm";
#include "generated_assets/pill_yellow_top.asm";
#include "generated_assets/pill_yellow_bottom.asm";
#include "generated_assets/pill_yellow_single.asm";
#include "generated_assets/pill_yellow_empty.asm";
#include "generated_assets/virus_red1.asm";
#include "generated_assets/virus_blue1.asm";
#include "generated_assets/virus_yellow1.asm";
#include "generated_assets/virus_red2.asm";
#include "generated_assets/virus_blue2.asm";
#include "generated_assets/virus_yellow2.asm";
#include "generated_assets/game_over.asm";
#include "generated_assets/pause_screen.asm";
#include "generated_assets/mario1.asm";
#include "generated_assets/mario2.asm";
#include "generated_assets/mario3.asm";
#include "generated_assets/mario4.asm";
#include "generated_assets/mario_bg.asm";
#include "generated_assets/vvirus_red1.asm";
#include "generated_assets/vvirus_blue1.asm";
#include "generated_assets/vvirus_yellow1.asm";
#include "generated_assets/vvirus_red2.asm";
#include "generated_assets/vvirus_blue2.asm";
#include "generated_assets/vvirus_yellow2.asm";
#include "generated_assets/vvirus_red3.asm";
#include "generated_assets/vvirus_blue3.asm";
#include "generated_assets/vvirus_yellow3.asm";
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


void _macro_set_x_i(Arg *arg_a1) {	
	
	_instr_li(s0, arg_a1);
	_instr_sll(s0, s0, 2);
}


void _macro_set_y_i(Arg *arg_a1) {	
	
	_instr_li(s1, arg_a1);
	_instr_sll(s1, s1, 10);
	_instr_add(s0, s1, s0);
}


void _macro_draw() {	
	
	_instr_lw(t8, _label_address(disp_addr));
	_instr_add(t8, s2, t8);
	_instr_add(t8, t8, s0);
	_instr_sw(s7, _offset(0, t8));
}


void _macro_draw_background() {	_macro_push_zero(t0);
	_macro_push_zero(t1);
	_macro_push(t2);
	_macro_push(t3);
	_macro_push(t4);
	_instr_li(t0, 31);
	_instr_li(t1, 27);
	_instr_li(t3, 8);
	draw_background_loop_y:
	_instr_mul(s1, t1, t3);
	_instr_li(t0, 31);
	draw_background_loop_x:
	_instr_xor(t4, t1, t0);
	
	_instr_andi(t4, t4, 1);
	
	_instr_beqz(t4, _label_address(draw_background_set_black));
	draw_background_set_white:
	_macro_set_color_w(color_black);
	_instr_j(draw_background_draw);
	draw_background_set_black:
	_macro_set_color_w(color_dark_purple);
	draw_background_draw:
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
	draw_square_loop:
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


void _macro_draw_asset(Arg *arg_asset_size, Arg *arg_asset_data) {	_macro_push(t0);
	_macro_push(t1);
	_instr_lw(t0, _label_address(arg_asset_size));
	_instr_la(t1, arg_asset_data);
	draw_asset_loop:
	_instr_lw(s2, _offset(0, t1));
	
	_instr_lw(s3, _offset(4, t1));
	
	_instr_lw(s7, _offset(8, t1));
	
	_macro_draw();
	_instr_addi(t1, t1, 12);
	_instr_subi(t0, t0, 1);
	_instr_bgtz(t0, draw_asset_loop);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_draw_board(Arg *arg_board) {	_macro_push(t0);
	_macro_push(t1);
	_macro_push(t2);
	_instr_lw(t0, _label_address(board_width));
	_instr_lw(t1, _label_address(board_height));
	_instr_la(t2, board);
	draw_board_loop_y:
	_instr_lw(t0, _label_address(board_width));
	draw_board_loop_x:
	_instr_move(a0, t2);
	_macro_draw_board_cell();
	_instr_addi(t2, t2, 32);
	
	_instr_subi(t0, t0, 1);
	_instr_bgtz(t0, draw_board_loop_x);
	_instr_subi(t1, t1, 1);
	_instr_bgtz(t1, draw_board_loop_y);
	_macro_pop(t2);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_draw_board_cell() {	_instr_move(t2, a0);
	_instr_lw(s0, _offset(0, t2));
	
	_instr_sll(s0, s0, 2);
	_instr_lw(s1, _offset(4, t2));
	
	_instr_sll(s1, s1, 10);
	_instr_add(s0, s0, s1);
	_instr_lw(t5, _offset(8, t2));
	
	_instr_lw(t6, _offset(12, t2));
	
	_instr_andi(t7, t6, 64);
	
	_instr_bgtz(t7, it_is_a_pill);
	_instr_andi(t7, t6, 128);
	_instr_bgtz(t7, it_is_a_virus);
	_instr_j(draw_empty_cell);
	it_is_a_virus:
	_instr_andi(t7, t5, 1);
	
	_instr_bgtz(t7, draw_red_virus);
	_instr_andi(t7, t5, 2);
	
	_instr_bgtz(t7, draw_blue_virus);
	_instr_andi(t7, t5, 4);
	
	_instr_bgtz(t7, draw_yellow_virus);
	_instr_j(not_a_pill);
	
	draw_red_virus:
	_instr_andi(t7, s6, 512);
	_instr_beq(t7, 0, draw_red_virus_1);
	_instr_j(draw_red_virus_2);
	draw_red_virus_1:
	_macro_draw_asset(asset_virus_red1_size, asset_virus_red1_data);
	_instr_j(not_a_pill);
	draw_red_virus_2:
	_macro_draw_asset(asset_virus_red2_size, asset_virus_red2_data);
	_instr_j(not_a_pill);
	_instr_j(not_a_pill);
	draw_blue_virus:
	_instr_andi(t7, s6, 512);
	_instr_beq(t7, 0, draw_blue_virus_1);
	_instr_j(draw_blue_virus_2);
	draw_blue_virus_1:
	_macro_draw_asset(asset_virus_blue1_size, asset_virus_blue1_data);
	_instr_j(not_a_pill);
	draw_blue_virus_2:
	_macro_draw_asset(asset_virus_blue2_size, asset_virus_blue2_data);
	_instr_j(not_a_pill);
	_instr_j(not_a_pill);
	draw_yellow_virus:
	_instr_andi(t7, s6, 512);
	_instr_beq(t7, 0, draw_yellow_virus_1);
	_instr_j(draw_yellow_virus_2);
	draw_yellow_virus_1:
	_macro_draw_asset(asset_virus_yellow1_size, asset_virus_yellow1_data);
	_instr_j(not_a_pill);
	draw_yellow_virus_2:
	_macro_draw_asset(asset_virus_yellow2_size, asset_virus_yellow2_data);
	_instr_j(not_a_pill);
	_instr_j(not_a_pill);
	it_is_a_pill:
	_instr_andi(t7, t5, 1);
	
	_instr_bgtz(t7, draw_red_pill);
	_instr_andi(t7, t5, 2);
	
	_instr_bgtz(t7, draw_blue_pill);
	_instr_andi(t7, t5, 4);
	
	_instr_bgtz(t7, draw_yellow_pill);
	_instr_j(not_a_pill);
	
	draw_red_pill:
	_instr_andi(t8, t6, 32);
	
	_instr_bgtz(t8, draw_red_left_pill);
	_instr_andi(t8, t6, 16);
	
	_instr_bgtz(t8, draw_red_right_pill);
	_instr_andi(t8, t6, 8);
	
	_instr_bgtz(t8, draw_red_top_pill);
	_instr_andi(t8, t6, 4);
	
	_instr_bgtz(t8, draw_red_bottom_pill);
	_instr_andi(t8, t6, 2);
	
	_instr_bgtz(t8, draw_red_single_pill);
	_instr_andi(t8, t6, 1);
	
	_instr_bgtz(t8, draw_red_empty_pill);
	_instr_j(not_a_pill);
	
	draw_red_left_pill:
	_macro_draw_asset(asset_pill_red_left_size, asset_pill_red_left_data);
	_instr_j(not_a_pill);
	
	draw_red_right_pill:
	_macro_draw_asset(asset_pill_red_right_size, asset_pill_red_right_data);
	_instr_j(not_a_pill);
	
	draw_red_top_pill:
	_macro_draw_asset(asset_pill_red_top_size, asset_pill_red_top_data);
	_instr_j(not_a_pill);
	
	draw_red_bottom_pill:
	_macro_draw_asset(asset_pill_red_bottom_size, asset_pill_red_bottom_data);
	_instr_j(not_a_pill);
	
	draw_red_single_pill:
	_macro_draw_asset(asset_pill_red_single_size, asset_pill_red_single_data);
	_instr_j(not_a_pill);
	
	draw_red_empty_pill:
	_macro_draw_asset(asset_pill_red_empty_size, asset_pill_red_empty_data);
	_instr_j(not_a_pill);
	
	_instr_j(not_a_pill);
	
	draw_blue_pill:
	_instr_andi(t8, t6, 32);
	
	_instr_bgtz(t8, draw_blue_left_pill);
	_instr_andi(t8, t6, 16);
	
	_instr_bgtz(t8, draw_blue_right_pill);
	_instr_andi(t8, t6, 8);
	
	_instr_bgtz(t8, draw_blue_top_pill);
	_instr_andi(t8, t6, 4);
	
	_instr_bgtz(t8, draw_blue_bottom_pill);
	_instr_andi(t8, t6, 2);
	
	_instr_bgtz(t8, draw_blue_single_pill);
	_instr_andi(t8, t6, 1);
	
	_instr_bgtz(t8, draw_blue_empty_pill);
	_instr_j(not_a_pill);
	
	draw_blue_left_pill:
	_macro_draw_asset(asset_pill_blue_left_size, asset_pill_blue_left_data);
	_instr_j(not_a_pill);
	
	draw_blue_right_pill:
	_macro_draw_asset(asset_pill_blue_right_size, asset_pill_blue_right_data);
	_instr_j(not_a_pill);
	
	draw_blue_top_pill:
	_macro_draw_asset(asset_pill_blue_top_size, asset_pill_blue_top_data);
	_instr_j(not_a_pill);
	
	draw_blue_bottom_pill:
	_macro_draw_asset(asset_pill_blue_bottom_size, asset_pill_blue_bottom_data);
	_instr_j(not_a_pill);
	
	draw_blue_single_pill:
	_macro_draw_asset(asset_pill_blue_single_size, asset_pill_blue_single_data);
	_instr_j(not_a_pill);
	
	draw_blue_empty_pill:
	_macro_draw_asset(asset_pill_blue_empty_size, asset_pill_blue_empty_data);
	_instr_j(not_a_pill);
	
	_instr_j(not_a_pill);
	
	draw_yellow_pill:
	_instr_andi(t8, t6, 32);
	
	_instr_bgtz(t8, draw_yellow_left_pill);
	_instr_andi(t8, t6, 16);
	
	_instr_bgtz(t8, draw_yellow_right_pill);
	_instr_andi(t8, t6, 8);
	
	_instr_bgtz(t8, draw_yellow_top_pill);
	_instr_andi(t8, t6, 4);
	
	_instr_bgtz(t8, draw_yellow_bottom_pill);
	_instr_andi(t8, t6, 2);
	
	_instr_bgtz(t8, draw_yellow_single_pill);
	_instr_andi(t8, t6, 1);
	
	_instr_bgtz(t8, draw_yellow_empty_pill);
	_instr_j(not_a_pill);
	
	draw_yellow_left_pill:
	_macro_draw_asset(asset_pill_yellow_left_size, asset_pill_yellow_left_data);
	_instr_j(not_a_pill);
	
	draw_yellow_right_pill:
	_macro_draw_asset(asset_pill_yellow_right_size, asset_pill_yellow_right_data);
	_instr_j(not_a_pill);
	
	draw_yellow_top_pill:
	_macro_draw_asset(asset_pill_yellow_top_size, asset_pill_yellow_top_data);
	_instr_j(not_a_pill);
	
	draw_yellow_bottom_pill:
	_macro_draw_asset(asset_pill_yellow_bottom_size, asset_pill_yellow_bottom_data);
	_instr_j(not_a_pill);
	
	draw_yellow_single_pill:
	_macro_draw_asset(asset_pill_yellow_single_size, asset_pill_yellow_single_data);
	_instr_j(not_a_pill);
	
	draw_yellow_empty_pill:
	_macro_draw_asset(asset_pill_yellow_empty_size, asset_pill_yellow_empty_data);
	_instr_j(not_a_pill);
	
	_instr_j(not_a_pill);
	
	draw_empty_cell:
	_instr_li(s7, 0);
	_instr_li(a0, 2048);
	_macro_draw_square(a0);
	not_a_pill:
}


void _macro_remove_cell(Arg *arg_cell_addr) {	_macro_push(t0);
	_macro_push(t1);
	_macro_push(t2);
	_instr_lw(t0, _offset(12, arg_cell_addr));
	
	_instr_andi(t0, t0, 60);
	
	
	_instr_beq(t0, zero, zero_memory);
	
	_instr_andi(t1, t0, 32);
	
	_instr_bgtz(t1, remove_left_pill);
	_instr_andi(t1, t0, 16);
	
	_instr_bgtz(t1, remove_right_pill);
	_instr_andi(t1, t0, 8);
	
	_instr_bgtz(t1, remove_top_pill);
	_instr_andi(t1, t0, 4);
	
	_instr_bgtz(t1, remove_bottom_pill);
	_instr_j(zero_memory);
	remove_left_pill:
	_instr_addi(arg_cell_addr, arg_cell_addr, 32);
	
	_instr_lw(t2, _offset(12, arg_cell_addr));
	
	_instr_andi(t2, t2, 195);
	
	_instr_ori(t2, t2, 2);
	
	_instr_sw(t2, _offset(12, arg_cell_addr));
	_instr_subi(arg_cell_addr, arg_cell_addr, 32);
	_instr_j(zero_memory);
	remove_right_pill:
	_instr_subi(arg_cell_addr, arg_cell_addr, 32);
	
	_instr_lw(t2, _offset(12, arg_cell_addr));
	
	_instr_andi(t2, t2, 195);
	
	_instr_ori(t2, t2, 2);
	
	_instr_sw(t2, _offset(12, arg_cell_addr));
	_instr_addi(arg_cell_addr, arg_cell_addr, 32);
	_instr_j(zero_memory);
	remove_top_pill:
	_instr_addi(arg_cell_addr, arg_cell_addr, 256);
	
	_instr_lw(t2, _offset(12, arg_cell_addr));
	
	_instr_andi(t2, t2, 195);
	
	_instr_ori(t2, t2, 2);
	
	_instr_sw(t2, _offset(12, arg_cell_addr));
	_instr_subi(arg_cell_addr, arg_cell_addr, 256);
	_instr_j(zero_memory);
	remove_bottom_pill:
	_instr_subi(arg_cell_addr, arg_cell_addr, 256);
	
	_instr_lw(t2, _offset(12, arg_cell_addr));
	
	_instr_andi(t2, t2, 195);
	
	_instr_ori(t2, t2, 2);
	
	_instr_sw(t2, _offset(12, arg_cell_addr));
	_instr_addi(arg_cell_addr, arg_cell_addr, 256);
	_instr_j(zero_memory);
	zero_memory:
	
	
	_instr_sw(zero, _offset(8, arg_cell_addr));
	_instr_sw(zero, _offset(12, arg_cell_addr));
	_instr_sw(zero, _offset(16, arg_cell_addr));
	_instr_sw(zero, _offset(20, arg_cell_addr));
	_instr_sw(zero, _offset(24, arg_cell_addr));
	_instr_sw(zero, _offset(28, arg_cell_addr));
	_macro_pop(t2);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_remove_connected(Arg *arg_board) {	_instr_lw(t0, _label_address(board_width_minus_one));
	
	_instr_lw(t1, _label_address(board_height_minus_one));
	
	draw_board_loop_y:
	_instr_lw(t0, _label_address(board_width_minus_one));
	draw_board_loop_x:
	_instr_la(t2, board);
	_instr_li(t3, 256);
	_instr_mul(t3, t3, t1);
	_instr_add(t2, t2, t3);
	_instr_li(t3, 32);
	_instr_mul(t3, t3, t0);
	_instr_add(t2, t2, t3);
	
	_instr_lw(t5, _offset(8, t2));
	
	_instr_li(t6, 3);
	anding_color:
	_instr_subi(t2, t2, 256);
	_instr_lw(t7, _offset(8, t2));
	_instr_and(t5, t5, t7);
	_instr_subi(t6, t6, 1);
	_instr_bgtz(t6, anding_color);
	_instr_beq(t5, zero, remove_conntected_continue);
	_macro_COUNTDOWN_BEEP();
	_instr_li(t6, 4);
	removing_cells:
	_instr_move(a0, t2);
	
	_macro_remove_cell(a0);
	_instr_addi(t2, t2, 256);
	
	_instr_subi(t6, t6, 1);
	_instr_bgtz(t6, removing_cells);
	remove_conntected_continue:
	_instr_subi(t0, t0, 1);
	_instr_bgez(t0, _label_address(draw_board_loop_x));
	_instr_subi(t1, t1, 1);
	_instr_li(t0, 3);
	_instr_bge(t1, t0, draw_board_loop_y);
}


void _macro_remove_connected_horizontal(Arg *arg_board_addr) {	_instr_lw(t0, _label_address(board_width_minus_one));
	
	_instr_lw(t1, _label_address(board_height_minus_one));
	
	draw_board_loop_y:
	_instr_lw(t0, _label_address(board_width_minus_one));
	draw_board_loop_x:
	_instr_la(t2, board);
	_instr_li(t3, 256);
	_instr_mul(t3, t3, t1);
	_instr_add(t2, t2, t3);
	_instr_li(t3, 32);
	_instr_mul(t3, t3, t0);
	_instr_add(t2, t2, t3);
	
	_instr_lw(t5, _offset(8, t2));
	
	_instr_li(t6, 3);
	anding_color:
	_instr_subi(t2, t2, 32);
	_instr_lw(t7, _offset(8, t2));
	_instr_and(t5, t5, t7);
	_instr_subi(t6, t6, 1);
	_instr_bgtz(t6, anding_color);
	_instr_beq(t5, zero, remove_conntected_continue);
	_macro_COUNTDOWN_BEEP();
	_instr_li(t6, 4);
	removing_cells:
	_instr_move(a0, t2);
	
	_macro_remove_cell(a0);
	_instr_addi(t2, t2, 32);
	
	_instr_subi(t6, t6, 1);
	_instr_bgtz(t6, removing_cells);
	remove_conntected_continue:
	_instr_subi(t0, t0, 1);
	_instr_li(t6, 3);
	_instr_bge(t0, t6, draw_board_loop_x);
	_instr_subi(t1, t1, 1);
	_instr_bgez(t1, _label_address(draw_board_loop_y));
}


void _macro_try_drop_cell(Arg *arg_cell_addr) {	_macro_push(t0);
	_macro_push(t1);
	_macro_push(t2);
	
	_instr_lw(t0, _offset(12, arg_cell_addr));
	_instr_andi(t1, t0, 32);
	
	_instr_bgtz(t1, drop_left_pill);
	_instr_andi(t1, t0, 8);
	
	_instr_bgtz(t1, drop_bottom_or_top);
	_instr_andi(t1, t0, 4);
	
	_instr_bgtz(t1, drop_bottom_or_top);
	_instr_andi(t1, t0, 2);
	
	_instr_bgtz(t1, drop_bottom_or_top);
	_instr_j(exit_try_drop_cell);
	drop_left_pill:
	_instr_move(t2, arg_cell_addr);
	_instr_addi(t2, t2, 256);
	
	_instr_lw(t1, _offset(12, t2));
	
	_instr_addi(t2, t2, 32);
	
	_instr_lw(t0, _offset(12, t2));
	
	_instr_add(t1, t1, t0);
	_instr_bgtz(t1, exit_try_drop_cell);
	
	_instr_subi(t2, t2, 32);
	_instr_lw(t1, _offset(8, arg_cell_addr));
	_instr_sw(t1, _offset(8, t2));
	_instr_sw(zero, _offset(8, arg_cell_addr));
	_instr_lw(t1, _offset(12, arg_cell_addr));
	_instr_sw(t1, _offset(12, t2));
	_instr_sw(zero, _offset(12, arg_cell_addr));
	_instr_lw(t1, _offset(16, arg_cell_addr));
	_instr_sw(t1, _offset(16, t2));
	_instr_sw(zero, _offset(16, arg_cell_addr));
	_instr_lw(t1, _offset(20, arg_cell_addr));
	_instr_sw(t1, _offset(20, t2));
	_instr_sw(zero, _offset(20, arg_cell_addr));
	_instr_lw(t1, _offset(24, arg_cell_addr));
	_instr_sw(t1, _offset(24, t2));
	_instr_sw(zero, _offset(24, arg_cell_addr));
	_instr_lw(t1, _offset(28, arg_cell_addr));
	_instr_sw(t1, _offset(28, t2));
	_instr_sw(zero, _offset(28, arg_cell_addr));
	_instr_bne(s4, arg_cell_addr, do_not_set_current_left_pill);
	_instr_move(s4, t2);
	
	do_not_set_current_left_pill:
	_instr_addi(t2, t2, 32);
	_instr_addi(arg_cell_addr, arg_cell_addr, 32);
	_instr_lw(t1, _offset(8, arg_cell_addr));
	_instr_sw(t1, _offset(8, t2));
	_instr_sw(zero, _offset(8, arg_cell_addr));
	_instr_lw(t1, _offset(12, arg_cell_addr));
	_instr_sw(t1, _offset(12, t2));
	_instr_sw(zero, _offset(12, arg_cell_addr));
	_instr_lw(t1, _offset(16, arg_cell_addr));
	_instr_sw(t1, _offset(16, t2));
	_instr_sw(zero, _offset(16, arg_cell_addr));
	_instr_lw(t1, _offset(20, arg_cell_addr));
	_instr_sw(t1, _offset(20, t2));
	_instr_sw(zero, _offset(20, arg_cell_addr));
	_instr_lw(t1, _offset(24, arg_cell_addr));
	_instr_sw(t1, _offset(24, t2));
	_instr_sw(zero, _offset(24, arg_cell_addr));
	_instr_lw(t1, _offset(28, arg_cell_addr));
	_instr_sw(t1, _offset(28, t2));
	_instr_sw(zero, _offset(28, arg_cell_addr));
	_instr_bne(s5, arg_cell_addr, do_not_set_current_left_right);
	_instr_move(s5, t2);
	
	do_not_set_current_left_right:
	_instr_j(exit_try_drop_cell);
	drop_bottom_or_top:
	_instr_move(t2, arg_cell_addr);
	_instr_addi(t2, t2, 256);
	
	_instr_lw(t1, _offset(12, t2));
	
	_instr_bgtz(t1, exit_try_drop_cell);
	
	_instr_beq(arg_cell_addr, s4, drop_set_top);
	_instr_beq(arg_cell_addr, s5, drop_set_right);
	_instr_j(drop_set_cont);
	drop_set_top:
	_instr_addi(s4, s4, 256);
	_instr_j(drop_set_cont);
	drop_set_right:
	_instr_addi(s5, s5, 256);
	_instr_j(drop_set_cont);
	drop_set_cont:
	
	_instr_lw(t1, _offset(8, arg_cell_addr));
	_instr_sw(t1, _offset(8, t2));
	_instr_sw(zero, _offset(8, arg_cell_addr));
	_instr_lw(t1, _offset(12, arg_cell_addr));
	_instr_sw(t1, _offset(12, t2));
	_instr_sw(zero, _offset(12, arg_cell_addr));
	_instr_lw(t1, _offset(16, arg_cell_addr));
	_instr_sw(t1, _offset(16, t2));
	_instr_sw(zero, _offset(16, arg_cell_addr));
	_instr_lw(t1, _offset(20, arg_cell_addr));
	_instr_sw(t1, _offset(20, t2));
	_instr_sw(zero, _offset(20, arg_cell_addr));
	_instr_lw(t1, _offset(24, arg_cell_addr));
	_instr_sw(t1, _offset(24, t2));
	_instr_sw(zero, _offset(24, arg_cell_addr));
	_instr_lw(t1, _offset(28, arg_cell_addr));
	_instr_sw(t1, _offset(28, t2));
	_instr_sw(zero, _offset(28, arg_cell_addr));
	exit_try_drop_cell:
	_macro_pop(t2);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_do_gravity(Arg *arg_board) {	_instr_lw(t0, _label_address(board_width_minus_one));
	
	_instr_lw(t1, _label_address(board_height_minus_one));
	
	_instr_subi(t1, t1, 1);
	
	draw_board_loop_y:
	_instr_lw(t0, _label_address(board_width_minus_one));
	draw_board_loop_x:
	_instr_la(t2, board);
	_instr_li(t3, 256);
	_instr_mul(t3, t3, t1);
	_instr_add(t2, t2, t3);
	_instr_li(t3, 32);
	_instr_mul(t3, t3, t0);
	_instr_add(t2, t2, t3);
	
	_instr_move(a0, t2);
	_macro_try_drop_cell(a0);
	_instr_subi(t0, t0, 1);
	_instr_bgez(t0, _label_address(draw_board_loop_x));
	_instr_subi(t1, t1, 1);
	_instr_bgez(t1, _label_address(draw_board_loop_y));
}


void _macro_rand(Arg *arg_max) {	_macro_push(a0);
	_macro_push(a1);
	_instr_li(v0, 42);
	_instr_li(a0, 0);
	_instr_li(a1, arg_max);
	syscall();
	_instr_move(v0, a0);
	_macro_pop(a1);
	_macro_pop(a0);
}


void _macro_rand_pill_color() {	_macro_push(t0);
	_macro_rand(3);
	_instr_beq(v0, zero, rand_color_red);
	_instr_li(t0, 1);
	_instr_beq(v0, t0, rand_color_blue);
	_instr_li(t0, 2);
	_instr_beq(v0, t0, rand_color_yellow);
	rand_color_red:
	_instr_li(v0, 1);
	_instr_j(rand_color_exit);
	rand_color_blue:
	_instr_li(v0, 2);
	_instr_j(rand_color_exit);
	rand_color_yellow:
	_instr_li(v0, 4);
	_instr_j(rand_color_exit);
	rand_color_exit:
	_macro_pop(t0);
}


void _macro_generate_random_pill() {	_macro_push(t0);
	_macro_push(t1);
	_macro_push(t2);
	_instr_la(t0, board);
	_instr_addi(t0, t0, 96);
	
	_instr_addi(t1, t0, 32);
	
	_instr_li(v0, 0);
	_instr_li(v1, 0);
	_macro_is_occupied_add(t0, 0);
	_instr_move(v1, v0);
	_macro_is_occupied_add(t1, 0);
	_instr_or(v1, v0, v1);
	_instr_move(s4, t0);
	_instr_move(s5, t1);
	_macro_rand_pill_color();
	_instr_sw(v0, _offset(8, t0));
	_instr_li(t2, 96);
	
	_instr_sw(t2, _offset(12, t0));
	_macro_rand_pill_color();
	_instr_sw(v0, _offset(8, t1));
	_instr_li(t2, 80);
	
	_instr_sw(t2, _offset(12, t1));
	_macro_pop(t2);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_sleep(Arg *arg_millis) {	_macro_push(a0);
	_instr_li(v0, 32);
	_instr_li(a0, arg_millis);
	syscall();
	_macro_pop(a0);
}


void _macro_tick_set_zero() {	_instr_li(s6, 0);
}


void _macro_tick_sleep() {	_macro_push(t0);
	_macro_sleep(0);
	_instr_addi(s6, s6, 1);
	_instr_li(t0, 1024);
	_instr_bge(s6, t0, set_zero);
	_instr_j(tick_sleep_exit);
	set_zero:
	_instr_li(s6, 0);
	_instr_addi(t9, t9, 1);
	tick_sleep_exit:
	_macro_pop(t0);
}


void _macro_on_tick(Arg *arg_tick, Arg *arg_label) {	_macro_push(t0);
	_instr_li(t0, arg_tick);
	_instr_div(s6, t0);
	_instr_mfhi(t0);
	_instr_bne(t0, zero, arg_label);
	_macro_pop(t0);
}


void _macro_on_tick_reg(Arg *arg_tick, Arg *arg_label) {	_macro_push(t0);
	_instr_div(s6, arg_tick);
	_instr_mfhi(t0);
	_instr_bne(t0, zero, arg_label);
	_macro_pop(t0);
}


void _macro_is_vertical() {	_instr_sub(v0, s5, s4);
	_instr_srl(v0, v0, 8);
}


void _macro_set_pill_left(Arg *arg_pill_addr) {	_macro_push(t0);
	_instr_li(t0, 96);
	_instr_sw(t0, _offset(12, arg_pill_addr));
	_macro_pop(t0);
}


void _macro_set_pill_right(Arg *arg_pill_addr) {	_macro_push(t0);
	_instr_li(t0, 80);
	_instr_sw(t0, _offset(12, arg_pill_addr));
	_macro_pop(t0);
}


void _macro_set_pill_top(Arg *arg_pill_addr) {	_macro_push(t0);
	_instr_li(t0, 72);
	_instr_sw(t0, _offset(12, arg_pill_addr));
	_macro_pop(t0);
}


void _macro_set_pill_bottom(Arg *arg_pill_addr) {	_macro_push(t0);
	_instr_li(t0, 68);
	_instr_sw(t0, _offset(12, arg_pill_addr));
	_macro_pop(t0);
}


void _macro_move_pill(Arg *arg_destination, Arg *arg_source) {	_macro_push(t1);
	_instr_lw(t1, _offset(8, arg_source));
	_instr_sw(t1, _offset(8, arg_destination));
	_instr_sw(zero, _offset(8, arg_source));
	_instr_lw(t1, _offset(12, arg_source));
	_instr_sw(t1, _offset(12, arg_destination));
	_instr_sw(zero, _offset(12, arg_source));
	_instr_lw(t1, _offset(16, arg_source));
	_instr_sw(t1, _offset(16, arg_destination));
	_instr_sw(zero, _offset(16, arg_source));
	_instr_lw(t1, _offset(20, arg_source));
	_instr_sw(t1, _offset(20, arg_destination));
	_instr_sw(zero, _offset(20, arg_source));
	_instr_lw(t1, _offset(24, arg_source));
	_instr_sw(t1, _offset(24, arg_destination));
	_instr_sw(zero, _offset(24, arg_source));
	_instr_lw(t1, _offset(28, arg_source));
	_instr_sw(t1, _offset(28, arg_destination));
	_instr_sw(zero, _offset(28, arg_source));
	_macro_pop(t1);
}


void _macro_rotate() {	_macro_push(v0);
	_macro_push(t0);
	_macro_push(t1);
	
	
	
	
	_instr_lw(t0, _offset(4, s4));
	_instr_li(t1, 72);
	_instr_beq(t0, t1, rotate_exit);
	_macro_ALERT_BEEP();
	_macro_is_vertical();
	_instr_beq(v0, zero, rotate_horizontal);
	_instr_bne(v0, zero, rotate_vertical);
	rotate_horizontal:
	
	_macro_is_occupied_sub(s4, 256);
	_instr_bgtz(v0, rotate_exit);
	
	
	_instr_move(t0, s4);
	
	_instr_move(t1, s5);
	
	_instr_subi(s5, s5, 32);
	
	_instr_subi(s4, s4, 256);
	
	_instr_move(a0, s4);
	_instr_move(a1, t0);
	_macro_move_pill(a0, a1);
	_macro_set_pill_top(s4);
	_instr_move(a0, s5);
	_instr_move(a1, t1);
	_macro_move_pill(a0, a1);
	_macro_set_pill_bottom(s5);
	_instr_move(a0, s4);
	_macro_draw_board_cell();
	_instr_move(a0, s5);
	_macro_draw_board_cell();
	_instr_move(a0, t0);
	_macro_draw_board_cell();
	_instr_move(a0, t1);
	_macro_draw_board_cell();
	_instr_j(rotate_exit);
	rotate_vertical:
	_instr_lw(t0, _offset(0, s5));
	_instr_beq(t0, 152, rotate_exit);
	_macro_is_occupied_add(s5, 32);
	_instr_bgtz(v0, rotate_exit);
	_instr_move(t0, s4);
	
	_instr_move(t1, s5);
	
	_instr_addi(s5, s5, 32);
	_instr_addi(s4, s4, 256);
	_instr_move(a0, s5);
	_instr_move(a1, t0);
	_macro_move_pill(a0, a1);
	_macro_set_pill_right(s5);
	_macro_set_pill_left(s4);
	_instr_move(a0, s4);
	_macro_draw_board_cell();
	_instr_move(a0, s5);
	_macro_draw_board_cell();
	_instr_move(a0, t0);
	_macro_draw_board_cell();
	_instr_move(a0, t1);
	_macro_draw_board_cell();
	_instr_j(rotate_exit);
	rotate_exit:
	_macro_pop(t1);
	_macro_pop(t0);
	_macro_pop(v0);
}


void _macro_move_right() {	_instr_lw(t0, _offset(0, s5));
	_instr_beq(t0, 152, move_right_exit);
	_macro_is_occupied_add(s5, 32);
	_instr_bgtz(v0, move_right_exit);
	_macro_is_vertical();
	_instr_bgtz(v0, check_vertical);
	_instr_j(continue_move_right);
	check_vertical:
	_macro_is_occupied_add(s4, 32);
	_instr_bgtz(v0, move_right_exit);
	_macro_is_occupied_add(s5, 32);
	_instr_bgtz(v0, move_right_exit);
	continue_move_right:
	_instr_move(t0, s4);
	_instr_move(t1, s5);
	_instr_addi(s4, s4, 32);
	_instr_addi(s5, s5, 32);
	_instr_move(a0, s5);
	_instr_move(a1, t1);
	_macro_move_pill(a0, a1);
	_instr_move(a0, s4);
	_instr_move(a1, t0);
	_macro_move_pill(a0, a1);
	move_right_exit:
}


void _macro_move_left() {	_instr_lw(t0, _offset(0, s4));
	_instr_beq(t0, 96, move_left_exit);
	_macro_is_occupied_sub(s4, 32);
	_instr_bgtz(v0, move_left_exit);
	_macro_is_vertical();
	_instr_bgtz(v0, check_vertical);
	_instr_j(continue_move_left);
	check_vertical:
	_macro_is_occupied_sub(s4, 32);
	_instr_bgtz(v0, move_left_exit);
	_macro_is_occupied_sub(s5, 32);
	_instr_bgtz(v0, move_left_exit);
	continue_move_left:
	_instr_move(t0, s4);
	_instr_move(t1, s5);
	_instr_subi(s4, s4, 32);
	_instr_subi(s5, s5, 32);
	_instr_move(a0, s4);
	_instr_move(a1, t0);
	_macro_move_pill(a0, a1);
	_instr_move(a0, s5);
	_instr_move(a1, t1);
	_macro_move_pill(a0, a1);
	move_left_exit:
}


void _macro_move_down() {	_instr_lw(t0, _offset(4, s5));
	_instr_beq(t0, 192, move_down_exit);
	_macro_is_occupied_add(s5, 256);
	_instr_bgtz(v0, move_down_exit);
	_macro_is_vertical();
	_instr_beq(zero, v0, check_horizontal);
	_instr_j(continue_move_down);
	check_horizontal:
	_macro_is_occupied_add(s4, 256);
	_instr_bgtz(v0, move_down_exit);
	_macro_is_occupied_add(s5, 256);
	_instr_bgtz(v0, move_down_exit);
	continue_move_down:
	_macro_SUCCESS_JINGLE();
	_instr_move(t0, s4);
	_instr_move(t1, s5);
	_instr_addi(s4, s4, 256);
	_instr_addi(s5, s5, 256);
	_instr_move(a0, s5);
	_instr_move(a1, t1);
	_macro_move_pill(a0, a1);
	_instr_move(a0, s4);
	_instr_move(a1, t0);
	_macro_move_pill(a0, a1);
	move_down_exit:
}


void _macro_is_occupied_add(Arg *arg_base, Arg *arg_offset) {	_macro_push(t0);
	_instr_addi(t0, arg_base, arg_offset);
	_instr_lw(t0, _offset(12, t0));
	_instr_bgtz(t0, is_occupied_true);
	_instr_li(v0, 0);
	_instr_j(is_occupied_exit);
	is_occupied_true:
	_instr_li(v0, 1);
	is_occupied_exit:
	_macro_pop(t0);
}


void _macro_is_occupied_sub(Arg *arg_base, Arg *arg_offset) {	_macro_push(t0);
	_instr_subi(t0, arg_base, arg_offset);
	_instr_lw(t0, _offset(12, t0));
	_instr_bgtz(t0, is_occupied_true);
	_instr_li(v0, 0);
	_instr_j(is_occupied_exit);
	is_occupied_true:
	_instr_li(v0, 1);
	is_occupied_exit:
	_macro_pop(t0);
}


void _macro_check_kb() {	_macro_push(t0);
	_macro_push(t1);
	_instr_lw(t0, _label_address(keyboard_address));
	_instr_lw(t1, _offset(0, t0));
	_instr_bne(t1, 1, check_kb_exit);
	_instr_lw(t1, _offset(4, t0));
	
	_instr_beq(t1, 114, handle_r);
	_instr_beq(t1, 119, handle_w);
	_instr_beq(t1, 100, handle_d);
	_instr_beq(t1, 97, handle_a);
	_instr_beq(t1, 115, handle_s);
	_instr_beq(t1, 112, handle_p);
	_instr_j(check_kb_exit);
	handle_p:
	_macro_flip_paused_state();
	handle_p1:
	_macro_check_paused();
	_instr_beq(zero, v0, check_kb_exit);
	_macro_set_x_i(96);
	_macro_set_y_i(72);
	_macro_draw_asset(asset_pause_screen_size, asset_pause_screen_data);
	_instr_lw(t0, _label_address(keyboard_address));
	_instr_lw(t1, _offset(0, t0));
	_instr_bne(t1, 1, handle_p1);
	_instr_lw(t1, _offset(4, t0));
	
	_instr_beq(t1, 112, handle_p);
	_instr_j(handle_p1);
	check_kb_start:
	handle_r:
	_macro_generate_random_pill();
	_macro_do_gravity(board);
	_instr_j(check_kb_exit);
	handle_d:
	_macro_move_right();
	
	
	
	
	
	_macro_draw_board(board);
	_instr_j(check_kb_exit);
	handle_w:
	_macro_rotate();
	_macro_draw_board(board);
	_instr_j(check_kb_exit);
	handle_a:
	_macro_move_left();
	_macro_draw_board(board);
	_instr_j(check_kb_exit);
	handle_s:
	_macro_move_down();
	_macro_draw_board(board);
	_instr_j(check_kb_exit);
	check_kb_exit:
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_handle_handover() {	
	
	_instr_lw(t0, _offset(4, s5));
	_instr_beq(t0, 192, commit_handover);
	
	
	_macro_is_vertical();
	_instr_bgtz(v0, handover_vertical);
	_instr_j(handover_horizontal);
	handover_horizontal:
	_macro_is_occupied_add(s4, 256);
	_instr_bgtz(v0, commit_handover);
	_macro_is_occupied_add(s5, 256);
	_instr_bgtz(v0, commit_handover);
	_instr_li(v0, 0);
	_instr_j(handover_exit);
	handover_vertical:
	_macro_is_occupied_add(s5, 256);
	_instr_bgtz(v0, commit_handover);
	_instr_li(v0, 0);
	_instr_j(handover_exit);
	commit_handover:
	_macro_generate_random_pill();
	handover_exit:
}



void _macro_spawn_virus(Arg *arg_offset) {	_macro_push(t0);
	_instr_la(t0, board);
	_instr_add(t0, t0, arg_offset);
	_macro_is_occupied_add(t0, 0);
	_instr_bgtz(v0, already_occupied);
	_macro_rand_pill_color();
	_instr_sw(v0, _offset(8, t0));
	_instr_li(v0, 128);
	_instr_sw(v0, _offset(12, t0));
	_instr_li(v0, 1);
	_instr_j(spawn_virus_exit);
	already_occupied:
	_instr_li(v0, 0);
	_instr_j(spawn_virus_exit);
	spawn_virus_exit:
	_macro_pop(t0);
}


void _macro_check_restart() {	_macro_push(t0);
	_macro_push(t1);
	_instr_lw(t0, _label_address(keyboard_address));
	_instr_lw(t1, _offset(0, t0));
	_instr_bne(t1, 1, check_restart_exit);
	_instr_lw(t1, _offset(4, t0));
	
	_instr_beq(t1, 114, handle_q);
	_instr_beq(t1, 10, handle_enter);
	_instr_j(check_restart_exit);
	handle_q:
	_instr_li(v0, 10);
	syscall();
	handle_enter:
	_instr_li(v0, 1);
	_instr_j(check_restart_exit);
	_instr_li(v0, 0);
	check_restart_exit:
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_clear_board() {	_macro_push(t0);
	_macro_push(t1);
	_instr_move(s4, zero);
	_instr_move(s5, zero);
	_instr_li(t0, 127);
	_instr_la(t1, board);
	clear_board_loop:
	_instr_bltz(t0, clear_board_exit);
	_instr_sw(zero, _offset(8, t1));
	_instr_sw(zero, _offset(12, t1));
	_instr_sw(zero, _offset(16, t1));
	_instr_sw(zero, _offset(20, t1));
	_instr_sw(zero, _offset(24, t1));
	_instr_sw(zero, _offset(28, t1));
	_instr_addi(t1, t1, 32);
	_instr_subi(t0, t0, 1);
	_instr_j(clear_board_loop);
	clear_board_exit:
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_check_paused() {	_macro_push(t0);
	_instr_la(t0, is_paused);
	_instr_lw(v0, _offset(0, t0));
	_macro_pop(t0);
}


void _macro_flip_paused_state() {	_macro_push(t0);
	_macro_push(t1);
	_instr_la(t0, is_paused);
	_instr_lw(t1, _offset(0, t0));
	_instr_xori(t1, t1, 1);
	
	_instr_sw(t1, _offset(0, t0));
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_draw_mario() {	_macro_set_x_i(190);
	_macro_set_y_i(60);
	_instr_beq(s6, 0, draw_mario_1);
	_instr_beq(s6, 256, draw_mario_2);
	_instr_beq(s6, 512, draw_mario_3);
	_instr_beq(s6, 768, draw_mario_4);
	_instr_j(draw_mario_exit);
	draw_mario_1:
	_macro_draw_asset(asset_mario1_size, asset_mario1_data);
	_instr_j(draw_mario_exit);
	draw_mario_2:
	_macro_draw_asset(asset_mario2_size, asset_mario2_data);
	_instr_j(draw_mario_exit);
	draw_mario_3:
	_macro_draw_asset(asset_mario3_size, asset_mario3_data);
	_instr_j(draw_mario_exit);
	draw_mario_4:
	_macro_draw_asset(asset_mario4_size, asset_mario4_data);
	_instr_j(draw_mario_exit);
	draw_mario_exit:
}


void _macro_draw_viruses() {	_instr_beq(s6, 0, draw_viruses_1);
	_instr_beq(s6, 256, draw_viruses_2);
	_instr_beq(s6, 512, draw_viruses_3);
	_instr_beq(s6, 768, draw_viruses_4);
	_instr_j(draw_virses_exit);
	draw_viruses_1:
	_macro_set_x_i(30);
	_macro_set_y_i(130);
	_macro_draw_asset(asset_vvirus_red1_size, asset_vvirus_red1_data);
	_macro_set_x_i(20);
	_macro_set_y_i(160);
	_macro_draw_asset(asset_vvirus_blue1_size, asset_vvirus_blue1_data);
	_macro_set_x_i(45);
	_macro_set_y_i(155);
	_macro_draw_asset(asset_vvirus_yellow1_size, asset_vvirus_yellow1_data);
	_instr_j(draw_virses_exit);
	draw_viruses_2:
	_macro_set_x_i(30);
	_macro_set_y_i(130);
	_macro_draw_asset(asset_vvirus_red2_size, asset_vvirus_red2_data);
	_macro_set_x_i(20);
	_macro_set_y_i(160);
	_macro_draw_asset(asset_vvirus_blue2_size, asset_vvirus_blue2_data);
	_macro_set_x_i(45);
	_macro_set_y_i(155);
	_macro_draw_asset(asset_vvirus_yellow2_size, asset_vvirus_yellow2_data);
	_instr_j(draw_virses_exit);
	draw_viruses_3:
	_macro_set_x_i(30);
	_macro_set_y_i(130);
	_macro_draw_asset(asset_vvirus_red3_size, asset_vvirus_red3_data);
	_macro_set_x_i(20);
	_macro_set_y_i(160);
	_macro_draw_asset(asset_vvirus_blue3_size, asset_vvirus_blue3_data);
	_macro_set_x_i(45);
	_macro_set_y_i(155);
	_macro_draw_asset(asset_vvirus_yellow3_size, asset_vvirus_yellow3_data);
	_instr_j(draw_virses_exit);
	draw_viruses_4:
	_macro_set_x_i(30);
	_macro_set_y_i(130);
	_macro_draw_asset(asset_vvirus_red4_size, asset_vvirus_red4_data);
	_macro_set_x_i(20);
	_macro_set_y_i(160);
	_macro_draw_asset(asset_vvirus_blue4_size, asset_vvirus_blue4_data);
	_macro_set_x_i(45);
	_macro_set_y_i(155);
	_macro_draw_asset(asset_vvirus_yellow4_size, asset_vvirus_yellow4_data);
	_instr_j(draw_virses_exit);
	draw_virses_exit:
}


void _macro_ALERT_BEEP() {	_instr_li(v0, 31);
	_instr_li(a0, 84);
	_instr_li(a1, 300);
	_instr_li(a2, 113);
	_instr_li(a3, 127);
	syscall();
}


void _macro_ERROR_BUZZ() {	_instr_li(v0, 31);
	_instr_li(a0, 48);
	_instr_li(a1, 500);
	_instr_li(a2, 20);
	_instr_li(a3, 120);
	syscall();
	_instr_li(v0, 31);
	_instr_li(a0, 49);
	_instr_li(a1, 400);
	_instr_li(a2, 20);
	_instr_li(a3, 110);
	syscall();
}


void _macro_SUCCESS_JINGLE() {	_instr_li(v0, 31);
	_instr_li(a0, 60);
	_instr_li(a1, 200);
	_instr_li(a2, 9);
	_instr_li(a3, 100);
	syscall();
	_instr_li(v0, 31);
	_instr_li(a0, 64);
	_instr_li(a1, 200);
	_instr_li(a2, 9);
	_instr_li(a3, 105);
	syscall();
	_instr_li(v0, 31);
	_instr_li(a0, 67);
	_instr_li(a1, 400);
	_instr_li(a2, 9);
	_instr_li(a3, 110);
	syscall();
}


void _macro_COUNTDOWN_BEEP() {	_instr_li(v0, 31);
	_instr_li(a0, 72);
	_instr_li(a1, 250);
	_instr_li(a2, 115);
	_instr_li(a3, 110);
	syscall();
	_instr_li(v0, 31);
	_instr_li(a0, 67);
	_instr_li(a1, 250);
	_instr_li(a2, 115);
	_instr_li(a3, 115);
	syscall();
	_instr_li(v0, 31);
	_instr_li(a0, 60);
	_instr_li(a1, 400);
	_instr_li(a2, 115);
	_instr_li(a3, 127);
	syscall();
}


void _macro_get_gravity_speed() {	_instr_blt(t9, 15, get_speed_1);
	_instr_blt(t9, 30, get_speed_2);
	_instr_blt(t9, 50, get_speed_3);
	_instr_j(get_speed_max);
	get_speed_1:
	_instr_li(v0, 512);
	_instr_j(get_gravity_exit);
	get_speed_2:
	_instr_li(v0, 256);
	_instr_j(get_gravity_exit);
	get_speed_3:
	_instr_li(v0, 128);
	_instr_j(get_gravity_exit);
	get_speed_max:
	_instr_li(v0, 2);
	_instr_j(get_gravity_exit);
	get_gravity_exit:
}


void _macro_get_n_virses() {	_macro_push(t0);
	_macro_push(t1);
	_macro_push(t2);
	_macro_push(t3);
	_instr_lw(t0, _label_address(board_width_minus_one));
	
	_instr_lw(t1, _label_address(board_height_minus_one));
	
	_instr_li(v0, 0);
	draw_board_loop_y:
	_instr_lw(t0, _label_address(board_width_minus_one));
	draw_board_loop_x:
	_instr_la(t2, board);
	_instr_li(t3, 256);
	_instr_mul(t3, t3, t1);
	_instr_add(t2, t2, t3);
	_instr_li(t3, 32);
	_instr_mul(t3, t3, t0);
	_instr_add(t2, t2, t3);
	
	_instr_lw(t3, _offset(12, t2));
	_instr_srl(t3, t3, 7);
	_instr_add(v0, v0, t3);
	_instr_subi(t0, t0, 1);
	_instr_bgez(t0, _label_address(draw_board_loop_x));
	_instr_subi(t1, t1, 1);
	_instr_bgez(t1, _label_address(draw_board_loop_y));
	_macro_pop(t3);
	_macro_pop(t2);
	_macro_pop(t1);
	_macro_pop(t0);
}


void _macro_spawn_n_virus(Arg *arg_num_to_spawn) {	spawn_virus_loop:
	_instr_beq(zero, arg_num_to_spawn, spawn_n_virus_exit);
	_instr_lw(t0, _label_address(board));
	_macro_rand(96);
	_instr_li(t1, 32);
	_instr_mul(t1, v0, t1);
	_instr_addi(t1, t1, 1024);
	_macro_spawn_virus(t1);
	_instr_sub(arg_num_to_spawn, arg_num_to_spawn, v0);
	_instr_j(spawn_virus_loop);
	spawn_n_virus_exit:
}


void _macro_spawn_double_viruses() {	_instr_la(t0, viruses_to_spawn);
	_instr_lw(a0, _offset(0, t0));
	_instr_sll(a0, a0, 1);
	
	_instr_sw(a0, _offset(0, t0));
	_macro_spawn_n_virus(a0);
}


game_loop_start:
_instr_li(t9, 0);
_macro_clear_board();
_macro_set_color_w(background_color);
_instr_lw(a0, _label_address(screen_size));
_macro_set_x_i(0);
_macro_set_y_i(0);
_macro_draw_asset(asset_mario_bg_size, asset_mario_bg_data);
_macro_set_x_i(0);
_macro_set_y_i(0);
_macro_draw_board(board);
_macro_generate_random_pill();
_macro_spawn_double_viruses();
_macro_tick_set_zero();
game_loop:
_macro_on_tick(256, animation_cont);
_macro_draw_mario();
_macro_draw_viruses();
animation_cont:
_macro_check_kb();
_macro_get_gravity_speed();
_macro_on_tick_reg(v0, remove_cont);
_macro_get_n_virses();
_instr_beq(v0, zero, game_loop_start);
_macro_handle_handover();
_macro_remove_connected(board);
_macro_remove_connected_horizontal(board);
_macro_do_gravity(board);
_macro_handle_handover();
_instr_bgtz(v1, pre_end_game_loop);
_macro_draw_board(board);
remove_cont:
_macro_tick_sleep();
_instr_j(game_loop);
pre_end_game_loop:
_macro_ERROR_BUZZ();
end_game_loop:
_macro_set_x_i(96);
_macro_set_y_i(72);
_macro_draw_asset(asset_game_over_size, asset_game_over_data);
_instr_li(v0, 0);
_macro_check_restart();
_instr_bgtz(v0, game_loop_start);
_instr_j(end_game_loop);