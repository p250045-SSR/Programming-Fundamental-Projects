#include <stdio.h>
#include <string.h>

float calculate_average(float marks[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += marks[i];
    }
    return sum / n;
}

int count_failing(float marks[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (marks[i] < 50)
        {
            count++;
        }
    }
    return count;
}

void find_top_student(char names[][50], float marks[], int n)
{
    int max_index = 0;
    for (int i = 1; i < n; i++)
    {
        if (marks[i] > marks[max_index])
        {
            max_index = i;
        }
    }
    printf("Top Student: %s (%.1f)\n", names[max_index], marks[max_index]);
}

int check_eligibility(float marks, float attendance)
{
    if (marks >= 50 && attendance >= 75)
    {
        return 1;
    }
    return 0;
}

int main()
{
    char names[5][50];
    float marks[5];
    float attendance[5];

    printf("Enter details for 5 students:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Student %d - Name: ", i + 1);
        scanf("%s", names[i]);
        printf("Marks: ");
        scanf("%f", &marks[i]);
        printf("Attendance: ");
        scanf("%f", &attendance[i]);
    }

    printf("\n--- Statistics ---\n");
    printf("Class Average: %.2f\n", calculate_average(marks, 5));
    printf("Failing Students: %d\n", count_failing(marks, 5));
    find_top_student(names, marks, 5);

    printf("Students eligible for exam: ");
    for (int i = 0; i < 5; i++)
    {
        if (check_eligibility(marks[i], attendance[i]))
        {
            printf("%s ", names[i]);
        }
    }
    printf("\n");

    return 0;
}