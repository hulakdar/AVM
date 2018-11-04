#include "OperandFactory.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "VirtualMachine.hpp"
#include "Instruction.hpp"
#include <fstream>
#include <vector>

void Execute(const std::vector<std::unique_ptr<Instruction>>& Instructions)
{
	auto& LastInstruction = Instructions.back();
	for (auto& Instruction : Instructions)
	{
		if (&Instruction == &LastInstruction && Instruction->Execute())
			throw Runtime::ExitException();
		else
			Instruction->Execute();
	}
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

	std::vector<std::string> Tokens;
	std::vector<std::unique_ptr<Instruction>> Instructions;

	try
	{
		Tokens = Lexer::Tokenize(Buffer);
		Instructions = Parser::Parse(Tokens);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}

	try
	{
		Execute(Instructions);
	}
	catch (Runtime::RuntimeException &e)
	{
		std::cerr << "\n"
				  << e.what() << "\n";
		return 2;
	}
}