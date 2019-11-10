#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"morus_cubes.h"
#include"morus_encrypt.h"
#include"generate_random_value_using_AES.h"
#define T 100
#define n 128
#define cube_num 111
state_word c[3] = {
	{0xdb3d18556dc22ff1,0x2011314273b528dd},
	{0x000101020305080d,0x1522375990e97962},
	{0xffffffffffffffff,0xffffffffffffffff}
};
struct linear_poly {
	uint8_t coef[n + 1];
	bool flag = true;
};
state_word get_nonce(int value, int number) {
	int cube_size = cube[number][0];
	state_word nonce = { 0 };
	for (int j = 1; j < cube_size + 1; j++) {
		nonce.m[cube[number][j] / 64] ^= ((uint64_t)(1 & (value >> (cube_size - j)))) << (63 - cube[number][j] % 64);
	}
	return nonce;
}
int get_cube_sum(state_word key, int number) {
	int cube_size = cube[number][0];
	state_word cube_sum = { 0 };
	state_word S[5];
	for (int i = 0; i < (1 << cube_size); i++) {
		S[4] = c[0];
		S[3] = c[1];
		S[2] = c[2];
		S[1] = key;
		S[0] = get_nonce(i, number);
		cube_sum = state_xor(output_ciphertext(S, 4), cube_sum);
	}
	return (cube_sum.m[output[number] / 64] >> (63 - output[number] % 64)) & 1;
}
bool linearity_test(int number)
{
	state_word random_key[3] = { 0 };
	int constant;
	constant = get_cube_sum(random_key[0], number);
	bool boolean = true;
	for (int i = 0; i < T; i++)
	{
		random_key[0].m[0] = get_random_value();
		random_key[0].m[1] = get_random_value();
		random_key[1].m[0] = get_random_value();
		random_key[1].m[1] = get_random_value();
		random_key[2] = state_xor(random_key[0], random_key[1]);

		if ((get_cube_sum(random_key[0], number) ^ get_cube_sum(random_key[1], number)) != (get_cube_sum(random_key[2], number) ^ constant)) {
			boolean = false;
			break;
		}
	}
	return boolean;
}
void get_one_superpoly(linear_poly& superpoly, int number)
{
	state_word unit_key = { 0 };
	superpoly.coef[n] = get_cube_sum(unit_key, number);
	for (int i = 0; i < n; i++)
	{
		unit_key.m[1 ^ (i / 64)] = 0x0000000000000000;
		unit_key.m[i / 64] = ((uint64_t)1) << (63 - i % 64);
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
	FILE* f = fopen("morus_superpolys_coef_matrix.txt", "w");
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

	printf("*********************************MORUS******************************\n");
	printf("****************** Linearity test for the 111 cubes ****************\n");
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

