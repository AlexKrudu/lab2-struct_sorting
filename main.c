#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Person {
    char surname[20];
    char name[20];
    char batua[20];
    unsigned int phone_number;
};

int compare(struct Person p1, struct Person p2) {
    int comp = 0;
    comp = strncmp(p1.surname, p2.surname, 20);
    if (!comp) {
        comp = strncmp(p1.name, p2.name, 20);
        if (!comp) {
            comp = strncmp(p1.batua, p2.batua, 20);
            if (!comp) {
                comp = p1.phone_number - p2.phone_number;
            }
        }
    }
    return comp;
}

void swap(struct Person *a, struct Person *b) {
    struct Person temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct Person *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    if (l < n && compare(arr[l], arr[largest]) > 0)
        largest = l;

    if (r < n && compare(arr[r], arr[largest]) > 0)
        largest = r;

    if (largest != i) {
        swap(arr + i, arr + largest);
        heapify(arr, n, largest);
    }
}

void heapSort(struct Person *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr, arr + i);

        heapify(arr, i, 0);
    }
}

void quicksort(struct Person *left, int n, int depth) {
    sort:
    if (depth > 4096) {
        heapSort(left, n);
        return;
    }
    struct Person *right = left + n - 1;
    if (left < right) {
        struct Person pivot = *(left + (right - left) / 2);
        struct Person *low = left;
        struct Person *high = right;
        while (1) {
            while (compare(*(low),pivot) < 0) {
                low++;
            }
            while (compare(*(high), pivot) > 0) {
                high--;
            }
            if (high <= low) {
                break;
            }
            swap(low++, high--);
        }
        if (high - left + 1 < right - high) {
            quicksort(left, high - left + 1, ++depth);
            left = high + 1;
            n = right - high;
            goto sort;
        } else {
            quicksort(high + 1, right - high, ++depth);
            n = high - left + 1;
            goto sort;
        }

    }
}


int main(int argc, char *argv[]) {
    FILE *in, *out;
    int i = 0, size = 1;
    in = fopen(argv[1], "r");
    struct Person *arr = (struct Person *) malloc(sizeof(struct Person) * size);
    while (!feof(in)) {
        if (i == size){
            size *= 2;
            arr = (struct Person*) realloc(arr, sizeof(struct Person) * size);
        }
        fscanf(in, "%s %s %s %i\n", arr[i].surname, arr[i].name, arr[i].batua, &arr[i].phone_number);
        i++;
    }
    fclose(in);
    out = fopen(argv[2], "w");
    quicksort(arr, i, 0);
    for (int j = 0; j < i; j++){
        fprintf(out, "%s %s %s %i\n", arr[j].surname, arr[j].name, arr[j].batua, arr[j].phone_number);
    }
    fclose(out);
    return 0;
}


