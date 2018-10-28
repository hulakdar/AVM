#include "Instruction.hpp"

Instruction::Instruction(std::function<bool(const IOperand *)>& Func, const IOperand *Operand) :
    _Func(Func),
    _Operand(Operand)
{

} 
 
bool Instruction::Execute() const {
    return _Func(_Operand);
}


Instruction::Instruction(const Instruction& Other)
{
    *this = Other;
}

Instruction& Instruction::operator=(const Instruction& Other) {
    _Func = Other._Func;
    _Operand = Other._Operand;
    return *this;
}

Instruction::~Instruction() {}