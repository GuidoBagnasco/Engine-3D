#include "Entity.h"

namespace engine{
	class Renderer;
	class MYENGINE_API Quad : public Entity{
	public:
		Quad();
		~Quad();
		void setColor(DWORD c);
		void setColor(DWORD c, int v);
	private:
		ColorVertex* _Vertex;
	public:
		void draw(Renderer& r) const;
	};
}