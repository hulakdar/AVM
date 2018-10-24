#include "Parser.hpp"
#include <map>
#include <functional>
#include "VirtualMachine.hpp"
#include <iostream>
#include "OperandFactory.hpp"
#include <memory>
#include "TOperand.hpp"
#include "IOperand.hpp"

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
	default: throw std::exception();
	}
	return 0;
}

const std::map<std::string, std::function<bool (const IOperand *)>> s_Instructions = {
	{";;",
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{";",
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{"exit",
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{"dump",
	[](const IOperand *Value) -> bool {
		for (auto &Element : VirtualMachine::s_Stack)
			std::cout << Element->ToString() << "\n";
		
		return true;
	}
},
	{"add",
	[](const IOperand *Value) -> bool {
		if (VirtualMachine::s_Stack.size() < 2)
			throw std::exception();

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
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{"mul",
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{"div",
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{"mod",
	[](const IOperand *Value) -> bool {
		
		return true;
	}
},
	{"print",
	[](const IOperand *Value) -> bool {
		
		std::cout << GetCharFromOperand(Value) << "\n";
		
		return true;
	}
},
	{"push",
	[](const IOperand *Value) -> bool {
		if (!Value)
			throw std::exception();

		VirtualMachine::s_Stack.emplace_back(Value);
		return true;
	}
},
	{"pop",
	[](const IOperand *Value) -> bool {
		if (VirtualMachine::s_Stack.size())
		{
			VirtualMachine::s_Stack.pop_back();
			return true;
		}
		else
			throw std::exception();

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
				throw std::exception();
			
			auto& Lambda = Pair->second;

			const IOperand *Arg = nullptr;
			if (*It == "push" || *It == "assert")
			{
				if (++It == Tokens.end())
					throw std::exception();

				auto Type = s_Types.find(*It);

				if (++It == Tokens.end())
					throw std::exception();

				OperandFactory *Factory = OperandFactory::Get();

				Arg = Factory->createOperand(Type->second, *It);
			}
			Tmp.emplace_back(new Instruction(Lambda, Arg));
		}
		return Tmp;
	}
}