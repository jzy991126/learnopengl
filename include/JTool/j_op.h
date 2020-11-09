#ifndef J_OP_H
#define J_OP_H

#include<functional>

class JOp
{
public:
	JOp(std::function<void()> op);
	void operator()();
private:
	std::function<void()> op;

};


#endif // !J_OP_H
