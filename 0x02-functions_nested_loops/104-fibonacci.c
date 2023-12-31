#include <stdio.h>
/**
*main - finds and prints the first 98 Fibonacci numbers, from with 1 and 2
*fibonacci suit numbers
*Return: each time 0
*/
int main(void)
{
	int fibn;
	unsigned long f1 = 0, f2 = 1, f3;
	unsigned long f1_s1, f1_s2, f2_s1, f2_s2;
	unsigned long s1, s2;

	for (fibn = 0; fibn < 92; fibn++)
	{
		f3 = f1 + f2;
		printf("%lu, ", f3);
		f1 = f2;
		f2 = f3;
	}
	f1_s1 = f1 / 10000000000;
	f2_s1 = f2 / 10000000000;
	f1_s2 = f1 % 10000000000;
	f2_s2 = f2 % 10000000000;

	for (fibn = 93; fibn < 99; fibn++)
	{
		s1 = f1_s1 + f2_s1;
		s2 = f1_s2 + f2_s2;
		if ((f1_s2 + f2_s2) > 9999999999)
		{
			s1 += 1;
			s2 %= 10000000000;
		}
		printf("%lu%lu", s1, s2);
		if (fibn != 98)
		printf(", ");

		f1_s1 = f2_s1;
		f1_s2 = f2_s2;
		f2_s1 = s1;
		f2_s2 = s2;
	}
	printf("\n");
	return (0);
}
