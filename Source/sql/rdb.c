#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64

struct column {
    char name[NAME_SIZE];
    int type; // For simplicity, 0->int, 1->string
    int data_size;
    int index; // in table columns (not needed??)
};

struct row {
    char** values; // array of values, one for each column
};

struct table {
    char name[NAME_SIZE];
    int column_count;
    struct column* columns; // dynamically allocated array
    int row_count;
    struct row* rows; // dynamically allocated array
};

struct database {
    int table_count;
    struct table* tables; // dynamically allocated array
};

void init_table(struct table* t, const char* name, int column_count) {

    strcpy(t->name, name);
    t->column_count = column_count;
    t->columns = (struct column*)malloc(column_count * sizeof(struct column));
    t->row_count = 0;
    t->rows = NULL; // Initially no rows
}

// Function to add a new row to a table
void add_row(struct table* t, char** values) {
    t->rows = (struct row*)realloc(t->rows, (t->row_count + 1) * sizeof(struct row));
    t->rows[t->row_count].values = (char**)malloc(t->column_count * sizeof(char*));
    for (int i = 0; i < t->column_count; i++) {
        t->rows[t->row_count].values[i] = strdup(values[i]);
    }
    t->row_count++;
}

// Function to create a new database
void init_database(struct database* db, int table_count) {
    db->table_count = table_count;
    db->tables = (struct table*)malloc(table_count * sizeof(struct table));
}

void free_table(struct table* t) {
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
    struct database db;
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
    printf("First row: ID = %s, Name = %s, Age = %s\n",
        db.tables[0].rows[0].values[0],
        db.tables[0].rows[0].values[1],
        db.tables[0].rows[0].values[2]);

    // Free allocated memory
    free_table(&db.tables[0]);
    free(db.tables);
}


int main() {
    /*struct database* db = (struct database*)malloc(sizeof(struct database));
    if (db == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    create_table(db);

    return 0;*/
    test();
}