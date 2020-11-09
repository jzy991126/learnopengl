#include "JTool/j_op.h"

JOp::JOp(std::function<void()> op):op(op)
{
}

void JOp::operator()()
{
	op();
}

