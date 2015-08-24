#pragma once
#include "./myEngine_API.h"
#include <vector>
#include <string>
namespace engine{
class Timer;
	class MYENGINE_API Animation{
	public:
		Animation();
		~Animation();
		struct Frame{
			float u1;	float v1;
			float u2;	float v2;
			float u3;	float v3;
			float u4;	float v4;
		};
		unsigned int m_uiCurrentFrame;
		unsigned int currentFrame() const;
		const std::vector<Frame> &frames () const { return m_akFrames; }
		void addFrame (float fTextureWidth, float fTextureHeight, 
					   float fFramePosX,	float fFramePosY,
					   float fFrameWidth,	float fFrameHeight
		);
	private:
		std::vector<Frame> m_akFrames;
	public:
		void setLength(float fLength);
		void update(Timer& rkTimer);
		void resetFrames();
		void setName(std::string _name);
		std::string getName() const;
	private:
		float m_fCurrentTime;
		float m_fLength;
		std::string _Name;
	};
}