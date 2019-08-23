//Name��VipFontManager
//Func:		��ȡVip������Ȩ��Ϣ
//Written By��lvyunlong
//Date:20131126
#ifndef   _DOTATRIBE_VIPFONTMANAGER_H
#define   _DOTATRIBE_VIPFONTMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <vector>

#pragma pack(push, 1)
class   VipFontData: public IData
{
public:
	int viptype_;
	int id_;
	int syslangid_;
	int fsyleid_;
public:
	VipFontData();
	virtual ~VipFontData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)
 


class VipFontManager : public IDataManager, public cobra_win::Singleton2<VipFontManager>
{
public:
	std::map<int,std::vector<VipFontData*> > m_mapList;
public:
	VipFontManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){};
	virtual ~VipFontManager(){};

public:
	
	std::vector<VipFontData*> getDataByID(size_t idx);

	VipFontData* getVipFontData(size_t idx,size_t subIdx);

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
	//
	//
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
	friend   class   cobra_win::Singleton2<VipFontManager>;
};

#define  VIPFONTMANAGER  VipFontManager::get_instance2()
  
#endif