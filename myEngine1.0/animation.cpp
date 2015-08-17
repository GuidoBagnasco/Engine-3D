#include "animation.h"
#include "timer\pg1_timer.h"

using namespace engine;
Animation::Animation() : m_uiCurrentFrame(0), m_fCurrentTime(0), m_fLength(1.0f){
	// Bleh
}
Animation::~Animation(){
	m_akFrames.clear();
}
unsigned int Animation::currentFrame() const{
	return m_uiCurrentFrame;
}

void Animation::addFrame(float fTextureWidth, float fTextureHeight, float fFramePosX,	 float fFramePosY,float fFrameWidth,   float fFrameHeight){
Frame rkFrame;
rkFrame.u1 = (fFramePosX / fTextureWidth);
rkFrame.v1 = (fFramePosY / fTextureHeight);

rkFrame.u2 = ( (fFramePosX + fFrameWidth) / fTextureWidth);
rkFrame.v2 = (fFramePosY / fTextureHeight);

rkFrame.u3 = (fFramePosX / fTextureWidth);
rkFrame.v3 = ( (fFramePosY + fFrameHeight) / fTextureHeight);

rkFrame.u4 = ( (fFramePosX + fFrameWidth) / fTextureWidth);
rkFrame.v4 = ( (fFramePosY + fFrameHeight)/ fTextureHeight);

m_akFrames.push_back(rkFrame);
}

void Animation::resetFrames(){
	m_uiCurrentFrame = 0;
}

void Animation::update(Timer& rkTimer){
	m_fCurrentTime += rkTimer.timeBetweenFrames();
	while(m_fCurrentTime > m_fLength){
		m_fCurrentTime-= m_fLength;
	}
	m_uiCurrentFrame = static_cast<unsigned int>((m_fCurrentTime / m_fLength) * m_akFrames.size());
}

void Animation::setLength(float Length){
	m_fLength = Length;
}

void Animation::setName(std::string _name){
	_Name = _name;
}

std::string Animation::getName() const{
	return _Name;
}