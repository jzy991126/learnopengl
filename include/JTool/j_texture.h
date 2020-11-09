#ifndef J_TEXTURE_H
#define J_TEXTURE_H

#include<string>

class JTexture
{
public:
	JTexture(std::string filepath);
	unsigned int getID();

private:
	unsigned int id;


};


#endif // !J_TEXTURE_H
