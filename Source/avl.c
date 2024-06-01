#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node* left;
    struct node* right;
    int height;
    char key[16];
    char value[128];
};

void insert(struct node** rp, char key[16], char value[128]);
char* get_value(struct node* n, char key[16]);
void print_tree(struct node* n, int depth);
void print_tree_json(struct node* n, int depth);
int height(struct node* n);
void update_height(struct node* n);
int get_balance(struct node* n);
struct node* rotate_right(struct node* n);
struct node* rotate_left(struct node* n);
struct node* balance(struct node* n);

int main() {
    struct node* root = NULL;
    printf("Hello World!\n");

    while (1) {
        char chr;
        printf("\n\n");
        printf("i - insert\n");
        printf("g - get\n");
        printf("p - print tree\n");
        printf("j - print tree json\n");
        printf("Enter command:\n");
        scanf(" %c", &chr);

        switch (chr)
        {
        case ('i'): {
            char insert_key[16];
            printf("Enter key:\n");
            scanf(" %s", &insert_key);

            char insert_value[128];
            printf("Enter value:\n");
            scanf(" %s", &insert_value);

            insert(&root, insert_key, insert_value);
            break;
        }
        case ('g'): {
            char key[16];
            printf("Enter key:\n");
            scanf(" %s", &key);

            get_value(root, key);
            break;
        }
        case ('p'):
            print_tree(root, 0);
            break;
        case ('j'):
            print_tree_json(root, 0);
            break;
        default:
            break;
        }
    }
}

// malloc example
//  int* pA = malloc(sizeof(int) * 8);
//  if (!pA) { perror("malloc"); exit(EXIT_FAILURE); }


void insert(struct node** rp, char key[16], char value[128]) {
    if (*rp == NULL) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        if (new_node == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1;
        strcpy(new_node->key, key);
        strcpy(new_node->value, value);
        // update root pointer to the new node
        *rp = new_node;
        return;
    }
    // if root is not null, traverse tree like with search to find where to insert
    struct node* current = *rp;
    if (strcmp(key, current->key) < 0) {
        // go to left
        insert(&current->left, key, value);
    }
    else if (strcmp(key, current->key) > 0) {
        // go to right
        insert(&current->right, key, value);
    }
    else {
        printf("err: duplicate key: %s. not inserting", key);
        return;
    }

    update_height(current);
    *rp = balance(current);
}

char* get_value(struct node* n, char key[16]) {
    if (n == NULL) {
        printf("key not found!\n");
        return "";
    }
    int strcmp_val = strcmp(key, n->key);
    if (strcmp_val < 0) {
        get_value(n->left, key);
    }
    else if (strcmp_val > 0) {
        get_value(n->right, key);
    }
    else { // (strcmp_val == 0)
        printf("value: %s", n->value);
        return n->value;
    }
}

void print_tree(struct node* n, int depth) {
    if (n == NULL) {
        return;
    }
    print_tree(n->left, depth + 1);
    printf("Key: %s, Value: %s, Height: %d, Depth %d\n", n->key, n->value, n->height, depth);
    print_tree(n->right, depth + 1);
}

void print_tree_json(struct node* n, int depth) {
    /*{
        value: x
        left : { }
        right: { }
    }*/
    if (n == NULL) {
        printf("{}");
        return;
    }
    printf("{\n");
    int i;
    for (i = 0; i < depth + 1; i++)
    {
        printf("  ");
    }
    printf("key: %s\n", n->key);
    for (i = 0; i < depth + 1; i++)
    {
        printf("  ");
    }
    printf("value: %s\n", n->value);
    for (i = 0; i < depth + 1; i++)
    {
        printf("  ");
    }
    printf("left: ");
    print_tree_json(n->left, depth + 1);
    printf("\n");
    for (i = 0; i < depth + 1; i++)
    {
        printf("  ");
    }
    printf("right: ");
    print_tree_json(n->right, depth + 1);
    printf("\n");
    for (i = 0; i < depth; i++)
    {
        printf("  ");
    }
    printf("}");
}

int height(struct node* n) {
    return n == NULL ? 0 : n->height;
}

void update_height(struct node* n) {
    if (n != NULL) {
        int left_height = height(n->left);
        int right_height = height(n->right);
        n->height = (left_height > right_height ? left_height : right_height) + 1;
    }
}

int get_balance(struct node* n) {
    return n == NULL ? 0 : height(n->right) - height(n->left);
}

struct node* balance(struct node* n) {
    int balance = get_balance(n);

    // LEFT heavy
    if (balance < -1) {
        if (get_balance(n->left) > 0) {
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }

    // RIGHT heavy
    if (balance > 1) {
        if (get_balance(n->right) < 0) {
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }

    return n;
}

//    a              b
//   / \              \
//  b   c    ->        a
//                      \
//                       c
struct node* rotate_right(struct node* a) { // pointer to a pointer to a node (root pointer)
    struct node* b = a->left;
    struct node* b_right = b->right;
    b->right = a;
    a->left = b_right;
    update_height(a);
    update_height(b);
    return b;
}

//    a                b
//   / \              / \
//  c   b    ->      a   d
//       \          /
//        d        c
struct node* rotate_left(struct node* a) {
    struct node* b = a->right;
    struct node* b_left = b->left;
    b->left = a;
    a->right = b_left;
    update_height(a);
    update_height(b);
    return b;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
