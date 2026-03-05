/*
* A tokenbucket is a rate limiting algorithm that limiting the rate of traffic
* to a particular device.
* It comprises of -
* max_capacity
* current_tokens
* a refill rate
*
* API reference:
* tokenbucket_init()
* tokenbucket_fill()
* tokenbucket_consume()
* tokenbucket_add()
* tokenbucket_check()
*
* We can use MICROTOKENS for better precision
*
* Tokens are refilled as - time_elapsed since last refill * rate
*
* Overall, we need to track last_refill_time and tokens
* Refill logic:
* 1. Calculate time elapsed since last refill
* 2. Calculate tokens to add = time_elapsed * refill_rate
* 3. Update tokens = min(tokens + tokens_to_add, max_capacity)
* 4. Update last_refill_time = current time
* Consumption logic:
* 1. Check if tokens >= tokens_to_consume
* 2. If yes, tokens -= tokens_to_consume and return true
* 3. If no, return false
* 
* Microtoken implementation:
* Caller always supplies tokens but we can use microtokens for better precision.
* For example, if we want to allow 1 token per second, we can use 1M microtokens per second.
*/

#define MICROTOKENS 1000000
#define TOKENS_TO_MICROTOKENS(tokens) ((tokens) * MICROTOKENS)

#include <stdint.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    uint64_t tokens;
    time_t last_refill_time;
} TOKENBUCKET;

void
tokenbucket_init(TOKENBUCKET *tb, time_t now, uint64_t initial_tokens) {
    if (!tb) return;
    tb->tokens = TOKENS_TO_MICROTOKENS(initial_tokens);
    tb->last_refill_time = now;
}

void
tokenbucket_fill(TOKENBUCKET *tb, time_t current_time, uint64_t refill_rate, uint64_t max_capacity) {
    if (!tb) return;

    if (tb->last_refill_time == 0) {
        // We start with all tokens available if last_refill_time is not set
        tokenbucket_init(tb, current_time, max_capacity);
        return;
    }

    if (current_time <= tb->last_refill_time) {
        return; // No time has passed, so no refill needed
    }

    time_t time_elapsed = current_time - tb->last_refill_time;
    uint64_t tokens_to_add = TOKENS_TO_MICROTOKENS(time_elapsed * refill_rate);
    tb->tokens = (tb->tokens + tokens_to_add > TOKENS_TO_MICROTOKENS(max_capacity)) ?
        TOKENS_TO_MICROTOKENS(max_capacity) :
        (tb->tokens + tokens_to_add);
    tb->last_refill_time = current_time;
}

bool
tokenbucket_consume(TOKENBUCKET *tb, uint64_t tokens_to_consume) {
    if (!tb) return false;
    if (tb->tokens >= TOKENS_TO_MICROTOKENS(tokens_to_consume)) {
        tb->tokens -= TOKENS_TO_MICROTOKENS(tokens_to_consume);
        return true;
    }
    return false;
}

bool
tokenbucket_check(TOKENBUCKET *tb, uint64_t tokens_to_check) {
    if (!tb) return false;
    return tb->tokens >= TOKENS_TO_MICROTOKENS(tokens_to_check);
}

bool
tokenbucket_add(TOKENBUCKET *tb, uint64_t tokens_to_add, uint64_t max_capacity) {
    if (!tb) return false;
    tb->tokens = (
        tb->tokens + TOKENS_TO_MICROTOKENS(tokens_to_add) > TOKENS_TO_MICROTOKENS(max_capacity)) ?
        TOKENS_TO_MICROTOKENS(max_capacity) :
        (tb->tokens + TOKENS_TO_MICROTOKENS(tokens_to_add)
    );
    return true;
}

// ------------------- TESTS -------------------
#include <stdio.h>
#include <assert.h>

void test_tokenbucket_init() {
    TOKENBUCKET tb;
    time_t now = time(NULL);
    tokenbucket_init(&tb, now, 5);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(5));
    assert(tb.last_refill_time == now);
    printf("test_tokenbucket_init passed\n");
}

void test_tokenbucket_fill() {
    TOKENBUCKET tb;
    time_t now = time(NULL);
    tokenbucket_init(&tb, now, 0);
    time_t start = tb.last_refill_time;
    // Simulate 2 seconds elapsed, refill rate 3 tokens/sec, max 10 tokens
    tokenbucket_fill(&tb, start + 2, 3, 10);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(6));
    // Fill again, should add 0 tokens if no time passed
    tokenbucket_fill(&tb, start + 2, 3, 10);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(6));
    // Fill to max capacity
    tokenbucket_fill(&tb, start + 10, 3, 10);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(10));
    printf("test_tokenbucket_fill passed\n");
}

void test_tokenbucket_consume() {
    TOKENBUCKET tb;
    time_t now = time(NULL);
    tokenbucket_init(&tb, now, 5);
    assert(tokenbucket_consume(&tb, 3) == true);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(2));
    assert(tokenbucket_consume(&tb, 3) == false);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(2));
    assert(tokenbucket_consume(&tb, 2) == true);
    assert(tb.tokens == 0);
    printf("test_tokenbucket_consume passed\n");
}

void test_tokenbucket_check() {
    TOKENBUCKET tb;
    time_t now = time(NULL);
    tokenbucket_init(&tb, now, 4);
    assert(tokenbucket_check(&tb, 3) == true);
    assert(tokenbucket_check(&tb, 4) == true);
    assert(tokenbucket_check(&tb, 5) == false);
    printf("test_tokenbucket_check passed\n");
}

void test_tokenbucket_add() {
    TOKENBUCKET tb;
    time_t now = time(NULL);
    tokenbucket_init(&tb, now, 2);
    assert(tokenbucket_add(&tb, 3, 5) == true);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(5));
    // Try to add more than max_capacity
    assert(tokenbucket_add(&tb, 10, 5) == true);
    assert(tb.tokens == TOKENS_TO_MICROTOKENS(5));
    printf("test_tokenbucket_add passed\n");
}

void test_edge_cases() {
    TOKENBUCKET tb;
    // Null pointer checks
    assert(tokenbucket_consume(NULL, 1) == false);
    assert(tokenbucket_check(NULL, 1) == false);
    assert(tokenbucket_add(NULL, 1, 1) == false);
    time_t now = time(NULL);
    tokenbucket_init(&tb, now, 0);
    assert(tb.tokens == 0);
    assert(tokenbucket_consume(&tb, 1) == false);
    assert(tokenbucket_check(&tb, 0) == true);
    printf("test_edge_cases passed\n");
}

int main() {
    test_tokenbucket_init();
    test_tokenbucket_fill();
    test_tokenbucket_consume();
    test_tokenbucket_check();
    test_tokenbucket_add();
    test_edge_cases();
    printf("All tests passed!\n");
    return 0;
}

