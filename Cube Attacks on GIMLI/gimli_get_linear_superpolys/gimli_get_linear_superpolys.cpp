#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"gimli_cubes.h"
#include"generate_random_value_using_AES.h" //
#define R 7          //round
#define cube_num 229 //the number of cubes
#define n 256        //the dimension of matrix.
#define T 100        // for each cube, run T times liearity test
using namespace std;

struct linear_poly {
	uint8_t coef[n + 1];
	bool flag = true;
};
uint32_t NONCE[4] = { 0 };

uint32_t word_rotate(uint32_t word, int rot) {
	if (rot == 0) return word;
	else return (word << rot) | (word >> (32 - rot));
}

void gimli_encrypt(uint32_t* state) {
	int round, column;
	uint32_t x, y, z;
	for (round = 0; round < R; round++) {
		for (column = 0; column < 4; column++) {
			x = word_rotate(state[column], 24);
			y = word_rotate(state[4 + column], 9);
			z = state[8 + column];
			state[8 + column] = x ^ (z << 1) ^ ((y & z) << 2);
			state[4 + column] = y ^ x ^ ((x | z) << 1);
			state[column] = z ^ y ^ ((x & y) << 3);
		}
		if (((24 - round) & 3) == 0) { // small swap: pattern s...s...s... etc.
			x = state[0]; state[0] = state[1]; state[1] = x;
			x = state[2]; state[2] = state[3]; state[3] = x;
		}
		if (((24 - round) & 3) == 2) { // big swap: pattern ..S...S...S. etc.
			x = state[0]; state[0] = state[2]; state[2] = x;
			x = state[1]; state[1] = state[3]; state[3] = x;
		}
		if (((24 - round) & 3) == 0) // add constant: pattern c...c...c... etc.
			state[0] ^= (0x9e377900 | (24 - round));
	}
}
void get_nonce(int value, int number) {
	int temp;
	int cube_size = cube[number][0];
	for (int i = 0; i < 4; i++) NONCE[i] = 0;
	for (int j = 1; j < cube_size + 1; j++) {
		temp = 1 & (value >> (cube_size - j));
		NONCE[cube[number][j] / 32] ^= (temp << (31 - cube[number][j] % 32));
	}
}
int get_cube_sum(uint32_t* k, int number) {
	uint32_t cube_sum[4] = { 0 }, state[12];
	int cube_size = cube[number][0];
	for (int i = 0; i < 1 << cube_size; i++) {
		get_nonce(i, number);
		for (int j = 0; j < 4; j++) {
			state[j] = NONCE[j];
			state[j + 4] = k[j];
			state[j + 8] = k[j + 4];
		}
		gimli_encrypt(state);
		for (int j = 0; j < 4; j++) cube_sum[j] ^= state[j];
	}
	return 1 & (cube_sum[output[number] / 32] >> (31 - output[number] % 32));
}

bool linearity_test(int number) {
	uint32_t random_key[3][8] = { 0 }, constant;
	constant = get_cube_sum(random_key[0], number);
	bool boolean = true;
	for (int i = 0; i < T; i++) {
		for (int j = 0; j < 8; j++) {
			random_key[0][j] = get_random_value();
			random_key[1][j] = get_random_value();
			random_key[2][j] = random_key[1][j] ^ random_key[0][j];
		}
		if ((get_cube_sum(random_key[0], number) ^ get_cube_sum(random_key[1], number)) != (get_cube_sum(random_key[2], number) ^ constant)) {
			boolean = false;
			break;
		}
	}
	return boolean;
}

void get_one_superpoly(linear_poly& superpoly, int number) {
	uint32_t unit_key[8] = { 0 };
	superpoly.coef[n] = get_cube_sum(unit_key, number);
	for (int i = 0; i < n; i++)
	{
		memset(unit_key, 0, 8 * (sizeof(uint32_t)));
		unit_key[i / 32] = 1 << (31 - i % 32);
		superpoly.coef[i] = get_cube_sum(unit_key, number) ^ superpoly.coef[n];
	}
}
void get_superpolys(linear_poly* superpoly)
{
	for (int number = 0; number < cube_num; number++)
	{
		if (linearity_test(number))
		{
			get_one_superpoly(superpoly[number], number);
		}
		else
		{
			superpoly[number].flag = false;
			printf("The superpoly of one cube is not linear!!!\n");
		}
	}
}
int get_linear_superpolys_num(linear_poly* superpoly)
{
	int num = 0;
	for (int i = 0; i < cube_num; i++)
	{
		if (superpoly[i].flag) num++;
	}
	return num;
}
void write_superpolys_coef_matrix(linear_poly* superpoly)
{
	FILE* f = fopen("gimli_superpolys_coef_matrix.txt","w");
	for (int i = 0; i < cube_num; i++)
	{
		if (superpoly[i].flag)
		{
			fprintf(f, "%d,", i);
			for (int j = 0; j < n + 1; j++)
			{
				fprintf(f, "%d", superpoly[i].coef[j]);
			}
			fprintf(f, "\n");
		}
	}
	fclose(f);
}

int main() {
	time_t start, end;
	start = time(NULL);
	linear_poly superpoly[cube_num];

	printf("*****************************GIMLI**********************************\n");
	printf("****************** Linearity test for the 229 cubes ****************\n");
	printf("********************************************************************\n");
	printf("The linearity test is running, it will take some time......\n\n");

	get_superpolys(superpoly);
	
	write_superpolys_coef_matrix(superpoly);

	int linear_superpolys_num = get_linear_superpolys_num(superpoly);
	printf("The linearity test finished, we have obtianed %d linear superpolys.\n", linear_superpolys_num);
	printf("The serial number of cube that can get linear superpoly and "
		   "the coefficient matrix of these superpolys has been written into a text file.\n");

	end = time(NULL);

	printf("*****************************************************************\n");
	printf("This program takes: %d s\n", end - start);
	return 0;
}
