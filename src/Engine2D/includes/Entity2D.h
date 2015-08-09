#ifndef ENTITY2D
#define ENTITY2D
#include "Defines.h"
#include <iostream>
#include <string>

namespace Engine{
class Renderer;
class Timer;


class ENGINE_API Entity2D{
private:
	float _x, _y, _z;
	float _prevX, _prevY;
	float _w, _h;
	float _rot;
	std::string m_name;
	std::string m_sColsGroup;

public:
	Entity2D();
	~Entity2D();
	virtual void Draw(Renderer* renderer);
	virtual void Update(Timer& pkTimer) { }
	//------------------Setters------------------//
	void SetScale(float w, float h);
	void SetPosition(float x, float y);
	void SetPreviousPosition();
	void SetRotation(float fRotation);

	//------------------Getters------------------//
	// Position
	float GetPositionX() const;
	float GetPositionY() const;
	void GetPositionXY(float& x, float& y);
	float GetPreviousX() const;
	float GetPreviousY() const;
	// Scale
	float GetScaleX() const;
	float GetScaleY() const;
	void GetScaleXY(float& x, float& y);
	// Rotation
	float GetRotation();


	// Name
	void SetName(std::string name);
	std::string GetName();

	// Collisions
	enum CollisionResult{
			VerticalCollision = 0,
			HorizontalCollision = 1,
			NoCollision = 2
	};

	const std::string& GetCollisionsGroup() const;
	void SetCollisionsGroup(std::string ColGroup);
	CollisionResult CheckCollision(Entity2D& r_Entity2D) const;
};
}

#endif	// ENTITY2D