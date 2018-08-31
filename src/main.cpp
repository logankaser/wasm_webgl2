#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <iostream>

int	main(void)
{
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.depth = 0;
    attrs.stencil = 0;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;

	auto context = emscripten_webgl_create_context("canvas", &attrs);
	emscripten_webgl_make_context_current(context);
	glClearColor(0.5,  0.1,  0.9,  1);
	glClear(GL_COLOR_BUFFER_BIT);
}

// Will get called whenever the browser is ready for a new frame.
// void emscripten_set_main_loop(void (*render)(void), 0, false)
