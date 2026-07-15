# syntax=docker/dockerfile:1

# --- Build stage: compile the sorting test harness ---
FROM gcc:14-bookworm AS builder

WORKDIR /src

COPY sorting_test.cpp ./
COPY bubble_sort.cpp bubble_sort.h ./
COPY selection_sort.cpp selection_sort.h ./
COPY insertion_sort.cpp insertion_sort.h ./
COPY merge_sort.cpp merge_sort.h ./
COPY cycle_sort.cpp cycle_sort.h ./
COPY heap_sort.cpp heap_sort.h ./

RUN g++ -std=c++17 -O2 -pipe \
    -static-libstdc++ -static-libgcc \
    sorting_test.cpp -o sorting_test

# --- Runtime stage: minimal image with only the binary ---
FROM debian:bookworm-slim AS runtime

WORKDIR /app

COPY --from=builder /src/sorting_test /app/sorting_test

RUN useradd --system --no-create-home appuser \
    && chown appuser:appuser /app/sorting_test

USER appuser

ENTRYPOINT ["/app/sorting_test"]
