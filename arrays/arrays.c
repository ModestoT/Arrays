#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
  // Allocate memory for the Array struct
  Array *arr = malloc(sizeof(Array));
  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;
  // Allocate memory for elements
  arr->elements = malloc( capacity * sizeof(char *) );

  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  free(arr->elements);
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  // char **newStorage = malloc(20);
  int newCapcity = arr->capacity * 2;
  char **newStorage = malloc( newCapcity * sizeof(char *) );
  // newStorage[0] = arr->elements[0];
  // printf("%s\n", newStorage[0]);

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++){
    newStorage[i] = arr->elements[i];
  }
  // printf("new string: %s\n", newStorage[0]);
  // printf("new array size: %ld\n", sizeof(*newStorage));
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->capacity = newCapcity;
  arr->elements = newStorage;
}



/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index) {

  // Throw an error if the index is greater or equal to than the current count
  if (index >= arr->count){
    fprintf(stderr, "index out of bounds\n");
    return NULL;
  }
  // Otherwise, return the element at the given index
  return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *
 * Store the VALUE of the given string, not the REFERENCE
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count){
    fprintf(stderr, "index out of bounds\n");
    exit(1);
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count+1 > arr->capacity){
    printf("going over capcity need to resize array\n");
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = arr->count-1; i >= index; i--){
    arr->elements[i+1] = arr->elements[i];
  }
  // Copy the element (hint: use `strdup()`) and add it to the array
  // char *temp = strdup(element);
  arr->elements[index] = strdup(element);
  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count > (arr->capacity - 1)){
    // fprintf(stderr, "array at capacity\n");
    // exit(1);
    resize_array(arr);
  }
  // Copy the element and add it to the end of the array
  // char *temp = strdup(element);

  arr->elements[arr->count] = strdup(element);
  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {
  int found = 0;
  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  for (int i = 0; i < arr->count; i++){
    if (strcmp(arr->elements[i], element) == 0){
      found = i;
      printf("Found element: %s\n", arr->elements[i]);
    }
  }
  
  if (found < 0){
    fprintf(stderr, "Value not found\n");
    exit(1);
  }

  // after finding the element free that spot in memory
  free(arr->elements[found]);
  
  // printf("String: %s, Index: %d\n", element, found);
  // Shift over every element after the removed element to the left one position
  for (int i = found; i < arr->count-1; i++){
    arr->elements[i] = arr->elements[i+1];
  }
  // Decrement count by 1
  printf("first spot: %s\n", arr_read(arr, 0));
  printf("last spot: %s\n", arr->elements[arr->count-1]);
  arr->count--;
}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  // arr_insert(arr, "STRING1", 0);
  arr_insert(arr, "STRING4", 0);
  resize_array(arr);
  arr_insert(arr, "STRING2", 0);
  // char *read = arr_read(arr, 1);
  // printf("Read method: %s\n", read);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING4");
  arr_append(arr, "VALUE-1");
  arr_print(arr);
  arr_remove(arr, "STRING2");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
