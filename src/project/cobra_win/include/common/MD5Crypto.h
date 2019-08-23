#ifndef  _LC_COBRA_WIN_MD5CRYPTO_H
#define  _LC_COBRA_WIN_MD5CRYPTO_H


#include <string>

namespace  cobra_win
{


class  MD5Crypto
{
private:
	unsigned char m_Buffer[64];
	unsigned int  m_iCount[2];
	unsigned int  m_lMD5[4];

private:
	MD5Crypto();
	~MD5Crypto();

private:
	void          transform(unsigned char Block[64]);
	void          update(unsigned char* Input, unsigned int nInputLen);
	std::string   final();

private:
	inline        unsigned int     rotate_left(unsigned int x, int n);
	inline        void             ff(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline        void             gg(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline        void             hh(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline        void             ii(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline        void             dword_to_byte(unsigned char* Output, unsigned int* Input, unsigned int nLength);
	inline        void             byte_to_dword(unsigned int* Output, unsigned char* Input, unsigned int nLength);

public:
	static        std::string    md5(unsigned char* pBuf, unsigned int nLength);
	static        std::string    md5(const char* strFilePath);
};


}


#endif
