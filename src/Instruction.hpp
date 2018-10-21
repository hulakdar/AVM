#pragma once
#include <functional>

class Instruction
{
	std::function<bool(const std::string &)> _Func;
	std::string _Operand;
public:
	Instruction(std::function<bool(const std::string &)> Func, const std::string& Operand);

	bool Execute();
};