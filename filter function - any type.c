#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FilterResult
{
      void *array;
      int length;
} FilterResult;

FilterResult filterArray(void *array, size_t size, int length, int (*filterFunction)(const void *))
{
      char *arr = (char *)array;
      char *newArray = NULL;
      int newLength = 0;
      char *end = arr + length * size;
      for (char *element = arr; element < end; element += size)
      {
            if (filterFunction(element))
            {
                  newLength++;
                  size_t newSize = newLength * size;
                  newArray = realloc(newArray, newSize);
                  memcpy(newArray + newSize - size, element, size);
            }
      }
      FilterResult result = {newArray, newLength};
      return result;
}

int filterFunction(const void *valuePtr)
{
      int value = *(const int *)valuePtr;
      return value > 5;
}

int main()
{
      int array[] = {0, 1, 1, 5, 6, 7, 4, 3, 5, 2, 8};
      int length = sizeof(array) / sizeof(int);

      FilterResult result = filterArray(array, sizeof(int), length, filterFunction);
      int *filtered = result.array;
      int filteredLength = result.length;

      printf("Filtered array: ");
      for (int i = 0; i < filteredLength; i++)
      {
            printf("%d ", filtered[i]);
      }
      printf("\n");

      free(result.array);
      return 0;
}