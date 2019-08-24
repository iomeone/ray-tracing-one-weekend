#pragma once

#include <iostream>

static uint32_t colorCallCount = 0;

#define DEBUG_MSG_EN 1
#define DEBUG_MSG_LVL_0_EN 1
#define DEBUG_MSG_FUNC_NAME_EN 1

#if defined DEBUG_MSG_EN && DEBUG_MSG_EN == 1

	#if defined DEBUG_MSG_LVL_0_EN && DEBUG_MSG_LVL_0_EN == 1

	#define DEBUG_MSG_L0(functionName, coutLine)	\
		coutLock.lock();	\
		std::cout << functionName << " " << coutLine << "\n";	\
		coutLock.unlock();
	#endif

	#if defined DEBUG_MSG_FUNC_NAME_EN && DEBUG_MSG_FUNC_NAME_EN 1

	#define DEBUG_MSG_FUNC_NAME(functionName, coutLine)	\
		coutLock.lock();	\
		std::cout << functionName << " " << coutLine << "\n";	\
		coutLock.unlock();
	#endif

#endif