#include<stdio.h>
#include<math.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"gimli_cubes.h" // include cubes
#define R 7          //round
#define cube_num 229 //the number of cubes
#define n 256        //the dimension of matrix.
using namespace std;

uint32_t NONCE[4] = { 0 };
//uint32_t KEY[8]={0x01234567,0x89abcdef,0xfedcab98,0x76543210,0x02468ace,0x13579bdf,0xfdb97531,0xeca86420};//a fixed key

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
/* return the number of linear superpolys */
int read_matrix_file(uint8_t matrix[][n + 1], int* cube_flag)
{
	FILE* f = fopen("../gimli_get_linear_superpolys/gimli_superpolys_coef_matrix.txt", "r");
	int count_row = 0;
	if (f == NULL)
	{
		printf("Reading error, please check whether this file exists!!!\n");
	}
	else
	{
		char line_str[270];
		while (!feof(f))
		{
			int cube_NO = 0;
			fgets(line_str, 270, f);
			int count_char = 0;
			int comma_position;
			while (line_str[count_char] != '\n')
			{
				if (line_str[count_char] == ',')
					comma_position = count_char;
				count_char++;
			}

			for (int i = 0; i < comma_position; i++)
				cube_NO += (line_str[i] - '0') * pow(10, comma_position - 1 - i);
			cube_flag[cube_NO] = 1;

			for (int i = 0; i < n + 1; i++) 
				matrix[count_row][i] = (uint8_t)(line_str[i + comma_position + 1] - '0');
			count_row++;
		}
		fclose(f);
	}
	return count_row - 1;
}
void get_matrix(uint8_t matrix[][n + 1], int* cube_flag, uint32_t* key)
{
	int cur_row = 0;
	for (int number = 0; number < cube_num; number++)
	{
		if (cube_flag[number])
		{
			matrix[cur_row][n] ^= get_cube_sum(key, number);
			cur_row++;
		}
	}
}
void matrix_row_add(uint8_t matrix[][n + 1], int dst_row, int src_row)
{
	for (int col = 0; col < n + 1; col++)
	{
		matrix[dst_row][col] ^= matrix[src_row][col];
	}
}
void matrix_row_swap(uint8_t matrix[][n + 1], int dst_row, int src_row)
{
	uint8_t tmp_row[n + 1];
	memcpy(tmp_row, matrix[src_row], n + 1 * (sizeof(uint8_t)));
	memcpy(matrix[src_row], matrix[dst_row], n + 1 * (sizeof(uint8_t)));
	memcpy(matrix[dst_row], tmp_row, n + 1 * (sizeof(uint8_t)));
}
int nonzero_row_position(uint8_t matrix[][n + 1], int col, int cur_row, int matrix_row)
{
	int first_nonzero_row = -1;
	for (int row = cur_row; row < matrix_row; row++)
	{
		if (matrix[row][col])
		{
			first_nonzero_row = row;
			break;
		}
	}
	return first_nonzero_row;
}
uint8_t get_row_weight(uint8_t* row)
{
	uint8_t weight = 0;
	for (int i = 0; i < n; i++)
	{
		weight += row[i];
	}
	return weight;
}
uint8_t matrix_trans(uint8_t matrix[][n + 1], int matrix_row)
{
	uint8_t zero_col_num = 0;
	int first_nonzero_row;
	for (int col = 0; col < n; col++)
	{
		first_nonzero_row = nonzero_row_position(matrix, col, col - zero_col_num, matrix_row);
		if (first_nonzero_row >= col - zero_col_num)
		{
			matrix_row_swap(matrix, first_nonzero_row, col - zero_col_num);

			for (int row = 0; row < matrix_row; row++)
			{
				if ((row != (col - zero_col_num)) && (matrix[row][col] == 1))
				{
					matrix_row_add(matrix, row, col - zero_col_num);
				}
			}
		}
		else
		{
			zero_col_num++;
		}
	}
	uint8_t rank = 0;
	uint8_t weight[n] = { 0 };
	for (int i = 0; i < matrix_row; i++)
	{
		weight[i] = get_row_weight(matrix[i]);
		if (weight[i] > 0) rank++;
	}
	// FILE* f = fopen("matrix.txt", "w");
	// for (int i = 0; i < rank; i++) {
	// 	for (int j = 0; j < n + 1; j++)
	// 	{
	// 		fprintf(f, "%d ", matrix[i][j]);
	// 	}
	// 	fprintf(f, "\n");
	// }
	// fclose(f);
	printf("The rank of matrix is %d.\n", rank);
	return rank;
}
void solve_equations(uint8_t matrix[][n + 1], int* recovered_key, int rank)
{
	for (int row = 0; row < rank; row++)
	{
		for (int col = row; col < n; col++)
		{
			if (matrix[row][col] == 1)
			{
				if (get_row_weight(matrix[row]) == 1)
					recovered_key[col] = matrix[row][n];
				else
					recovered_key[col] = 2;
				break;
			}
		}
	}
}

