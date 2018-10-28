#ifndef TOPERAND_HPP
# define TOPERAND_HPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <cmath>
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
    TOperand(const TOperand& Other) {
		*this = Other;
	}
    virtual ~TOperand() {}

	TOperand(const std::string &Value);

	TOperand& operator=(const TOperand& Other) {
		m_Value = Other.m_Value;
		m_String = Other.m_String;
        return *this;
    }

	virtual EOperandType GetType(void) const final;

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

    bool operator==(IOperand const& rhs) const final
    {
		EOperandType RhsType = rhs.GetType();

		if (RhsType != GetType())
			return false;

		const TOperand<T>& Other = reinterpret_cast<const TOperand<T>&>(rhs);
		return m_Value == Other.m_Value;
    }

    bool operator!=(IOperand const& rhs) const final
	{
		return !(*this == rhs);
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

#endif