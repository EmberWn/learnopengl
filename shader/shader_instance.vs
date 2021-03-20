#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 instanceMatrix;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT
{
   vec2 texCoords;
} vs_out;

out vec2 TexCoords;

void main()
{
   gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
   FragPos = vec3(model * vec4(aPos, 1.0));
   Normal = mat3(transpose(inverse(model))) * aNormal;
   vs_out.texCoords = aTexCoord;
   TexCoords = aTexCoord;

}
