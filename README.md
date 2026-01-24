<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/6wj0hh6.jpg" alt="Project logo"></a>
</p>

<h3 align="center">University Library Management System (C++)</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![Language](https://img.shields.io/badge/language-C++-blue.svg)]()
[![OOP](https://img.shields.io/badge/design-OOP-important.svg)]()
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center">
A robust, console-based Library Management System built in C++ using Object-Oriented Programming, file handling, and modular architecture.
<br>
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Deployment](#deployment)
- [Usage](#usage)
- [Built Using](#built_using)
- [Contributing](../CONTRIBUTING.md)

## 🧐 About <a name = "about"></a>

The University Library Management System is a console-based C++ application designed to manage books, members, and borrowing transactions efficiently using Object-Oriented Programming principles.

The system supports secure authentication, polymorphic member handling (Students & Faculty), automated fine calculation, and file-based data persistence using CSV files.
It follows a modular manager architecture, making the system scalable, maintainable, and ideal for academic and real-world simulations.

## 🏁 Getting Started <a name = "getting_started"></a>

These instructions will help you run the project locally for development and testing.

### Prerequisites

You need the following installed on your system:

C++ Compiler (`GCC / MinGW`)

Make Utility (`mingw32-make`)

Windows OS (for `_getch()` password masking)

Check compiler installation: `g++ --version`

### Installing

Clone the repository:

```
git clone https://github.com/your-username/University-Library-Management-System.git
```

Navigate to the project directory:

```
cd University-Library-Management-System
```

Compile the project using Makefile:

```
mingw32-make
```

Run the application:

```
./main.exe
```

## 🎈 Usage <a name="usage"></a>

After launching the program:

## 🔐 Authentication

- Login or Register users
- System exits after 3 failed login attempts
- Passwords are masked during input
- 📚 Main Menu
- Book Management
- Member Management
- Issue Book
- Return Book
- View Member Issue History
- Exit

## 📚 Book Management

- Add, Update, Remove, View books
- Search by ID, ISBN, Title, Author
- Prevents duplicate ISBNs & IDs
- 👥 Member Management
- Add, Update, Remove, View members
- Supports Students & Faculty
- Different borrow limits and fine policies
- Displays Degree / Department using polymorphism

## 🔄 Issue & Return

- Enforces borrow limits
- Automatically calculates due dates & fines
- Updates book copies and member records

## 🚀 Deployment <a name = "deployment"></a>

This project is designed for local console execution.

To deploy:

Ensure all `.csv` files exist in the `/Data` directory

Run on Windows for full feature compatibility

Compile using provided Makefile

## ⛏️ Built Using <a name = "built_using"></a>

- C++ — Core programming language
- STL (Vectors, Strings, Algorithms) — Data handling
- File Handling (CSV) — Persistent storage
- OOP Concepts — Inheritance, Polymorphism, Encapsulation
- MinGW / GCC — Compilation
- Makefile — Build automation

## ✍️ Authors <a name = "authors"></a>

- Muhammad Abu Hurairah Nazar — Design, Implementation & Architecture

## 🎉 Acknowledgements <a name = "acknowledgement"></a>

- Inspired by real-world University Library Systems
-  Thanks to C++ STL documentation
- Academic guidance and OOP best practices
- Open-source documentation templates
