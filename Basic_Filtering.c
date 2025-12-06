#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED "\e[31m"
#define GREEN "\e[32m"
#define BLUE "\e[34m"
#define BOLD "\e[1m"
#define RESET "\e[0m"

void main()
{
    char names[][20] = {"Shayan", "Awais", "Waleed", "Rayyan", "Syed", "Asjal"};
    char categories[][20] = {"manager", "staff", "manager", "staff", "manager", "staff"};

    for (;;)
    {

        int choice;
        printf(BLUE "\nSelect option: \n" RESET);
        printf("1. Manager\n");
        printf("2. Staff\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1)
        {
            printf("Manager: \n");
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(categories[i], "manager") == 0)
                {
                    printf(" %s\n", names[i]);
                }
            }
        }
        else if (choice == 2)
        {
            printf("Staff: \n");
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(categories[i], "staff") == 0)
                {

                    printf(" %s\n", names[i]);
                }
            }
        }
        else if (choice == 3)
        {
            return;
        }
        else
        {

            printf(RED "Invalid choice!" RESET);
        }
    }
}
