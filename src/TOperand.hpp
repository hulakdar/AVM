#pragma once

#include "IOperand.hpp"
#include <climits>
#include <vector>

static inline EOperandType GetResultingType(const IOperand *Lhs, const IOperand *Rhs)
{
    EOperandType LhsType = Lhs->GetType();
    EOperandType RhsType = Rhs->GetType();

    return LhsType > RhsType ? LhsType : RhsType;
}

template<typename T>
class TOperand : public IOperand
{
    T m_Value;
	std::string m_String;
public:
    TOperand() {}
    TOperand(const TOperand& Other) {}
    virtual ~TOperand() {}

    TOperand(const std::string& Value) {
		exit(200);
	}

    TOperand& operator=(const TOperand& Other) {
		m_Value = Other.m_Value;
		m_String = Other.m_String;
        return *this;
    }

	EOperandType GetType(void) const final
	{
		exit(200);
	}

    int GetPrecision(void) const final
    {
        return GetType();
    }
	
	char GetChar() const
	{
		return static_cast<char>(m_Value);
	}

    IOperand const* operator+(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();
		EOperandType ResultType = GetResultingType(this, &rhs);

		switch (RhsType)
		{
			case Int8:		return Add(*this, reinterpret_cast<const TOperand<char>&>(rhs), ResultType);
			case Int16:		return Add(*this, reinterpret_cast<const TOperand<short>&>(rhs), ResultType);
			case Int32:		return Add(*this, reinterpret_cast<const TOperand<int>&>(rhs), ResultType);
			case Float:		return Add(*this, reinterpret_cast<const TOperand<float>&>(rhs), ResultType);
			case Double:	return Add(*this, reinterpret_cast<const TOperand<double>&>(rhs), ResultType);
		}
		return nullptr;
    }

    IOperand const* operator-(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();
		EOperandType ResultType = GetResultingType(this, &rhs);

		switch (RhsType)
		{
			case Int8:		return Substract(*this, reinterpret_cast<const TOperand<char>&>(rhs), ResultType);
			case Int16:		return Substract(*this, reinterpret_cast<const TOperand<short>&>(rhs), ResultType);
			case Int32:		return Substract(*this, reinterpret_cast<const TOperand<int>&>(rhs), ResultType);
			case Float:		return Substract(*this, reinterpret_cast<const TOperand<float>&>(rhs), ResultType);
			case Double:	return Substract(*this, reinterpret_cast<const TOperand<double>&>(rhs), ResultType);
		}
		return nullptr;
    }

    IOperand const* operator*(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();
		EOperandType ResultType = GetResultingType(this, &rhs);

		switch (RhsType)
		{
			case Int8:		return Multiply(*this, reinterpret_cast<const TOperand<char>&>(rhs), ResultType);
			case Int16:		return Multiply(*this, reinterpret_cast<const TOperand<short>&>(rhs), ResultType);
			case Int32:		return Multiply(*this, reinterpret_cast<const TOperand<int>&>(rhs), ResultType);
			case Float:		return Multiply(*this, reinterpret_cast<const TOperand<float>&>(rhs), ResultType);
			case Double:	return Multiply(*this, reinterpret_cast<const TOperand<double>&>(rhs), ResultType);
		}
		return nullptr;
    }

    IOperand const* operator/(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();
		EOperandType ResultType = GetResultingType(this, &rhs);

		switch (RhsType)
		{
			case Int8:		return Divide(*this, reinterpret_cast<const TOperand<char>&>(rhs), ResultType);
			case Int16:		return Divide(*this, reinterpret_cast<const TOperand<short>&>(rhs), ResultType);
			case Int32:		return Divide(*this, reinterpret_cast<const TOperand<int>&>(rhs), ResultType);
			case Float:		return Divide(*this, reinterpret_cast<const TOperand<float>&>(rhs), ResultType);
			case Double:	return Divide(*this, reinterpret_cast<const TOperand<double>&>(rhs), ResultType);
		}
		return nullptr;
    }

    IOperand const* operator%(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();
		EOperandType ResultType = GetResultingType(this, &rhs);

		switch (RhsType)
		{
			case Int8:		return Modulo(*this, reinterpret_cast<const TOperand<char>&>(rhs), ResultType);
			case Int16:		return Modulo(*this, reinterpret_cast<const TOperand<short>&>(rhs), ResultType);
			case Int32:		return Modulo(*this, reinterpret_cast<const TOperand<int>&>(rhs), ResultType);
			case Float:		return Modulo(*this, reinterpret_cast<const TOperand<float>&>(rhs), ResultType);
			case Double:	return Modulo(*this, reinterpret_cast<const TOperand<double>&>(rhs), ResultType);
		}
		return nullptr;
    }

    IOperand const* operator^(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();
		EOperandType ResultType = GetResultingType(this, &rhs);

		switch (RhsType)
		{
			case Int8:		return Power(*this, reinterpret_cast<const TOperand<char>&>(rhs), ResultType);
			case Int16:		return Power(*this, reinterpret_cast<const TOperand<short>&>(rhs), ResultType);
			case Int32:		return Power(*this, reinterpret_cast<const TOperand<int>&>(rhs), ResultType);
			case Float:		return Power(*this, reinterpret_cast<const TOperand<float>&>(rhs), ResultType);
			case Double:	return Power(*this, reinterpret_cast<const TOperand<double>&>(rhs), ResultType);
		}
		return nullptr;
    }

    bool const* operator==(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();

		if (RhsType != GetType())
			return false;

		T& Other = reinterpret_cast<T&>(rhs);
		return m_Value == Other.m_Value;
    }

    std::string const& ToString(void) const final
    {
		return m_String;
    }

	template<typename L, typename R>
	friend IOperand const *Add(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType);

	template<typename L, typename R>
	friend IOperand const *Substract(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType);

	template<typename L, typename R>
	friend IOperand const *Multiply(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType);

	template<typename L, typename R>
	friend IOperand const *Divide(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType);

	template<typename L, typename R>
	friend IOperand const *Modulo(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType);

	template<typename L, typename R>
	friend IOperand const *Power(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType);
};

template<typename T>
TOperand<T>::TOperand(const std::string& Value);

template<typename T>
EOperandType TOperand<T>::GetType() const ;

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
inline IOperand const *Add(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value + Rhs.m_Value));
}

template<typename L, typename R>
inline IOperand const * Substract(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value - Rhs.m_Value));
}

template<typename L, typename R>
inline IOperand const * Multiply(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value * Rhs.m_Value));
}

template<typename L, typename R>
inline IOperand const * Divide(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(Lhs.m_Value / Rhs.m_Value));
}

template<typename L, typename R>
inline IOperand const *Modulo(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(std::remainder(Lhs.m_Value, Rhs.m_Value)));
}

template<typename L, typename R>
inline IOperand const * Power(const TOperand<L>& Lhs, const TOperand<R>& Rhs, EOperandType ResultingType)
{
	OperandFactory *Factory = OperandFactory::Get();

	return Factory->createOperand(ResultingType, std::to_string(std::pow(Lhs.m_Value, Rhs.m_Value)));
}