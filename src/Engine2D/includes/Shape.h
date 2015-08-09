#ifndef SHAPE_H
#define SHAPE_H
#include "Entity2D.h"
#include "Defines.h"

namespace Engine{
class ENGINE_API Shape : public Entity2D{
private:
	DWORD m_Color;

public:
	Shape();
	~Shape();
	virtual void SetColor(DWORD color);
	DWORD GetColor();
};
}


#endif	// SHAPE_H