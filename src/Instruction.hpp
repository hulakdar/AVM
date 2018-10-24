#pragma once
#include <functional>
#include "IOperand.hpp"

class Instruction
{
	std::function<bool (const IOperand *)> _Func;
	const IOperand *_Operand;
public:
	Instruction(std::function<bool(const IOperand *)> Func, const IOperand *Operand);

	bool Execute() const;
};