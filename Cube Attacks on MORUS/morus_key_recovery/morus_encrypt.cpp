#include<iostream>
//#include"morus_cubes.h"
struct state_word {
	uint64_t m[2];
};

//res=src1+src2
state_word state_xor(state_word src1, state_word src2) {
	state_word res;
	res.m[0] = src1.m[0] ^ src2.m[0];
	res.m[1] = src1.m[1] ^ src2.m[1];
	return res;
}
//res=src1*src2
state_word state_and(state_word src1, state_word src2) {
	state_word res;
	res.m[0] = src1.m[0] & src2.m[0];
	res.m[1] = src1.m[1] & src2.m[1];
	return res;
}
state_word word_rotate(state_word src, int arg) {
	uint32_t temp[4] = { (src.m[0] >> 32) & 0xffffffff, src.m[0] & 0xffffffff,(src.m[1] >> 32) & 0xffffffff, src.m[1] & 0xffffffff };
	for (int i = 0; i < 4; i++) temp[i] = (temp[i] << arg) | (temp[i] >> (32 - arg));
	state_word res;
	res.m[0] = (((uint64_t)temp[0]) << 32) ^ temp[1];
	res.m[1] = (((uint64_t)temp[2]) << 32) ^ temp[3];
	return res;
}
state_word bit_rotate(state_word src, int arg) {
	state_word res;
	switch (arg)
	{
	case 32:
		res.m[0] = (src.m[0] << 32) ^ (src.m[1] >> 32);
		res.m[1] = (src.m[0] >> 32) ^ (src.m[1] << 32);
		break;
	case 64:
		res.m[0] = src.m[1];
		res.m[1] = src.m[0];
		break;
	default:
		res.m[0] = (src.m[0] >> 32) ^ (src.m[1] << 32);
		res.m[1] = (src.m[0] << 32) ^ (src.m[1] >> 32);
		break;
	}
	return res;
}

void state_update(state_word* S) {
	state_word temp[4];
	temp[0] = state_and(S[1], S[2]);
	temp[0] = state_xor(S[0], temp[0]);
	temp[0] = state_xor(S[3], temp[0]);
	S[0] = bit_rotate(word_rotate(temp[0], 5), 96);

	temp[1] = state_and(S[2], bit_rotate(S[3], 32));
	temp[1] = state_xor(S[1], temp[1]);
	temp[1] = state_xor(S[4], temp[1]);
	S[1] = bit_rotate(word_rotate(temp[1], 31), 64);

	temp[2] = state_and(bit_rotate(S[3], 32), bit_rotate(S[4], 64));
	temp[2] = state_xor(S[2], temp[2]);
	temp[2] = state_xor(temp[2], word_rotate(temp[0], 5));
	S[2] = bit_rotate(word_rotate(temp[2], 7), 32);

	temp[3] = state_and(bit_rotate(S[4], 64), S[0]);
	temp[3] = state_xor(bit_rotate(S[3], 32), temp[3]);
	temp[3] = state_xor(temp[3], word_rotate(temp[1], 31));
	S[3] = word_rotate(temp[3], 22);

	temp[3] = state_and(S[0], S[1]);
	temp[3] = state_xor(bit_rotate(S[4], 64), temp[3]);
	temp[3] = state_xor(temp[3], word_rotate(temp[2], 7));
	S[4] = word_rotate(temp[3], 13);

}
void half_step(state_word* S) {
	S[0] = word_rotate(state_xor(state_xor(state_and(S[1], S[2]), S[0]), S[3]), 5);
	S[1] = word_rotate(state_xor(state_xor(state_and(S[2], bit_rotate(S[3], 32)), S[1]), S[4]), 31);
	S[3] = bit_rotate(S[3], 32);
	S[4] = bit_rotate(S[4], 64);
}
state_word output_ciphertext(state_word* S, int round) {
	state_word res;
	for (int r = 0; r < round; r++) state_update(S);
	half_step(S);
	res = state_and(S[2], S[3]);
	res = state_xor(res, bit_rotate(S[1], 96));
	res = state_xor(res, S[0]);
	return res;
}
/* get Initial variables */
