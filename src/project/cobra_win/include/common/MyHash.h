#ifndef  _LC_COBRA_WIN_MYHASH_H
#define  _LC_COBRA_WIN_MYHASH_H


namespace  cobra_win
{


class  MyHash
{
public:
	static  unsigned  int  rs_hash(char* pStr);
	static  unsigned  int  js_hash(char* pStr);
	static  unsigned  int  pjw_hash(char* pStr);
	static  unsigned  int  elf_hash(char* pStr);
	static  unsigned  int  bkdr_hash(char* pStr);
	static  unsigned  int  sdbm_hash(char* pStr);
	static  unsigned  int  djb_hash(char* pStr);
	static  unsigned  int  dek_hash(char* pStr);
	static  unsigned  int  bp_hash(char* pStr);
	static  unsigned  int  fnv_hash(char* pStr);
	static  unsigned  int  ap_hash(char* pStr);
};


}

#endif
