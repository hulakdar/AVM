#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Instruction.hpp"

namespace Parser
{
	using Instruction = std::function<void (void)>
	std::vector<std::unique_ptr<Instruction>> Parse(const std::vector<std::string>& Tokens);

	std::vector<std::unique_ptr<const IOperand>> s_Arguments;

	class ParseErrorException : public std::exception
	{
		public:
		virtual const char *what() const _NOEXCEPT override {
			return "Parse Error";
		}
	};

	class UnknownInstructionException : public ParseErrorException 
	{
		public:
		virtual const char *what()const _NOEXCEPT final {
			return "Unknown Instruction";
		}
	};

	class UnknownTypeException : public ParseErrorException
	{
		public:
		virtual const char *what()const _NOEXCEPT  final {
			return "Unknown Type";
		}
	};
}