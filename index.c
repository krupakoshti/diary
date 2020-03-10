#include<C:\Users\Dell\Desktop\DA-IICT\C project\account.h>
void main()
{
	int ch;
	do
	{
		printf("\n1.Create account\n");
		printf("2.Login\n");
		printf("3.Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				create_account();
				break;
			case 2:
				login_account();
				break;
			case 3:
				break;
			default:
				printf("Invalid choice");
		}
	}while(ch!=3);
	getch();
}
