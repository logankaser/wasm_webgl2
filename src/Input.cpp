#include "Input.hpp"

EM_BOOL	Input::keyDown(int, const EmscriptenKeyboardEvent* mouseEvent, void*)
{
	std::cout << "key down" << std::endl;
	std::cout << mouseEvent->code << std::endl;
	return false;
}

EM_BOOL	Input::keyUp(int, const EmscriptenKeyboardEvent* mouseEvent, void*)
{
	std::cout << "key up" << std::endl;
	std::cout << mouseEvent->code << std::endl;
	return false;
}

EM_BOOL Input::mouseDown(int, const EmscriptenMouseEvent* mouseEvent, void*)
{
	std::cout << mouseEvent->targetX << " " << mouseEvent->targetY << std::endl;
	return false;
}

EM_BOOL Input::mouseUp(int, const EmscriptenMouseEvent* mouseEvent, void*)
{
	std::cout << mouseEvent->targetX << " " << mouseEvent->targetY << std::endl;
	return false;
}

Input::Input(const char* element)
{
	emscripten_set_keydown_callback(element, this, false, keyDown);
	emscripten_set_keyup_callback(element, this, false, keyUp);
	emscripten_set_mousedown_callback(element, this, false, mouseDown);
	emscripten_set_mouseup_callback(element, this, false, mouseUp);
}
