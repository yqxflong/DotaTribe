//Name��IBagData
//Function���������ݽӿ�
//Written By����ǿ

#ifndef _DOTATRIBE_IBAGDATA_H
#define _DOTATRIBE_IBAGDATA_H

class IBagData
{
public:
		unsigned short index_;				//����λ��<br>
		unsigned short itemcount_;		//��Ʒ����<br>
		bool __delectflag;
		IBagData()
		{
			__delectflag = false;
		}
};
#endif