void print_recovered_key(int* recovered_key, uint32_t* key, int rank)
{
	int right_key_num = 0;
	printf("%d key bits have been recovered, comparision with master key is shown as follow.\n"
		"\"?\" represents the unknown key bit, \"*\" represents the recovered key bit which is determined by the unknown bits.\n\n", rank);
	for (int i = 0; i < 8; i++)
	{
		printf("The master key K[%d]: ", i);
		for (int j = 0; j < 32; j++)
		{
			printf("%d", (key[i] >> (31 - j)) & 1);
		}
		printf(";\n");
		printf("Our recovered K[%d]:  ", i);
		for (int j = 0; j < 32; j++)
		{
			if (recovered_key[32 * i + j] > -1 && recovered_key[32 * i + j] < 2)
				printf("%d", recovered_key[32 * i + j]);
			else if (recovered_key[32 * i + j] == 2)
				printf("*");
			else
				printf("?");
		}
		printf(";\n\n");
	}
}
void trav_remaining_key(uint8_t matrix[][n+1], int* recovered_key, uint32_t* key, uint8_t matrix_rank)
{
	uint8_t re_key_num = 0;
	uint8_t* re_key_bit = new uint8_t[n - matrix_rank];
	uint8_t  unsure_key_num = 0;
	uint32_t tmp_key[8] = { 0 };
	for (int i = 0; i < n; i++)
	{
		if (recovered_key[i] < 0)
		{
			re_key_bit[re_key_num] = i;
			re_key_num++;
		}
		else if (recovered_key[i] > 1)
			unsure_key_num++;
		else
			tmp_key[i / 32] ^= recovered_key[i] << (31 - i % 32);
	}
	uint8_t* unsure_key_bit_row = new uint8_t[unsure_key_num];
	uint8_t* unsure_key_bit_col = new uint8_t[unsure_key_num];
	int count_unsure_key = 0;
	for (int row = 0; row < matrix_rank; row++)
	{
		if (get_row_weight(matrix[row]) > 1)
		{	
			unsure_key_bit_row[count_unsure_key] = row;
			for (int col = row; col < n; col++)
				if (matrix[row][col]) 
				{
					unsure_key_bit_col[count_unsure_key] = col;
					break;
				}
			count_unsure_key++;
		}
	}
	uint32_t state[12] = { 0 };
	uint32_t test_state[12];
	memcpy(state + 4 , key, 8 * sizeof(uint32_t));
	gimli_encrypt(state);
	for (int i = 0; i < 1<<re_key_num; i++)
	{
		uint32_t candidate_key[8];
		memcpy(candidate_key, tmp_key, 8 * sizeof(uint32_t));
		memset(test_state, 0, 4 * sizeof(uint32_t));
		for (int j = 0; j < re_key_num; j++) recovered_key[re_key_bit[j]] = 1 & (i >> (re_key_num - 1 - j));
		for (int j = 0; j < re_key_num; j++) candidate_key[re_key_bit[j] / 32] ^= recovered_key[re_key_bit[j]] << (31 - re_key_bit[j] % 32);
		for (int j = 0; j < unsure_key_num; j++)
		{
			recovered_key[unsure_key_bit_col[j]] = 0;
			for (int col = unsure_key_bit_col[j] + 1; col < n+1; col++)
			{
				if (matrix[unsure_key_bit_row[j]][col])
					recovered_key[unsure_key_bit_col[j]] ^= matrix[unsure_key_bit_row[j]][col];
			}
			candidate_key[unsure_key_bit_col[j] / 32] ^= recovered_key[unsure_key_bit_col[j]] << (31 - unsure_key_bit_col[j] % 32);
		}
		memcpy(test_state + 4, candidate_key, 8 * sizeof(uint32_t));
		gimli_encrypt(test_state);
		bool flag = true;
		for (int j = 0; j < 12; j++) {
			if (state[j] != test_state[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			printf("The master key has been recovered: ");
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					if (((candidate_key[j] >> ((7 - k) * 4)) & 0xf) > 0)
					{
						printf("%lx", candidate_key[j]);
						break;
					}
					else
						printf("0");
				}
			}
			printf("\n");
			break;
		}
	}
	delete[] re_key_bit, unsure_key_bit_row, unsure_key_bit_col;
}
int main() {
	time_t start, end;
	
	uint8_t matrix[n][n + 1] = { 0 };
	int cube_flag[cube_num] = { 0 };
	//uint32_t key[8] = {0x01234567,0x89abcdef,0x02468ace,0x13579bdf,0xfdb97531,0xeca86420,0xfedcba98,0x76543210};
	uint32_t key[8];
	int recovered_key[n];
	memset(recovered_key, -1, n * (sizeof(int)));

	printf("******************************************************************\n");
	printf("***************** Cube attack on 7-round GIMLI *******************\n");
	printf("******************************************************************\n");
	printf("Please input a 256-bit master key (64 hexadecimal digits, enter 8 digits per line):\n");
	for (int i = 0; i < 8; i++) scanf("%lx", &key[i]);
	start = time(NULL);
	printf("The master key is: ");
	for (int j = 0; j < 8; j++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (((key[j] >> ((7 - k) * 4)) & 0xf) > 0)
			{
				printf("%lx", key[j]);
				break;
			}
			else
				printf("0");
		}
	}
	printf("\n\n");

	printf("******************************************************************\n");
	printf("*********** Solving the system of linear equations. **************\n");
	printf("******************************************************************\n");

	int matrix_row = read_matrix_file(matrix, cube_flag);
	
	get_matrix(matrix, cube_flag, key); /* get the matrix of coefficients of linear equation system. */

	uint8_t matrix_rank = matrix_trans(matrix, matrix_row);

	solve_equations(matrix, recovered_key, matrix_rank);

	print_recovered_key(recovered_key, key, matrix_rank);

	printf("******************************************************************\n");
	printf("*********** Exhausted searching for remaining key bits. **********\n");
	printf("******************************************************************\n");

	trav_remaining_key(matrix, recovered_key, key, matrix_rank);

	end = time(NULL);
	printf("This program takes: %d s\n", end - start);
	return 0;
}
