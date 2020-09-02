#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main (
	int argc,
	char * * argv
) {
	if (argc != 2) {
		puts("Usage: shadertoy <shaderfile>");
		return 1;
	}

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
		{-1.0, -1.0}, {3.0, -1.0}, {-1.0, 3.0}
	};
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned const bufferlen = 1024;
	char buffer [bufferlen];

	char shadervertexsource [] =
		"#version 110\n"
		"attribute vec2 aposition;"
		"varying vec2 vposition;"
		"void main (void) {"
			"gl_Position = vec4(aposition, 0.0, 1.0);"
			"vposition = aposition;"
		"}";
	GLint shadervertexsourcelen = sizeof shadervertexsource - 1;
	GLchar const * shadervertexsourcep = shadervertexsource;
	GLuint shadervertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shadervertex, 1, &shadervertexsourcep, &shadervertexsourcelen);
	glCompileShader(shadervertex);

	FILE * shaderfragmentfile = fopen(argv[1], "r");
	unsigned shaderfragmentsourcelenmax = 1024;
	char shaderfragmentsource [shaderfragmentsourcelenmax];
	GLchar const * shaderfragmentsourcep = shaderfragmentsource;
	GLint shaderfragmentsourcelen = fread(shaderfragmentsource, 1, shaderfragmentsourcelenmax, shaderfragmentfile);
	fclose(shaderfragmentfile);
	GLuint shaderfragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderfragment, 1, &shaderfragmentsourcep, &shaderfragmentsourcelen);
	glCompileShader(shaderfragment);
	glGetShaderInfoLog(shaderfragment, bufferlen, NULL, buffer);
	fputs(buffer, stdout);

	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, shadervertex);
	glAttachShader(shaderprogram, shaderfragment);
	glBindAttribLocation(shaderprogram, 0, "aposition");
	glLinkProgram(shaderprogram);
	glUseProgram(shaderprogram);

	while (1) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	// Unreachable
	puts("WTF error");
	return 1;
}
