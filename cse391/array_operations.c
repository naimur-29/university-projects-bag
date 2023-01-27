#include <stdio.h>
#include <math.h>

// Array Operations:
// Display array elements:
void display(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Copy Array:
void copy(int arr[], int duplicate[], int size) {
    for (int i = 0; i < size; i++) {
        duplicate[i] = arr[i];
    }
}

// Left Shift:
void left_shift(int arr[], int size) {
    int duplicate[size];
    copy(arr, duplicate, size);
    int temp = duplicate[0];
    
    for (int i = 1; i < size; i++) {
        duplicate[i-1] = duplicate[i];
    }
    
    duplicate[size-1] = temp;
    printf("Left Shifted: ");
    display(duplicate, size);
}

// Right Shift:
void right_shift(int arr[], int size) {
    int duplicate[size];
    copy(arr, duplicate, size);
    int temp = duplicate[size-1];
    
    for (int i = 1; i < size; i++) {
        duplicate[size-i] = duplicate[(size-1) - i];
    }
    
    duplicate[0] = temp;
    printf("Right Shifted: ");
    display(duplicate, size);
}

// Reverse:
void reverse(int arr[], int size) {
    int duplicate[size];
    copy(arr, duplicate, size);
    
    for (int i = 0; i < size/2; i++) {
        int temp = duplicate[i];
        duplicate[i] = duplicate[(size-1) - i];
        duplicate[(size-1) - i] = temp;
    }
    
    printf("Reversed: ");
    display(duplicate, size);
}

// Insert (Right shifted):
void insert(int arr[], int size, int index, int val) {
    int duplicate[size];
    copy(arr, duplicate, size);
    
    for(int i = size-1; i > index; i--) {
        duplicate[i] = duplicate[i-1];
    }
    
    duplicate[index] = val;
    printf("After insertion: ");
    display(duplicate, size);
}

// Create Number:
void numberify(int arr[], int size) {
    int forward = 0, backward = 0;
    
    for (int i = 0; i < size; i++) {
        forward += arr[(size-1) - i] * pow(10, i);
        backward += arr[i] * pow(10, i);
    }
    
    printf("Forward Number: %d\n", forward);
    printf("Backward Number: %d", backward);
}

int main()
{
    int SIZE = 5;
    int arr[5] = {1, 2, 3, 4, 5};
    
    printf("Array: ");
    display(arr, SIZE);
    
    reverse(arr, SIZE);
    left_shift(arr, SIZE);
    right_shift(arr, SIZE);
    insert(arr, SIZE, 2, 0);
    numberify(arr, SIZE);
    
    return 0;
}