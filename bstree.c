#include "bstree.h"

// struct declarations here
struct node
{
	struct node *left;
	struct node *right;
	int x;
	int y;
	int width;
	int height;
};
typedef struct node node_t;

struct bstree
{
	node_t *root;
	int width;
	int height;
	double masterWidthFactor;
};

// declaring static functions here
static node_t *create_node(int x, int y, int width, int height);
static void destroy_node(node_t *node, bool recursive);
static void print_node(const node_t *node, FILE *out);

bstree *bstree_create(int width, int height, double masterWidthFactor)
{
	bstree *tree = malloc(sizeof(bstree));
	tree->root = NULL;
	tree->width = width;
	tree->height = height;
	tree->masterWidthFactor = masterWidthFactor;
	return tree;
}

static node_t *create_node(int x, int y, int width, int height)
{
	node_t *node = malloc(sizeof(node_t));
	node->left = NULL;
	node->right = NULL;
	node->x = x;
	node->y = y;
	node->width = width;
	node->height = height;
	return node;
}

void bstree_destroy(bstree *tree)
{
	if (tree == NULL)
		return;
	destroy_node(tree->root, true);
	free(tree);
}

static void destroy_node(node_t *node, bool recursive)
{
	if (node == NULL)
		return;
	if (recursive)
	{
		destroy_node(node->left, recursive);
		destroy_node(node->right, recursive);
	}
	node->left = NULL;
	node->right = NULL;
	free(node);
}

void bstree_insert(bstree *tree, bool master)
{
	if (tree->root == NULL)
	{
		tree->root = create_node(0, 0, tree->width, tree->height);
	}
	else
	{
		node_t *insert = tree->root;
		while (insert->right != NULL)
		{
			insert = insert->right;
		}
		if (insert->width >= insert->height)
		{
			int leftWidth = insert->width;
			//split width
			if (insert == tree->root)
			{
				leftWidth *= tree->masterWidthFactor;
			}
			else
			{
				leftWidth /= 2;
			}
			insert->left = create_node(insert->x, insert->y, leftWidth, insert->height);
			insert->right = create_node(insert->x + leftWidth, insert->y, insert->width - leftWidth, insert->height);
		}
		else
		{
			//split height
			int leftHeight = insert->height / 2;
			insert->left = create_node(insert->x, insert->y, insert->width, leftHeight);
			insert->right = create_node(insert->x, insert->y + leftHeight, insert->width, insert->height - leftHeight);
		}
	}
}

void bstree_print(const bstree *tree, FILE *out)
{
	if (tree == NULL || tree->root == NULL)
		return;
	else
		print_node(tree->root, out);
}

static void print_node(const node_t *node, FILE *out)
{
	if (node->left != NULL)
	{
		//full binary tree, either no children or two
		print_node(node->left, out);
		print_node(node->right, out);
	}
	else
	{
		//only print node when it is a leaf, therefore representing a client
		char numstr[32];
		snprintf(numstr, 32, "%d %d %d %d\n", node->x, node->y, node->width, node->height);
		fputs(numstr, out);
	}
}
