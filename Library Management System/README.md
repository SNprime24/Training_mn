# Library Management System ( DAY - 10 )

A simple SQL database for managing library users, books, and borrow records.

## Database structure

| Table           | Purpose                                              |
|-----------------|------------------------------------------------------|
| `users`         | Library members (students, faculty, staff, public)   |
| `books`         | Catalog of available titles                          |
| `borrowed_books`| Tracks who borrowed which book and when              |

## Setup

Run the scripts in this order (MySQL / MariaDB):

```bash
mysql -u root -p < schema.sql
mysql -u root -p < insert_users.sql
mysql -u root -p < insert_books.sql
mysql -u root -p < insert_borrowed_books.sql
```

Or from a MySQL client:

```sql
SOURCE schema.sql;
SOURCE insert_users.sql;
SOURCE insert_books.sql;
SOURCE insert_borrowed_books.sql;
```

## Sample queries

```sql
USE library_management;

-- Active borrowers and their books
SELECT u.first_name, u.last_name, b.title, bb.borrow_date, bb.due_date, bb.status
FROM borrowed_books bb
JOIN users u ON bb.user_id = u.user_id
JOIN books b ON bb.book_id = b.book_id
WHERE bb.status = 'borrowed';

-- Books currently available
SELECT title, author, available_copies
FROM books
WHERE available_copies > 0;
```
