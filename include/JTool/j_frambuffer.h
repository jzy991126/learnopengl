#ifndef J_FRAMBUFFER_H
#define J_FRAMBUFFER_H


class JFrambuffer
{
public:
	JFrambuffer(int width,int height);
	~JFrambuffer();
	unsigned int getFrambuffer();
	unsigned int getTexturebuffer();
	unsigned int getRBO();
	void bind();
	void unbind();
private:
	unsigned int framebuffer, textureColorbuffer, rbo;

};






#endif