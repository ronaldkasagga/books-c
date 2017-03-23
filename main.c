#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "book_store.h"

Book* create_book(char *title, char *author);
void print_book(int i, Book* book);

int main() {
    printf("Testing book app ;)\n\n");

    BookStore *store = BookStore_new();

    store->add_book(store, create_book(strdup("Jane Austen"),strdup("Pride and Prejudice")));
    store->add_book(store, create_book(strdup("Stendhal"),strdup("Le Rouge et le Noi")));
    store->add_book(store, create_book(strdup("Andrew Stellman, Jennifer Greene"),strdup("Head first C#")));

    printf("3 Books\n");
    store->show_books(store, print_book);

    store->add_book(store, create_book(strdup("Rahul Soni"),strdup("Nginx")));
    store->remove_book(store, "Pride and Prejudice");

    printf("\nAdded 'Nginx', Deleted #0'Pride and Prejudice'. -> Showing 3\n");
    store->show_books(store, print_book);

    store->add_book(store, create_book(strdup("Lee Zhi Eng"),strdup("Qt5 C++ GUI Programming Cookbook")));
    store->remove_book(store, "Head first C#");

    printf("\nAdded 'Qt5...', Deleted #1'Head first C#'. -> Showing 3\n");
    store->show_books(store, print_book);

    remove_book(store,"Qt5 C++ GUI Programming Cookbook");

    printf("\nDeleted #2'Qt5...'. -> Showing 2\n");
    store->show_books(store, print_book);

    BookStore_free(store);

    return 0;
}

void print_book(int index, Book* book){
    fprintf(stdout, "[%d][Title : '%s' ][Author : '%s' ]\n",index, book->title, book->author);
}

Book* create_book(char *author,char *title){
    Book *book = malloc(sizeof(Book));
    book->title = title;
    book->author= author;
    return book;
}