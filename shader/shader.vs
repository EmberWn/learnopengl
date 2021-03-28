#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

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
uniform bool reverse_normals;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   FragPos = vec3(model * vec4(aPos, 1.0));
   if(reverse_normals) // a slight hack to make sure the outer large cube displays lighting from the 'inside' instead of the default 'outside'.
        Normal = transpose(inverse(mat3(model))) * (-1.0 * aNormal);
    else
        Normal = transpose(inverse(mat3(model))) * aNormal;
   vs_out.texCoords = aTexCoord;
   TexCoords = aTexCoord;

}
