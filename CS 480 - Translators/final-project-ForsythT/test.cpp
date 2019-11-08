#include "stdio.h"

extern "C" {
	float python_compiler();
}

int main() {
	float x = python_compiler();

	printf("Return from python_compiler(): %f\n", x);
}
