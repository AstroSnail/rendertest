#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main (void) {
	int glfwinit = glfwInit();
	if (glfwinit != GLFW_TRUE) {
		puts("GLFW error");
		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(640, 480, "Shadertoy", NULL, NULL);
	if (window == NULL) {
		puts("Window error");
		return 1;
	}

	glfwMakeContextCurrent(window);

	GLenum glewinit = glewInit();
	if (glewinit != GLEW_OK) {
		printf("GLEW error: %s\n", glewGetErrorString(glewinit));
		return 1;
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	GLfloat vertices [3][2] = {
		//{-1.0, -1.0}, {3.0, -1.0}, {-1.0, 3.0}
		{-0.5, -0.5}, {0.5, -0.5}, {-0.5, 0.5}
	};
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned const bufferlen = 1024;
	char buffer [bufferlen];

	GLchar const *const shadervertexsource = 
		"#version 100 es\n"
		"attribute vec2 aposition;\n"
		"varying lowp vec2 vposition;\n"
		"void main (void) {\n"
		"	gl_Position = vec4(aposition, 0.0, 1.0);\n"
		"	vposition = aposition;\n"
		"}\n";
	GLint shadervertexsourcelen = sizeof shadervertexsource - 1;
	GLuint shadervertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shadervertex, 1, &shadervertexsource, &shadervertexsourcelen);
	glCompileShader(shadervertex);
	puts("Vertex shader:");
	glGetShaderInfoLog(shadervertex, bufferlen, NULL, buffer);
	fputs(buffer, stdout);
	puts("Source:");
	fputs(shadervertexsource, stdout);

	GLchar const *const shaderfragmentsource = 
		"#version 100 es\n"
		"varying lowp vec2 vposition;\n"
		"void main (void) {\n"
		"	gl_FragColor = vec4(0.7, 0.6, 0.5, 1.0);\n"
		"}\n";
	GLint shaderfragmentsourcelen = sizeof shaderfragmentsource - 1;
	GLuint shaderfragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderfragment, 1, &shaderfragmentsource, &shaderfragmentsourcelen);
	glCompileShader(shaderfragment);
	puts("Fragment shader:");
	glGetShaderInfoLog(shaderfragment, bufferlen, NULL, buffer);
	fputs(buffer, stdout);
	puts("Source:");
	fputs(shaderfragmentsource, stdout);

	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, shadervertex);
	glAttachShader(shaderprogram, shaderfragment);
	glBindAttribLocation(shaderprogram, 0, "aposition");
	glLinkProgram(shaderprogram);
	glUseProgram(shaderprogram);

	glClearColor(0.4, 0.3, 0.2, 0.0);

	while (1) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	// Unreachable
	puts("WTF error");
	return 1;
}
