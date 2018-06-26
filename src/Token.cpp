#include "Token.hpp"
#include <iostream>

const std::map<std::string, ETokenType> Token::s_Tokens = {
	{"int16", Type},
	{"int8", Type},
	{"int32", Type},
	{"float", Type},
	{"double", Type},
	{"\n", Separator},
	{"(", OpeningBracket},
	{")", ClosingBracket},
	{";;", Instruction},
	{";", Instruction},
	{"exit", Instruction},
	{"dump", Instruction},
	{"add", Instruction},
	{"sub", Instruction},
	{"mul", Instruction},
	{"div", Instruction},
	{"mod", Instruction},
	{"print", Instruction},
	{"push", Instruction},
	{"pop", Instruction}
};

Token& Token::operator=(const Token& Other)
{
	m_Value = Other.m_Value;
	m_Type = Other.m_Type;
	return *this;
}

Token::Token() : m_Type(None), m_Value(nullptr) {}

Token::Token(const Token& Other) { *this = Other; }

Token::~Token() {}

Token::Token(const std::string & Value)
{
	auto FindIterator = s_Tokens.find(Value);
	if (FindIterator == s_Tokens.end())
		m_Type = Symbol;
	m_Value = &FindIterator->first;
	m_Type = FindIterator->second;
}

ETokenType Token::GetType(void) const
{
	return m_Type;
}

const std::string& Token::GetValue(void) const
{
	return *m_Value;
}
