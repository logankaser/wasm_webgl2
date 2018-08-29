#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <iostream>

int	main(void)
{
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;

	auto context = emscripten_webgl_create_context("canvas", &attrs);
	emscripten_webgl_make_context_current(context);
}

// Will get called whenever the browser is ready for a new frame.
// void emscripten_set_main_loop(void (*render)(void), 0, false)
