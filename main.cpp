#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Book{
private:
    string bookName;
    bool isBorrowed=false;
public:
    Book(string bookName=""){
        this -> bookName = bookName;
    }
    
    void setName(string bookName){this -> bookName = bookName;}
    string getName(){return bookName;}
    bool getIsborrowed(){return isBorrowed;}
    void setIsBorrowed(bool isBorrowed){this -> isBorrowed = isBorrowed;}
    
    void Status(){
        if(isBorrowed){
            cout << "Book is borrowed" << endl;
        }else{
            cout << "Book is available" << endl;
        }
    }
    
    void displayBook(){
        cout << "Book Name: " << bookName << endl;
        Status();
    }
    
    void borrowBook(){
        if(isBorrowed){
            cout << "Book is already borrowed" << endl;
        }else{
            isBorrowed = true;
            cout << "Book is borrowed. Return within 7 days." << endl;
        }
    }
    
    void returnBook(){
        if(isBorrowed){
            isBorrowed = false;
            cout << "Book is returned. Thank you!" << endl;
        }else{
            cout << "Book is not borrowed" << endl;
        }
    }
    
    friend ifstream &operator>>(ifstream &input, Book &book);
    friend ofstream &operator<<(ofstream &output, Book &book);
};

ifstream &operator>>(ifstream &input, Book &book){
    getline(input, book.bookName);
    input >> book.isBorrowed;
    input.ignore();
    return input;
}

ofstream &operator<<(ofstream &output, Book &book){
    output << book.bookName << endl;
    output << book.isBorrowed << endl;
    return output;
}

class User{
private:
    string userName;
    vector <Book> borrowedBooks;
public:
    User(string name=""){
        userName = name;
    }
    void setUserName(string userName){this -> userName = userName;}
    string getUserName(){return userName;}
    vector <Book> getBorrowedBooks(){return borrowedBooks;}
    
    void borrowBook(Book &book){
        if (!book.getIsborrowed()){
            book.borrowBook();
            borrowedBooks.push_back(book);
        }else{
            book.Status();
        }
    }
    
    void returnBook(Book &book){
        book.returnBook();
        for (int i = 0; i < borrowedBooks.size(); i++){
            if (borrowedBooks[i].getName() == book.getName()){
                borrowedBooks.erase(borrowedBooks.begin() + i);
                break;
            }
        }
    }
    
    void displayDetails(){
        cout << "User Name: " << userName << endl;
        if (borrowedBooks.empty()){
            cout << "No borrowed books" << endl;
        }
        else {
            cout << "Borrowed Books: " << endl;
            for (auto &book:borrowedBooks){
                book.displayBook();
            }
        }
    }
    friend ifstream &operator>>(ifstream &input, User &user);
    friend ofstream &operator<<(ofstream &output, User &user);
};

ifstream &operator>>(ifstream &input, User &user){
    getline(input, user.userName);
    int size;
    input >> size;
    input.ignore();
    for (int i = 0; i < size; i++){
        Book book;
        input >> book;
        user.borrowedBooks.push_back(book);
    }
    return input;
}

ofstream &operator<<(ofstream &output, User &user){
    output << user.userName << endl;
    output << user.borrowedBooks.size() << endl;
    for (auto &book:user.borrowedBooks){
        output << book;
    }
    return output;
}


class Library {
private:
    int bookIndex;
    int userIndex;
    map<int, Book> books;
    map<int, User> users;

    void loadBooks() {
        ifstream bookFile("books.txt");
        if (bookFile.is_open()) {
            books.clear();
            Book book("");
            while (bookFile >> book) {
                books[bookIndex++] = book;
            }
            bookFile.close();
        }
    }

    void loadUsers() {
        ifstream userFile("users.txt");
        if (userFile.is_open()) {
            users.clear();
            User user("");
            while (userFile >> user) {
                users[userIndex++] = user;
            }
            userFile.close();
        }
    }

    void saveBooks() {
        ofstream bookFile("books.txt");
        if (bookFile.is_open()) {
            for (auto &book : books) {
                bookFile << book.second;
            }
            bookFile.close();
        }
    }

