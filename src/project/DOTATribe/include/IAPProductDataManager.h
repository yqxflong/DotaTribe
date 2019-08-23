#ifndef  _DOTATRIBE_IAPDATAMANAGER_H_
#define  _DOTATRIBE_IAPDATAMANAGER_H_


#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <map>

#pragma pack(push, 1)
class IAPProductData : public IData
{
public:
	enum
	{
		_TYPED_IAP_PRODUCT_UNKOWN_, // 未知商品类型
		_TYPED_IAP_PRODUCT_TEST_,// 测试商品类型
		_TYPED_IAP_PRODUCT_001_, // 未知商品类型
		_TYPED_IAP_PRODUCT_002_, // 未知商品类型
		_TYPED_IAP_PRODUCT_003_, // 未知商品类型
		_TYPED_IAP_PRODUCT_004_, // 未知商品类型
		_TYPED_IAP_PRODUCT_005_, // 未知商品类型
		_TYPED_IAP_PRODUCT_006_, // 未知商品类型
		_TYPED_IAP_PRODUCT_007_, // 未知商品类型
		_TYPED_IAP_PRODUCT_008_, // 未知商品类型
		_TYPED_IAP_PRODUCT_009_, // 未知商品类型
	};

public:
	int   mProductType;        // 商品类型
	int   mProductGoodsId;     // 商品GoodsId(畅游平台专用)
	char  mProductId[128];     // 商品Id
	char  mProductName[128];   // 商品名称
	char  mProductDesc[128];   // 商品描述信息
	float mProductPrice;       // 商品价格(Android专用)
	int   mProductChargePoint; // 商品签名(Android专用)
	bool  mIsNonConsume;       // 是否非消耗类

public:
	IAPProductData();
	virtual ~IAPProductData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class IAPProductDataManager : public IDataManager, public cobra_win::Singleton2<IAPProductDataManager>
{
private:
	std::map<int, IAPProductData*> m_IAPProductListByType;
	std::map<std::string, IAPProductData*> m_IAPProductListById;

public:
	IAPProductDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~IAPProductDataManager();

public:
	/*
		得到商品个数
	*/
	int  GetIAPProductNumber();
	/*
        得到指定位置的商品信息
    */
	IAPProductData* GetIAPProductDataByPos(int pos);
	/*
		得到指定ProductType的商品信息
	*/
	IAPProductData* GetIAPProductByProductType(int productType);
	/*
		得到指定ProductId的商品信息
	*/
	IAPProductData* GetIAPProductByProductId(std::string productId);

public:
	/*
		得到对应的数据管理器名称
	*/
	virtual  std::string   GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		初始化数据管理器
	*/
	virtual  bool  Init();
	/*
		数据管理器帧更新处理
	*/
	virtual  void  Tick();
	/*
		销毁数据管理器
	*/
	virtual  void  Destroy();

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<IAPProductDataManager>;
};


#endif
