#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <string>
#include <unordered_map>

#include "graphic_core.hpp"

class	Input
{
	static constexpr int _mouseButtons = 10;

	std::unordered_map<std::string, bool> _keyDown;
	std::unordered_map<std::string, bool> _keyPress;
	bool _mouseDown[_mouseButtons] = {false};
	bool _mouseClick[_mouseButtons] = {false};
	glm::vec2 _mousePos = {0, 0};

	static EM_BOOL keyDown(int, const EmscriptenKeyboardEvent*, void*);
	static EM_BOOL keyUp(int, const EmscriptenKeyboardEvent*, void*);
	static EM_BOOL mouseDown(int, const EmscriptenMouseEvent*, void*);
	static EM_BOOL mouseUp(int, const EmscriptenMouseEvent*, void*);
	static EM_BOOL mouseMove(int, const EmscriptenMouseEvent*, void*);
public:
	Input(const char* element);

	void	Update();
	bool	KeyDown(const std::string&) const;
	bool	KeyPress(const std::string&) const;
	bool	MouseDown(int) const;
	bool	MouseClick(int) const;
	glm::vec2	MousePos() const;
};
