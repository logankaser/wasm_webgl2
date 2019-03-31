// "use strict";

window.raster_canvas = document.createElement("canvas");
window.raster_cache = {};

function register_texture_id(textureResource)
{
    var id = GL.getNewId(GL.textures);
    textureResource.name = id;
    GL.textures[id] = textureResource;

    return id;
}

function unregister_texture_id(nativeTextureId)
{
    var tex = GL.textures[nativeTextureId];

    tex.name = 0;
    GL.textures[nativeTextureId] = null;

    return tex;
}


function generate_texture(str_ptr, len, mode, id_ptr) {
	const id = AsciiToString(str_ptr, len);

	if (window.raster_cache[id + mode])
		return window.raster_cache[id + mode];
	// Rasterize SVG
	const canvas = window.raster_canvas;
	const r = canvas.getContext("2d");
	const img = document.getElementById(id);
	canvas.width = img.width;
	canvas.height = img.height;
	r.drawImage(img, 0, 0);
	const img_data = r.getImageData(0, 0, img.width, img.height);

	// Upload to GPU.
	const gl = document.getElementById("gl").getContext("webgl2");
	const texture = gl.createTexture();
	const texture_id = register_texture_id(texture);
	gl.bindTexture(gl.TEXTURE_2D, texture);
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

	// Cache texture for later calls.
	window.raster_cache[id + mode] = texture_id;
}