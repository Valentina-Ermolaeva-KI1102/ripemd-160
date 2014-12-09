#include "rip.h"

#define F(x, y, z)    (x ^ y ^ z) 
#define G(x, y, z)    (z ^ (x & (y^z)))
#define H(x, y, z)    (z ^ (x | ~y))
#define I(x, y, z)    (y ^ (z & (x^y)))
#define J(x, y, z)    (x ^ (y | ~z))

#define k0 0
#define k1 0x5a827999UL
#define k2 0x6ed9eba1UL
#define k3 0x8f1bbcdcUL
#define k4 0xa953fd4eUL
#define k5 0x50a28be6UL
#define k6 0x5c4dd124UL
#define k7 0x6d703ef3UL
#define k8 0x7a6d76e9UL
#define k9 0

#define Subround(f, a, b, c, d, e, x, s, k)        \
	a += f(b, c, d) + x + k;\
	a = rotlFixed((unsigned int)a, s) + e;\
	c = rotlFixed((unsigned int)c, 10U)

unsigned int rotlFixed(unsigned int x, unsigned int y)
{
	return (x << y) | (x >> (32-y));
}

void InitState(unsigned int *state)
{
	state[0] = 0x67452301UL;
	state[1] = 0xefcdab89UL;
	state[2] = 0x98badcfeUL;
	state[3] = 0x10325476UL;
	state[4] = 0xc3d2e1f0UL;
}

