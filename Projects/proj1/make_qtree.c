/*
 * PROJ1-1: YOUR TASK B CODE HERE
 *
 * Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "quadtree.h"
#include "make_qtree.h"
#include "utils.h"

#define ABS(x) (((x) < 0) ? (-(x)) : (x))


int homogenous(unsigned char *depth_map, int map_width, int x, int y, int section_width) {

    int v = y;
    int u = x;
    int raw = map_width*y + x;
    int val = depth_map[raw];
    for(int sec_v = v; sec_v<(v+section_width); sec_v++) //v
    {
        for(int sec_u = u; sec_u<(u+section_width); sec_u++) //u
        {   
            if(depth_map[map_width*sec_v + sec_u] != val)
                return 256;
        }

    }
    return val;
 
}


qNode *qtree_helper(unsigned char *depth_map, int map_width, int section_width, int x, int y) {
    
    qNode *root = (qNode *)malloc(sizeof(qNode));
    if(root==NULL)
    {
        allocation_failed();
    }

    root->x = x;
    root->y = y;
    root->size = section_width;
    int val = homogenous(depth_map, map_width, x, y, section_width);
    (*root).gray_value = val;

    if(val!=256)
    {
        (*root).leaf = 1;
        return root;
    }
    else
    {
        root->leaf = 0;
        root->child_NW = qtree_helper(depth_map, map_width, section_width/2, x, y);
        root->child_NE = qtree_helper(depth_map, map_width, section_width/2, x + (section_width/2), y);
        root->child_SW = qtree_helper(depth_map, map_width, section_width/2, x, y + (section_width/2));
        root->child_SE = qtree_helper(depth_map, map_width, section_width/2, x + (section_width/2), y + (section_width/2));
        return root;
    }

}

qNode *depth_to_quad(unsigned char *depth_map, int map_width) {
    
    qNode *root = qtree_helper(depth_map, map_width, map_width, 0, 0);
    return root;
}

void free_qtree(qNode *qtree_node) {
    if(qtree_node) {
        if(!qtree_node->leaf){
            free_qtree(qtree_node->child_NW);
            free_qtree(qtree_node->child_NE);
            free_qtree(qtree_node->child_SE);
            free_qtree(qtree_node->child_SW);
        }
        free(qtree_node);
    }
}

