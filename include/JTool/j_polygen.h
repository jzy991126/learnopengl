#ifndef J_POLYGEN_H
#define J_POLYGEN_H

#include "JTool/shader.h"

class JPolygen
{
public:

	JPolygen(float* vertices,int size,int count);
	unsigned int getVAO();
	~JPolygen();
	void draw(Shader &shader);
	void setAttrib(int index,int count,int all_count,int offset);

private:
	unsigned int VAO, VBO;
	int count;


};



#endif // !J_POLYGEN_H
