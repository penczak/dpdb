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


// Generic Utils
bool is_Int(char* str1) {
	int n, m;
	while (*str1 == ' ') str1++;
	n = m = 0;
	if (*str1 == '+' || *str1 == '-') str1++;
	while (*str1 >= '0' && *str1 <= '9') {
		n++;
		str1++;
	}
	while (*str1 == ' ') str1++;
	return *str1 == 0;
}

bool is_Decimal(char* str1) {
	int n, m;
	while (*str1 == ' ') str1++;
	n = m = 0;
	if (*str1 == '+' || *str1 == '-') str1++;
	while (*str1 >= '0' && *str1 <= '9') {
		n++;
		str1++;
	}
	if (*str1 == '.') {
		str1++;
		while (*str1 >= '0' && *str1 <= '9') {
			m++;
			str1++;
		}
		if (!n && !m) return false;
	}
	else if (!n) {
		return false;
	}
	while (*str1 == ' ') str1++;
	return *str1 == 0;
}


// Table management
void init_table(table* t, const char* name, int column_count) {
	strcpy(t->name, name);
	t->column_count = column_count;
	t->columns = (column*)malloc(column_count * sizeof(column));
	t->row_count = 0;
	t->rows = NULL; // Initially no rows
}

void add_row_internal(table* t, char** values) {
	t->rows = (row*)realloc(t->rows, (t->row_count + 1) * sizeof(row));
	t->rows[t->row_count].values = (char**)malloc(t->column_count * sizeof(char*));
	for (int i = 0; i < t->column_count; i++) {
		t->rows[t->row_count].values[i] = strdup(values[i]);
	}
	t->row_count++;
}

void add_row(table* t, char** values) {
	for (int i = 0; i < t->column_count; i++)
	{
		switch (t->columns[i].type)
		{
		case 0:
			if (!is_Int(values[i])) {
				printf("Value [%s] was not an integer for column [%s].", values[i], t->columns[i].name);
				return;
			}
			break;
		case 1: // string passes
		default:
			break;
		}
	}

	add_row_internal(t, values);
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
	add_row_internal(&db.tables[0], row1_values);

	// Print the first row of the first table
	printf("\n\nFirst row: ID = %s, Name = %s, Age = %s\n",
		db.tables[0].rows[0].values[0],
		db.tables[0].rows[0].values[1],
		db.tables[0].rows[0].values[2]);

	// Free allocated memory
	free_table(&db.tables[0]);
	free(db.tables);
}


int main() {
	database db;
	init_database(&db, 2);

	init_table(&db.tables[0], "Table1", 1);

	// Set column names for the first table
	strcpy(db.tables[0].columns[0].name, "ID");
	db.tables[0].columns[0].type = 0;

	while (true) {

		char *input = malloc(sizeof(char) * 100);
		printf("Enter value:\n");
		scanf(" %s", &input);
		add_row(&db.tables[0], &input);

		for (int i = 0; i < db.tables[0].row_count; i++)
		{
			printf("\n : %s", db.tables[0].rows[i].values[0]);
		}
	}

	return 0;
}
