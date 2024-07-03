#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

class Book {
public:
    string title;
    string author;
    int total_copies;
    string isbn;
    int available_copies;

    Book() {}

    Book(string title, string author, string isbn, int available_copies, int total_copies) {
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->available_copies = available_copies;
        this->total_copies = total_copies;
    }

    void display_info() {
        cout << "BOOK TITLE IS: " << title << " BOOK AUTHOR IS: " << author
             << " INTERNATIONAL STANDARD BOOK NUMBER: " << isbn
             << " AVAILABLE COPIES: " << available_copies << " TOTAL COPIES: " << total_copies << endl;
    }
};




class Patron {
    string pname;
    vector<string> books_issued; // Store ISBNs of issued books

public:
    string patron_id;

    Patron() {}

    Patron(string pname, string patron_id) {
        this->pname = pname;
        this->patron_id = patron_id;
    }

    int find_book_index(string isbn) {
        for (int i = 0; i < books_issued.size(); i++) {
            if (books_issued[i] == isbn) {
                return i;
            }
        }
        return -1; // Return -1 if the book is not found
    }

    void checkout_book(Book &b) {
        if (b.available_copies >= 1) {
            books_issued.push_back(b.isbn);
            b.available_copies--;
            cout << b.isbn << " BOOK CHECKED OUT SUCCESSFULLY" << endl;
        } else {
            cout << "No available copies for book: " << b.isbn <<endl<<" Cant check out this book!"<< endl;
        }
    }

    void return_book(Book &b) {
        int index = find_book_index(b.isbn);
        if (index != -1) {
            books_issued.erase(books_issued.begin() + index);
            b.available_copies++;
            cout << b.isbn << " BOOK RETURNED SUCCESSFULLY" << endl;
        } else {
            cout << "Book not found in the list of issued books." << endl;
        }
    }

    void display_pinfo() {
        cout << "Patron name: " << pname << " Patron ID: " << patron_id << endl;
        cout << "Books issued:" << endl;
        for (int i = 0; i < books_issued.size(); i++) {
            cout << books_issued[i] << endl;
        }
    }
};





class Library :public Patron{
    vector<Book> books_collection;
    vector<Patron> registered_patrons;

public:
    Library() {
        cout << "CREATED A LIBRARY" << endl;
    }

    int find_book_index(string isbn) {
        for (int i = 0; i < books_collection.size(); i++) {
            if (books_collection[i].isbn == isbn) {
                return i;
            }
        }
        return -1; // Return -1 if the book is not found
    }

    void add_book(Book b) {
        books_collection.push_back(b);
        cout << "BOOK " << b.isbn << " ADDED SUCCESSFULLY" << endl;
    }

    void remove_book(string isbn) {
        int index = find_book_index(isbn);
        if (index != -1) {
            books_collection.erase(books_collection.begin() + index);
            cout << "BOOK " << isbn << " REMOVED SUCCESSFULLY" << endl;
        } else {
            cout << "Book not found in the library collection." << endl;
        }
    }

    void add_patron(Patron &p) {
        registered_patrons.push_back(p);
        cout << "PATRON " << p.patron_id << " REGISTERED SUCCESSFULLY" << endl;
    }

    void remove_patron(string patron_id) {
        for (int i = 0; i < registered_patrons.size(); i++) {
            if (registered_patrons[i].patron_id == patron_id) {
                registered_patrons.erase(registered_patrons.begin() + i);
                cout << "PATRON " << patron_id << " REMOVED SUCCESSFULLY" << endl;
                return;
            }
        }
        cout << "Patron not found in the list of registered patrons." << endl;
    }

    void display_books() {
        cout << "Available books in the library:" << endl;
        for (int i = 0; i < books_collection.size(); i++) {
            books_collection[i].display_info();
            cout << endl;
        }
    }

    void display_patrons() {
        cout << "Registered patrons in the library:" << endl;
        for (int i = 0; i < registered_patrons.size(); i++) {
            registered_patrons[i].display_pinfo();
            cout << endl;
        }
    }

    void checkout_book(string patron_id, string isbn) {
        int patron_index = find_patron_index(patron_id);
        int book_index = find_book_index(isbn);

        if (patron_index != -1 && book_index != -1) {
            registered_patrons[patron_index].checkout_book(books_collection[book_index]);
        } else {
            if (patron_index == -1) cout << "Patron not found." << endl;
            if (book_index == -1) cout << "Book not found." << endl;
        }
    }

    void return_book(string patron_id, string isbn) {
        int patron_index = find_patron_index(patron_id);
        int book_index = find_book_index(isbn);

        if (patron_index != -1 && book_index != -1) {
            registered_patrons[patron_index].return_book(books_collection[book_index]);
        } else {
            if (patron_index == -1) cout << "Patron not found." << endl;
            if (book_index == -1) cout << "Book not found." << endl;
        }
    }

private:
    int find_patron_index(string patron_id) {
        for (int i = 0; i < registered_patrons.size(); i++) {
            if (registered_patrons[i].patron_id == patron_id) {
                return i;
            }
        }
        return -1; // Return -1 if the patron is not found
    }
};

int main() {
    Library iitjammu;
    Book b1("THERMODYNAMICS", "K RUTLEY", "A", 2, 2);
    Book b2("SOLID MECHANICS", "RC HIBBELER", "B", 2, 2);
    Patron P1("sumit", "rtw34");
    Patron P2("shreya", "twe2");
    Patron P3("jack","aa");

    iitjammu.add_book(b1);
    iitjammu.add_book(b2);
    iitjammu.display_books();

    iitjammu.add_patron(P1);
    iitjammu.add_patron(P2);
    iitjammu.display_patrons();

    iitjammu.checkout_book("rtw34", "A");
    iitjammu.display_books();
    iitjammu.display_patrons();

    iitjammu.return_book("rtw34", "A");
    iitjammu.display_books();
    iitjammu.display_patrons();

iitjammu.remove_patron("rtw34");

iitjammu.display_patrons();
 iitjammu.checkout_book("twe2", "A");
 iitjammu.display_books();
    iitjammu.add_patron(P1);
     iitjammu.checkout_book("rtw34", "A");
      iitjammu.display_books();
iitjammu.display_patrons();

iitjammu.add_patron(P3);
  iitjammu.checkout_book("aa", "B");
iitjammu.display_patrons();
 iitjammu.checkout_book("aa", "B");
 iitjammu.display_patrons();
    iitjammu.display_books();
    return 0;
}
