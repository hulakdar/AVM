
#include "VirtualMachine.hpp"

std::vector<std::unique_ptr<const IOperand>> VirtualMachine::s_Stack;
bool   s_Exit = false;