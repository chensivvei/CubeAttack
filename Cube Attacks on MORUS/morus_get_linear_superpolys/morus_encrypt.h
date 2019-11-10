#ifndef morus_encrypt_H_
#define morus_encrypt_H_
//#include "morus_cubes.h"
struct state_word {
	uint64_t m[2];
};
state_word state_xor(state_word src1, state_word src2);

state_word output_ciphertext(state_word* S, int round);

#endif // !morus_encrypt_H_
#pragma once
