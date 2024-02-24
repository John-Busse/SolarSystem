#version 430
//Blinn-Phong shading
layout (binding = 0) uniform sampler2D texSamp;

in vec3 varyingNormal;      //eye-space vertex normal
in vec3 varyingLightDir;    //vector to light
in vec3 varyingVertPos;     //vertex position
in vec3 varyingHalfVector;  //halfway vector
in vec2 texCoord;           //texture coordinate
out vec4 fragColor;

//uniforms match vert shader uniforms

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
uniform mat4 norm_matrix;

void main(void) {
    //normalize vectors
    vec3 L = normalize(varyingLightDir);
    vec3 N = normalize(varyingNormal);
    vec3 V = normalize(-varyingVertPos);
    vec3 H = normalize(varyingHalfVector);

    //compute light reflection vector w.r.t. N
    vec3 R = normalize(reflect(-L, N));
    //get angle between light and surface normal
    float cosTheta = dot(L, N);
    //angle between normal and halfway vector
    float cosPhi = dot(H, N);

    //compute ADS contributions (per-pixel), and combine to build output color
    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta, 0.0);
    vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(cosPhi, 0.0), material.shine * 3.0);
        //the * 3.0 at the end is a 'tweak' to improve specular highlight

    vec4 texColor = texture(texSamp, texCoord);
    fragColor = texColor * vec4((ambient + diffuse + specular), 1.0);
}