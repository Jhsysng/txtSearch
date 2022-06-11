#pragma once
#define TABLE_SIZE 10000
#define WORD_SIZE 20
#define Queue_MAX 3

int num_comparisons;
int num_documents;
char* file[10][2000];
char* file_[10][2000];
typedef struct element {
	int txt; 
	int count; 
	int position[100];
}element;

typedef struct information* infor_pointer;

typedef struct information {
	char* key;
	element e[10];
	infor_pointer link;
}information;

infor_pointer Table[TABLE_SIZE] = { NULL }; // HashTable

void chaining_insert();
infor_pointer chaining_search(char* insert);
int hash(char* key);
int transform(char* key);
void getFile(char* file_name);
void indexing1(char* text);
void indexing2(char* text);
void getFilelist();
void sort(element list[], int n);

typedef struct element* element_pointer;

element_pointer printing[10];
