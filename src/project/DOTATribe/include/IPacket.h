#ifndef  _DOTATRIBE_IPACKET_H_
#define  _DOTATRIBE_IPACKET_H_


class IPacket
{
protected:
	char m_PacketPrefix[2]; // 数据包头
	int m_PacketLength;// 数据包长度
	unsigned short   m_PacketTyper; // 数据包类型
public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType()    =  0;
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength()  =  0;

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen)   =   0;
	/*
		发送字节流
	*/
	virtual  void  Send()                                   =   0;
};


#endif
