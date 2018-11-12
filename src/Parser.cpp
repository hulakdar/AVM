#include "Parser.hpp"
#include <map>
#include <functional>
#include "VirtualMachine.hpp"
#include <iostream>
#include "OperandFactory.hpp"
#include <memory>
#include "TOperand.hpp"

enum class ETokenType : unsigned char{
	Instruction,
	Symbol,
	Type,
	Separator,
	OpeningBracket,
	ClosingBracket,
	None
};


const std::map<std::string, EOperandType> s_Types = {
	{"int16", EOperandType::Int16},
	{"int8", EOperandType::Int8},
	{"int32", EOperandType::Int32},
	{"float", EOperandType::Float},
	{"double", EOperandType::Double}
};

static char GetCharFromOperand(const IOperand*Operand)
{
	EOperandType Type = Operand->GetType();

	switch (Type)
	{
	case Int8: return ((const TOperand<char>*)Operand)->GetChar();
	case Int16: return ((const TOperand<short>*)Operand)->GetChar();
	case Int32: return ((const TOperand<int>*)Operand)->GetChar();
	case Float: return ((const TOperand<float>*)Operand)->GetChar();
	case Double: return ((const TOperand<double>*)Operand)->GetChar();
	}
	return -1;
}

std::map<std::string, std::function<void (void)>> s_Instructions =
{
	{
		"exit",
		[](){
			VirtualMachine::s_Exit = true;
		}
	},
	{
		"dump",
		[](){
			for (auto &Element : VirtualMachine::s_Stack)
				std::cout << Element->ToString() << "\n";
		}
	},
	{
		"add",
		[](){
			if (VirtualMachine::s_Stack.size() < 2)
				throw Runtime::StackSizeException();

			std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();
			std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();

			std::unique_ptr<const IOperand> NewTop(*lhs + *rhs);
			VirtualMachine::s_Stack.push_back(std::move(NewTop));
		}
	},
	{
		"sub",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();
			std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();
			std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();

			std::unique_ptr<const IOperand> NewTop(*lhs - *rhs);
			VirtualMachine::s_Stack.push_back(std::move(NewTop));
		}
	},
	{
		"mul",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();
			std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();
			std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();

			std::unique_ptr<const IOperand> NewTop(*lhs * *rhs);
			VirtualMachine::s_Stack.push_back(std::move(NewTop));
		}
	},
	{
		"div",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();
			std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();
			std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();

			std::unique_ptr<const IOperand> NewTop(*lhs / *rhs);
			VirtualMachine::s_Stack.push_back(std::move(NewTop));
		}
	},
	{
		"pow",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();
			std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();
			std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();

			std::unique_ptr<const IOperand> NewTop(*lhs ^ *rhs);
			VirtualMachine::s_Stack.push_back(std::move(NewTop));
		}
	},
	{
		"mod",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();
			std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();
			std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
			VirtualMachine::s_Stack.pop_back();

			std::unique_ptr<const IOperand> NewTop(*lhs % *rhs);
			VirtualMachine::s_Stack.push_back(std::move(NewTop));
		}
	},
	{
		"print",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();
			std::cout << GetCharFromOperand(VirtualMachine::s_Stack.back().get());
		}
	},
	{
		"push",
		[](){
			std::unique_ptr<const IOperand> Value = std::move(VirtualMachine::s_Arguments.back());
			VirtualMachine::s_Arguments.pop_back();
			if (!Value)
				throw Runtime::RuntimeException();

			VirtualMachine::s_Stack.emplace_back(std::move(Value));
		}
	},
	{
		"assert",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();

			std::unique_ptr<const IOperand> Value = std::move(VirtualMachine::s_Arguments.back());
			VirtualMachine::s_Arguments.pop_back();
			if (!Value)
				throw Runtime::RuntimeException();

			if (*VirtualMachine::s_Stack.back() != *Value)
				throw Runtime::AssertException();
		}
	},
	{
		"pop",
		[](){
			if (!VirtualMachine::s_Stack.size())
				throw Runtime::StackSizeException();

			VirtualMachine::s_Stack.pop_back();
		}
	}
};

namespace Parser
{
	std::vector<Instruction> Parse(const std::vector<std::string>& Tokens)
	{
		std::vector<Instruction> Tmp;
		for (auto It = Tokens.begin(); It != Tokens.end(); ++It)
		{
			auto Pair = s_Instructions.find(*It);
			if (Pair == s_Instructions.end())
				throw UnknownInstructionException();
			
			Tmp.emplace_back(Pair->second);

			if (*It == "push" || *It == "assert")
			{
				if (++It == Tokens.end())
					throw UnknownTypeException();

				auto Type = s_Types.find(*It);

				if (Type == s_Types.end())
					throw UnknownTypeException();

				if (++It == Tokens.end())
					throw ParseErrorException();

				VirtualMachine::s_Arguments.emplace_back(OperandFactory::Get()->createOperand(Type->second, *It));
			}
		}
		return Tmp;
	}
}