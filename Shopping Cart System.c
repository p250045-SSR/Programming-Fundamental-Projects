#include <stdio.h>

void input_cart(char names[][50], float prices[], int quantities[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Item %d - Name: ", i + 1);
        scanf("%s", names[i]);
        printf("Price: ");
        scanf("%f", &prices[i]);
        printf("Quantity: ");
        scanf("%d", &quantities[i]);
    }
}

float calculate_subtotal(float prices[], int quantities[], int n)
{
    float subtotal = 0;
    for (int i = 0; i < n; i++)
    {
        subtotal += prices[i] * quantities[i];
    }
    return subtotal;
}

float apply_discount(float subtotal, float *discount_percent)
{
    if (subtotal > 5000)
    {
        *discount_percent = 20;
    }
    else if (subtotal > 3000)
    {
        *discount_percent = 15;
    }
    else if (subtotal > 1000)
    {
        *discount_percent = 10;
    }
    else
    {
        *discount_percent = 0;
    }
    return subtotal * (*discount_percent) / 100;
}

void generate_bill(char names[][50], float prices[], int quantities[], int n)
{
    printf("\n--- BILL ---\n");
    printf("%-15s %-10s %-5s %-10s\n", "Item", "Price", "Qty", "Total");
    printf("--------------------------------------------\n");

    float subtotal = 0;
    for (int i = 0; i < n; i++)
    {
        float total = prices[i] * quantities[i];
        printf("%-15s %-10.2f %-5d %-10.2f\n", names[i], prices[i], quantities[i], total);
        subtotal += total;
    }

    printf("--------------------------------------------\n");
    printf("Subtotal: %.2f\n", subtotal);

    float discount_percent = 0;
    float discount = apply_discount(subtotal, &discount_percent);

    if (discount > 0)
    {
        printf("Discount (%.0f%%): %.2f\n", discount_percent, discount);
    }

    printf("Final Total: %.2f\n", subtotal - discount);
}

int main()
{
    char names[5][50];
    float prices[5];
    int quantities[5];

    printf("Enter details for 5 items:\n");
    input_cart(names, prices, quantities, 5);

    generate_bill(names, prices, quantities, 5);

    return 0;
}