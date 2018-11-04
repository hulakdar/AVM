#pragma once
#include <vector>
#include "IOperand.hpp"

namespace VirtualMachine
{
	extern std::vector<std::unique_ptr<const IOperand>> s_Stack;
};

namespace Runtime
{
	class RuntimeException : public std::exception
	{
		public:
		virtual const char *what() const _NOEXCEPT override {
			return "Runtime Error";
		}
	};

	class AssertException : public RuntimeException
	{
		public:
		virtual const char *what() const _NOEXCEPT final {
			return "Assert Failed";
		}
	};

	class StackSizeException : public RuntimeException
	{
		public:
		virtual const char *what() const _NOEXCEPT final {
			return "Stack size is insufficient for this operation";
		}
	};

	class DivisionByZeroException : public RuntimeException
	{
		public:
		virtual const char *what() const _NOEXCEPT final {
			return "Division by zero";
		}
	};

	class ExitException : public RuntimeException
	{
		public:
		virtual const char *what() const _NOEXCEPT final {
			return "Last Instruction was not 'exit'";
		}
	};
}