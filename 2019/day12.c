/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>

typedef unsigned __int64 u64;
typedef unsigned __int32 u32;
typedef unsigned __int16 u16;
typedef unsigned __int8  u8;

struct ivec3 { int x, y, z; } vel[4];

#include "day12_data.c"

#define INPUT input
#define ABS(x) (x<0?-x:x)

struct ivec3 compare(struct ivec3 *a, struct ivec3 *b)
{
	struct ivec3 out;
	
	out.x = b->x > a->x ? 1 : (b->x < a->x ? -1 : 0);
	out.y = b->y > a->y ? 1 : (b->y < a->y ? -1 : 0);
	out.z = b->z > a->z ? 1 : (b->z < a->z ? -1 : 0);

	return out;
}


void run1(void)
{
	int i,j,step;
	int energy = 0;
	
	for(step = 0; step < 1001; step++) {
		
		//printf("STEP %d:\n", step);
		//printf("\tp(%d,%d,%d) v(%d,%d,%d)\n",INPUT[0].x,INPUT[0].y,INPUT[0].z,vel[0].x,vel[0].y,vel[0].z);
		//printf("\tp(%d,%d,%d) v(%d,%d,%d)\n",INPUT[1].x,INPUT[1].y,INPUT[1].z,vel[1].x,vel[1].y,vel[1].z);
		//printf("\tp(%d,%d,%d) v(%d,%d,%d)\n",INPUT[2].x,INPUT[2].y,INPUT[2].z,vel[2].x,vel[2].y,vel[2].z);
		//printf("\tp(%d,%d,%d) v(%d,%d,%d)\n",INPUT[3].x,INPUT[3].y,INPUT[3].z,vel[3].x,vel[3].y,vel[3].z);
		if(step == 1000) break;
		
		for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			struct ivec3 diff = compare(&INPUT[i], &INPUT[j]);
			
			vel[i].x += diff.x;
			vel[i].y += diff.y;
			vel[i].z += diff.z;
		}
		
		for(i = 0; i < 4; i++) {
			INPUT[i].x += vel[i].x;
			INPUT[i].y += vel[i].y;
			INPUT[i].z += vel[i].z;
		}
	}
	
	for(i = 0; i < 4; i++) {
		int pot = ABS(INPUT[i].x) + ABS(INPUT[i].y) + ABS(INPUT[i].z);
		int kin = ABS(vel[i].x) + ABS(vel[i].y) + ABS(vel[i].z);
		energy += pot * kin;
	}
	
	printf("Total energy: %d\n", energy);
}

int main(void)
{
	int i,j;
	u64 step = 0, step3[3] = {0}, repeat[3] = {0};
	struct ivec3 start[4];

	for(i = 0; i < 4; i++){
		start[i] = INPUT[i];
	}
	
	while(1) {
		struct ivec3 equal = {1,1,1};
		
		for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			struct ivec3 diff = compare(&INPUT[i], &INPUT[j]);
			
			vel[i].x += diff.x;
			vel[i].y += diff.y;
			vel[i].z += diff.z;
		}
		
		for(i = 0; i < 4; i++) {
			INPUT[i].x += vel[i].x;
			INPUT[i].y += vel[i].y;
			INPUT[i].z += vel[i].z;
		}
		
		step++;
		
		for(i = 0; i < 4; i++) {
			equal.x &= INPUT[i].x == start[i].x;
			equal.y &= INPUT[i].y == start[i].y;
			equal.z &= INPUT[i].z == start[i].z;
		}
		
		if(equal.x) {
			u64 s = step - step3[0];
			if(s > repeat[0]) repeat[0] = s+1;
			step3[0] = step;
		}
			
		if(equal.y) {
			u64 s = step - step3[1];
			if(s > repeat[1]) repeat[1] = s+1;
			step3[1] = step;
		}
		
		if(equal.z) {
			u64 s = step - step3[2];
			if(s > repeat[2]) repeat[2] = s+1;
			step3[2] = step;
		}
		
		
		if(equal.x || equal.y || equal.z) {
			printf("\rRepeat pattern: %llu, %llu, %llu", repeat[0], repeat[1], repeat[2]);
		}
		
		if(equal.x && equal.y && equal.z) {
			printf("\n");
			step++;
			break;
		}
	}
	
	printf("Takes %llu steps for the cycle to repeat. ", step);
	
	return 0;
}