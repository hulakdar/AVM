
#include "VirtualMachine.hpp"

std::vector<std::unique_ptr<const IOperand>>	VirtualMachine::s_Stack;
std::vector<std::unique_ptr<const IOperand>>	VirtualMachine::s_Arguments;
bool											VirtualMachine::s_Exit = false;