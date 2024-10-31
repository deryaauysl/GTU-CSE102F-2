#include <stdio.h>
#include <string.h>

#define X 2
#define Y 150

// Compare two array if is equal each other one by one
int is_equal_arr(int arr1[], int arr2[])
{
    int i = 0;

    for (i = 0; i < X; i++)
    {
        if (!(arr1[i] == arr2[i]))
        {
            return 0;
        }
    }
    return 1;
}

// Copy source array to destination array
void copy_arr(int source[], int dest[])
{
    int i;

    for (i = 0; i < X; i++)
    {
        dest[i] = source[i];
    }
}

// Shift an array and fill last index by last_num
void shift_arr(int arr[], int size, int last_num)
{
    int i = 0;

    for (i = 0; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    arr[size - 1] = last_num;
}

// Shift an array of segment and shift the counters
void shift_seg(int seg[Y][X], int arr[], int counters[])
{
    int i = 0;

    for (i = 0; i < Y - 1; i++)
    {
        copy_arr(seg[i + 1], seg[i]);
    }

    copy_arr(arr, seg[Y - 1]);
    shift_arr(counters, Y, 1);
}

// Print shifts
void print_shifts(int arr[])
{
    int i = 0;
    for (i = 0; i < X; i++)
    {

        printf(" %d ", arr[i]);
    }
    printf(" \n");
}

// Compare two segment if it is equal to each other and increment the counter
int compare_segment(int segment[Y][X], int arr[], int counters[])
{
    int i = 0;
    for (i = 0; i < Y; i++)
    {
        if (is_equal_arr(segment[i], arr))
        {
            counters[i]++;
            return 1;
        }
    }
    return 0;
}

void seg_to_file(FILE *fp, int seg[Y][X], int counter[])
{
    int i = 0, j = 0;
    for (i = 0; i < Y; i++)
    {
        for (j = 0; j < X; j++)
        {
            fprintf(fp, "%d ", seg[i][j]);
        }
        fprintf(fp, ": %d\n", counter[i]);
    }
}

int main()
{
    FILE *input, *output;

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int num;
    int size_control = 0;
    int segment[Y][X] = {0};
    int arr[X] = {0};
    int is_first_seg = 1;
    int seg_counter[Y] = {0};

    // Take the numbers from input file until end of file
    while (fscanf(input, "%d", &num) == 1)
    {
        if (size_control == X)
        {
            is_first_seg = 0;
        }

        if (is_first_seg)
        {
            arr[size_control] = num;
            size_control++;
        }

        if (size_control >= X)
        {

            shift_arr(arr, X, num);

            if (!compare_segment(segment, arr, seg_counter))
            {
                shift_seg(segment, arr, seg_counter);
            }
        }
    }

    seg_to_file(output, segment, seg_counter);

    fclose(input);
    fclose(output);

    return 0;
}
