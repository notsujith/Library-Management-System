# Library Management System

This project is a console-based **Library Management System** written in C++. The system allows users to manage books and users, providing features to add, borrow, return, and remove books as well as manage library users. This system leverages basic file I/O to store and retrieve library data from text files, ensuring data persistence across program executions.

## Features

- **Add Book**: Allows a new book to be added to the library.
- **Borrow Book**: Enables a registered user to borrow a book if it is available.
- **Return Book**: Allows a user to return a previously borrowed book.
- **Add User**: Registers a new user in the library system.
- **Remove Book**: Deletes a book from the library inventory.
- **Remove User**: Removes a user from the library system.
- **Persistent Data Storage**: Utilizes text files (`books.txt` and `users.txt`) to store book and user data, preserving information between sessions.

## File Structure

- **`Book` Class**: Manages individual book details, including book name and borrowing status.
- **`User` Class**: Handles user details and the list of books borrowed by the user.
- **`Library` Class**: Oversees the entire library system, maintaining collections of books and users and providing functionalities for managing both.

## Usage

### Prerequisites

To run this program, you need:
- A C++ compiler (e.g., GCC)
- Basic understanding of C++ and file I/O operations

### Installation and Running the Program

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/library-management-system.git
    ```

2. Navigate to the project directory:

    ```bash
    cd library-management-system
    ```

3. Compile the program:

    ```bash
    g++ library_management_system.cpp -o library_management_system
    ```

4. Run the program:

    ```bash
    ./library_management_system
    ```

### How to Use

After running, you will see a menu with various options:

1. **Add Book**: Adds a new book to the library.
2. **Borrow Book**: Allows a user to borrow a book using their User ID and the Book ID.
3. **Return Book**: Enables a user to return a borrowed book.
4. **Add User**: Registers a new user in the library.
5. **Remove Book**: Removes a specified book from the library.
6. **Remove User**: Deletes a user from the library database.
7. **Exit**: Exits the program.

Enter the corresponding number for the desired action and follow the prompts.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some YourFeature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a Pull Request.

## License

Distributed under the MIT License. See `LICENSE` for more information.
