#include "Entity2D.h"
#include "Renderer.h"
using namespace Engine;


Entity2D::Entity2D(){
	_x = 0;
	_y = 0;
	_z = 0;
	_w = 0;
	_h = 0;
	_rot = 0;
	m_name = "New Entity";
	m_sColsGroup = "";
}


Entity2D::~Entity2D(){

}



void Entity2D::SetPosition(float x, float y){
	SetPreviousPosition();
	_x = x;
	_y = y;
	_z = 1;
}


void Entity2D::SetPreviousPosition(){
	_prevX = _x;
	_prevY = _y;
	_z = 1;
}


void Entity2D::SetScale(float w, float h){
	_w = w;
	_h = h;
}


void Entity2D::SetRotation(float r){
	_rot = r;
}




float Entity2D::GetPositionX() const{
	return _x;
}



float Entity2D::GetPositionY() const{
	return _y;
}



void Entity2D::GetPositionXY(float& x, float& y){
	x = _x;
	y = _y;
}



float Entity2D::GetPreviousX() const{
	return _prevX;
}



float Entity2D::GetPreviousY() const{
	return _prevY;
}



float Entity2D::GetScaleX() const{
	return _w;
}



float Entity2D::GetScaleY() const{
	return _h;
}


void Entity2D::GetScaleXY(float& x, float& y){
	x = _w;
	y = _h;
}



float Entity2D::GetRotation(){
	return _rot;
}



void Entity2D::Draw(Renderer* renderer){
	renderer->SetMatrixMode(World);
	renderer->LoadIdentity();
	renderer->Translate(_x, _y);
	renderer->Scale(_w, _h);
	renderer->SetTexture(NULL);
}



void Entity2D::SetName(std::string name){
	m_name = name;
}



std::string Entity2D::GetName(){
	return m_name;
}



const std::string& Entity2D::GetCollisionsGroup() const{
	return m_sColsGroup;
}



void Entity2D::SetCollisionsGroup(std::string colsGroup){
	m_sColsGroup = colsGroup;
}


Entity2D::CollisionResult Entity2D::CheckCollision(Entity2D& r_Entity2D) const{
        float fOverlap_X = std::max(0.0f, std::min(GetPositionX() + fabs(GetScaleX()) / 2.0f, r_Entity2D.GetPositionX() + fabs(r_Entity2D.GetScaleX()) / 2.0f) -  
										  std::max(GetPositionX() - fabs(GetScaleX()) / 2.0f, r_Entity2D.GetPositionX() - fabs(r_Entity2D.GetScaleX()) / 2.0f)
        );
        float fOverlap_Y = std::max(0.0f, std::min(GetPositionY() + fabs(GetScaleY()) / 2.0f, r_Entity2D.GetPositionY() + fabs(r_Entity2D.GetScaleY()) / 2.0f) -  
										  std::max(GetPositionY() - fabs(GetScaleY()) / 2.0f, r_Entity2D.GetPositionY() - fabs(r_Entity2D.GetScaleY()) / 2.0f)
        );

        if(fOverlap_X != 0.0f && fOverlap_Y != 0.0f){
            if(fOverlap_X > fOverlap_Y){
				return VerticalCollision;
			}
			else{
				return HorizontalCollision;
			}
        }

        return NoCollision;
}