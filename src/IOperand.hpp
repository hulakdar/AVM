#pragma once
#include <string>

typedef enum {
	Int8,
	Int16,
	Int32,
	Float,
	Double
} EOperandType;

class IOperand {
   public:
    virtual int GetPrecision(void) const = 0;
    virtual EOperandType GetType(void) const = 0;
    virtual IOperand const* operator+(IOperand const& rhs) const = 0;
    virtual IOperand const* operator-(IOperand const& rhs) const = 0;
    virtual IOperand const* operator*(IOperand const& rhs) const = 0;
    virtual IOperand const* operator/(IOperand const& rhs) const = 0;
    virtual IOperand const* operator%(IOperand const& rhs) const = 0;
    virtual IOperand const* operator^(IOperand const& rhs) const = 0;
    virtual bool operator==(IOperand const& rhs) const = 0;
    virtual bool operator!=(IOperand const& rhs) const = 0;
    virtual std::string const& ToString(void) const = 0;
    virtual ~IOperand(void) {}
};
