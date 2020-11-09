#ifndef j_opqueue_h
#define j_opqueue_h
#include<vector>
#include<functional>
#include"JTool/j_op.h"

class JOpQueue
{
public:
	JOpQueue();
	JOpQueue& operator<<(JOp &op);
	void run();


private:
	std::vector<std::function<void()>> oplist;



};

#endif // !j_opqueue_h
