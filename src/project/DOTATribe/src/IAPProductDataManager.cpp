#include "../include/IAPProductDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <include/common/Random.h>
#include <assert.h>


IAPProductData::IAPProductData()
{
	mProductType = _TYPED_IAP_PRODUCT_UNKOWN_;
	mProductGoodsId = 0;
	memset(mProductId, 0, sizeof(mProductId));
	memset(mProductName, 0, sizeof(mProductName));
	memset(mProductDesc, 0, sizeof(mProductDesc));
	mProductPrice = 0.0f;
	mProductChargePoint = 0;
	mIsNonConsume= false;
}

IAPProductData::~IAPProductData()
{

}

bool IAPProductData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	int id = 0;
	if (!parser.parser_int_value(id))
		return false;

	if (!parser.parser_int_value(mProductType))
		return false;

	if (!parser.parser_int_value(mProductGoodsId))
		return false;

	if (!parser.parser_string_value(mProductId, sizeof(mProductId)))
		return false;

	if (!parser.parser_string_value(mProductName, sizeof(mProductName)))
		return false;

	if (!parser.parser_string_value(mProductDesc, sizeof(mProductDesc)))
		return false;

	if (!parser.parser_float_value(mProductPrice))
		return false;

	if (!parser.parser_int_value(mProductChargePoint))
		return false;

	if (!parser.parser_bool_value(mIsNonConsume))
		return false;

	return true;
}

template<> IAPProductDataManager* cobra_win::Singleton2<IAPProductDataManager>::m_pMySelf = NULL;

IAPProductDataManager::IAPProductDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_IAPProductListByType.clear();
	m_IAPProductListById.clear();
}

IAPProductDataManager::~IAPProductDataManager()
{

}

int IAPProductDataManager::GetIAPProductNumber()
{
	return m_IAPProductListByType.size();
}

IAPProductData* IAPProductDataManager::GetIAPProductDataByPos(int pos)
{
	std::map<int, IAPProductData*>::iterator iter   = m_IAPProductListByType.begin();
	std::map<int, IAPProductData*>::iterator iter_e = m_IAPProductListByType.end();
	for (int i=0; iter!=iter_e; ++iter, i++)
	{
		if (i == pos)
		{
			return iter->second;
		}
	}

	return NULL;
}

IAPProductData* IAPProductDataManager::GetIAPProductByProductType(int productType)
{
	std::map<int, IAPProductData*>::iterator iter = m_IAPProductListByType.find(productType);
	if (iter == m_IAPProductListByType.end())
		return NULL;

	return iter->second;	
}

IAPProductData* IAPProductDataManager::GetIAPProductByProductId(std::string productId)
{
	std::map<std::string, IAPProductData*>::iterator iter = m_IAPProductListById.find(productId);
	if (iter == m_IAPProductListById.end())
		return NULL;

	return iter->second;	
}

std::string IAPProductDataManager::GetName()
{
	if (!m_bLoadFromDB)
	{
		return "resource/data/product.txt";
	}

	return "product";
}

unsigned  int IAPProductDataManager::GetSize()
{
	return m_IAPProductListByType.size()*sizeof(IAPProductData);
}

bool  IAPProductDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
		{
			if (!LoadFromDB())
				break;
		}
		else
		{
			if (!LoadFromFile())
				break;
		}

		return true;
	} 
	while(false);

	return false;
}

void  IAPProductDataManager::Tick()
{

}

void  IAPProductDataManager::Destroy()
{
	std::map<int, IAPProductData*>::iterator iter   = m_IAPProductListByType.begin();
	std::map<int, IAPProductData*>::iterator iter_e = m_IAPProductListByType.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_IAPProductListByType.clear();
	m_IAPProductListById.clear();
}

bool  IAPProductDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	IAPProductData* pProduct = (IAPProductData*)pData;
	assert(pProduct != NULL);

	if (pProduct->mProductId[0] == '\0')
		return false;

	if (pProduct->mProductName[0] == '\0')
		return false;

	if (pProduct->mProductDesc[0] == '\0')
		return false;

	if (pProduct->mProductPrice < 0)
		return false;

	if (pProduct->mProductChargePoint < 0)
		return false;

	return true;
}

bool  IAPProductDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  IAPProductDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	IAPProductData* pProduct = new IAPProductData;
	if (!pProduct->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pProduct))
		return false;

	m_IAPProductListByType.insert(std::map<int, IAPProductData*>::value_type(pProduct->mProductType, pProduct));
	m_IAPProductListById.insert(std::map<std::string, IAPProductData*>::value_type(pProduct->mProductId, pProduct));
	return true;
}
