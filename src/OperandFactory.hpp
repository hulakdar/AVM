#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "IOperand.hpp"

class OperandFactory
{
private:
    IOperand const* createInt8(std::string const& value) const;
    IOperand const* createInt16(std::string const& value) const;
    IOperand const* createInt32(std::string const& value) const;
    IOperand const* createFloat(std::string const& value) const;
    IOperand const* createDouble(std::string const& value) const;

	OperandFactory();
public:
    IOperand const* createOperand(EOperandType type, std::string const& value) const;

    static OperandFactory *Get();
};
