#pragma once
#include "EMath.h"
#include <string>
#include "RenderTypes.h"
#include "myEngine_API.h"



namespace engine{
	class Renderer;
	class Timer;
	class MYENGINE_API Entity{
	public:
		Entity();
		~Entity();
	public:
		void setPos(float fPosX, float fPosY);
		void setPos(float fPosX, float fPosY, float fPosZ);
		void setRotation(float fRotation);
		void setScale(float fScale, float fScaleY, float fScaleZ = 1.0f);
		float posX() const;
		float posY() const;
		float posZ() const;
		float rotation() const;
		float scaleX() const;
		float scaleY() const;
		float scaleZ() const;

		void returnToPreviousPos();

		virtual void draw(Renderer&) const = 0;
		virtual void update(Timer&) { }

		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision,
			CollisionZ
		};

		CollisionResult checkCollision(Entity& rkEntity2D) const;
		void Entity::drawAABB(Renderer& rkRenderer) const;
		const std::string& getCollisionGroup() const { return m_sColGroup; }
		void setCollisionGroup(std::string ColGroup) { m_sColGroup = ColGroup; }

		void setName(std::string n) { m_sName = n; }
		std::string getName() { return m_sName;  }

	private:
		float _PosX, _PosY, _PosZ;
		float _Rot;
		float _ScaleX;
		float _ScaleY;
		float _ScaleZ;

		float m_fPrevPosX, m_fPrevPosY, m_fPrevPosZ;
		std::string m_sColGroup;
		std::string m_sName;
		void updateLocalTransformation();
	protected:
		Matrix _TrMatrix;
	};
}