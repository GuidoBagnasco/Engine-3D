#include "Timer.h"
using namespace Engine;


Timer::Timer(){
	m_kDeltaTime = 0;
	m_uiFPS = 0;
	m_uiFrameCounter = 0;
	m_dMeasureFPSSample = 0;
}


void Timer::FirstMeasure(){
	QueryPerformanceFrequency(&m_kFrequency);
	QueryPerformanceCounter(&m_kLastTime);
}


void Timer::Measure(){
	QueryPerformanceCounter(&m_kActualTime);
	m_kDeltaTime = static_cast<double>((m_kActualTime.QuadPart - m_kLastTime.QuadPart) * 1000.0f / m_kFrequency.QuadPart);

	m_kLastTime = m_kActualTime;
	m_uiFrameCounter++;
	m_dMeasureFPSSample += m_kDeltaTime;

	if(m_dMeasureFPSSample >= 1000){
		m_dMeasureFPSSample -= 1000;
		m_uiFPS = m_uiFrameCounter;
		m_uiFrameCounter = 0;
	}
}


double Timer::GetDT(){
	return m_kDeltaTime;
}


unsigned int Timer::GetFPS(){
	return m_uiFPS;
}