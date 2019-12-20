/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <windows.h>
#include <stdio.h>

typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

#define INPUT_SIZE 20480
#include "day15_data.c"

#define param(X) (m##X==0?input[n##X]:(m##X==1?n##X:input[n##X+rel]))
#define param_out(X) (input[n##X+(m##X==2?rel:0)])

#define DIR_NORTH 0
#define DIR_SOUTH 1
#define DIR_WEST  2
#define DIR_EAST  3

#define DISPSIZE 48
char display[DISPSIZE*DISPSIZE];

HANDLE console;
CHAR_INFO output[DISPSIZE*DISPSIZE];

int posx = DISPSIZE/2;
int posy = DISPSIZE/2;
int start_pos = (DISPSIZE*(DISPSIZE+1))/2;
int steps, max_steps;
int oxygen_pos;
int oxygen_steps;
int mov, mov0 = -1;
int state;
int hitwall;

struct cross {
	int x, y, ret, steps;
	char block[4];
};

struct cross cpath[1024];
int cpidx;

void move(int back)
{
	switch(mov) {
	case DIR_NORTH: back? posy++ : posy--; break;
	case DIR_SOUTH: back? posy-- : posy++; break;
	case DIR_WEST:  back? posx++ : posx--; break;
	case DIR_EAST:  back? posx-- : posx++; break;
	}
}

char check_dir(int dir)
{
	int x = posx;
	int y = posy;

	switch(dir) {
	case DIR_NORTH: y--; break;
	case DIR_SOUTH: y++; break;
	case DIR_WEST:  x--; break;
	case DIR_EAST:  x++; break;
	}
	
	return display[y*DISPSIZE+x];
}

int returning(void)
{
	struct cross *last = &cpath[cpidx-1];
	int i;
	
	if(cpidx && last->x == posx && last->y == posy) {
		steps = last->steps;
		last->block[mov0^1] = 0;
		for(i = 0; i < 4; i++) 
			if(last->block[i] == '.') {
				mov = i;
				mov0 = i;
				return -2;
			}
		mov = last->ret;
		mov0 = mov;
		cpidx--;
		return 0;
	} else {
		for(i = 0; i < 4; i++)
			if(check_dir(i) == '.' && i != (mov0^1)) {
				mov = i;
				mov0 = i;
				return 0;
			}
	}
	
	if(start_pos == (posy*DISPSIZE+posx)) {
		mov = 99;
	}
	
	return 0;
}

int check_around(void)
{
	char block[4];
	int i, open = 0;
	
	for(i = 0; i < 4; i++) block[i] = check_dir(i);
	for(i = 0; i < 4; i++) if(block[i] == ' ') { mov = i; return 1; }
	for(i = 0; i < 4; i++) if(block[i] == '.') open++;
	
	if(open == 1) {
		for(i = 0; i < 4; i++)
			if(block[i] == '.') {
				mov = i;
				mov0 = i;
				return cpidx ? 2 : 0;
			}
	} else if(open == 2) {
		for(i = 0; i < 4; i++) 
			if(block[i] == '.' && i != (mov0^1)) {
				mov = i;
				mov0 = i;
				steps++;
				return 0;
			}
	} else if(open > 2) {
		cpath[cpidx].x   = posx;
		cpath[cpidx].y   = posy;
		cpath[cpidx].ret = mov0^1;
		cpath[cpidx].steps = ++steps;

		cpath[cpidx].block[0] = block[0];
		cpath[cpidx].block[1] = block[1];
		cpath[cpidx].block[2] = block[2];
		cpath[cpidx].block[3] = block[3];
		
		cpath[cpidx].block[mov0^1] = 0;
		
		for(i = 0; i < 4; i++) 
			if(block[i] == '.' && i != (mov0^1)) {
				mov = i;
				mov0 = i;
				break;
			}

		cpidx++;

		return 0;
	}
	
	return 0;
}

