/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdlib.h>
#include <stdio.h>

typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

#define INPUT_SIZE 16384
#include "day23_data.c"

#define param(X) (m##X==0?buf[n##X]:(m##X==1?n##X:buf[n##X+rel]))
#define param_out(X) (buf[n##X+(m##X==2?rel:0)])

struct state {
	int id;
	int idle;
	s64 pc;
	s64 rel;
	s64 *buf;
	s64 *buf_in;
	s64 *buf_out;
	int inr, inw, outx;
} device[50];

s64 nat_packet[2];

s64 data_in(struct state *s)
{
	s64 in = -1;
	
	if(s->inr != s->inw) {
		in = s->buf_in[s->inr++]; s->inr &= 0x3FF;
		//printf("%d) IN (%d) %llu\n", s->id, s->inr, in);
		s->idle = 0;
	} else {
		s->idle = 1;
	}
	
	return in;
}

void send_packet(int id, s64 x, s64 y)
{
	if(id < 50) {
		struct state *r = &device[id];
		r->buf_in[r->inw++] = x; r->inw &= 0x3FF;
		r->buf_in[r->inw++] = y; r->inw &= 0x3FF;
	} else if(id == 255) {
		nat_packet[0] = x;
		nat_packet[1] = y;
	}
}

void data_out(struct state *s, s64 out)
{
	s->buf_out[s->outx++] = out;
	//printf("%d) OUT %llu\n", s->id, out);
	
	if(s->outx == 3) {
		s->outx = 0;
		send_packet(s->buf_out[0], s->buf_out[1], s->buf_out[2]);

		printf("%d) OUT PACKET %llu, ", s->id, s->buf_out[0]);
		printf("%llu, ", s->buf_out[1]);
		printf("%llu\n", s->buf_out[2]);
	}
}

int run(struct state *s)
{
	s64 pc   = s->pc;
	s64 rel  = s->rel;
	s64 *buf = s->buf;
	
	s64 op = buf[pc+0];
	s64 n1 = buf[pc+1];
	s64 n2 = buf[pc+2];
	s64 n3 = buf[pc+3];
	s64 m1 = op /   100;
	s64 m2 = op /  1000;
	s64 m3 = op / 10000;
	
	op %= 100;
	m1 -= (m1/10) * 10;
	m2 -= (m2/10) * 10;
	m3 -= (m3/10) * 10;
	
	if(op == 99) {
		printf("Program Stopped.\n");
		return 0;
	} else if((op == 1 || op == 2) && (
			  (m1 == 0 && (n1 < 0 || n1 >= INPUT_SIZE)) || 
			  (m2 == 0 && (n2 < 0 || n2 >= INPUT_SIZE)) || 
			  (m3 == 0 && (n3 < 0 || n3 >= INPUT_SIZE)))) {
		printf("Error! Overflow. %lld %lld %lld\n", n1, n2, n3);
		return 0;
	} else if((op == 3 || op == 4) && (
			  (m1 == 0 && (n1 < 0 || n1 >= INPUT_SIZE)))) {
		printf("Error! Overflow. %lld\n", n1);
		return 0;
	}
	
	switch(op) {
	case 1: param_out(3) = param(1) + param(2); pc += 4; break;
	case 2: param_out(3) = param(1) * param(2); pc += 4; break;
	case 3: param_out(1) = data_in(s); pc += 2; break;
	case 4: data_out(s,param(1)); pc += 2; break;
	case 5: if(param(1)) pc = param(2); else pc += 3; break;
	case 6: if(param(1) == 0) pc = param(2); else pc += 3; break;
	case 7: param_out(3) = param(1) < param(2) ? 1 : 0; pc += 4; break;
	case 8: param_out(3) = param(1) == param(2) ? 1 : 0; pc += 4; break;
	case 9: rel += param(1); pc += 2; break;
	default: printf("Unknown Opcode: %lld\n", op); return 0;
	}
	
	s->pc  = pc;
	s->rel = rel;
	
	return 1;
}

int main(void)
{
	int i;
	for(i = 0; i < 50; i++) {
		device[i].id = i;
		device[i].buf_in = malloc(512 * 8);
		device[i].buf_out = malloc(512 * 8);
		device[i].buf = malloc(sizeof(input));
		memcpy(device[i].buf, input, sizeof(input));
		
		device[i].buf_in[0] = i;
		device[i].inw = 1;
	}
	
	while(1) {
		int idle_delay;
		int all_on     = 1;
		int all_idle   = 1;
		
		for(i = 0; i < 50; i++) {
			all_on &= run(&device[i]);
			all_idle &= device[i].idle;
		}

		if(!all_on) break;
		
		idle_delay = all_idle? idle_delay + 1 : 0;
		if(idle_delay > 100)
		{
			static s64 prevy = -1;
			idle_delay = 0;
			printf("Network idle! Sending packet to 0: %llu", nat_packet[0]);
			printf(" %llu\n", nat_packet[1]);
			send_packet(0, nat_packet[0], nat_packet[1]);
			
			if(prevy == nat_packet[1]) return 0; // part2 number
			else prevy = nat_packet[1];
		}
	}
	
	return 0;
}