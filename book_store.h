#ifndef BOOKS_BOOK_STORE_H
#define BOOKS_BOOK_STORE_H

#include "book.h"

    typedef void(*Iterator)(int, Book*);

    typedef struct BookStore {
        Book **books;
        int book_count;

        void(*add_book)(struct BookStore*, Book*);
        void(*show_books)(struct BookStore*, Iterator);
        Book*(*find_book)(struct BookStore*, char const *);
        void(*remove_book)(struct BookStore*, char const *);
    } BookStore;

    BookStore *BookStore_new();

    void add_book(BookStore *store, Book *book);
    void show_books(BookStore *store, Iterator iterator);
    Book * find_book(BookStore *store, char const *search_title);
    void remove_book(BookStore *store, char const *name);

    void purge_book(Book *book);
    void cascade_store(BookStore *store, int deleted_index);
    void BookStore_free(BookStore *store);

#endif //BOOKS_BOOK_STORE_H
