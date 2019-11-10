#ifndef generate_random_value_using_AES_H_
#define generate_random_value_using_AES_H_
#include "iostream"
#include "fstream"
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <wmmintrin.h>
#include <x86intrin.h>
#include <stdlib.h>
using namespace std;

typedef unsigned long long int uint64;
#pragma intrinsic( __rdtsc )

__inline volatile unsigned long long read_tsc(void)
{
	return __rdtsc();
}


#define RAND(a,b) (((a = 36969 * (a & 65535) + (a >> 16)) << 16) + \
	(b = 18000 * (b & 65535) + (b >> 16))  )

void block_rndfill(unsigned char* buf, const int len)
{
	static unsigned long a[2], mt = 1, count = 4;
	static unsigned char r[4];
	int                  i;

	if (mt) { mt = 0; *(unsigned long long*)a = read_tsc(); }

	for (i = 0; i < len; ++i)
	{
		if (count == 4)
		{
			*(unsigned long*)r = RAND(a[0], a[1]);
			count = 0;
		}

		buf[i] = r[count++];
	}
}

unsigned long int get_random_value()
{
	__m128i AESkey[10];
	__m128i rmm00;
	block_rndfill((unsigned char*)(AESkey), sizeof(AESkey));
	block_rndfill((unsigned char*)(&rmm00), sizeof(rmm00));
	rmm00 = _mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(_mm_aesenc_si128(rmm00, AESkey[0]), AESkey[1]), AESkey[2]), AESkey[3]), AESkey[4]), AESkey[5]), AESkey[6]), AESkey[7]), AESkey[8]), AESkey[9]);
	unsigned long long* randnp = (unsigned long long*)(&rmm00);
	return (*randnp) & 0xffffffff;
}

#endif // !generate_random_value_using_AES_H_
#pragma once
