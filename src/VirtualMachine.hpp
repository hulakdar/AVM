#pragma once
#include <vector>
#include <list>
#include "IOperand.hpp"

#ifndef _NOEXCEPT
#define _NOEXCEPT
#endif

namespace VirtualMachine
{
	extern std::vector<std::unique_ptr<const IOperand>> s_Stack;
	extern std::list<std::unique_ptr<const IOperand>> s_Arguments;
	extern bool s_Exit;
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

	class EarlyExitException : public RuntimeException
	{
		public:
		virtual const char *what() const _NOEXCEPT final {
			return "Early Exit";
		}
	};

	class NoExitException : public RuntimeException
	{
		public:
		virtual const char *what() const _NOEXCEPT final {
			return "No exit instruction";
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