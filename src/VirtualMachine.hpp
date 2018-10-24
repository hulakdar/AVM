#pragma once
#include <vector>
#include "IOperand.hpp"

namespace VirtualMachine
{
	extern std::vector<std::unique_ptr<const IOperand>> s_Stack;
};