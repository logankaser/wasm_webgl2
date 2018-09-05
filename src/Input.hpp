#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>

class	Input
{
	static EM_BOOL keyDown(int, const EmscriptenKeyboardEvent*, void*);
	static EM_BOOL keyUp(int, const EmscriptenKeyboardEvent*, void*);
	static EM_BOOL mouseDown(int, const EmscriptenMouseEvent*, void*);
	static EM_BOOL mouseUp(int, const EmscriptenMouseEvent*, void*);
public:
	Input(const char* element);
	void	Update();
	bool	KeyDown(const std::string&);
	bool	KeyPress(const std::string&);
};
