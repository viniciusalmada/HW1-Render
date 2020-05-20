#version 430 core

/*****************************************************************************
 * Uniform fields
 *
 * @uniform UAmbientComp - Material ambient color component
 * @uniform ULightColor - Light color
 * @uniform ULightPos - Light position
 * @uniform UDiffuseTexture - Diffuse texture sampler
 * @uniform UNormalTexture - Normal texture sampler
 *****************************************************************************/
uniform vec3 UAmbientComp;
uniform vec3 ULightColor;
uniform vec3 ULightPos;
uniform sampler2D UDiffuseTexture;
uniform sampler2D UNormalTexture;

/*****************************************************************************
 * Input parameters from vertex shader
 *
 * @param[in] FGTexCoords - Fragment texture coordinates
 * @param[in] FGPosition - Fragment position coordinates
 * @param[in] TBNMatrix - Tangent-bitangent-normal coordinate space
 *                         transformation matrix
 *****************************************************************************/
in vec2 FGTexCoords;
in vec3 FGPosition;
in mat3 TBNMatrix;

/*****************************************************************************
 * Output parameters
 *
 * @param[out] FragColor - Fragment color
 *****************************************************************************/
out vec4 FragColor;

void main()
{
    // Normal texture
    vec3 normalTex = texture(UNormalTexture, FGTexCoords).rgb;
    normalTex = normalize(2.0 * (normalTex - 0.5));

    // Ambient color
    vec3 ambientColor = UAmbientComp * ULightColor;

    // Light direction using TBN matrix
    vec3 lightDir = normalize(TBNMatrix * ULightPos - FGPosition);

    // Normal and light direction cosine
    float iDiff = max(dot(lightDir, normalTex), 0.0);

    // Diffuse color component
    vec3 diffuseColor = ULightColor * iDiff;

    // Diffuse texture
    vec3 diffuseTex = texture(UDiffuseTexture, FGTexCoords).rgb;

    // Result color
    vec3 resultColor = (ambientColor + diffuseColor) * diffuseTex;

    // Fragment color
    FragColor = vec4(resultColor, 1.0f);
}