#include <stdio.h>
#include <string.h>
#include <time.h>
#include <GLFW/glfw3.h>

void fpsshow (
	struct timespec * t,
	unsigned int f
) {
	struct timespec tn;
	clock_gettime(CLOCK_MONOTONIC, &tn);
	double td = (tn.tv_sec - t->tv_sec) + 0.000000001 * (tn.tv_nsec - t->tv_nsec);
	double tf = 1000 * td / f;
	double fps = f / td;
	printf("%.3f F/s\n%.3f ms/F\n", fps, tf);
	memcpy(t, &tn, sizeof *t);
}

int main (void) {
	int init = glfwInit();
	if (init != GLFW_TRUE) {
		puts("Init error");
		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(640, 480, "glfwSwapBuffers test", NULL, NULL);
	if (window == NULL) {
		puts("Window error");
		return 1;
	}

	glfwMakeContextCurrent(window);

	struct timespec t;
	int time_error = clock_gettime(CLOCK_MONOTONIC, &t);
	unsigned int f = 0;
	if (time_error != 0) {
		puts("Time error");
		return 1;
	}

	while (1) {
		glfwSwapBuffers(window);

		f++;
		if (f == 1000) {
			fpsshow(&t, f);
			f = 0;
		}
	}

	// Unreachable
	puts("WTF error");
	return 1;
}
