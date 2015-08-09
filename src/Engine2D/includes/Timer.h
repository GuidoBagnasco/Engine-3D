#ifndef TIMER_H
#define TIMER_H
#include "Defines.h"

namespace Engine{
class ENGINE_API Timer{
	LARGE_INTEGER m_kFrequency;
	LARGE_INTEGER m_kActualTime;
	LARGE_INTEGER m_kLastTime;
	double m_kDeltaTime;

	double m_dMeasureFPSSample;
	unsigned int m_uiFPS;
	unsigned int m_uiFrameCounter;
	void FirstMeasure();
	void Measure();
public:
	Timer();
	friend class Game;
	double GetDT();
	unsigned int GetFPS();
};
}

#endif