//Name：IBagData
//Function：背包数据接口
//Written By：尹强

#ifndef _DOTATRIBE_IBAGDATA_H
#define _DOTATRIBE_IBAGDATA_H

class IBagData
{
public:
		unsigned short index_;				//索引位置<br>
		unsigned short itemcount_;		//物品数量<br>
		bool __delectflag;
		IBagData()
		{
			__delectflag = false;
		}
};
#endif