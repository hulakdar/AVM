#include "Instruction.hpp"

Instruction::Instruction(const std::function<bool(const IOperand *)>& Func, const IOperand *Operand) : _Func(Func), _Operand(Operand) { }

bool Instruction::Execute() const { return _Func(_Operand); }
