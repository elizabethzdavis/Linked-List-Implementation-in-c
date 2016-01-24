#include <stdio.h>
#include <stdlib.h>
#include "ldata.h"
#include <string.h>



// Creates and returns an empty data record, where
// city = "", lat = 0.0, lon = 0.0
struct LData *create_empty_data() {
	struct LData *data;
	data = malloc(sizeof(struct LData));
	data->city = ""; 
	data->lat = 0.0;
	data->lon = 0.0;
	return data;
}


// Creates and returns a data record with the specified values
struct LData *create_data(char *city, double lat, double lon) {
struct LData *data;
	data = malloc(sizeof(struct LData));
	data->city = city; 
	data->lat = lat;
	data->lon = lon;
	return data;
}

// Returns true if and only if the city of data1 comes
// alphanumerically before or is the same as the city of data2
int are_ordered(struct LData *data1, struct LData *data2) {
	//string compare - if equal return 0, if first is greater, it's more than one 
	//String compare - if the second greater, returns less than 1

	//If less it means it is in order
	int compare = strcmp (data1 -> city, data2 -> city);
	if(compare <= 0) {
		return 1;
	}

	else { 
		return 0;
	}
}

// Returns true if and only if the city of data1 equals the city of data2
int are_equal(struct LData *data1, struct LData *data2) {
	int compare = strcmp (data1 -> city, data2 -> city);
	if(compare == 0) {
		return 1;
	}

	else {
		return 0;
	}
}

// Swaps the contents of data1 and data2
void swap_data(struct LData *data1, struct LData *data2) {
	struct LData data = *data1;
	*data1 = *data2;
	*data2 = data;
}

// Resets the information in data to default values (see create_empty_data)
void clear_data(struct LData *data) {
	data -> city = "";
	data -> lat = 0.0;
	data -> lon = 0.0;
}

// Prints the data in the format: (city, lat, lon)
// where lat and lon are printed to one decimal place
void print_data(struct LData *data) {
		printf("(%s, %.1f, %.1f)",
			data->city,
			data->lat,
			data->lon);
}