void Transform (unsigned int *digest, const unsigned int *X)
{
	unsigned long a1, b1, c1, d1, e1, a2, b2, c2, d2, e2;
	a1 = a2 = digest[0];
	b1 = b2 = digest[1];
	c1 = c2 = digest[2];
	d1 = d2 = digest[3];
	e1 = e2 = digest[4];

	Subround(F, a1, b1, c1, d1, e1, X[ 0], 11, k0);
	Subround(F, e1, a1, b1, c1, d1, X[ 1], 14, k0);
	Subround(F, d1, e1, a1, b1, c1, X[ 2], 15, k0);
	Subround(F, c1, d1, e1, a1, b1, X[ 3], 12, k0);
	Subround(F, b1, c1, d1, e1, a1, X[ 4],  5, k0);
	Subround(F, a1, b1, c1, d1, e1, X[ 5],  8, k0);
	Subround(F, e1, a1, b1, c1, d1, X[ 6],  7, k0);
	Subround(F, d1, e1, a1, b1, c1, X[ 7],  9, k0);
	Subround(F, c1, d1, e1, a1, b1, X[ 8], 11, k0);
	Subround(F, b1, c1, d1, e1, a1, X[ 9], 13, k0);
	Subround(F, a1, b1, c1, d1, e1, X[10], 14, k0);
	Subround(F, e1, a1, b1, c1, d1, X[11], 15, k0);
	Subround(F, d1, e1, a1, b1, c1, X[12],  6, k0);
	Subround(F, c1, d1, e1, a1, b1, X[13],  7, k0);
	Subround(F, b1, c1, d1, e1, a1, X[14],  9, k0);
	Subround(F, a1, b1, c1, d1, e1, X[15],  8, k0);

	Subround(G, e1, a1, b1, c1, d1, X[ 7],  7, k1);
	Subround(G, d1, e1, a1, b1, c1, X[ 4],  6, k1);
	Subround(G, c1, d1, e1, a1, b1, X[13],  8, k1);
	Subround(G, b1, c1, d1, e1, a1, X[ 1], 13, k1);
	Subround(G, a1, b1, c1, d1, e1, X[10], 11, k1);
	Subround(G, e1, a1, b1, c1, d1, X[ 6],  9, k1);
	Subround(G, d1, e1, a1, b1, c1, X[15],  7, k1);
	Subround(G, c1, d1, e1, a1, b1, X[ 3], 15, k1);
	Subround(G, b1, c1, d1, e1, a1, X[12],  7, k1);
	Subround(G, a1, b1, c1, d1, e1, X[ 0], 12, k1);
	Subround(G, e1, a1, b1, c1, d1, X[ 9], 15, k1);
	Subround(G, d1, e1, a1, b1, c1, X[ 5],  9, k1);
	Subround(G, c1, d1, e1, a1, b1, X[ 2], 11, k1);
	Subround(G, b1, c1, d1, e1, a1, X[14],  7, k1);
	Subround(G, a1, b1, c1, d1, e1, X[11], 13, k1);
	Subround(G, e1, a1, b1, c1, d1, X[ 8], 12, k1);

	Subround(H, d1, e1, a1, b1, c1, X[ 3], 11, k2);
	Subround(H, c1, d1, e1, a1, b1, X[10], 13, k2);
	Subround(H, b1, c1, d1, e1, a1, X[14],  6, k2);
	Subround(H, a1, b1, c1, d1, e1, X[ 4],  7, k2);
	Subround(H, e1, a1, b1, c1, d1, X[ 9], 14, k2);
	Subround(H, d1, e1, a1, b1, c1, X[15],  9, k2);
	Subround(H, c1, d1, e1, a1, b1, X[ 8], 13, k2);
	Subround(H, b1, c1, d1, e1, a1, X[ 1], 15, k2);
	Subround(H, a1, b1, c1, d1, e1, X[ 2], 14, k2);
	Subround(H, e1, a1, b1, c1, d1, X[ 7],  8, k2);
	Subround(H, d1, e1, a1, b1, c1, X[ 0], 13, k2);
	Subround(H, c1, d1, e1, a1, b1, X[ 6],  6, k2);
	Subround(H, b1, c1, d1, e1, a1, X[13],  5, k2);
	Subround(H, a1, b1, c1, d1, e1, X[11], 12, k2);
	Subround(H, e1, a1, b1, c1, d1, X[ 5],  7, k2);
	Subround(H, d1, e1, a1, b1, c1, X[12],  5, k2);

	Subround(I, c1, d1, e1, a1, b1, X[ 1], 11, k3);
	Subround(I, b1, c1, d1, e1, a1, X[ 9], 12, k3);
	Subround(I, a1, b1, c1, d1, e1, X[11], 14, k3);
	Subround(I, e1, a1, b1, c1, d1, X[10], 15, k3);
	Subround(I, d1, e1, a1, b1, c1, X[ 0], 14, k3);
	Subround(I, c1, d1, e1, a1, b1, X[ 8], 15, k3);
	Subround(I, b1, c1, d1, e1, a1, X[12],  9, k3);
	Subround(I, a1, b1, c1, d1, e1, X[ 4],  8, k3);
	Subround(I, e1, a1, b1, c1, d1, X[13],  9, k3);
	Subround(I, d1, e1, a1, b1, c1, X[ 3], 14, k3);
	Subround(I, c1, d1, e1, a1, b1, X[ 7],  5, k3);
	Subround(I, b1, c1, d1, e1, a1, X[15],  6, k3);
	Subround(I, a1, b1, c1, d1, e1, X[14],  8, k3);
	Subround(I, e1, a1, b1, c1, d1, X[ 5],  6, k3);
	Subround(I, d1, e1, a1, b1, c1, X[ 6],  5, k3);
	Subround(I, c1, d1, e1, a1, b1, X[ 2], 12, k3);

	Subround(J, b1, c1, d1, e1, a1, X[ 4],  9, k4);
	Subround(J, a1, b1, c1, d1, e1, X[ 0], 15, k4);
	Subround(J, e1, a1, b1, c1, d1, X[ 5],  5, k4);
	Subround(J, d1, e1, a1, b1, c1, X[ 9], 11, k4);
	Subround(J, c1, d1, e1, a1, b1, X[ 7],  6, k4);
	Subround(J, b1, c1, d1, e1, a1, X[12],  8, k4);
	Subround(J, a1, b1, c1, d1, e1, X[ 2], 13, k4);
	Subround(J, e1, a1, b1, c1, d1, X[10], 12, k4);
	Subround(J, d1, e1, a1, b1, c1, X[14],  5, k4);
	Subround(J, c1, d1, e1, a1, b1, X[ 1], 12, k4);
	Subround(J, b1, c1, d1, e1, a1, X[ 3], 13, k4);
	Subround(J, a1, b1, c1, d1, e1, X[ 8], 14, k4);
	Subround(J, e1, a1, b1, c1, d1, X[11], 11, k4);
	Subround(J, d1, e1, a1, b1, c1, X[ 6],  8, k4);
	Subround(J, c1, d1, e1, a1, b1, X[15],  5, k4);
	Subround(J, b1, c1, d1, e1, a1, X[13],  6, k4);

	Subround(J, a2, b2, c2, d2, e2, X[ 5],  8, k5);
	Subround(J, e2, a2, b2, c2, d2, X[14],  9, k5);
	Subround(J, d2, e2, a2, b2, c2, X[ 7],  9, k5);
	Subround(J, c2, d2, e2, a2, b2, X[ 0], 11, k5);
	Subround(J, b2, c2, d2, e2, a2, X[ 9], 13, k5);
	Subround(J, a2, b2, c2, d2, e2, X[ 2], 15, k5);
	Subround(J, e2, a2, b2, c2, d2, X[11], 15, k5);
	Subround(J, d2, e2, a2, b2, c2, X[ 4],  5, k5);
	Subround(J, c2, d2, e2, a2, b2, X[13],  7, k5);
	Subround(J, b2, c2, d2, e2, a2, X[ 6],  7, k5);
	Subround(J, a2, b2, c2, d2, e2, X[15],  8, k5);
	Subround(J, e2, a2, b2, c2, d2, X[ 8], 11, k5);
	Subround(J, d2, e2, a2, b2, c2, X[ 1], 14, k5);
	Subround(J, c2, d2, e2, a2, b2, X[10], 14, k5);
	Subround(J, b2, c2, d2, e2, a2, X[ 3], 12, k5);
	Subround(J, a2, b2, c2, d2, e2, X[12],  6, k5);

	Subround(I, e2, a2, b2, c2, d2, X[ 6],  9, k6); 
	Subround(I, d2, e2, a2, b2, c2, X[11], 13, k6);
	Subround(I, c2, d2, e2, a2, b2, X[ 3], 15, k6);
	Subround(I, b2, c2, d2, e2, a2, X[ 7],  7, k6);
	Subround(I, a2, b2, c2, d2, e2, X[ 0], 12, k6);
	Subround(I, e2, a2, b2, c2, d2, X[13],  8, k6);
	Subround(I, d2, e2, a2, b2, c2, X[ 5],  9, k6);
	Subround(I, c2, d2, e2, a2, b2, X[10], 11, k6);
	Subround(I, b2, c2, d2, e2, a2, X[14],  7, k6);
	Subround(I, a2, b2, c2, d2, e2, X[15],  7, k6);
	Subround(I, e2, a2, b2, c2, d2, X[ 8], 12, k6);
	Subround(I, d2, e2, a2, b2, c2, X[12],  7, k6);
	Subround(I, c2, d2, e2, a2, b2, X[ 4],  6, k6);
	Subround(I, b2, c2, d2, e2, a2, X[ 9], 15, k6);
	Subround(I, a2, b2, c2, d2, e2, X[ 1], 13, k6);
	Subround(I, e2, a2, b2, c2, d2, X[ 2], 11, k6);

	Subround(H, d2, e2, a2, b2, c2, X[15],  9, k7);
	Subround(H, c2, d2, e2, a2, b2, X[ 5],  7, k7);
	Subround(H, b2, c2, d2, e2, a2, X[ 1], 15, k7);
	Subround(H, a2, b2, c2, d2, e2, X[ 3], 11, k7);
	Subround(H, e2, a2, b2, c2, d2, X[ 7],  8, k7);
	Subround(H, d2, e2, a2, b2, c2, X[14],  6, k7);
	Subround(H, c2, d2, e2, a2, b2, X[ 6],  6, k7);
	Subround(H, b2, c2, d2, e2, a2, X[ 9], 14, k7);
	Subround(H, a2, b2, c2, d2, e2, X[11], 12, k7);
	Subround(H, e2, a2, b2, c2, d2, X[ 8], 13, k7);
	Subround(H, d2, e2, a2, b2, c2, X[12],  5, k7);
	Subround(H, c2, d2, e2, a2, b2, X[ 2], 14, k7);
	Subround(H, b2, c2, d2, e2, a2, X[10], 13, k7);
	Subround(H, a2, b2, c2, d2, e2, X[ 0], 13, k7);
	Subround(H, e2, a2, b2, c2, d2, X[ 4],  7, k7);
	Subround(H, d2, e2, a2, b2, c2, X[13],  5, k7);

	Subround(G, c2, d2, e2, a2, b2, X[ 8], 15, k8);
	Subround(G, b2, c2, d2, e2, a2, X[ 6],  5, k8);
	Subround(G, a2, b2, c2, d2, e2, X[ 4],  8, k8);
	Subround(G, e2, a2, b2, c2, d2, X[ 1], 11, k8);
	Subround(G, d2, e2, a2, b2, c2, X[ 3], 14, k8);
	Subround(G, c2, d2, e2, a2, b2, X[11], 14, k8);
	Subround(G, b2, c2, d2, e2, a2, X[15],  6, k8);
	Subround(G, a2, b2, c2, d2, e2, X[ 0], 14, k8);
	Subround(G, e2, a2, b2, c2, d2, X[ 5],  6, k8);
	Subround(G, d2, e2, a2, b2, c2, X[12],  9, k8);
	Subround(G, c2, d2, e2, a2, b2, X[ 2], 12, k8);
	Subround(G, b2, c2, d2, e2, a2, X[13],  9, k8);
	Subround(G, a2, b2, c2, d2, e2, X[ 9], 12, k8);
	Subround(G, e2, a2, b2, c2, d2, X[ 7],  5, k8);
	Subround(G, d2, e2, a2, b2, c2, X[10], 15, k8);
	Subround(G, c2, d2, e2, a2, b2, X[14],  8, k8);

	Subround(F, b2, c2, d2, e2, a2, X[12],  8, k9);
	Subround(F, a2, b2, c2, d2, e2, X[15],  5, k9);
	Subround(F, e2, a2, b2, c2, d2, X[10], 12, k9);
	Subround(F, d2, e2, a2, b2, c2, X[ 4],  9, k9);
	Subround(F, c2, d2, e2, a2, b2, X[ 1], 12, k9);
	Subround(F, b2, c2, d2, e2, a2, X[ 5],  5, k9);
	Subround(F, a2, b2, c2, d2, e2, X[ 8], 14, k9);
	Subround(F, e2, a2, b2, c2, d2, X[ 7],  6, k9);
	Subround(F, d2, e2, a2, b2, c2, X[ 6],  8, k9);
	Subround(F, c2, d2, e2, a2, b2, X[ 2], 13, k9);
	Subround(F, b2, c2, d2, e2, a2, X[13],  6, k9);
	Subround(F, a2, b2, c2, d2, e2, X[14],  5, k9);
	Subround(F, e2, a2, b2, c2, d2, X[ 0], 15, k9);
	Subround(F, d2, e2, a2, b2, c2, X[ 3], 13, k9);
	Subround(F, c2, d2, e2, a2, b2, X[ 9], 11, k9);
	Subround(F, b2, c2, d2, e2, a2, X[11], 11, k9);

	c1        = digest[1] + c1 + d2;
	digest[1] = digest[2] + d1 + e2;
	digest[2] = digest[3] + e1 + a2;
	digest[3] = digest[4] + a1 + b2;
	digest[4] = digest[0] + b1 + c2;
	digest[0] = c1;
}

