#include "book_store.h"
#include "book.h"

#include <stdlib.h>
#include <string.h>

    BookStore *BookStore_new(){
        BookStore *instance = malloc(sizeof(BookStore));
        *instance = (BookStore){
                .add_book=add_book,.find_book=find_book,.show_books=show_books,.remove_book=remove_book,
                .book_count=0,.books=NULL
        };
        return instance;
    }

    void add_book(BookStore *store, Book *book){
        if(store->book_count == 0){
            store->books = malloc(sizeof(Book*));
        }else{
            store->books = realloc(store->books, sizeof(Book*) * (store->book_count + 1));
        }

        store->books[store->book_count] = book;
        store->book_count++;
    }

    void show_books(BookStore *store, Iterator iterator){
        for(int i =0; i<store->book_count; i++){
            iterator(i, store->books[i]);
        }
    }

    Book* find_book(BookStore *store, const char *search_title){
        for(int i = 0; i<store->book_count; i++){
            if(strcmp(store->books[i]->title, search_title) == 0){
                return store->books[i];
            }
        }
        return NULL;
    }

    void remove_book(BookStore *store, const char *title){
        for(int i = 0; i<store->book_count; i++){
            if(strcmp(store->books[i]->title, title) == 0){
                Book *temp = store->books[i];
                cascade_store(store, i);
                purge_book(temp);
            }
        }
    }

    void purge_book(Book *book){
        free(book->title);
        free(book->author);
        free(book);
    }

    void cascade_store(BookStore *store, int deleted_index){
        store->book_count--;

        if(store->book_count == deleted_index)
            return;

        for(int i = deleted_index; i < store->book_count; i++){
            store->books[i] = store->books[i+1];
        }
    }

    void BookStore_free(BookStore *store){
        for(int i = 0; i<store->book_count; i++){
            purge_book(store->books[i]);
        }
        free(store);
    }