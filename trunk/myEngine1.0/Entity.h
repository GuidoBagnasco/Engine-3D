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
		void SetPos(float fPosX, float fPosY);
		void SetPos(float fPosX, float fPosY, float fPosZ);
		void SetRotation(float fRotation);
		void SetScale(float fScale, float fScaleY, float fScaleZ = 1.0f);
		float PosX() const;
		float PosY() const;
		float PosZ() const;
		float Rotation() const;
		float ScaleX() const;
		float ScaleY() const;
		float ScaleZ() const;

		void ReturnToPreviousPos();

		virtual void Draw() const = 0;
		virtual void Update(Timer&) { }

		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision,
			CollisionZ
		};

		CollisionResult CheckCollision(Entity& rkEntity2D) const;
		void Entity::DrawAABB(Renderer& rkRenderer) const;
		const std::string& GetCollisionGroup() const { return m_sColGroup; }
		void SetCollisionGroup(std::string ColGroup) { m_sColGroup = ColGroup; }

		void SetName(std::string n) { m_sName = n; }
		std::string GetName() { return m_sName;  }

	private:
		float _PosX, _PosY, _PosZ;
		float _Rot;
		float _ScaleX;
		float _ScaleY;
		float _ScaleZ;

		float m_fPrevPosX, m_fPrevPosY, m_fPrevPosZ;
		std::string m_sColGroup;
		std::string m_sName;
		void UpdateLocalTransformation();

	protected:
		Matrix _TrMatrix;
		VertexBuffer * p_vb;
		IndexBuffer * p_ib;
	};
}