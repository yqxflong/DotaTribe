#include "../../include/common/Random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using  namespace  cobra_win;


const static unsigned long int X_SEED_DEFAULT = 123456789UL;
const static unsigned long int Y_SEED_DEFAULT = 362436069UL;
const static unsigned long int Z_SEED_DEFAULT = 521288629UL;
const static unsigned long int W_SEED_DEFAULT = 88675123UL;


static unsigned long int mXSeed;
static unsigned long int mYSeed;
static unsigned long int mZSeed;
static unsigned long int mWSeed;
static unsigned long int mX;
static unsigned long int mY;
static unsigned long int mZ;
static unsigned long int mW;


unsigned  int  Random::rand()
{
	static  bool  bFirst = true;
	if (bFirst)
	{
		mXSeed = (unsigned long)time(NULL) ^ X_SEED_DEFAULT;
		mYSeed = (unsigned long)time(NULL) ^ Y_SEED_DEFAULT;
		mZSeed = (unsigned long)time(NULL) ^ Z_SEED_DEFAULT;
		mWSeed = (unsigned long)time(NULL) ^ W_SEED_DEFAULT;

		mX = mXSeed;
		mY = mYSeed;
		mZ = mZSeed;
		mW = mWSeed;

		bFirst = !bFirst;
	}

	register unsigned long int t = (mX ^ (mX<<11));
	mX = mY;
	mY = mZ;
	mZ = mW;

	return(mW = (mW ^ (mW>>19)) ^ (t ^ (t>>8)));	
}

unsigned  int  Random::rand2()
{
	// 程序在外部启动时，毕竟首先调用
	// srand((unsigned)time(NULL));
	// 来初始化随机数产生器
	return (unsigned int)::rand();
}
