#include "TOperand.hpp"

template<>
EOperandType TOperand<char>::GetType() const
{
	return Int8;
}

template<>
EOperandType TOperand<short>::GetType() const
{
	return Int16;
}

template<>
EOperandType TOperand<int>::GetType() const
{
	return Int32;
}

template<>
EOperandType TOperand<float>::GetType() const
{
	return Float;
}

template<>
EOperandType TOperand<double>::GetType() const
{
	return Double;
}

template<>
TOperand<char>::TOperand(const std::string& Value) :
	m_String(Value)
{
	int Tmp;
	Tmp = std::stoi(Value, 0, 0);
	if (Tmp > CHAR_MAX || Tmp < CHAR_MIN)
		throw std::out_of_range("Out of Int8 range");
	m_Value = Tmp;
}

template<>
TOperand<short>::TOperand(const std::string& Value) :
	m_String(Value)
{
	int Tmp;
	Tmp = std::stoi(Value, 0, 0);
	if (Tmp > SHRT_MAX || Tmp < SHRT_MIN)
		throw std::out_of_range("Out of Int16 range");
	m_Value = Tmp;
}

template<>
TOperand<int>::TOperand(const std::string& Value) :
	m_String(Value)
{
	int Tmp;
	try {
		Tmp = std::stoi(Value);
	}
	catch (std::out_of_range) {
		throw std::out_of_range("Out of Int32 range");
	}
	m_Value = Tmp;
}

template<>
TOperand<float>::TOperand(const std::string& Value) :
	m_String(Value)
{
	float Tmp;
	try {
		Tmp = std::stof(Value);
	}
	catch (std::out_of_range) {
		throw std::out_of_range("Out of Float range");
	}
	m_Value = Tmp;
}

template<>
TOperand<double>::TOperand(const std::string& Value) :
	m_String(Value)
{
	double Tmp;
	try {
		Tmp = std::stod(Value);
	}
	catch (std::out_of_range) {
		throw std::out_of_range("Out of Double range");
	}
	m_Value = Tmp;
}

template <typename L, typename R>
IOperand const *Add(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value + Rhs.m_Value));
}

template<typename L, typename R>
IOperand const * Substract(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value - Rhs.m_Value));
}

template<typename L, typename R>
IOperand const * Multiply(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value * Rhs.m_Value));
}

template<typename L, typename R>
IOperand const * Divide(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value / Rhs.m_Value));
}

template<typename L, typename R>
IOperand const *Modulo(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(std::remainder(Lhs.m_Value, Rhs.m_Value)));
}

template<typename L, typename R>
IOperand const * Power(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(std::pow(Lhs.m_Value, Rhs.m_Value)));
}
