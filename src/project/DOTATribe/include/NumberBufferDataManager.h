#ifndef   _DOTATRIBE_NUMBERBUFFERDATAMANGER_H
#define   _DOTATRIBE_NUMBERBUFFERDATAMANGER_H

 
 
#include  <include/common/Singleton.h>
#include  "IDataManager.h"
#include  <cocos2d.h>
#include  <string>
#include  <map>

#pragma pack(push, 1)

class   NumberBufferData: public IData
{
public:
	  int    numberBufferFormatID;					 //����Buffer��ʽID
	  int    numberBufferFontType;					 //���������ID
	  float  numberBufferScale;						 //����Buffer�ĳ�ʼ���ű���
	  float  numberBufferMaxScale;					 //����Buffer��������ű���		 
	  float  numberBufferScaleDurationTime;			 //����Buffer������ʱ��
	  float  numberBufferInitHeigh;					 //����Buffer�ĳ�ʼ�߶�
	  float  numberBufferEndHeigh;					 //��ֵBuffer�Ľ����߶�
	  float  numberBufferDurationTime;				 //��ֵBuffer�ĳ���ʱ��			    //��λMS
	  float  numberBufferTriggerFadeOutTime;		 //��ֵBuffer�Ŀ�ʼ����ʧʱ���    //��λMS
	  bool   numberBufferIsNeedScale;				 //����Buffer�Ƿ���Ҫ����
public:
	NumberBufferData();
	~NumberBufferData();
public:
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class  NumberBufferDataManager: public IDataManager, public cobra_win::Singleton2<NumberBufferDataManager>
{
public:
	std::map<int, NumberBufferData*>  m_numberBufferMapList;

public:
	NumberBufferDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~NumberBufferDataManager();

public:
	
    NumberBufferData * GetNumberBufferDataByID(int numberBufferID);

	/*
		�õ���Ӧ�����ݹ���������
	*/
	virtual  std::string   GetName();
	/*
		�õ���Ӧ�����ݹ������ڴ�ռ�ô�С
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		��ʼ�����ݹ�����
	*/
	virtual  bool  Init();
	/*
		���ݹ�����֡���´���
	*/
	virtual  void  Tick();
	/*
		�������ݹ�����
	*/
	virtual  void  Destroy();

public:
	/*
		У����ص�����(�������ݵ���Ч��У��)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		У����ص�����(�������ݼ�����֮����еı���������У��)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		����ָ����ItemData����
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<NumberBufferDataManager>;

};








#endif 