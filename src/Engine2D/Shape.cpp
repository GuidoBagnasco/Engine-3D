#include "Shape.h"
using namespace Engine;

Shape::Shape(){
	m_Color = 0;
}


Shape::~Shape(){

}



void Shape::SetColor(DWORD color){
	m_Color = color;
}



DWORD Shape::GetColor(){
	return m_Color;
}
