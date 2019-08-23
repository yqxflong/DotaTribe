#include "../include/DebugerSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/NetDebuger.h"
#include "../include/RenderDebuger.h"
#include "../include/LogicDebuger.h"


template<> DebugerSystem* cobra_win::Singleton2<DebugerSystem>::m_pMySelf = NULL;

DebugerSystem::DebugerSystem()
{
	m_pNetDebuger    = 0;
	m_pLogicDebuger  = 0;
	m_pRenderDebuger = 0;
}

DebugerSystem::~DebugerSystem()
{

}

bool DebugerSystem::Init()
{
	do 
	{
		// 创建并初始化网络信息调试器
		m_pNetDebuger = new NetDebuger;
		if (!m_pNetDebuger->Init())
			break;

		// 创建并初始化渲染信息调试器
		m_pRenderDebuger = new RenderDebuger;
		if (!m_pRenderDebuger->Init())
			break;

		// 创建并初始化逻辑信息调试器
		m_pLogicDebuger = new LogicDebuger;
		if (!m_pLogicDebuger->Init())
			break;

		LOGGERSYSTEM->LogInfo("Init DebugerSystem Success\n");
		return true;
	} 
	while(false);

	LOGGERSYSTEM->LogFatal("Init DebugerSystem Failed\n");
	return false;
}

void DebugerSystem::Tick()
{
	// 网络信息调试器帧更新
	m_pNetDebuger->Tick();
	// 渲染信息调试器帧更新
	m_pRenderDebuger->Tick();
	// 逻辑信息调试器帧更新
	m_pLogicDebuger->Tick();
}

void DebugerSystem::Destroy()
{
	// 销毁网络信息调试器
	if (m_pNetDebuger != 0)
	{
		m_pNetDebuger->Destroy();
		delete m_pNetDebuger;
	}

	// 销毁渲染信息调试器
	if (m_pRenderDebuger != 0)
	{
		m_pRenderDebuger->Destroy();
		delete m_pRenderDebuger;
	}

	// 销毁逻辑信息调试器
	if (m_pLogicDebuger != 0)
	{
		m_pLogicDebuger->Destroy();
		delete m_pLogicDebuger;
	}

	LOGGERSYSTEM->LogInfo("Destroy DebugerSystem Success\n");
}
