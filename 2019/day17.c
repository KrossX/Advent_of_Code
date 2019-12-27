/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>

typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

#define INPUT_SIZE 10240
#include "day17_data.c"

#define param(X) (m##X==0?input[n##X]:(m##X==1?n##X:input[n##X+rel]))
#define param_out(X) (input[n##X+(m##X==2?rel:0)])

// Solved using Photoshop to rotate sections

char movement_input[5][25] = {
	"A,B,A,B,A,C,B,C,A,C\n", // MAIN
	"L,10,L,12,R,6\n",       // A
	"R,10,L,4,L,4,L,12\n",   // B
	"L,10,R,10,R,6,L,4\n",   // C
	"n\n"                    // Video feed
};

int mv_fn, mv_char;


s64 data_in(void)
{
	char c = movement_input[mv_fn][mv_char++];
	
	if(c == '\n') {
		mv_fn++;
		mv_char = 0;
	}
	
	return c;
}

void data_out(s64 x)
{
	if(x < 256) {
		char c = x&0xFF;
		putchar(c);
	} else {
		printf("OUT: %lld\n", x);
	}
}

void run(void)
{
	s64 pc = 0;
	s64 rel = 0;
	
	while(1) {
		s64 op = input[pc+0];
		s64 n1 = input[pc+1];
		s64 n2 = input[pc+2];
		s64 n3 = input[pc+3];
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
		case 1: param_out(3) = param(1) + param(2); pc += 4; break;
		case 2: param_out(3) = param(1) * param(2); pc += 4; break;
		case 3: param_out(1) = data_in(); pc += 2; break;
		case 4: data_out(param(1)); pc += 2; break;
		case 5: if(param(1)) pc = param(2); else pc += 3; break;
		case 6: if(param(1) == 0) pc = param(2); else pc += 3; break;
		case 7: param_out(3) = param(1) < param(2) ? 1 : 0; pc += 4; break;
		case 8: param_out(3) = param(1) == param(2) ? 1 : 0; pc += 4; break;
		case 9: rel += param(1); pc += 2; break;
		default: printf("Unknown Opcode: %lld\n", op); return;
		}
	}
}

int main(void)
{
	input[0] = 2;
	run();

	return 0;
}