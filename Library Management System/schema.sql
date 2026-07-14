-- Library Management System - Database Schema

CREATE DATABASE IF NOT EXISTS library_management;
USE library_management;

-- Users
CREATE TABLE IF NOT EXISTS users (
    user_id         INT PRIMARY KEY AUTO_INCREMENT,
    first_name      VARCHAR(50)  NOT NULL,
    last_name       VARCHAR(50)  NOT NULL,
    email           VARCHAR(100) NOT NULL UNIQUE,
    phone           VARCHAR(20),
    membership_type ENUM('student', 'faculty', 'staff', 'public') NOT NULL DEFAULT 'public',
    join_date       DATE         NOT NULL,
    address         VARCHAR(255),
    status          ENUM('active', 'inactive', 'suspended') NOT NULL DEFAULT 'active',
    created_at      TIMESTAMP    DEFAULT CURRENT_TIMESTAMP
);

-- Books
CREATE TABLE IF NOT EXISTS books (
    book_id          INT PRIMARY KEY AUTO_INCREMENT,
    title            VARCHAR(200) NOT NULL,
    author           VARCHAR(100) NOT NULL,
    isbn             VARCHAR(20)  NOT NULL UNIQUE,
    category         VARCHAR(50)  NOT NULL,
    publication_year YEAR         NOT NULL,
    total_copies     INT          NOT NULL DEFAULT 1,
    available_copies INT          NOT NULL DEFAULT 1,
    created_at       TIMESTAMP    DEFAULT CURRENT_TIMESTAMP,
    CHECK (total_copies >= 0),
    CHECK (available_copies >= 0),
    CHECK (available_copies <= total_copies)
);

-- Borrowed books (many-to-many relation between users and books)
CREATE TABLE IF NOT EXISTS borrowed_books (
    borrow_id   INT PRIMARY KEY AUTO_INCREMENT,
    user_id     INT  NOT NULL,
    book_id     INT  NOT NULL,
    borrow_date DATE NOT NULL,
    due_date    DATE NOT NULL,
    return_date DATE,
    status      ENUM('borrowed', 'returned', 'overdue') NOT NULL DEFAULT 'borrowed',
    created_at  TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (book_id) REFERENCES books(book_id) ON DELETE CASCADE
);
