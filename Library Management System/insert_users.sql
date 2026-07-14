-- Library Management System - Sample User Records (5 documents)

USE library_management;

INSERT INTO users (first_name, last_name, email, phone, membership_type, join_date, address, status) VALUES
('Alice',   'Johnson',  'alice.johnson@email.com',   '555-0101', 'student', '2024-09-01', '12 Oak Street, Springfield',   'active'),
('Robert',  'Chen',     'robert.chen@email.com',     '555-0102', 'faculty', '2022-01-15', '45 Maple Avenue, Springfield', 'active'),
('Maria',   'Garcia',   'maria.garcia@email.com',    '555-0103', 'staff',   '2020-06-20', '78 Pine Road, Springfield',    'active'),
('James',   'Williams', 'james.williams@email.com',  '555-0104', 'public',  '2025-03-10', '23 Elm Lane, Springfield',     'active'),
('Priya',   'Patel',    'priya.patel@email.com',     '555-0105', 'student', '2024-09-01', '56 Birch Court, Springfield',  'inactive');
