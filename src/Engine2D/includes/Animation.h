#ifndef ANIMATION_H
#define ANIMATION_H
#include "Defines.h"
#include <vector>
#include <string>

namespace Engine{
class Timer;

class ENGINE_API Animation{
	public:
		Animation();
		~Animation(){ m_akFrames.clear(); }
		struct Frame{
			float U1; float V1;
			float U2; float V2;
			float U3; float V3;
			float U4; float V4;
		};
		unsigned int m_uiCurrentFrame;
		unsigned int currentFrame() const { return m_uiCurrentFrame; };

		const std::vector<Frame>& Frames() const  { return m_akFrames; }
		void AddFrame ( float fTextureWidth, float fTextureHeight,  float fFramePosX, float fFramePosY, float fFrameWidth, float fFrameHeight);

		void SetLength (float fLength);
		void Update(Timer& pkTimer);
		void ResetFrames();
		void SetName(std::string _name);
		std::string GetName() const;

	private:

		float m_fCurrentTime;
		float m_fLength;
		std::string _Name;
		std::vector<Frame> m_akFrames;
};
}

#endif