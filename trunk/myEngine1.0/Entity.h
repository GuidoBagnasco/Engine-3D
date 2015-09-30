#pragma once
#include "EMath.h"
#include <string>
#include "RenderTypes.h"
#include "myEngine_API.h"



namespace engine{
	class Renderer;
	class Timer;
	class VertexBuffer;
	class IndexBuffer;
	class MYENGINE_API Entity{
	public:
		Entity();
		~Entity();
	public:
		virtual void Update(Timer&){ }

		const std::string& GetCollisionGroup() const { return m_sColGroup; }
		void SetCollisionGroup(std::string ColGroup) { m_sColGroup = ColGroup; }

		void SetName(std::string n) { m_sName = n; }
		std::string GetName() { return m_sName;  }

	private:
		std::string m_sColGroup;
		std::string m_sName;

	protected:
		VertexBuffer * p_vb;
		IndexBuffer * p_ib;
	};
}