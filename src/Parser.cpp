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
	default: throw Runtime::RuntimeException();
	}
	return -1;
}

const std::map<std::string, std::function<bool (const IOperand *)>> s_Instructions = {
	{"exit",
	[](const IOperand *) -> bool {
		return false;
	}
},
	{"dump",
	[](const IOperand *) -> bool {
		for (auto &Element : VirtualMachine::s_Stack)
			std::cout << Element->ToString() << "\n";

		return true;
	}
},
	{"add",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		if (VirtualMachine::s_Stack.size() < 2)
			throw Runtime::StackSizeException();

		std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();
		std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();

		const IOperand* NewTop = *lhs + *rhs;
		VirtualMachine::s_Stack.emplace_back(NewTop);
		return true;
	}
},
	{"sub",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();
		std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();

		const IOperand* NewTop = *lhs - *rhs;
		VirtualMachine::s_Stack.emplace_back(NewTop);
		return true;
	}
},
	{"mul",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();
		std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();

		const IOperand* NewTop = *lhs * *rhs;
		VirtualMachine::s_Stack.emplace_back(NewTop);
		return true;
	}
},
	{"div",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();
		std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();

		const IOperand* NewTop = *lhs / *rhs;
		VirtualMachine::s_Stack.emplace_back(NewTop);
		return true;
	}
},
	{"pow",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();
		std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();

		const IOperand* NewTop = *lhs ^ *rhs;
		VirtualMachine::s_Stack.emplace_back(NewTop);
		return true;
	}
},
	{"mod",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		std::unique_ptr<const IOperand> rhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();
		std::unique_ptr<const IOperand> lhs = std::move(VirtualMachine::s_Stack.back());
		VirtualMachine::s_Stack.pop_back();

		const IOperand* NewTop = *lhs % *rhs;
		VirtualMachine::s_Stack.emplace_back(NewTop);
		return true;
	}
},
	{"print",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		std::cout << GetCharFromOperand(VirtualMachine::s_Stack.back().get());
		return true;
	}
},
	{"push",
	[](const IOperand *Value) -> bool {
		if (!Value)
			throw Runtime::RuntimeException();

		VirtualMachine::s_Stack.emplace_back(Value);
		return true;
	}
},
	{"assert",
	[](const IOperand *Value) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();
		if (!Value)
			throw Runtime::RuntimeException();

		if (*VirtualMachine::s_Stack.back() != *Value)
			throw Runtime::AssertException();

		return true;
	}
},
	{"pop",
	[](const IOperand *) -> bool {
		if (!VirtualMachine::s_Stack.size())
			throw Runtime::StackSizeException();

		VirtualMachine::s_Stack.pop_back();
		return true;
	}
}
};

namespace Parser
{
	using VecOfInst = std::vector<std::unique_ptr<Instruction>>;

	VecOfInst Parse(const std::vector<std::string>& Tokens)
	{
		VecOfInst Tmp;
		for (auto It = Tokens.begin(); It != Tokens.end(); ++It)
		{
			auto Pair = s_Instructions.find(*It);
			if (Pair == s_Instructions.end())
				throw UnknownInstructionException();
			
			auto& Lambda = Pair->second;

			const IOperand *Arg = nullptr;
			if (*It == "push" || *It == "assert")
			{
				if (++It == Tokens.end())
					throw UnknownTypeException();

				auto Type = s_Types.find(*It);

				if (++It == Tokens.end())
					throw ParseErrorException();

				OperandFactory *Factory = OperandFactory::Get();

				Arg = Factory->createOperand(Type->second, *It);
			}
			Tmp.emplace_back(new Instruction(Lambda, Arg));
		}
		return Tmp;
	}
}