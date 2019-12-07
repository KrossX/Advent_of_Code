/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>
#include <stdlib.h>

#include "day07_data.c"
#define INPUT_BUFFER input

int run_amp(int *buffer, int buffer_size, int phase, int *signal)
{
	int data_in = 0;
	int pc = 0;
	
	while(1) {
		int op = buffer[pc+0];
		int n1 = buffer[pc+1];
		int n2 = buffer[pc+2];
		int n3 = buffer[pc+3];
		int m1 = op /   100;
		int m2 = op /  1000;
		int m3 = op / 10000;
		
		op %= 100;
		m1 -= (m1/10) * 10;
		m2 -= (m2/10) * 10;
		m3 -= (m3/10) * 10;
		
		//printf("%3d [%4d, %4d, %4d, %4d, %4d, %4d] ", pc, buffer[pc+0],buffer[pc+1],buffer[pc+2],buffer[pc+3],buffer[pc+4],buffer[pc+5]);
		//printf("OP: %d, %d, %d, %d, %d, %d, %d\n", op, n1, n2, n3, m1, m2, m3);
		
		if(op == 99) {
			//printf("Program Stopped.\n");
			return 1;
		} else if((op == 1 || op == 2) && (
		          (m1 == 0 && (n1 < 0 || n1 >= buffer_size)) || 
		          (m2 == 0 && (n2 < 0 || n2 >= buffer_size)) || 
				  (m3 == 0 && (n3 < 0 || n3 >= buffer_size)))) {
			printf("Error! Overflow. %d %d %d\n", n1, n2, n3);
		} else if((op == 3 || op == 4) && (
		          (m1 == 0 && (n1 < 0 || n1 >= buffer_size)))) {
			printf("Error! Overflow. %d\n", n1);
		}

		switch(op) {
		case 1: buffer[n3] = (m1?n1:buffer[n1]) + (m2?n2:buffer[n2]); pc += 4; break;
		case 2: buffer[n3] = (m1?n1:buffer[n1]) * (m2?n2:buffer[n2]); pc += 4; break;
		case 3: buffer[n1] = data_in ? *signal : phase; data_in++; data_in &= 1; pc += 2; break;
		case 4: *signal = m1?n1:buffer[n1]; pc += 2; break;
		case 5: if(m1?n1:buffer[n1]) pc = m2?n2:buffer[n2]; else pc += 3; break;
		case 6: if((m1?n1:buffer[n1]) == 0) pc = m2?n2:buffer[n2]; else pc += 3; break;
		case 7: buffer[n3] = (m1?n1:buffer[n1]) < (m2?n2:buffer[n2]) ? 1 : 0; pc += 4; break;
		case 8: buffer[n3] = (m1?n1:buffer[n1]) == (m2?n2:buffer[n2]) ? 1 : 0; pc += 4; break;
		default: printf("Unknown Opcode: %d\n", op); return -1;
		}
	}

	return 0;
}

int run_amp2(int *buffer, int buffer_size, int *pc, int data_in, int *data_out)
{
	while(1) {
		int op = buffer[*pc+0];
		int n1 = buffer[*pc+1];
		int n2 = buffer[*pc+2];
		int n3 = buffer[*pc+3];
		int m1 = op /   100;
		int m2 = op /  1000;
		int m3 = op / 10000;
		
		op %= 100;
		m1 -= (m1/10) * 10;
		m2 -= (m2/10) * 10;
		m3 -= (m3/10) * 10;
		
		if(op == 99) {
			//printf("Program Stopped.\n");
			return 1;
		} else if((op == 1 || op == 2) && (
		          (m1 == 0 && (n1 < 0 || n1 >= buffer_size)) || 
		          (m2 == 0 && (n2 < 0 || n2 >= buffer_size)) || 
				  (m3 == 0 && (n3 < 0 || n3 >= buffer_size)))) {
			printf("Error! Overflow. %d %d %d\n", n1, n2, n3);
		} else if((op == 3 || op == 4) && (
		          (m1 == 0 && (n1 < 0 || n1 >= buffer_size)))) {
			printf("Error! Overflow. %d\n", n1);
		}

		switch(op) {
		case 1: buffer[n3] = (m1?n1:buffer[n1]) + (m2?n2:buffer[n2]); *pc += 4; break;
		case 2: buffer[n3] = (m1?n1:buffer[n1]) * (m2?n2:buffer[n2]); *pc += 4; break;
		case 3: buffer[n1] = data_in; *pc += 2; return 3;
		case 4: *data_out = m1?n1:buffer[n1]; *pc += 2; return 2;
		case 5: if(m1?n1:buffer[n1]) *pc = m2?n2:buffer[n2]; else *pc += 3; break;
		case 6: if((m1?n1:buffer[n1]) == 0) *pc = m2?n2:buffer[n2]; else *pc += 3; break;
		case 7: buffer[n3] = (m1?n1:buffer[n1]) < (m2?n2:buffer[n2]) ? 1 : 0; *pc += 4; break;
		case 8: buffer[n3] = (m1?n1:buffer[n1]) == (m2?n2:buffer[n2]) ? 1 : 0; *pc += 4; break;
		default: printf("Unknown Opcode: %d\n", op); return -1;
		}
	}

	return 0;
}

