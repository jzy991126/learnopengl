#include"JTool/j_polygen.h"
#include<glad/glad.h>


JPolygen::JPolygen(float* vertices,int size,int count):count(count)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


    glBindVertexArray(VAO);
}

void JPolygen::draw(Shader &shader)
{
    shader.use();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, count);
}

unsigned int JPolygen::getVAO()
{
    return VAO;
}

JPolygen::~JPolygen()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void JPolygen::setAttrib(int index, int count, int all_count, int offset)
{

    glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, all_count * sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(index);
}