#include "../../include/common/MyHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
using  namespace  cobra_win;


unsigned int MyHash::rs_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int b    = 378551;
	unsigned int a    = 63689;
	unsigned int hash = 0;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = hash * a + pStr[i];
		a    = a * b;
	}

	return hash;
}
/* End Of RS Hash Function */


unsigned int MyHash::js_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int hash = 1315423911;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash ^= ((hash << 5) + pStr[i] + (hash >> 2));
	}

	return hash;
}
/* End Of JS Hash Function */


unsigned int MyHash::pjw_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
	unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
	unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
	unsigned int hash              = 0;
	unsigned int test              = 0;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = (hash << OneEighth) + pStr[i];

		if((test = hash & HighBits)  != 0)
		{
			hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return hash;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int MyHash::elf_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int hash = 0;
	unsigned int x    = 0;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = (hash << 4) + pStr[i];
		if((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}

	return hash;
}
/* End Of ELF Hash Function */


unsigned int MyHash::bkdr_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = (hash * seed) + pStr[i];
	}

	return hash;
}
/* End Of BKDR Hash Function */


unsigned int MyHash::sdbm_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int hash = 0;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = pStr[i] + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}
/* End Of SDBM Hash Function */


unsigned int MyHash::djb_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int hash = 5381;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = ((hash << 5) + hash) + pStr[i];
	}

	return hash;
}
/* End Of DJB Hash Function */


unsigned int MyHash::dek_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	size_t iLen = strlen(pStr);
	unsigned int hash = (unsigned int)iLen;

	for(size_t i = 0; i < iLen; i++)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ pStr[i];
	}

	return hash;
}
/* End Of DEK Hash Function */


unsigned int MyHash::bp_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int hash = 0;
	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash = hash << 7 ^ pStr[i];
	}

	return hash;
}
/* End Of BP Hash Function */


unsigned int MyHash::fnv_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;
	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash *= fnv_prime;
		hash ^= pStr[i];
	}

	return hash;
}
/* End Of FNV Hash Function */


unsigned int MyHash::ap_hash(char* pStr)
{
	assert(pStr!=NULL && strlen(pStr)>0);

	unsigned int hash = 0xAAAAAAAA;

	size_t iLen = strlen(pStr);
	for(size_t i = 0; i < iLen; i++)
	{
		hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ pStr[i] ^ (hash >> 3)) :
			(~((hash << 11) ^ pStr[i] ^ (hash >> 5)));
	}

	return hash;
}
/* End Of AP Hash Function */