    void saveUsers() {
        ofstream userFile("users.txt");
        if (userFile.is_open()) {
            for (auto &user : users) {
                userFile << user.second;
            }
            userFile.close();
        }
    }

public:
    Library() : bookIndex(1), userIndex(1) {
        loadBooks();
        loadUsers();
    }

    void addBook(Book &book) {
        books[bookIndex++] = book;
        saveBooks();
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "\n| The library is currently empty |" << endl;
        } else {
            for (auto &book : books) {
                cout << endl;
                cout << "Book ID: " << book.first << endl;
                book.second.displayBook();
            }
        }
    }

    void borrowBook(int userID, int bookID) {
        if (books.find(bookID) == books.end()) {
            cout << "Book ID is invalid" << endl;
        } else if (users.find(userID) == users.end()) {
            cout << "User ID is invalid" << endl;
        } else {
            Book &book = books[bookID];
            User &user = users[userID];
            user.borrowBook(book);
            saveBooks();
            saveUsers();
            
        }
    }

    void returnBook(int userID, int bookID) {
        if (users.find(userID) == users.end()) {
            cout << "User ID is invalid" << endl;
        } else {
            User &user = users[userID];
            for (auto &b : user.getBorrowedBooks()) {
                if (b.getName() == books[bookID].getName()) {
                    user.returnBook(books[bookID]);
                    saveBooks();
                    saveUsers();
                    return;
                }
            }
            cout << "Book was not borrowed by this user" << endl;
        }
    }

    void removeBook(int bookID) {
        if (books.find(bookID) == books.end()) {
            cout << "Book ID is invalid" << endl;
        } else {
            books.erase(bookID);
            saveBooks();
        }
    }

    void addUser(User &user) {
        users[userIndex++] = user;
        saveUsers();
        user.displayDetails();
    }

    void viewUsers() {
        if (users.empty()) {
            cout << "\n| No users in the library |" << endl;
        } else {
            for (auto &user : users) {
                cout << endl;
                cout << "User ID: " << user.first << endl;
                user.second.displayDetails();
            }
        }
    }

    void removeUser(int userID) {
        if (users.find(userID) == users.end()) {
            cout << "User ID is invalid" << endl;
        } else {
            users.erase(userID);
            saveUsers();
        }
    }

    ~Library() {
        saveBooks();
        saveUsers();
    }
};
int main()
{
    Library lb;
    Book book;
    User user;
    int choice, userID, bookID;;
    string bookName, userName;
    
    do{
        system("clear");
        cout << "Library Management System\n" << endl;
        lb.viewBooks();
        cout << endl;
        lb.viewUsers();
        cout << endl;
        cout << "1. Add Book\n2. Borrow Book\n3. Return Book\n4. Add User\n5. Remove Book\n6. Remove User\n7. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter book name: ";
                cin.ignore();
                getline(cin, bookName);
                cout << endl;
                book.setName(bookName);
                lb.addBook(book);
                cout << "Book added to the library" << endl;
                break;
            case 2:
                cout << "Enter User ID: ";
                cin >> userID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                cout << endl;
                lb.borrowBook(userID, bookID);
                break;
            case 3:
                cout << "Enter User ID: ";
                cin >> userID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                cout << endl;
                lb.returnBook(userID, bookID);
                cout << "Book returned" << endl;
                break;
            case 4:
                cout << "Enter user name: ";
                cin.ignore();
                getline(cin, userName);
                cout << endl;
                user.setUserName(userName);
                lb.addUser(user);
                cout << "User added to the database" << endl;
                break;
            case 5:
                cout << "Enter Book ID: ";
                cin >> bookID;
                cout << endl;
                lb.removeBook(bookID);
                cout << "Book removed from the library" << endl;
                break;
            case 6:
                cout << "Enter User ID: ";
                cin >> userID;
                cout << endl;
                lb.removeUser(userID);
                cout << "User removed from the database" << endl;
                break;
            case 7:
                cout << "Exiting the application..." << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }while(choice != 7);
    return 0;
}
