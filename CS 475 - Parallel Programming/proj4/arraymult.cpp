#include "simd.p4.h"

#ifndef OUTPUT_FILE
#define OUTPUT_FILE "results.txt"
#endif

#ifndef LEN
#define LEN	100000
#endif

void fillArray(float* array, float val, int len) {
	for (int i = 0; i < len; i++) {
		array[i] = val;
	}
}

int main() {
	float maxMulSpeedup, maxSumSpeedup;

	for (int i = 0; i < 20; i++) {
		float* a = (float*)malloc(sizeof(float) * LEN);
		float* b = (float*)malloc(sizeof(float) * LEN);
		float* c = (float*)malloc(sizeof(float) * LEN);
		float* d = (float*)malloc(sizeof(float) * LEN);
		float e, f;
		fillArray(a, 1, LEN);
		fillArray(b, 2, LEN);
		
		double time0 = omp_get_wtime();
		
		// do SIMD mult
		SimdMul(a, b, c, LEN);
		
		double time1 = omp_get_wtime();

		// do non SIMD mult
		NonSimdMul(a, b, d, LEN);

		double time2 = omp_get_wtime();

		// do SIMD mult reduction
		e = SimdMulSum(a, b, LEN);

		double time3 = omp_get_wtime();

		// do non SIMD mult reduction
		f = NonSimdMulSum(a, b, LEN);

		double time4 = omp_get_wtime();	
		
		double timeSIMD = (time1 - time0) * 1000000;
		double timeNon = (time2 - time1) * 1000000;
		double timeSIMDSum = (time3 - time2) * 1000000;
		double timeNonSum = (time4 - time3) * 1000000;
		
		double speedupMul = timeNon / timeSIMD;
		double speedupSum = timeNonSum / timeSIMDSum;

		if (speedupMul > maxMulSpeedup) {
			maxMulSpeedup = speedupMul;
		}
		if (speedupSum > maxSumSpeedup) {
			maxSumSpeedup = speedupSum;
		}
		
		free(a);
		free(b);
		free(c);
		free(d);
	}
	
	FILE *f = fopen(OUTPUT_FILE, "a");
	if (f != NULL) {
		fprintf(f, "%f\t%f", maxMulSpeedup, maxSumSpeedup);
	} else {
		printf("Can not open file.\n");
	}	
}
