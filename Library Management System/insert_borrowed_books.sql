-- Library Management System - Sample Borrowed Book Records
-- Assumes users (IDs 1-5) and books (IDs 1-8) were inserted in order.

USE library_management;

INSERT INTO borrowed_books (user_id, book_id, borrow_date, due_date, return_date, status) VALUES
(1, 1, '2026-06-01', '2026-06-15', NULL,         'borrowed'),
(2, 4, '2026-05-10', '2026-05-24', '2026-05-20', 'returned'),
(3, 5, '2026-06-05', '2026-06-19', NULL,         'borrowed'),
(1, 7, '2026-04-01', '2026-04-15', '2026-04-12', 'returned'),
(4, 2, '2026-06-10', '2026-06-24', NULL,         'borrowed'),
(2, 1, '2026-03-01', '2026-03-15', '2026-03-14', 'returned'),
(5, 3, '2026-01-05', '2026-01-19', NULL,         'overdue');
