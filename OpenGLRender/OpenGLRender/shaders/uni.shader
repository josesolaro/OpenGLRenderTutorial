#!VERTEX
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform float hOffset;

out vec3 fragColor;
void main() {
	gl_Position = vec4(aPos.x + hOffset, aPos.y, aPos.z, 1.0);
	fragColor = aColor;
}

#!FRAGMENT
#version 330 core

out vec4 color;
in vec3 fragColor;

void main() {
	color = vec4(fragColor, 1.0f);
}