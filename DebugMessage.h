#pragma once

#include <string>

class CDebugMessage
{
public:
	CDebugMessage(void);
	~CDebugMessage(void);

	static void AddMessage(std::string msg);
	static void ClearDebug();
	static void Draw();

	static bool debugOn;

private:
	static std::string debugMessage[6];

};
