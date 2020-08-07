#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"

int main(int argc, char **argv)
{
    if (argc != 6)
    {
        printf("Use with riverctl!\n");
        return EXIT_FAILURE;
    }
    //parse river parameters
    int clientCount = atoi(argv[1]);
    int masterCount = atoi(argv[2]);
    double masterWidthFactor = atof(argv[3]);
    int screenWidth = atoi(argv[4]);
    int screenHeight = atoi(argv[5]);

    //insert the given amount of clients into the tree
    bstree *tree = bstree_create(screenWidth, screenHeight, masterWidthFactor);
    for (int c = 0, m = 0; c < clientCount; c++, m++)
    {
        bstree_insert(tree, m < masterCount);
    }

    //print the tree to stdout
    bstree_print(tree, stdout);

    //cleanup and exit
    bstree_destroy(tree);
    return EXIT_SUCCESS;
}