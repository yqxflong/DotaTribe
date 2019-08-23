#ifndef  _LC_COBRA_WIN_RANDOM_H
#define  _LC_COBRA_WIN_RANDOM_H


namespace  cobra_win
{


class  Random
{
public:
	/*
		精确处理，大小在0-0XFFFFFFFF
	*/
	static  unsigned  int  rand();
	/*
		调用系统自带函数，不精确，并且范围在0-32767
	*/
	static  unsigned  int  rand2();
};


}



#endif
