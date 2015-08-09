#include "Animation.h"
#include "Timer.h"
using namespace Engine;


Animation::Animation() : m_uiCurrentFrame(0), m_fCurrentTime(0), m_fLength(0){

}

void Animation::AddFrame(float fTextureWidth, float fTextureHeight, float fFramePosX, float fFramePosY,float fFrameWidth, float fFrameHeight){
	Frame rkFrame;
	rkFrame.U1 = (fFramePosX / fTextureWidth);
	rkFrame.V1 = (fFramePosY / fTextureHeight);

	rkFrame.U2 = ( (fFramePosX + fFrameWidth) / fTextureWidth);
	rkFrame.V2 = (fFramePosY / fTextureHeight);

	rkFrame.U3 = (fFramePosX / fTextureWidth);
	rkFrame.V3 = ( (fFramePosY + fFrameHeight) / fTextureHeight);

	rkFrame.U4 = ( (fFramePosX + fFrameWidth) / fTextureWidth);
	rkFrame.V4 = ( (fFramePosY + fFrameHeight)/ fTextureHeight);

	m_akFrames.push_back(rkFrame);
}



void Animation::ResetFrames(){
	m_uiCurrentFrame = 0;
}



void Animation::Update(Timer& pkTimer){
	m_fCurrentTime += pkTimer.GetDT();
	
	while(m_fCurrentTime > m_fLength){
		m_fCurrentTime -= m_fLength;
	}

	m_uiCurrentFrame = static_cast<unsigned int>((m_fCurrentTime / m_fLength) * m_akFrames.size());
}



void Animation::SetLength(float Length){
	m_fLength = Length;
}



void Animation::SetName(std::string _name){
	_Name = _name;
}


std::string Animation::GetName() const{
	return _Name;
}