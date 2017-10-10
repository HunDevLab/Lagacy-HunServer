#include "stdafx.h"
#include "cEvent.h"


cEvent::cEvent()
{
}


cEvent::~cEvent()
{
}

void cEvent::SetEvent(int paraId, int paraType, unsigned long paraWakeTime)
{
	objId = paraId;
	type = paraType;
	wakeTime = paraWakeTime;
}