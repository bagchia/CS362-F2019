#include <stdio.h>
#include <stdlib.h>

void test_bool(int condition, char *message)
{
    if (condition == 0)
    {
        printf("\t%s: ", "FAILED");
    }
    else
    {
        printf("\t%s: ", "PASSED");
    }
    printf("%s\n", message);
}

void test_int(int value, int expected, char *message)
{
    printf("%s: ", message);
    if (value == expected)
    {
        printf("actual: %d , expected: %d\n", "PASSED", value, expected);
    }
    else
    {
        printf("actual: %d , expected: %d\n", "FAILED", value, expected);
    }
}

int count_array(int *array, int array_size, int value)
{
    int sum = 0;
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == value)
        {
            sum += 1;
        }
    }
    return sum;
}

int rand_range(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}