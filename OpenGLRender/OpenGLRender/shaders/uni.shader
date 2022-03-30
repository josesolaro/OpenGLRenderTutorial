#!VERTEX
#version 330 core

layout(location = 0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos, 1.0);
}

#!FRAGMENT
#version 330 core

out vec4 color;
void main() {
	color = vec4(1.0f, 0.5f, 0.5f, 1.0f);
}