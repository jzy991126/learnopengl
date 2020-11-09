#include"JTool/j_opqueue.h"

JOpQueue::JOpQueue()
{

}

JOpQueue& JOpQueue::operator<<(JOp &op)
{
	oplist.push_back(op);
	return *this;
}

void JOpQueue::run()
{
	for (auto op : oplist)
	{
		op();
	}
}
