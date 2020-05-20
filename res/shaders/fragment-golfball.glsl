#version 430 core

/*****************************************************************************
 * Uniform fields
 *
 * @uniform UAmbientComp - Material ambient color component
 * @uniform UDiffuseComp - Material diffuse color component
 * @uniform ULightColor - Light color
 * @uniform ULightPos - Light position
 * @uniform UNormalTexture - Normal texture sampler
 *****************************************************************************/
uniform vec3 UAmbientComp;
uniform vec3 UDiffuseComp;
uniform vec3 ULightColor;
uniform vec3 ULightPos;
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

    // Diffuse color
    vec3 diffuseColor = (iDiff * ULightColor) * UDiffuseComp;

    // Result color
    vec3 resultColor = ambientColor + diffuseColor;

    // Fragment color
    FragColor = vec4(resultColor, 1.0f);
}