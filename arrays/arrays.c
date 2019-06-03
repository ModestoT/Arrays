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
  char **newStorage = malloc( sizeof(arr->elements) * 2 );
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
  arr->capacity++;
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

  // Move every element after the insert index to the right one position

  // Copy the element (hint: use `strdup()`) and add it to the array

  // Increment count by 1

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count > (arr->capacity - 1)){
    fprintf(stderr, "array at capacity\n");
    exit(1);
  }
  // Copy the element and add it to the end of the array
  char *temp = malloc(strlen(element) * sizeof(char));

  for (int i = 0; i < strlen(element); i++){
    temp[i] = element[i];
  }
  temp[strlen(element)] = '\0';

  arr->elements[arr->count] = temp;
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

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!

  // Shift over every element after the removed element to the left one position

  // Decrement count by 1

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
  arr_append(arr, "STRING4");
  resize_array(arr);
  // arr_append(arr, "STRING2");
  // char *read = arr_read(arr, 1);
  // printf("Read method: %s\n", read);
  //arr_append(arr, "STRING3");
  arr_print(arr);
  // arr_remove(arr, "STRING3");
  // arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
