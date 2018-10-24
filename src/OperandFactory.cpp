#include "OperandFactory.hpp"
#include "TOperand.hpp"

OperandFactory::OperandFactory() {}

IOperand const* OperandFactory::createInt8(std::string const& Value) const {
    return (new TOperand<char>(Value));
}

IOperand const* OperandFactory::createInt16(std::string const& Value) const {
    return (new TOperand<short>(Value));
}

IOperand const* OperandFactory::createInt32(std::string const& Value) const {
    return (new TOperand<int>(Value));
}

IOperand const* OperandFactory::createFloat(std::string const& Value) const {
    return (new TOperand<float>(Value));
}

IOperand const* OperandFactory::createDouble(std::string const& Value) const {
    return (new TOperand<double>(Value));
}

IOperand const* OperandFactory::createOperand(EOperandType type,
					      std::string const& Value) const {
    const static IOperand * (OperandFactory::*funcs[])(std::string const&)const = {
	&OperandFactory::createInt8, &OperandFactory::createInt16, &OperandFactory::createInt32,
	&OperandFactory::createFloat, &OperandFactory::createDouble};

    return (this->*(funcs[type]))(Value);
}

OperandFactory *OperandFactory::Get()
{
	static std::unique_ptr<OperandFactory> s_OperandFactory(new OperandFactory());
    return s_OperandFactory.get();
}