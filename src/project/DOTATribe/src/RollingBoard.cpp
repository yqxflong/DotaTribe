#include "../include/RollingBoard.h"
#include "../include/CCRectClipNode.h"
#include "../include/TimeSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/CPublicVarReader.h"



DulNodeList::DulNodeList()
{
	m_vNodeList.clear();
	m_nSize = 0;
}

DulNodeList::~DulNodeList()
{
	m_vNodeList.clear();
	m_nSize = 0;
}

void DulNodeList::PushBack(CCNode * node)
{
	m_vNodeList.push_back(node);
	++m_nSize;
}

CCNode * DulNodeList::GetNodeById(int id)
{
	if(id < 0)
	{
		id += 10;
	}
	int t = id % m_nSize;
	CCNode * node = m_vNodeList[t];
	return node;
}

RollingBoard::RollingBoard()
{
	m_vBoardPicPath.clear();
	m_sBoardPath = "";
	m_nResultNumber = 0;
	m_fDuringTime = 0;
	m_pCallBack = NULL;
	m_nCallBackScript = 0;

	m_nShowingId = 0;
	m_A = 1;
	m_fDistance = 80;

	totalTime = 0;
	movetime = 0;
	actionResult = 0;
	ConstDestActionResult = (1 << 10) - 1;

	mileStone1 = 0;
	mileStone2 = 0;
	mileStone3 = 0;

	t = 0;
	c = 0;
	n = 0;
	ca = 0;
}

RollingBoard::~RollingBoard()
{

}

RollingBoard * RollingBoard::create(std::string numPathTemplate, int picNum, std::string boardPath, int resultNumber, float duringTime, AnimationEffectCallBackProtocol * pDelegate, float distance, float w, float h, float rpx, float rpy)
{
	RollingBoard * board = new RollingBoard();

	std::vector<std::string> filePath;
	filePath.clear();
	char path[128];
	for(int i = 0; i < picNum; ++i)
	{
		sprintf(path, numPathTemplate.c_str(), i);
		filePath.push_back(path);
	}

	if(board && board->init(filePath, boardPath, resultNumber, duringTime, pDelegate, distance, w, h, rpx, rpy))
	{
		board->autorelease();
	}
	else
	{
		delete board;
		board = NULL;
	}
	
	return board;
}

bool RollingBoard::init(std::vector<std::string> filePath, std::string boardPath, int resultNumber, float duringTime, AnimationEffectCallBackProtocol * pDelegate, float distance, float w, float h, float rpx, float rpy)
{
	for(unsigned int i = 0; i < filePath.size(); ++i)
	{
		m_vBoardPicPath.push_back(filePath[i]);
	}
	m_sBoardPath = boardPath;

	m_fDistance = distance;

	m_fDuringTime = duringTime;
	
	SetResultNum(resultNumber);

	m_pCallBack = pDelegate;


	//创建裁剪框
	CCRectClipNode * clip = CCRectClipNode::create(CCRectMake(rpx, rpy, w, h));
	this->addChild(clip, 0, 0);

	//创建一组滚筒图片
	CCNode * cardParent = CCNode::create();
	clip->addChild(cardParent, 0, 0);
	BlurSprite * boardPic = NULL;
	BlurSprite * numPic = NULL;
	for(unsigned int i = 0; i < m_vBoardPicPath.size(); ++i)
	{
		boardPic = BlurSprite::create(m_sBoardPath.c_str(), cc_shader_blur_vertical);
		numPic = BlurSprite::create(m_vBoardPicPath[i].c_str(), cc_shader_blur_vertical);
		numPic->setAnchorPoint(ccp(0.5f, 0.5f));
		numPic->setPosition(ccp(boardPic->getContentSize().width / 2, boardPic->getContentSize().height / 2));
		boardPic->addChild(numPic, 0, 100);//需要绑定它自己和自己的子节点

		cardParent->addChild(boardPic, 0, i);
		m_lNodeList.PushBack(boardPic);
	}
	//初始时将这些卡片排列好顺序：0号卡片在显示框中，9号在0上方，0下方依次为1--8
	SetCardsPosition();


	return true;
}


void RollingBoard::RegisterCallBackScript(int nScript)
{
	if (m_nCallBackScript)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nCallBackScript);
	}
	m_nCallBackScript = nScript;

}

void RollingBoard::SetResultNum(int number)
{
	m_nResultNumber = number;
	CalculateMileStone();
}

void RollingBoard::Run()
{
	totalTime = 0;
	movetime = 0;

	n = 0;
	ca = 0;
	c = 0;

	t = TIMESYSTEM->GetCurrentMicroSecond();

	ResetZero();

	Move();

}

void RollingBoard::Stop()
{

}

void RollingBoard::ResetZero()
{
	m_nShowingId = 0;

	actionResult = 0;

	SetCardsPosition();
}

