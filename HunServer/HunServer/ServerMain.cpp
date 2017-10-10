// HunServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	
	cIocpManager* server = cIocpManager::getInstance();
	cEventManager* eventManager = cEventManager::getInstance();

	server->Begin();
	eventManager->ResistEvent(1 + MONSTER_ID_START, MonsterEvent::MOVE, 1000 + GetTickCount());
	eventManager->ResistEvent(2 + MONSTER_ID_START, MonsterEvent::MOVE, 1000 + GetTickCount());
	eventManager->ResistEvent(3 + MONSTER_ID_START, MonsterEvent::MOVE, 1000 + GetTickCount());
	while (true)
	{
		Sleep(1);
		cEvent evt;
		while (eventManager->eventVec.empty() == false) {
			/*for (auto iter = eventManager->eventVec.begin(); iter != eventManager->eventVec.end(); ++iter) {
				if ((*iter).getWakeTime() > GetTickCount())
					continue;
				eventManager->PostEventToQueue((*iter));
				gLock.lock();
				eventManager->eventVec.erase(iter);
				gLock.unlock();
			}*/
			auto Event = eventManager->eventVec.front();
			if (Event.getWakeTime() > GetTickCount())
				continue;
			eventManager->PostEventToQueue(Event);
			eventManager->eventVec.erase(eventManager->eventVec.begin());
		}
	}
}

