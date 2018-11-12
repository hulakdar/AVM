#include "OperandFactory.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "VirtualMachine.hpp"
#include <fstream>
#include <vector>

void Execute(const std::vector<std::function<void (void)>>& Instructions)
{
	auto& LastInstruction = Instructions.back();
	for (auto& Instruction : Instructions)
	{
		Instruction();
		if (VirtualMachine::s_Exit)
			if (&Instruction != &LastInstruction)
				throw Runtime::EarlyExitException();
	}
	if (!VirtualMachine::s_Exit)
		throw Runtime::NoExitException();

}

int main(int argc, char *argv[])
{
	std::vector<std::string> Buffer;

	if (argc > 2)
	{
		std::cerr << "Usage:\n";
		std::cerr << "./avm [filepath]\n";
		return 1;
	}
	if (argc == 2)
	{
		const std::string FilePath(argv[1]);
		std::fstream File(FilePath);
		if (File.fail() || File.bad())
		{
			std::cerr << "File provided is not valid or not a file at all\n";
			return 1;
		}
		for (std::string Line; std::getline(File, Line);)
			Buffer.push_back(Line);
	}
	else
		for (std::string Line; std::getline(std::cin, Line);)
			if (Line == ";;")
				break;
			else
				Buffer.push_back(Line);

	try
	{
		std::vector<std::string> Tokens = Lexer::Tokenize(Buffer);
		std::vector<std::function<void (void)>> Instructions = Parser::Parse(Tokens);
		Execute(Instructions);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
}