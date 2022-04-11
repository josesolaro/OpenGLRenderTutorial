#!VERTEX
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fragColor;
out vec2 texCoord;

void main() {
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	fragColor = aColor;
	texCoord = aTexCoord;
}

#!FRAGMENT
#version 330 core

out vec4 color;
in vec3 fragColor;
in vec2 texCoord;
uniform sampler2D boxTexture;
uniform sampler2D faceTexture;
uniform float texMix;

void main() {
	color = mix(texture(boxTexture, texCoord), 
		texture(faceTexture, vec2(1.0f- texCoord.x, texCoord.y)), texMix);
}