#version 430 core

/*****************************************************************************
 * Uniform fields
 *
 * @uniform UModelMatrix - Model transformation matrix
 * @uniform UViewMatrix - View transformation matrix
 * @uniform UProjMatrix - Projection transformation matrix
 *****************************************************************************/
uniform mat4 UModelMatrix;
uniform mat4 UViewMatrix;
uniform mat4 UProjMatrix;

/******************************************************************************
 * Vertex attributes
 *
 * @attr VXPosition - Cartesian coordinates (x, y, z)
 * @attr VXNormal - Normal vector (x, y, z)
 * @attr VXTexCoords - Texture parametric coordinates (s, t)
 * @attr VXTangent - Tangent vector to build TBN coordinate space (x, y, z)
 * @attr VXBitangent - Bitangent vector to build TBN coordinate space (x, y, z)
 ******************************************************************************/
layout (location = 0) in vec3 VXPosition;
layout (location = 1) in vec3 VXNormal;
layout (location = 2) in vec2 VXTexCoords;
layout (location = 3) in vec3 VXTangent;
layout (location = 4) in vec3 VXBitangent;

/*****************************************************************************
 * Output parameters
 *
 * @param[out] FGTexCoords - Fragment texture coordinates
 * @param[out] FGPosition - Fragment position coordinates
 * @param[out] TBNMatrix - Tangent-bitangent-normal coordinate space
 *                         transformation matrix
 *****************************************************************************/
out vec2 FGTexCoords;
out vec3 FGPosition;
out mat3 TBNMatrix;

void main(){
    // TBN Matrix build
    vec3 T = normalize(vec3(UModelMatrix * vec4(VXTangent, 0.0)));
    vec3 B = normalize(vec3(UModelMatrix * vec4(VXBitangent, 0.0)));
    vec3 N = normalize(vec3(UModelMatrix * vec4(VXNormal, 0.0)));
    TBNMatrix = transpose(mat3(T, B, N));

    // Passing the texture coordinates
    FGTexCoords = VXTexCoords;

    // Passing the fragment position to calculate diffuse component
    FGPosition = vec3(UModelMatrix * vec4(VXPosition, 1.0f));

    // Vertex position transformed
    gl_Position = UProjMatrix * UViewMatrix * UModelMatrix * vec4(VXPosition, 1.0f);
}