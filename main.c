#include<stdio.h>
#include<math.h>

int main () {
	printf("Claculating Pi With Taylor Series\n");
	double sum = 0.0;
	//int n = 0;
	long long iter = 10000000000LL;
	FILE* csv = fopen("taylor.csv","a");
	if (csv == NULL) {
		printf("Can't write to csv !");
		return 0;
	}
	for (long long n=0; n<iter+1; n++) {
		double eq = pow(-1,n) / (2*n + 1);
		if (eq == 0.0) 
			break;
		// if n between 1 and 1M wirte it to csv, if it 1M or bigger write only millions to csv
		if (n < 1000000) {
			fprintf(csv, "%lld,%.10f\n",n,sum*4);
		}
		else if (((n >= 1000000) && (n % 1000000) == 0) && ( n > 0 )) {
			printf("	Iteration = %lld , pi = %.10f\r",n,sum*4);
			fprintf(csv, "%lld,%.10f\n",n,sum*4);
		}
		sum+=eq;
		//n++;
	}
	fclose(csv);
	printf("\nProgram Stoped in %lld Iteration",iter);
}