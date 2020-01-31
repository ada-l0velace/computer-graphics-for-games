#include "Figure.h"

Figure::Figure() {
    m_transform = cgj::MatrixFactory::CreateTransformMatrix(0.0f,0.0f,0.0f,0.0f,1.0f);
}

Figure::Figure(const cgj::Vector3& pos, float rotation, float scale) {
    m_transform = cgj::MatrixFactory::CreateTransformMatrix(pos.x,pos.y,pos.z,rotation,scale);
}

void Figure::addData(const cgj::ModelMesh& mesh) {
    m_model.addData(mesh);
}

void Figure::draw(cgj::ShaderProgram& s) {
    s.use();
    m_model.bindVAO();
    GLint uniformID = s.getUniformLocation("ModelMatrix");
    glUniformMatrix4fv(uniformID,1,GL_FALSE, m_transform.data);
    glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}