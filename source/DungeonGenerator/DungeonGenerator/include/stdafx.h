// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define USE_GLFW 1

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#ifdef USE_GLFW
	#include <gl_core_4_3.hpp>
	#include <glfw3.h>
	#include <EngineCoreGLFW.h>
#endif