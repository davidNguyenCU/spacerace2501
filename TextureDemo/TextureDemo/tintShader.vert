// Source code of vertex shader
#version 130

// Vertex buffer
in vec2 vertex;
in vec3 color;
uniform vec3 tint;
in vec2 uv;
out vec2 uv_interp;

// Uniform (global) buffer
uniform mat4 x;

// Attributes forwarded to the fragment shader
out vec4 color_interp
out vec3 tint_interp

void main()
{
	vec4 t;
	t = vec4(vertex, 0.0, 1.0);
    gl_Position = x*t;

    color_interp = vec4(color, 1.0);
	tint_interp = tint;
	uv_interp = uv;
}