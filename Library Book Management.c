#include <stdio.h>
#include <string.h>

void add_book(char titles[][100], int isbn[], int status[], int *count)
{
    printf("Enter book title: ");
    scanf(" %[^\n]", titles[*count]);
    printf("Enter ISBN: ");
    scanf("%d", &isbn[*count]);
    status[*count] = 1;
    (*count)++;
    printf("Book added successfully!\n");
}

int search_book(char titles[][100], char *search_title, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(titles[i], search_title) == 0)
        {
            return i;
        }
    }
    return -1;
}

void borrow_book(int status[], int index)
{
    status[index] = 0;
    printf("Book borrowed successfully!\n");
}

void return_book(int status[], int index)
{
    status[index] = 1;
    printf("Book returned successfully!\n");
}

void display_available(char titles[][100], int status[], int count)
{
    printf("\n--- Available Books ---\n");
    for (int i = 0; i < count; i++)
    {
        if (status[i] == 1)
        {
            printf("%s\n", titles[i]);
        }
    }
}

int count_borrowed(int status[], int count)
{
    int borrowed = 0;
    for (int i = 0; i < count; i++)
    {
        if (status[i] == 0)
        {
            borrowed++;
        }
    }
    return borrowed;
}

int main()
{
    char titles[10][100];
    int isbn[10];
    int status[10];
    int count = 0;
    int choice;
    char search_title[100];
    int index;

    do
    {
        printf("\n--- Library Management ---\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Display Available Books\n");
        printf("6. Count Borrowed Books\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (count < 10)
            {
                add_book(titles, isbn, status, &count);
            }
            else
            {
                printf("Library full!\n");
            }
            break;
        case 2:
            printf("Enter book title to search: ");
            scanf(" %[^\n]", search_title);
            index = search_book(titles, search_title, count);
            if (index != -1)
            {
                printf("Book found at position %d\n", index + 1);
            }
            else
            {
                printf("Book not found\n");
            }
            break;
        case 3:
            printf("Enter book title to borrow: ");
            scanf(" %[^\n]", search_title);
            index = search_book(titles, search_title, count);
            if (index != -1 && status[index] == 1)
            {
                borrow_book(status, index);
            }
            else
            {
                printf("Book not available\n");
            }
            break;
        case 4:
            printf("Enter book title to return: ");
            scanf(" %[^\n]", search_title);
            index = search_book(titles, search_title, count);
            if (index != -1)
            {
                return_book(status, index);
            }
            else
            {
                printf("Book not found\n");
            }
            break;
        case 5:
            display_available(titles, status, count);
            break;
        case 6:
            printf("Borrowed books: %d\n", count_borrowed(status, count));
            break;
        case 7:
            printf("Exit\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 7);

    return 0;
}