s64 data_in(void)
{
	switch(state) {
	case 0: state += check_around(); break;
	case 1: if(hitwall == 0) mov^=1; state = 0; break;
	case 2: state += returning(); break;
	}

	move(0);

	return mov+1;
}

void draw_output(void)
{
	SMALL_RECT region = {0,0,DISPSIZE-1,DISPSIZE-1};
	COORD bufsize = {DISPSIZE,DISPSIZE};
	COORD bufcoord = {0};
	
	int i;
	for(i = 0; i < (DISPSIZE*DISPSIZE); i++) {
		char c = display[i];
		
		switch(c) {
			case '#': c = 0xB1; output[i].Attributes = 0x0F; break;
			case '.': output[i].Attributes = 0x08; break;
			case 'o': output[i].Attributes = 0x09; break;
			default:  output[i].Attributes = 0x00; break;
		}
		
		output[i].Char.AsciiChar = c;
	}
	
	
	for(i = 0; i < cpidx; i++) {
		int j, o = 0, pos;
		for(j = 0; j < 4; j++)
			if(cpath[i].block[j] == '.') o++;

		pos = cpath[i].y * DISPSIZE + cpath[i].x;
		output[pos].Char.AsciiChar = '0' + o;
		output[pos].Attributes = 0x04;
	}
	
	if(oxygen_pos) {
		output[oxygen_pos].Char.AsciiChar = 'o';
		output[oxygen_pos].Attributes = 0x09;
	}
	
	output[start_pos].Char.AsciiChar = 0xF0;
	output[start_pos].Attributes = 0x0E;
	
	output[posy*DISPSIZE+posx].Char.AsciiChar = 'D';
	output[posy*DISPSIZE+posx].Attributes = 0x0E;
	
	WriteConsoleOutput(console, output, bufsize, bufcoord, &region);

	{
		char buffer[512];
		sprintf(buffer, "Steps: %d (%d), Oxygen steps: %d", steps, max_steps, oxygen_steps);
		SetConsoleTitle(buffer);
	}
}


void data_out(s64 out)
{
	int pos = posy*DISPSIZE+posx;
	hitwall = 0;
	
	switch(out) {
		case 0: display[pos] = '#'; move(1); hitwall = 1; break;
		case 1: display[pos] = '.'; break;
		case 2: display[pos] = '.'; oxygen_pos = pos; oxygen_steps = steps; break;
		default: printf("ERROR\n"); return;
	}
	
	if(steps > max_steps)
		max_steps = steps;
	
	draw_output();
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

void setup_console(void)
{
	SMALL_RECT rect = {0,0,1,1};
	COORD size = {DISPSIZE,DISPSIZE};

	console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleWindowInfo(console, TRUE, &rect);
	SetConsoleScreenBufferSize(console, size);
	SetConsoleActiveScreenBuffer(console);
	
	rect.Right  = DISPSIZE-1;
	rect.Bottom = DISPSIZE-1;
	
	if(!SetConsoleWindowInfo(console, TRUE, &rect)) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(console, &info);

		if(DISPSIZE > info.dwMaximumWindowSize.X) rect.Right  = info.dwMaximumWindowSize.X-1;
		if(DISPSIZE > info.dwMaximumWindowSize.Y) rect.Bottom = info.dwMaximumWindowSize.Y-1;

		SetConsoleWindowInfo(console, TRUE, &rect);
	}
}

int main(void)
{
	memset(display, ' ', sizeof(display));
	display[posy * DISPSIZE + posx] = '.';
	
	setup_console();
	
	run();
	
	max_steps = 0;
	mov0  =-1;
	mov   = 0;
	steps = 0;
	state = 0;
	cpidx = 0;

	posy = oxygen_pos/DISPSIZE;
	posx = oxygen_pos%DISPSIZE;

	while(1) {
		data_in();
		data_out(display[posy * DISPSIZE + posx] == '#' ? 0 : 1);
	}
	
	//steps amount is off by one, must increment
	
	return 0;
}