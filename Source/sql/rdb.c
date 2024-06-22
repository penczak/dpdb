#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64

struct column {
    char name[NAME_SIZE];
    char type[NAME_SIZE]; // For simplicity, storing type as string
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

void create_table(struct database* db);

int main() {
    struct database* db = (struct database*)malloc(sizeof(struct database));
    if (db == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    create_table(db);

    return 0;
}
struct table create_table(const char* name, int column_count) {
    struct table t;

    strcpy(t.name, name);
    t.column_count = column_count;
    t.columns = (struct column*)malloc(column_count * sizeof(struct column));
    t.row_count = 0;
    t.rows = NULL; // Initially no rows
    return t;
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
struct database create_database(int table_count) {
    struct database db;
    db.table_count = table_count;
    db.tables = (struct table*)malloc(table_count * sizeof(struct table));
    return db;
}

struct table create_table(const char* name, int column_count) {
    char table_name[NAME_SIZE];
    printf("Enter table name:\n");
    scanf(" %s", &table_name);

    int column_count;
    printf("Enter column count:\n");
    scanf(" %d", &column_count);

    printf("sizeof(struct table): %d", sizeof(struct table));
    printf("sizeof(struct column): %d", sizeof(struct column));
    printf("column_count * sizeof(struct column): %d", column_count * sizeof(struct column));

    struct table table_update = db->tables[table_count];
    strcpy(table_update.name, table_name);
    table_update.index = 0;

    printf("table count before: %d", db->table_count);
    printf("db->tables[table_count]->name: %s", db->tables[db->table_count].name);
    db->table_count++;
    printf("table count after: %d", db->table_count);

    int i;
    for (i = 0; i < column_count; i++)
    {

    }
}