void RollingBoard::DoCallBack()
{//开始回调

	for(unsigned int i = 0; i < m_vBoardPicPath.size(); ++i)
	{
		BlurSprite * bnode = (BlurSprite *)m_lNodeList.GetNodeById(i);
		bnode->setBlurSize(0);
	}

	if(m_pCallBack)
	{
		m_pCallBack->EffectCallBackEventHandler(this->getTag(), this, NULL);
	}

	if(m_nCallBackScript)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nCallBackScript, "CallBack", this->getTag(), "");
	}

	LOGGERSYSTEM->LogInfo("actural used time :%f", n);
	LOGGERSYSTEM->LogInfo("calculate used time : %f \n", ca);
	LOGGERSYSTEM->LogInfo("wucha time : %f \n", c);
}

void RollingBoard::Move()
{
	long long t1 = TIMESYSTEM->GetCurrentMicroSecond();
	t = t1 - t;
	float x = (float)t / 1000000;
	//LOGGERSYSTEM->LogInfo("now :%f", x);
	//LOGGERSYSTEM->LogInfo("calculate : %f \n", movetime);
	c = c + x - movetime;
	n = n + x;//实际
	ca = ca + movetime;//计算


	t = t1;


	//将当前时间加上之前的时间计时
	totalTime += movetime;

	//需要这些节点都一起运动
	CCNode * node = NULL;
	movetime = CalculateSpentTime(totalTime);
	for(unsigned int i = 0; i < m_vBoardPicPath.size(); ++i)
	{//将所有卡牌向它的上一个卡牌位置移动
		node = m_lNodeList.GetNodeById(i);
		BlurSprite * bnode = (BlurSprite *)node;
		float sz = CalculateBlurSize();
		bnode->setBlurSize(sz);
		CCPoint dest = node->getPosition();
		dest.y += m_fDistance;
		CCMoveTo * moveUp = CCMoveTo::create(movetime, dest);
		node->runAction(CCSequence::create(moveUp, CCCallFuncN::create(this, callfuncN_selector(RollingBoard::MoveToCallback)), NULL));

	}

	//当前运动是在展示 m_nShowingId
	m_nShowingId ++;//即将要展示的数字
}

float RollingBoard::CalculateSpentTime(float nowTime)
{
	//计算当前位移distance所需要花费的时间，使用以下公式：
	//前0.3s，需要从0滚动到9，其实就是展示数字是前9时
	//中间时间未知，需要计算（中间经过10的整数倍 + (destNum+1)%10 + 1 这么多的卡片）
	//后0.3秒，需要从 (destNum+1)%10 滚动到destNum
	
	float nowSpeed = 0;

	if(m_nShowingId < mileStone1)
	{//
		nowSpeed = 700 * (m_nShowingId + 1);
	}
	else if(m_nShowingId < mileStone2)
	{
		nowSpeed = 3000;
	}
	else
	{
		nowSpeed = 2547 - 283 * (m_nShowingId - mileStone2);
	}

	float time = m_fDistance / nowSpeed;

	return time;
}

float RollingBoard::CalculateBlurSize()
{
	float size = 0;

	if(m_nShowingId < mileStone1)
	{
		size = 10.0f / (10 - m_nShowingId);
	}
	else if(m_nShowingId < mileStone2)
	{
		size = 10.0f;
	}
	else
	{
		size = 10.0f / (m_nShowingId - mileStone2);
	}

	return size;
}

void RollingBoard::CalculateMileStone()
{
	mileStone1 = 9;
	mileStone2 = mileStone1 + (int)(((m_fDuringTime - 2) * 2547 / (m_fDistance * 10))) * 10 + (m_nResultNumber + 1) % 10 + 1;
	mileStone3 = 9 + mileStone2;
}

void RollingBoard::SetCardsPosition()
{
	//依照当前展示的卡牌的Id将这些卡牌位置重新设置
	CCNode * node = m_lNodeList.GetNodeById(m_nShowingId);
	node->setPositionY(0.0f);
	node = m_lNodeList.GetNodeById(m_nShowingId - 1);
	node->setPositionY(0 + m_fDistance);
	for(unsigned int i = 1; i < m_vBoardPicPath.size() - 1; i++)//后8个数
	{
		node = m_lNodeList.GetNodeById(m_nShowingId + i);
		node->setPositionY(0 - m_fDistance * i);
	}
}

void RollingBoard::MoveToCallback(CCNode* sender)
{
	//当前运动的节点
	int tag = sender->getTag();
	//检验当前节点的位置是不是在允许范围内，如果不是，则将当前节点向下移动
	if(sender->getPositionY() > m_fDistance)
	{
		sender->setPositionY(0 - 8 * m_fDistance);
	}

	actionResult = actionResult | (1 << tag);
	if(actionResult == ConstDestActionResult)
	{//说明当前所有节点均已完成上一次运动，此时需要计算下一次运动
		actionResult = 0;
		if(m_nShowingId == mileStone3)
		{
			//已完成滚动，需要停止
			DoCallBack();
		}
		else
		{
			Move();
		}
	}
}
