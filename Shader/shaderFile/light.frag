#version 460


in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

//struct Material {
//   sampler2D diffuse;
//   vec3 specular;
//   float shininess;
//
//};
//struct Light {
//    vec3 position;
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//
//};

out vec4 FragColor;

//uniform Material material;
//uniform Light light;
//uniform vec3 viewPos;

uniform sampler2D texSampler1;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientFactor;
uniform vec3 viewPos;

void main()
{
    // Ambient
   // float ambientFactor = 0.3f;
    vec3 ambient = lightColor * ambientFactor;
    //vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff;
    //vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular phong
    float specularFactor = 0.8f;
    float shininess = 32.0f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float RDotV = max(dot(reflectDir, viewDir), 0.0f); //, material.shininess);
    vec3 specular = lightColor * specularFactor * pow(RDotV, shininess); //material.specular);

    vec4 texel = texture(texSampler1, TexCoords);
    FragColor = vec4(ambient + diffuse + specular, 1.0f) * texel; 

}
