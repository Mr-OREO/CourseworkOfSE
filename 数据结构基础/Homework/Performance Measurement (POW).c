#include<stdio.h>
#include<time.h>

#define	Time 20000											// Repeat 5000 times for running time;
#define X 1.001
#define N 100000											// Change N for different scale of test, assuming X = 1.001;

clock_t	start, stop;
double duration;											// Time cost;

double Algorithm_1(double x, int n);						// Function declaration;
double Algorithm_2_iteration(double x, int n);
double Algorithm_2_recursion(double x, int n);


int main()
{
	double result;											// result --- Store the computational result;
	int a = 1;												// a --- Circulation variable;
	
	start = clock();										// Test the first algorithm;
	for(a = 1; a <= Time; a++)
		result = Algorithm_1(X, N);
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK;
	printf("%f\n", (double)(stop - start));
	printf("Algorithm_1 time cost: %lf\n", duration);
	
	start = clock();										// Test the second algorithm;
	for(a = 1; a <= Time; a++)
		result = Algorithm_2_iteration(X, N);
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK;
	printf("%f\n", (double)(stop - start));
	printf("Algorithm_2_iteration time cost: %lf\n", duration);

	start = clock();										// Test the third algorithm;
	for(a = 1; a <= Time; a++)
		result = Algorithm_2_recursion(X, N);
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK;
	printf("%f\n", (double)(stop - start));
	printf("Algorithm_2_recursion time cost: %lf\n", duration);
	return 0;
 } 
 
 
 double Algorithm_1(double x, int n)					// the first approach
 {
 	int i=1;
	double Result = 1;										// 'Result' saves the final result of calculation;
	for( i = 0; i < n; i++)									// construct a n-times loop;
		Result *= x;										// 1 multiplication each time;
	return Result;
 }
 
 
 double Algorithm_2_iteration(double x, int n)			// the second approach
 {
 	int  m = n, i = 0;
	double prev = x, Result = 1;
 	double exp[n/2];										// record the exponent during each iteration;
 	while(m != 0)
 	{
 		exp[i] = m;											// save the current exponent into the array exp[] decreasingly;
 		m /= 2;												// previous state of exponent;
 		i++;
	 }
	i--;
	while(i > 0)
	{
		if(2 * exp[i] == exp[i-1])							// if next exponent is even
			prev = prev * prev;								// prev = prev^2;
		else prev = x * prev * prev;						// if next exponent is odd, prev = x * prev^2;
		Result = prev;
		i--;
	 }
	 return Result;
 }
 
 
 double Algorithm_2_recursion(double x, int n)			// the third approach
 {
 	if(n == 0)
 		return 1;											// return x^0 = 1;
	if(n % 2 == 0)
 		return Algorithm_2_recursion(x * x, n / 2);			// if n is even return x^(n/2)^2
 	else 
		return x * Algorithm_2_recursion(x * x, n / 2);		// if n is odd return x * x^(n/2)^2
 }
 
