#include "DebugMessage.h"
#include "GameLogic.h"

std::string CDebugMessage::debugMessage[6];

CDebugMessage::CDebugMessage(void)
{
}

CDebugMessage::~CDebugMessage(void)
{
}

void CDebugMessage::AddMessage(std::string msg)
{
	//if (debugOn)
	//{
	//	for ( int i = 5; i > 0; i-- )
	//		debugMessage[i].swap(debugMessage[i-1]);
	//}
	//else
	//{
	//		debugMessage[0] = "LOL";
	//		debugMessage[1] = "LOL";
	//		debugMessage[2] = "LOL";
	//		debugMessage[3] = "LOL";
	//		debugMessage[4] = "LOL";
	//		debugMessage[5] = "LOL";
	//}

	//	if (msg.size() > 32)
	//	msg.resize(32);

	//	debugMessage[0] = msg;

	//	debugOn = true;
}

void CDebugMessage::ClearDebug()
{
	//for (int i = 0;i<5;i++)
	//	debugMessage[i].clear();
}

void CDebugMessage::Draw()
{
	//for (int i = 0;i<5;i++)
	//	CGameLogic::DrawText(CGameLogic::screen, debugMessage[i], 8, 8+(i*32), 255,255,255, false );
}