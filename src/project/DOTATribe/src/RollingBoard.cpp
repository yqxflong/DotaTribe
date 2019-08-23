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


	//�����ü���
	CCRectClipNode * clip = CCRectClipNode::create(CCRectMake(rpx, rpy, w, h));
	this->addChild(clip, 0, 0);

	//����һ���ͲͼƬ
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
		boardPic->addChild(numPic, 0, 100);//��Ҫ�����Լ����Լ����ӽڵ�

		cardParent->addChild(boardPic, 0, i);
		m_lNodeList.PushBack(boardPic);
	}
	//��ʼʱ����Щ��Ƭ���к�˳��0�ſ�Ƭ����ʾ���У�9����0�Ϸ���0�·�����Ϊ1--8
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
{//��ʼ�ص�

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
	n = n + x;//ʵ��
	ca = ca + movetime;//����


	t = t1;


	//����ǰʱ�����֮ǰ��ʱ���ʱ
	totalTime += movetime;

	//��Ҫ��Щ�ڵ㶼һ���˶�
	CCNode * node = NULL;
	movetime = CalculateSpentTime(totalTime);
	for(unsigned int i = 0; i < m_vBoardPicPath.size(); ++i)
	{//�����п�����������һ������λ���ƶ�
		node = m_lNodeList.GetNodeById(i);
		BlurSprite * bnode = (BlurSprite *)node;
		float sz = CalculateBlurSize();
		bnode->setBlurSize(sz);
		CCPoint dest = node->getPosition();
		dest.y += m_fDistance;
		CCMoveTo * moveUp = CCMoveTo::create(movetime, dest);
		node->runAction(CCSequence::create(moveUp, CCCallFuncN::create(this, callfuncN_selector(RollingBoard::MoveToCallback)), NULL));

	}

	//��ǰ�˶�����չʾ m_nShowingId
	m_nShowingId ++;//����Ҫչʾ������
}

float RollingBoard::CalculateSpentTime(float nowTime)
{
	//���㵱ǰλ��distance����Ҫ���ѵ�ʱ�䣬ʹ�����¹�ʽ��
	//ǰ0.3s����Ҫ��0������9����ʵ����չʾ������ǰ9ʱ
	//�м�ʱ��δ֪����Ҫ���㣨�м侭��10�������� + (destNum+1)%10 + 1 ��ô��Ŀ�Ƭ��
	//��0.3�룬��Ҫ�� (destNum+1)%10 ������destNum
	
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
	//���յ�ǰչʾ�Ŀ��Ƶ�Id����Щ����λ����������
	CCNode * node = m_lNodeList.GetNodeById(m_nShowingId);
	node->setPositionY(0.0f);
	node = m_lNodeList.GetNodeById(m_nShowingId - 1);
	node->setPositionY(0 + m_fDistance);
	for(unsigned int i = 1; i < m_vBoardPicPath.size() - 1; i++)//��8����
	{
		node = m_lNodeList.GetNodeById(m_nShowingId + i);
		node->setPositionY(0 - m_fDistance * i);
	}
}

void RollingBoard::MoveToCallback(CCNode* sender)
{
	//��ǰ�˶��Ľڵ�
	int tag = sender->getTag();
	//���鵱ǰ�ڵ��λ���ǲ���������Χ�ڣ�������ǣ��򽫵�ǰ�ڵ������ƶ�
	if(sender->getPositionY() > m_fDistance)
	{
		sender->setPositionY(0 - 8 * m_fDistance);
	}

	actionResult = actionResult | (1 << tag);
	if(actionResult == ConstDestActionResult)
	{//˵����ǰ���нڵ���������һ���˶�����ʱ��Ҫ������һ���˶�
		actionResult = 0;
		if(m_nShowingId == mileStone3)
		{
			//����ɹ�������Ҫֹͣ
			DoCallBack();
		}
		else
		{
			Move();
		}
	}
}
