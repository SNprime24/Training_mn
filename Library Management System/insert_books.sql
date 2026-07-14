-- Library Management System - Sample Book Records

USE library_management;

INSERT INTO books (title, author, isbn, category, publication_year, total_copies, available_copies) VALUES
('To Kill a Mockingbird',       'Harper Lee',           '978-0-06-112008-4', 'Fiction',       1960, 3, 2),
('1984',                        'George Orwell',        '978-0-452-28423-4', 'Fiction',       1949, 2, 1),
('The Great Gatsby',            'F. Scott Fitzgerald',  '978-0-7432-7356-5', 'Fiction',       1925, 2, 2),
('Introduction to Algorithms',  'Cormen et al.',        '978-0-262-03384-8', 'Computer Science', 2009, 4, 3),
('Clean Code',                  'Robert C. Martin',     '978-0-13-235088-4', 'Computer Science', 2008, 2, 1),
('A Brief History of Time',     'Stephen Hawking',      '978-0-553-10953-5', 'Science',       1988, 1, 1),
('The Hobbit',                  'J.R.R. Tolkien',       '978-0-547-92822-7', 'Fantasy',       1937, 3, 2),
('Pride and Prejudice',         'Jane Austen',          '978-0-14-143951-8', 'Classic',       1813, 2, 2);
