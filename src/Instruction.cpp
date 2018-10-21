#include "Instruction.hpp"

Instruction::Instruction(std::function<bool(const std::string &)> Func, const std::string& Operand) : _Func(Func), _Operand(Operand) { }

bool Instruction::Execute() { return _Func(_Operand); }
