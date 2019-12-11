/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>

typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

#define INPUT_SIZE 10240
#include "day11_data.c"

#define param(X) (m##X==0?input[n##X]:(m##X==1?n##X:input[n##X+state->rel]))
#define param_out(X) (input[n##X+(m##X==2?state->rel:0)])

struct cpu_state {
	s64 pc;
	s64 rel;
	s64 data_in;
	s64 data_out;
};

s64 run(struct cpu_state *state)
{
	while(1) {
		s64 op = input[state->pc+0];
		s64 n1 = input[state->pc+1];
		s64 n2 = input[state->pc+2];
		s64 n3 = input[state->pc+3];
		s64 m1 = op /   100;
		s64 m2 = op /  1000;
		s64 m3 = op / 10000;
		
		op %= 100;
		m1 -= (m1/10) * 10;
		m2 -= (m2/10) * 10;
		m3 -= (m3/10) * 10;
		
		if(op == 99) {
			printf("Program Stopped.\n");
			break;
		} else if((op == 1 || op == 2) && (
		          (m1 == 0 && (n1 < 0 || n1 >= INPUT_SIZE)) || 
		          (m2 == 0 && (n2 < 0 || n2 >= INPUT_SIZE)) || 
				  (m3 == 0 && (n3 < 0 || n3 >= INPUT_SIZE)))) {
			printf("Error! Overflow. %lld %lld %lld\n", n1, n2, n3);
		} else if((op == 3 || op == 4) && (
		          (m1 == 0 && (n1 < 0 || n1 >= INPUT_SIZE)))) {
			printf("Error! Overflow. %lld\n", n1);
		}
		
		switch(op) {
		case 1: param_out(3) = param(1) + param(2); state->pc += 4; break;
		case 2: param_out(3) = param(1) * param(2); state->pc += 4; break;
		case 3: param_out(1) = state->data_in; state->pc += 2; break;
		case 4: state->data_out = param(1); state->pc += 2; return 1;
		case 5: if(param(1))state->pc = param(2); else state->pc += 3; break;
		case 6: if(param(1) == 0)state->pc = param(2); else state->pc += 3; break;
		case 7: param_out(3) = param(1) < param(2) ? 1 : 0; state->pc += 4; break;
		case 8: param_out(3) = param(1) == param(2) ? 1 : 0; state->pc += 4; break;
		case 9: state->rel += param(1); state->pc += 2; break;
		default: printf("Unknown Opcode: %lld\n", op); return -1;
		}
	}
	
	return 0;
}

#define SIZE 90
u8 paint_area[SIZE * SIZE];
u8 paint_set[SIZE * SIZE];

int main(void)
{
	struct cpu_state state = {0};
	int x = SIZE/2;
	int y = SIZE/2;
	int dir = 0; // UP, 1 RIGHT, 2 DOWN, 3 LEFT
	int ret;
	int count = 0;
	int i, j;
	
	paint_area[y * SIZE + x] = 1;
	
	while(1)
	{
		u8 pix = paint_area[y * SIZE + x];
		state.data_in = pix;
		
		ret = run(&state);
		if(ret <= 0) break;
		
		paint_area[y * SIZE + x] = state.data_out;
		paint_set[y * SIZE + x] = 1;
		
		ret = run(&state);
		if(ret <= 0) break;
		
		dir += (state.data_out&1)?1:-1;
		dir &= 3;
		
		switch(dir) {
			case 0: y--; break;
			case 1: x++; break;
			case 2: y++; break;
			case 3: x--; break;
		}
		
		if(x < 0 || x > SIZE || y < 0 || y > SIZE) {
			printf("Error! Out of bounds.\n");
			break;
		}
	}
	
	for(j = 0; j < SIZE; j++) {
		for(i = 0; i < SIZE; i++) {
			if(paint_area[j * SIZE + i]) printf("#");
			else printf(" ");
		}
		printf("\n");
	}
	
	count = 0;
	
	for(i = 0; i < (SIZE*SIZE); i++)
		if(paint_set[i]) count++;
	
	printf("Painted blocks: %d\n", count);

	return 0;
}