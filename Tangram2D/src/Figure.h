#ifndef FIGURE_H
#define FIGURE_H
#include <CGJ/Graphics.h>
#include <CGJ/Maths.h>

class Figure {
	public:
		Figure();
		Figure(const cgj::Vector3& pos, float rotation, float scale);
		~Figure() = default;
		void draw(cgj::ShaderProgram& s);
		void addData(const cgj::ModelMesh& mesh);
	private:
		cgj::Matrix4 m_transform;
		cgj::Model m_model;	
};
#endif