#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 10
#define MAX_TITLE_LENGTH 50
#define MAX_AUTHOR_LENGTH 50
#define MAX_GENRE_LENGTH 20

struct Book {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char genre[MAX_GENRE_LENGTH];
    float price;
};

struct Book* bookstore[MAX_BOOKS];

// mock data
void Data() {
    for (int i = 0; i < MAX_BOOKS; i++) {
        bookstore[i] = (struct Book*)malloc(sizeof(struct Book));
        snprintf(bookstore[i]->title, sizeof(bookstore[i]->title), "Book %d", i + 1);
        snprintf(bookstore[i]->author, sizeof(bookstore[i]->author), "Author %d", i + 1);
        snprintf(bookstore[i]->genre, sizeof(bookstore[i]->genre), "Genre %d", i + 1);
        bookstore[i]->price = 10.00 + (i * 2);
    }
}

void insertBook(int index, const char* title, const char* author, const char* genre, float price) {
    if (index >= 0 && index < MAX_BOOKS) {
        if (bookstore[index] == NULL) {
            bookstore[index] = (struct Book*)malloc(sizeof(struct Book));
        }
        snprintf(bookstore[index]->title, sizeof(bookstore[index]->title), "%s", title);
        snprintf(bookstore[index]->author, sizeof(bookstore[index]->author), "%s", author);
        snprintf(bookstore[index]->genre, sizeof(bookstore[index]->genre), "%s", genre);
        bookstore[index]->price = price;
    }
}

void deleteBook(int index) {
    if (index >= 0 && index < MAX_BOOKS) {
        if (bookstore[index] != NULL) {
            free(bookstore[index]);
            bookstore[index] = NULL;
        }
    }
}

int linearSearch(const char* title) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (bookstore[i] != NULL && strcmp(bookstore[i]->title, title) == 0) {
            return i;
        }
    }
    return -1;  // Book not found
}

void displayBookstore() {
    printf("Bookstore Contents:\n");
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (bookstore[i] != NULL) {
            printf("Title: %s\n", bookstore[i]->title);
            printf("Author: %s\n", bookstore[i]->author);
            printf("Genre: %s\n", bookstore[i]->genre);
            printf("Price: %.2f\n", bookstore[i]->price);
            printf("\n");
        }
    }
}

int main() {
    Data();

    int choice;
    do {
        printf("Menu:\n");
        printf("1. Insert Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Display Bookstore\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    int index;
                    char title[MAX_TITLE_LENGTH];
                    char author[MAX_AUTHOR_LENGTH];
                    char genre[MAX_GENRE_LENGTH];
                    float price;
                    printf("Enter index: ");
                    scanf("%d", &index);
                    printf("Enter title: ");
                    scanf("%s", title);
                    printf("Enter author: ");
                    scanf("%s", author);
                    printf("Enter genre: ");
                    scanf("%s", genre);
                    printf("Enter price: ");
                    scanf("%f", &price);
                    insertBook(index, title, author, genre, price);
                    break;
                }
            case 2:
                {
                    int index;
                    printf("Enter index to delete: ");
                    scanf("%d", &index);
                    deleteBook(index);
                    break;
                }
            case 3:
                {
                    char title[MAX_TITLE_LENGTH];
                    printf("Enter title to search: ");
                    scanf("%s", title);
                    int searchResult = linearSearch(title);
                    if (searchResult != -1) {
                        printf("Book found at index %d\n", searchResult);
                    } else {
                        printf("Book not found\n");
                    }
                    break;
                }
            case 4:
                displayBookstore();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    for (int i = 0; i < MAX_BOOKS; i++) {
        if (bookstore[i] != NULL) {
            free(bookstore[i]);
        }
    }

    return 0;
}
