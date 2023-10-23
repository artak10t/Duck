#pragma once
#include "../pch.h"
#include <stdio.h>

//ANSI Colors
#define COLOR_TRACE "\033[0;90m"
#define COLOR_DEBUG "\033[0;97m"
#define COLOR_INFO "\033[0;92m"
#define COLOR_WARN "\033[0;93m"
#define COLOR_ERROR "\033[0;91m"
#define COLOR_FATAL "\033[0;97;41m"

//Macros
#define DUCK_ASSERT(x, ...) { if(!(x)) { Duck::Logger::Fatal(__VA_ARGS__); exit(-1); } }

namespace Duck::Logger
{
	enum LogPriority
	{
		TrancePriority,
		DebugPriority,
		InfoPriority,
		WarnPriority,
		ErrorPriority,
		FatalPriority
	};
	inline LogPriority Priority;
	inline std::mutex Mutex;

	template<typename ...Args>
	inline void Trace(const char* message, Args... args)
	{
		if (Priority > TrancePriority)
			return;

		std::scoped_lock lock(Mutex);
		fprintf(stdout, COLOR_TRACE"[Trace] ");
		fprintf(stdout, message, args...);
		fprintf(stdout, "\033[0m\n");
	}

	template<typename ...Args>
	inline void Debug(const char* message, Args... args)
	{
		if (Priority > DebugPriority)
			return;

		std::scoped_lock lock(Mutex);
		fprintf(stdout, COLOR_DEBUG"[Debug] ");
		fprintf(stdout, message, args...);
		fprintf(stdout, "\033[0m\n");
	}

	template<typename ...Args>
	inline void Info(const char* message, Args... args)
	{
		if (Priority > InfoPriority)
			return;

		std::scoped_lock lock(Mutex);
		fprintf(stdout, COLOR_INFO"[Info] ");
		fprintf(stdout, message, args...);
		fprintf(stdout, "\033[0m\n");
	}

	template<typename ...Args>
	inline void Warn(const char* message, Args... args)
	{
		if (Priority > WarnPriority)
			return;

		std::scoped_lock lock(Mutex);
		fprintf(stdout, COLOR_WARN"[Warn] ");
		fprintf(stdout, message, args...);
		fprintf(stdout, "\033[0m\n");
	}

	template<typename ...Args>
	inline void Error(const char* message, Args... args)
	{
		if (Priority > ErrorPriority)
			return;

		std::scoped_lock lock(Mutex);
		fprintf(stderr, COLOR_ERROR"[Error] ");
		fprintf(stderr, message, args...);
		fprintf(stderr, "\033[0m\n");
	}

	template<typename ...Args>
	inline void Fatal(const char* message, Args... args)
	{
		if (Priority > FatalPriority)
			return;

		std::scoped_lock lock(Mutex);
		fprintf(stderr, COLOR_FATAL"[Fatal] ");
		fprintf(stderr, message, args...);
		fprintf(stderr, "\033[0m\n");
	}
}
