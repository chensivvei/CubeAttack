#include<iostream>
#include<math.h>
#include<string.h>
#include<time.h>
#include"morus_cubes.h"
#include"morus_encrypt.h"
#define n 128
#define cube_num 111
state_word c[3] = {
	{0xdb3d18556dc22ff1,0x2011314273b528dd},
	{0x000101020305080d,0x1522375990e97962},
	{0xffffffffffffffff,0xffffffffffffffff}
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
/* return the number of linear superpolys */
int read_matrix_file(uint8_t matrix[][n + 1], int* cube_flag)
{
	FILE* f = fopen("../morus_get_linear_superpolys/morus_superpolys_coef_matrix.txt", "r");
	int count_row = 0;
	if (f == NULL)
	{
		printf("Reading error, please check whether this file exists!!!\n");
	}
	else
	{
		char line_str[140];
		while (!feof(f))
		{
			int cube_NO = 0;
			fgets(line_str, 140, f);
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
void get_matrix(uint8_t matrix[][n + 1], int* cube_flag, state_word key)
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
void print_recovered_key(int* recovered_key, state_word key, int rank)
{
	printf("%d key bits have been recovered, comparision with master key is shown as follow.\n"
		"\"?\" represents the unknown key bit, \"*\" represents the recovered key bit which is determined by the unknow bits.\n\n", rank);
	for (int i = 0; i < 2; i++)
	{
		printf("The master K[%d]:    ", i);
		for (int j = 0; j < 64; j++)
			printf("%d", (key.m[i] >> (63 - j)) & 1);
		printf(";\n");
		printf("Our recovered K[%d]: ", i);
		for (int j = 0; j < 64; j++)
		{
			if (recovered_key[64 * i + j] > -1 && recovered_key[64 * i + j] < 2)
				printf("%d", recovered_key[64 * i + j]);
			else if (recovered_key[64 * i + j] == 2)
				printf("*");
			else
				printf("?");
		}
		printf(";\n\n");
	}
}
void trav_remaining_key(uint8_t matrix[][n + 1], int* recovered_key, state_word key, uint8_t matrix_rank)
{
	uint8_t re_key_num = 0;
	uint8_t* re_key_bit = new uint8_t[n - matrix_rank];
	uint8_t  unsure_key_num = 0;
	state_word tmp_key = { 0 };
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
			tmp_key.m[i / 64] ^= ((uint64_t)recovered_key[i]) << (63 - i % 64);
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
			{
				if (matrix[row][col])
				{
					unsure_key_bit_col[count_unsure_key] = col;
					break;
				}
			}
			count_unsure_key++;
		}
	}
	state_word state[5] = { {0xffffffffffffffff,0xffffffffffffffff},key,c[2],c[1],c[0] };
	state_word test_state[5],tmp_state[5];
	memcpy(tmp_state, state, 5 * sizeof(state_word));
	state_word ciphertext, test_ciphertext, candidate_key;
	ciphertext = output_ciphertext(state, 4);
	for (int i = 0; i < 1 << re_key_num; i++)
	{
		candidate_key = tmp_key;
		for (int j = 0; j < re_key_num; j++) recovered_key[re_key_bit[j]] = 1 & (i >> (re_key_num - 1 - j));
		for (int j = 0; j < re_key_num; j++) candidate_key.m[re_key_bit[j] / 64] ^= ((uint64_t)recovered_key[re_key_bit[j]]) << (63 - re_key_bit[j] % 64);
		for (int j = 0; j < unsure_key_num; j++)
		{
			recovered_key[unsure_key_bit_col[j]] = 0;
			for (int col = unsure_key_bit_col[j] + 1; col < n + 1; col++)
			{
				if (matrix[unsure_key_bit_row[j]][col])
					recovered_key[unsure_key_bit_col[j]] ^= matrix[unsure_key_bit_row[j]][col];
			}
			candidate_key.m[unsure_key_bit_col[j] / 64] ^= ((uint64_t)recovered_key[unsure_key_bit_col[j]]) << (63 - unsure_key_bit_col[j] % 64);
		}
		memcpy(test_state, tmp_state, 5 * sizeof(state_word));
		test_state[1] = candidate_key;
		test_ciphertext = output_ciphertext(test_state, 4);
		bool flag = true;
		for (int j = 0; j < 2; j++) 
		{
			if (ciphertext.m[j] != test_ciphertext.m[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			//printf("%d\n", i);
			printf("The master key has been recovered: ");
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					if (((candidate_key.m[j] >> ((15 - k) * 4)) & 0xf) > 0)
					{
						printf("%llx", candidate_key.m[j]);
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
	start = time(NULL);
	uint8_t matrix[n][n + 1] = { 0 };
	int cube_flag[cube_num] = { 0 };
	//state_word key = { 0x0123456789abcdef,0xfedcba9876543210 };
	state_word key;
	int recovered_key[n];
	memset(recovered_key, -1, n * (sizeof(int)));

	printf("******************************************************************\n");
	printf("*************** Cube attack on 4.4-step MORUS *******************\n");
	printf("******************************************************************\n");
	

	printf("Input a 128-bit master key (32 hexadecimal digits, enter 16 digits per line):\n");
	for (int i = 0; i < 2; i++) scanf("%llx", &key.m[i]);
	//printf("\n");
	printf("The master key is: ");
	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			if (((key.m[j] >> ((15 - k) * 4)) & 0xf) > 0)
			{
				printf("%llx", key.m[j]);
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
	printf("*********** Exhaustive searching for remaining key bits. **********\n");
	printf("******************************************************************\n");

	trav_remaining_key(matrix, recovered_key, key, matrix_rank);

	end = time(NULL);
	printf("This program takes: %d s\n", end - start);
	return 0;
}
