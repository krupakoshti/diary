#include<stdio.h>
int main()
{
	static int x=5;
	static int y=5;
	if(--x)
	{
		main();
		printf("%d ",y);
		y--;
	}
}
