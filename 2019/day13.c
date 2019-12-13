/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <windows.h>

typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

#define INPUT_SIZE 10240
#include "day13_data.c"

#define param(X) (m##X==0?input[n##X]:(m##X==1?n##X:input[n##X+rel]))
#define param_out(X) (input[n##X+(m##X==2?rel:0)])

int player_pos;
int ball_pos;

s64 data_in(void)
{
	if(ball_pos > player_pos) return 1;
	if(ball_pos < player_pos) return -1;
	
	return 0;
}

#define WIDTH 44
#define HEIGHT 20

char display[WIDTH * HEIGHT];
int score;

void draw_screen(void)
{
	int x, y;
	
	system("cls");
	
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			printf("%c", display[y * WIDTH + x]);
		}
		printf("\n");
	}
}

void data_out(s64 x)
{
	static int i;
	static int op[3];
	
	op[i++] = (int)x;
	
	if(i == 3) {
		int x = op[0];
		int y = op[1];

		i = 0;
		
		if(x == -1 && y == 0) {
			score = op[2];
		} else { 
			switch(op[2]) {
			case 0: display[y * WIDTH + x] = ' '; break;
			case 1: display[y * WIDTH + x] = '#'; break;
			case 2: display[y * WIDTH + x] = 'X'; break;
			case 3: display[y * WIDTH + x] = '-'; player_pos = x; break;
			case 4: display[y * WIDTH + x] = 'o'; ball_pos = x;
				draw_screen();
				break;
			}
		}
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

void run1(void)
{
	int x, y;
	
	run();
	
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			printf("%c", display[y * WIDTH + x]);
		}
		printf("\n");
	}
	
	y = 0;
	for(x = 0; x < (WIDTH*HEIGHT); x++) {
		if(display[x] == 'X') y++;
	}

	printf("There are %d block tiles.\n", y);
}

int main(void)
{
	input[0] = 2;
	run();
	
	printf("The total score is %d\n", score);

	return 0;
}