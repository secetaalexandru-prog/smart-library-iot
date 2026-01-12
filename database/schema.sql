-- Baza de date pentru sistemul Smart Library

CREATE TABLE books (
    book_id SERIAL PRIMARY KEY,
    title TEXT,
    author TEXT,
    status TEXT
);

CREATE TABLE events (
    event_id SERIAL PRIMARY KEY,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    tag_uid TEXT,
    event_type TEXT,
    device_id TEXT,
    zone_id TEXT
);