void run(void)
{
	int phase[5];
	int max_signal = -99999;
	int buffer_size = sizeof(INPUT_BUFFER) / 4;
	int *buffer = malloc(buffer_size * 4 * 5);
	
	if(!buffer) {
		printf("Error! Could not allocate buffer.\n");
		return;
	}
	
	for(phase[0] = 0; phase[0] < 5; phase[0]++)
	for(phase[1] = 0; phase[1] < 5; phase[1]++)
	for(phase[2] = 0; phase[2] < 5; phase[2]++)
	for(phase[3] = 0; phase[3] < 5; phase[3]++)
	for(phase[4] = 0; phase[4] < 5; phase[4]++) {
		int count[5] = {0};
		int signal = 0;
		int i;
		
		for(i = 0; i < 5; i++) count[phase[i]]++;
		for(i = 0; i < 5; i++) if(count[i] > 1) signal = -1;
		if(signal < 0) continue;
		
		for(i = 0; i < 5; i++)
			memcpy(&buffer[buffer_size*i], INPUT_BUFFER, buffer_size*4);
		
		for(i = 0; i < 5; i++)
			run_amp(&buffer[buffer_size*i], buffer_size, phase[i], &signal);

		if(signal > max_signal)
			max_signal = signal;
	}
	
	printf("\nMax signal: %d\n", max_signal);
}

void run2(void)
{
	int phase[5];
	int max_signal = 0;
	int buffer_size = sizeof(INPUT_BUFFER) / 4;
	int *buffer = malloc(buffer_size * 4 * 5);
	
	if(!buffer) {
		printf("Error! Could not allocate buffer.\n");
		return;
	}
	
	for(phase[0] = 5; phase[0] < 10; phase[0]++)
	for(phase[1] = 5; phase[1] < 10; phase[1]++)
	for(phase[2] = 5; phase[2] < 10; phase[2]++)
	for(phase[3] = 5; phase[3] < 10; phase[3]++)
	for(phase[4] = 5; phase[4] < 10; phase[4]++) {
		int pc[5] = {0};
		int checked[5] = {0};
		int count[5] = {0};
		int signal = 0, running = 1;
		int i;
		
		for(i = 0; i < 5; i++) count[phase[i]-5]++;
		for(i = 0; i < 5; i++) if(count[i] > 1) signal = -1;
		if(signal < 0) continue;
		
		for(i = 0; i < 5; i++)
			memcpy(&buffer[buffer_size*i], INPUT_BUFFER, buffer_size*4);
		
		while(running) {
			for(i = 0; i < 5;) {
				int ret = run_amp2(&buffer[buffer_size*i], buffer_size, &pc[i], checked[i]? signal : phase[i], &signal);
				if(ret == 3) checked[i] = 1;
				if(ret == 2) i++;
				if(ret == 1) { i++; running = 0; }
				if(ret < 0) return;
			}
		}
		
		if(signal > max_signal)
			max_signal = signal;
	}
	
	printf("\nMax signal #2: %d\n", max_signal);
}


int main(void)
{
	run2();

	return 0;
}