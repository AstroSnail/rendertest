#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main (
	int argc,
	char **argv
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

	GLFWwindow *window = glfwCreateWindow(640, 480, "Shadertoy", NULL, NULL);
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

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	GLfloat vertices [3][2] = {
		{-1.0, -1.0}, {3.0, -1.0}, {-1.0, 3.0}
	};
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  unsigned int const bufferLen = 1024;
	char buffer [bufferLen];

	char const shaderVertexSource[] =
		"#version 110\n"
		"attribute vec2 aposition;"
		"varying vec2 vposition;"
		"void main (void) {"
			"gl_Position = vec4(aposition, 0.0, 1.0);"
			"vposition = aposition;"
		"}";
	GLint shaderVertexSourceLen = sizeof(shaderVertexSource) - 1;
	GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertex, 1, (const char* const*)&shaderVertexSource, &shaderVertexSourceLen);
	glCompileShader(shaderVertex);

	FILE *shaderFragmentFile = fopen(argv[1], "r");
  unsigned int const shaderFragmentSourceLenMax = 1024;
	char shaderFragmentSource[shaderFragmentSourceLenMax];
	GLint shaderFragmentSourceLen = fread(shaderFragmentSource, 1, sizeof(shaderFragmentSource), shaderFragmentFile);
	fclose(shaderFragmentFile);
	GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderFragment, 1, (const char* const*)&shaderFragmentSource, &shaderFragmentSourceLen);
	glCompileShader(shaderFragment);
	glGetShaderInfoLog(shaderFragment, sizeof(buffer), NULL, buffer);
	fputs(buffer, stdout);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaderVertex);
	glAttachShader(shaderProgram, shaderFragment);
	glBindAttribLocation(shaderProgram, 0, "aposition");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	while (1) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	// Unreachable
	puts("WTF error");
	return 1;
}
