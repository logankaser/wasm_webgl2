// "use strict";

window.raster_canvas = document.createElement("canvas");

function registerTextureId(texture)
{
    var id = GL.getNewId(GL.textures);
    texture.name = id;
    GL.textures[id] = texture;

    return id;
}

/*
function unregisterTextureId(texture_id)
{
    var tex = GL.textures[texture_id];

    tex.name = 0;
    GL.textures[texture_id] = null;

    return tex;
}
*/

function generateTexture(str_ptr, len, mode, id_ptr) {
	const id = UTF8ToString(str_ptr, len);

	console.log(`Loading texture "${id}" with filter mode: ${mode}`);
	// Rasterize SVG
	const canvas = window.raster_canvas;
	const ctx = canvas.getContext("2d");
	const img = document.getElementById(id);
	if (img.width > canvas.width)
		canvas.width = img.width;
	if (img.height > canvas.height)
		canvas.height = img.height;
	ctx.clearRect(0, 0, img.width, img.height);
	ctx.drawImage(img, 0, 0);
	const img_data = ctx.getImageData(0, 0, img.width, img.height);

	// Upload to GPU.
	const gl = document.getElementById("gl").getContext("webgl2");
	const texture = gl.createTexture();
	const texture_id = registerTextureId(texture);
	gl.bindTexture(gl.TEXTURE_2D, texture);
	gl.pixelStorei(gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL, true);
	if (mode == 0)
	{
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	}
	else if (mode == 1)
	{
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_LINEAR);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
	}
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
	gl.texImage2D(
		gl.TEXTURE_2D,
		0,
		gl.RGBA,
		img_data.width,
		img_data.height,
		0,
		gl.RGBA,
		gl.UNSIGNED_BYTE,
		img_data
	);
	if (mode == 1)
		gl.generateMipmap(gl.TEXTURE_2D);

	// Set texture id in WASM memory
	HEAPU32[id_ptr / 4] = texture_id;
}