unsigned char* ripemd(std::ifstream &ifst)
{
	int lenght, size = 64, rest, i;
	ifst.seekg(0, std::ios::end);
	lenght = ifst.tellg();
	ifst.seekg(0, std::ios::beg);
	bool end = false;
	rest = lenght % 64;
	unsigned char *msg_for_hash = new unsigned char[size];
	char buf;
	unsigned int *X=(unsigned int*)(msg_for_hash), state[5];
	InitState(state);
	while(!ifst.eof() && !end)
	{
		for(i = 0; i < size; i++)
		{
			ifst.get(buf);
			if(ifst.eof())
			{
				if(i < 55)
				{
					msg_for_hash[i] = 0x80;
					for(i++; i < 56; i++)
						msg_for_hash[i] = 0;
					long long bit_length = (unsigned int)(lenght)*8; //длина сообщения в битах.
					int buf_length = bit_length;
					for(int i = 3; i >= 0; i--) //последние 8 байт
						msg_for_hash[size - 8 + i] = (unsigned char)(buf_length >> (3 - i) * 8);
					buf_length = bit_length >> 8 * 4;
					for(int i = 3; i >= 0; i--)
						msg_for_hash[size - 4 + i] = (unsigned char)(buf_length >> (3 - i) * 8);
					break;
				}
				else
				{
					msg_for_hash[i] = 0x80;
					for(i++; i < size; i++)
						msg_for_hash[i] = 0;
					end = true;
					break;
				}
			}
			msg_for_hash[i] = buf;
		}
		if(end)
		{
			for(i++; i < 56; i++)
				msg_for_hash[i] = 0;
			long long bit_length = (unsigned int)(lenght)*8; //длина сообщения в битах.
			int buf_length = bit_length;
			for(int i = 3; i >= 0; i--) //последние 8 байт
				msg_for_hash[size - 8 + i] = (unsigned char)(buf_length >> (3 - i) * 8);
			buf_length = bit_length >> 8 * 4;
			for(int i = 3; i >= 0; i--)
				msg_for_hash[size - 4 + i] = (unsigned char)(buf_length >> (3 - i) * 8);
			end = false;
		}
		Transform(state, X);
	}
	unsigned char *RIPEND = new unsigned char[20];
	RIPEND[0] = state[0];	RIPEND[1] = state[0]>>8;	RIPEND[2] = state[0]>>16;	RIPEND[3] = state[0]>>24;
	RIPEND[4] = state[1];	RIPEND[5] = state[1]>>8;	RIPEND[6] = state[1]>>16;	RIPEND[7] = state[1]>>24;
	RIPEND[8] = state[2];	RIPEND[9] = state[2]>>8;	RIPEND[10] = state[2]>>16;	RIPEND[11] = state[2]>>24;
	RIPEND[12] = state[3];	RIPEND[13] = state[3]>>8;	RIPEND[14] = state[3]>>16;	RIPEND[15] = state[3]>>24;
	RIPEND[16] = state[4];	RIPEND[17] = state[4]>>8;	RIPEND[18] = state[4]>>16;	RIPEND[19] = state[4]>>24;
	return RIPEND;
}
