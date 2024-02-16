#version 430
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inTexCoord;

smooth out vec2 texCoord;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

layout (binding = 0) uniform sampler2D samp;

void main(void) {
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);
    texCoord = inTexCoord;
}