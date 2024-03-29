#version 430
//Blinn-Phong Shading
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 vertNormal;
layout (binding = 0) uniform sampler2D texSamp;

out vec3 varyingNormal;     //eye-space vertex normal
out vec3 varyingLightDir;   //vector to light
out vec3 varyingVertPos;    //vertex position
out vec3 varyingHalfVector; //halfway vector
out vec2 texCoord;

struct PositionalLight {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shine;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;   //for transforming normals

void main(void) {
    //output vertex position, light direction, and normal to rasterizer for interpolation
    varyingVertPos = (mv_matrix * vec4(vertPos, 1.0)).xyz;
    varyingLightDir = light.position - varyingVertPos;
    varyingNormal = (norm_matrix * vec4(vertNormal, 1.0)).xyz;
    varyingHalfVector = (varyingLightDir + (-varyingVertPos)).xyz;

    gl_Position = proj_matrix * mv_matrix * vec4(vertPos, 1.0);
    texCoord = inTexCoord;
}