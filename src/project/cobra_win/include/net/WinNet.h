#ifndef  _LC_COBRA_WIN_WINNET_H
#define  _LC_COBRA_WIN_WINNET_H


namespace  cobra_win
{


class  WinNet
{
public:
	/*
		初始化网络环境
	*/
	static   bool   init_network();
	/*
		销毁网络环境
	*/
	static   void   destroy_network();
};


}


#endif
