#include "Parser.hpp"
#include <map>
#include <functional>

enum class ETokenType : unsigned char{
	Instruction,
	Symbol,
	Type,
	Separator,
	OpeningBracket,
	ClosingBracket,
	None
};

const std::map<std::string, ETokenType> s_Tokens = {
	{"int16", ETokenType::Type},
	{"int8", ETokenType::Type},
	{"int32", ETokenType::Type},
	{"float", ETokenType::Type},
	{"double", ETokenType::Type},
	{"\n", ETokenType::Separator},
	{"(", ETokenType::OpeningBracket},
	{")", ETokenType::ClosingBracket},
	{";;", ETokenType::Instruction},
	{";", ETokenType::Instruction},
	{"exit", ETokenType::Instruction},
	{"dump", ETokenType::Instruction},
	{"add", ETokenType::Instruction},
	{"sub", ETokenType::Instruction},
	{"mul", ETokenType::Instruction},
	{"div", ETokenType::Instruction},
	{"mod", ETokenType::Instruction},
	{"print", ETokenType::Instruction},
	{"push", ETokenType::Instruction},
	{"pop", ETokenType::Instruction}
};

const std::map<std::string, std::function<bool (const std::string&)>> s_Instructions = {
	{";;",
	[](const std::string& Instr) -> bool {

		return true;
	}
},
	{";",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"exit",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"dump",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"add",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"sub",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"mul",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"div",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"mod",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"print",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"push",
	[](const std::string& Instr) -> bool {
		
		return true;
	}
},
	{"pop",
	[](const std::string& Instr) -> bool {


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
			auto Pair = s_Tokens.find(*It);
			if (Pair == s_Tokens.end() || Pair->second != ETokenType::Instruction)
				throw std::exception();
			
			auto& Lambda = s_Instructions.find(*It)->second; //the lambda with code

			std::string Arg = "";
			if (*It == "push" || *It == "assert")
			{
				if (++It == Tokens.end())
					throw std::exception();

				Arg = *It;
			}
			Tmp.push_back(std::make_unique<Instruction>(Lambda, Arg));
		}
		return Tmp;
	}
}