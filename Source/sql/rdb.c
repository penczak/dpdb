#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64

typedef struct column {
    char name[NAME_SIZE];
    int type; // For simplicity, 0->int, 1->string
    int data_size;
    int index; // in table columns (not needed??)
} column;

typedef struct row {
    char** values; // array of values, one for each column
} row;

typedef struct table {
    char name[NAME_SIZE];
    int column_count;
    struct column* columns; // dynamically allocated array
    int row_count;
    struct row* rows; // dynamically allocated array
} table;

typedef struct database {
    int table_count;
    struct table* tables; // dynamically allocated array
} database;

void init_table(table* t, const char* name, int column_count) {

    strcpy(t->name, name);
    t->column_count = column_count;
    t->columns = (column*)malloc(column_count * sizeof(column));
    t->row_count = 0;
    t->rows = NULL; // Initially no rows
}

// Function to add a new row to a table
void add_row(table* t, char** values) {
    t->rows = (row*)realloc(t->rows, (t->row_count + 1) * sizeof(row));
    t->rows[t->row_count].values = (char**)malloc(t->column_count * sizeof(char*));
    for (int i = 0; i < t->column_count; i++) {
        t->rows[t->row_count].values[i] = strdup(values[i]);
    }
    t->row_count++;
}

// Function to create a new database
void init_database(database* db, int table_count) {
    db->table_count = table_count;
    db->tables = (table*)malloc(table_count * sizeof(table));
}

void free_table(table* t) {
    for (int i = 0; i < t->row_count; i++)
    {
        for (int j = 0; j < t->column_count; j++)
        {
            free(t->rows[i].values[j]);
        }
        free(t->rows[i].values);
    }
    free(t->rows);
    free(t->columns);
}

void test() {
    database db;
    init_database(&db, 2); // Initialize a database with space for 2 tables

    init_table(&db.tables[0], "Table1", 3); // Initialize first table with 3 columns

    // Set column names for the first table
    strcpy(db.tables[0].columns[0].name, "ID");
    db.tables[0].columns[0].type = 0;
    strcpy(db.tables[0].columns[1].name, "Name");
    db.tables[0].columns[1].type = 1;
    strcpy(db.tables[0].columns[2].name, "Age");
    db.tables[0].columns[2].type = 0;

    // Add a row to the first table
    char* row1_values[] = { "1", "Alice", "30" };
    add_row(&db.tables[0], row1_values);

    // Print the first row of the first table
    printf("\n\nFirst row: ID = %s, Name = %s, Age = %s\n",
        db.tables[0].rows[0].values[0],
        db.tables[0].rows[0].values[1],
        db.tables[0].rows[0].values[2]);

    // Free allocated memory
    free_table(&db.tables[0]);
    free(db.tables);
}

typedef struct commandTree {
    char command[99]; // "table"
    bool isOptional; // true
    struct commandTree* children[99]; // "new", "update", "drop" trees
    char parameters[99];
    bool isLeaf;
    int (*func)(char*);
} commandTree;

int fun(char* input) { printf("Value of a is %s\n", input); return 1; }

typedef struct word {
    int length;
    char text[99];
} word;

word getWord(char* input) {
    word out = {};
    out.length = 0;
    //out.text = ;
    for (int i = 0; i < 99; i++)
    {
        if (input[i] == ' ') {
            return out;
        }
        out.length = i + 1;
        out.text[i] = input[i];
    }
    return out;
}

commandTree getCommandTree() {
    commandTree tr = {};
    //tr.command = NULL;
    tr.isOptional = false;
    tr.isLeaf = false;
    tr.func = &fun;
    //tr.children = 
    return tr;
}

int getCommand(char* input) {
    commandTree curr = getCommandTree();
    int inputPtr = 0;
    for (int i = 0; i < 99; i++)
    {

    }
    return 1;
}

int main() {
    char input[100];
    printf("Enter command:\n");
    scanf(" %s", &input);

    //if (command == "") {
    //
    //}
    //commandTree cmd = getCommandTree();

    //int x = (cmd.func)(command);
    //printf("\nx is %d", x);

    char *input = "hello world";
    char commands[99][99] = {{ 0 }};
    int commandCt = 1, i = 0, j = 0;
    while (input[i] != '\0')
    {
        if (input[i] == ' ') {
            if (j != 0) {
                j = 0;
                commandCt++;
            }
            i++;
            continue;
        }
        commands[commandCt - 1][j] = input[i];
        i++;
        j++;
    }

    printf("\ncount:|%d|", commandCt);
    for (int i = 0; i < commandCt; i++)
    {
        printf("\n|%s|", commands[i]);
    }

    /*int pt = 0;
    printf("\nwhole text is |%s|", commands[0]);
    word w = getWord(commands[0]);
    printf("\nw.length is |%d|", w.length);
    printf("\nw.text is |%s|", w.text);

    printf("\ntext after point is |%s|", commands[1]);*/

    //test();
    return 0;
}
