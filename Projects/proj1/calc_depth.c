/*
 * PROJ1-1: YOUR TASK A CODE HERE
 *
 * Feel free to define additional helper functions.
 */

#include "calc_depth.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

#define MIN(a,b) ((a) < (b) ? a : b)
#define MAX(a,b) ((a) > (b) ? a : b)

Image make_image(unsigned char *data, int width, int height) {
	Image image = {.data = data, .width = width, .height = height};
	return image;
}

unsigned char get_pixel(Image *image, int x, int y) {
	return *(image->data + x + image->width * y); // Row major implementation
}

void set_pixel(Image *image, int x, int y, unsigned char value) {
	*(image->data + x + image->width * y) = value; // Row major implementation
}

/* Stores a feature patch */
typedef struct {
	Image *image; // Image that the feature belongs to
	int width; // Dimensions of feature
	int height;
	int x; // Coordinates of the center
	int y;
} Feature;

/* Create a new feature patch */
Feature make_feature(Image *image, int width, int height, int x, int y) {
	Feature feature = {.image = image, .width = width, .height = height, .x = x, .y = y};
	return feature;
}

/* A SearchSpace represents the region of pixels to be searched */
typedef struct {
	int min_x; // Min and max coordinates, which bound the search space
	int max_x;
	int min_y;
	int max_y;
	Image *image; // The image that is being searched
} SearchSpace;

/* Creates a search space by considering the feature dimensions and image dimensions.
   Constructs a search space where every pixel is searchable */
SearchSpace make_search_space(Image * image, int maximum_displacement, int x, int y, 
	int feature_width, int feature_height) {
	int min_x = MAX(x - maximum_displacement, feature_width), 
		max_x = MIN(x + maximum_displacement, image->width - 1 - feature_width),
		min_y = MAX(y - maximum_displacement, feature_height), 
		max_y = MIN(y + maximum_displacement, image->height - 1 - feature_height);

	SearchSpace search_space = {.min_x = min_x, .max_x = max_x, 
								.min_y = min_y, .max_y = max_y, .image = image};
	return search_space;
}

long int calc_distance(Feature *left, Feature *right) {
	int w = left->width, h = left->height;
	long int distance = 0;
	Image *left_image = left->image, *right_image = right->image;
	
	for (int dx = -w; dx <= w; dx++) {
		for (int dy = -h; dy <= h; dy++) {
			// Getting the left and right (x, y) pairs
			int left_x = left->x + dx, left_y = left->y + dy;
			int right_x = right->x + dx, right_y = right->y + dy;
			// Getting left and right pixel values
			int left_pixel = get_pixel(left_image, left_x, left_y);
			int right_pixel = get_pixel(right_image, right_x, right_y);

			int delta = (left_pixel - right_pixel); // Pixel difference
			distance += delta * delta; // Distance is square of difference
		}
	}
	return distance;
}

/* Implements the normalized displacement function */
unsigned char normalized_displacement(int dx, int dy, int maximum_displacement) {
    double squared_displacement = dx * dx + dy * dy;
    double normalized_displacement = round(255 * sqrt(squared_displacement) / sqrt(2 * maximum_displacement * maximum_displacement));
    return (unsigned char) normalized_displacement;
}

/* Searches through a search space and then finds the optimum dx and dy */
void search(Feature *left_feature, SearchSpace *search_space, 
			int *dx, int *dy, int maximum_displacement) {
	
	long best_distance = LONG_MAX;
	unsigned char best_displacement = 0;
	
	Image *right_image = search_space->image; // The right image

	// Iterating thorugh search space
	for (int x = search_space->min_x; x <= search_space->max_x; x++) {
		for (int y = search_space->min_y; y <= search_space->max_y; y++) {
			// Create a feature around (x, y)
			Feature right_feature = make_feature(right_image, left_feature->width,
				left_feature->height, x, y);
			
			// Calculating the distance
			int delta_x = left_feature->x - x, delta_y = left_feature->y - y;
			long distance = calc_distance(left_feature, &right_feature);
			unsigned char curr_displacement = normalized_displacement(delta_x, delta_y, maximum_displacement);

			// Store the position at which the best distance was found
			if (distance < best_distance || 
			   (distance == best_distance && curr_displacement < best_displacement)) {
				best_distance = distance;
				*dx = delta_x;
				*dy = delta_y;
				best_displacement = curr_displacement;
			}
		}
	}
}

/* Fills an entire image with the specified value */
void fill(Image *image, unsigned char value) {
	for (int i = 0; i < image->width; i++) { // Iterate through all pixels
		for (int j = 0; j < image->height; j++) {
			set_pixel(image, i, j, value); // Set the value of the pixel
		}
	}
}

void calc_depth(unsigned char *depth_map, unsigned char *left, unsigned char *right, 
				int image_width, int image_height, int feature_width, 
				int feature_height, int maximum_displacement) {

	// Wrapping buffers as image objects
	Image depth_map_image = make_image(depth_map, image_width, image_height);
	Image left_image = make_image(left, image_width, image_height);
	Image right_image = make_image(right, image_width, image_height);

	fill(&depth_map_image, 0); // Filling with 0s

	if (maximum_displacement == 0) { // End here if maximum displacement is 0
		return;
	}

	for (int i = 0; i < left_image.width; i++) { // Iterating through all the pixels
		for (int j = 0; j < left_image.height; j++) {
			// Check if feature fits inside the image
			if (i - feature_width < 0 || i + feature_width >= left_image.width || 
				j - feature_height < 0 || j + feature_height >= left_image.height) {
				continue; // These pixels have a feature patch that is out of bounds. Skip them
			}
			// The pixel in the left image can be assigned a displacement. 
			// Create a feature struct and a search space around this pixel location
			Feature left_feature = make_feature(&left_image, feature_width, feature_height, i, j);
			SearchSpace search_space = make_search_space(&right_image, maximum_displacement, i, j,
				feature_width, feature_height);

			//print_search_space(&search_space);

			int dx, dy; // Integers that store the displacement vector
			search(&left_feature, &search_space, &dx, &dy, maximum_displacement); // Search and find the best displacement
			unsigned char depth_value = normalized_displacement(dx, dy, maximum_displacement);

			set_pixel(&depth_map_image, i, j, depth_value); // Store the normalized displaement
		}
	}
}

