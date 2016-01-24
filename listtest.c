/*
 * listtest.c
 */

#include <stdio.h>
#include "ldata.h"
#include "llist.h"

int main() {

struct LData *d1 = create_data("DC", 38.9, 77.0);
struct LData *d2 = create_data("New York", 40.7, 74.0);
struct LData *d3 = create_data("Los Angeles", 34.1, 118.3);
struct LData *d4 = create_data("Chicago", 41.8, 87.7);
struct LData *d5;
struct LData *d6;
struct LData *d7;
struct LData *d8;
struct LData *d9;


struct LList *s = create_empty_list();

print_data(d1); printf("\n");// expected: (DC, 38.9, 77.0) //ldata
print_list(s); printf("\n"); // expected: [ ]//llist
add_first(s, d1);
print_list(s); printf("\n");// expected: [(DC, 38.9, 77.0)]//llist
add_first(s, d2);
add_last(s, d3);
print_list(s); printf("\n");// expected: [(New York, 40.7, 74.0) (DC, 38.9, 77.0) (Los Angeles, 34.1, 118.3)]//llist
d5 = rem_last(s);
print_list(s); printf("\n");// expected: [(New York, 40.7, 74.0) (DC, 38.9, 77.0)]//llist
print_data(d5); printf("\n");// expected: (Los Angeles, 34.1, 118.3)//ldata

//Test the cases for part 2://
printf("\n");
printf("tests for part two: \n");
printf("\n");
//Test for lists://newFirst = list -> next;
print_list(s); printf("\n"); //Expected: [NY, DC] 
d6 = rem_first(s); //Removing NY//Removing first, returning last
print_data(d6); printf("\n"); //Expected: NY
print_list(s); printf("\n"); //Expected: [DC]//WORKING
//Removing DC
d7 = rem_first(s);//Issue
print_list(s); printf("\n"); //Expected: []//Issue
add_first(s, d1); //Add DC Back
add_first(s, d4); //Add Chicago
add_last(s, d2); //Add NY
print_list(s); printf("\n"); //Expected: [Chicago, DC, NY]
 printf("\n");
swap_elems(s, 2, 1);
print_list(s);  printf("\n"); //expected: [Chicago, NY, DC]

//--
d8 = rem_elem(s, 1); //removing NY//Do first
print_list(s); printf("\n"); //Expected: [Chicago, DC]
d9 = get_elem(s, 1);
print_data(d9); printf("\n"); //DC
add_elem(s, d3, 1);
print_list(s); printf("\n"); //Expected: [Chicago, LA, DC]

//clear_list(s); print_list(s); //Expected: [0]

printf("\n");

//--
printf("%d", is_empty(s)); printf("\n");//0
printf("%d", size(s)); printf("\n"); //3
printf("%d", contains(s, d3)); printf("\n");//1
printf("%d", contains(s, d2)); printf("\n"); //0
printf("\n");
printf("%d", are_ordered(d4, d1)); printf("\n"); //1
printf("%d", are_ordered(d1, d4)); printf("\n"); //0
printf("%d", are_equal(d4, d1)); printf("\n"); //0
printf("%d", are_equal(d1, d1)); printf("\n"); //1

swap_data(d4, d1); //swap chicago and DC
print_data(d4); printf("\n"); //Should say DC
print_data(d1); printf("\n"); //Should say Chicago
swap_data(d1, d4);
print_data(d4); printf("\n"); //Should say Chicago
print_data(d1); printf("\n"); //Should say DC
//clear_data(d4);
print_data(d4); printf("\n"); //Should say (,0,0)


print_list(s); printf("\n"); //Expected: [Chicago, LA, DC]
insertion_sort(s);
print_list(s); printf("\n"); //Expected: [Chicago, DC, LA]
add_first(s, d2);
print_list(s); printf("\n"); //Expected: [NY, Chicago, DC, LA]
insertion_sort(s);
print_list(s); printf("\n"); //Expected: [Chicago, DC, LA, NY]

}