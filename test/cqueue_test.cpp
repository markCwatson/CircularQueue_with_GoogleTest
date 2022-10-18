#include <gtest/gtest.h>

extern "C" {
    #include "../cqueue.h"
}

class cqueue_test : public ::testing::Test {
protected:
    int test_data[6] = {1, 2, 3, 4, 5, 6};
    int peek;
    int dequeue;
    cqueue_s myCqueue;

    cqueue_test(/* args */) {}
    ~cqueue_test() {}

    void SetUp() override {
        for(int i = 0; i < 5; i++)
            test_data[i] = i + 1;

        cqueue_init(&myCqueue, 5, sizeof(int), NULL);
    }

    void TearDown() override {
        cqueue_close(&myCqueue);
    }
};


TEST_F(cqueue_test, insert_one_element_and_check_size) {
    cqueue_enque(&myCqueue, &test_data[0]);
    EXPECT_EQ(1, cqueue_get_size(&myCqueue));
}

TEST_F(cqueue_test, reset) {
    cqueue_enque(&myCqueue, &test_data[0]);
    cqueue_reset(&myCqueue);
    EXPECT_EQ(0, cqueue_get_size(&myCqueue));
    EXPECT_EQ(1, cqueue_is_empty(&myCqueue));
}

TEST_F(cqueue_test, insert_one_element_and_peek) {
    cqueue_enque(&myCqueue, &test_data[0]);
    cqueue_peek(&myCqueue, &peek);
    EXPECT_EQ(peek, test_data[0]);
}

TEST_F(cqueue_test, insert_two_elements_and_peek) {
    cqueue_enque(&myCqueue, &test_data[0]);
    cqueue_enque(&myCqueue, &test_data[1]);
    cqueue_peek(&myCqueue, &peek);
    EXPECT_EQ(peek, test_data[0]);
}

TEST_F(cqueue_test, insert_two_elements_and_check_size) {
    cqueue_enque(&myCqueue, &test_data[0]);
    cqueue_enque(&myCqueue, &test_data[1]);
    cqueue_peek(&myCqueue, &peek);
    EXPECT_EQ(2, cqueue_get_size(&myCqueue));
}

TEST_F(cqueue_test, overfill_and_check_size) {
    for (int i = 0; i < 6; i++)
        cqueue_enque(&myCqueue, &test_data[i]);

    EXPECT_EQ(5, cqueue_get_size(&myCqueue));
}

TEST_F(cqueue_test, overfill_and_peek) {
    for (int i = 0; i < 6; i++)
        cqueue_enque(&myCqueue, &test_data[i]);

    cqueue_peek(&myCqueue, &peek);
    EXPECT_EQ(peek, test_data[1]);
}

TEST_F(cqueue_test, overfill_and_dequeue) {
    for (int i = 0; i < 6; i++)
        cqueue_enque(&myCqueue, &test_data[i]);

    for (int i = 1; i < 5; i++) {
        cqueue_deque(&myCqueue, &dequeue);
        EXPECT_EQ(dequeue, test_data[i]);
        EXPECT_EQ(0, cqueue_is_empty(&myCqueue));
    }

    cqueue_deque(&myCqueue, &dequeue);
    EXPECT_EQ(dequeue, test_data[5]);
    EXPECT_EQ(1, cqueue_is_empty(&myCqueue));
}

TEST_F(cqueue_test, insert_after_fill_then_empty) {
    for (int i = 0; i < 5; i++)
        cqueue_enque(&myCqueue, &test_data[i]);

    for (int i = 0; i < 5; i++)
        cqueue_deque(&myCqueue, &dequeue);

    cqueue_enque(&myCqueue, &test_data[0]);
    cqueue_peek(&myCqueue, &peek);
    EXPECT_EQ(peek, test_data[0]);
    EXPECT_EQ(1, cqueue_get_size(&myCqueue));
    EXPECT_EQ(0, cqueue_is_empty(&myCqueue));
    cqueue_deque(&myCqueue, &dequeue);
    EXPECT_EQ(dequeue, test_data[0]);
    EXPECT_EQ(0, cqueue_get_size(&myCqueue));
    EXPECT_EQ(1, cqueue_is_empty(&myCqueue));
}

TEST_F(cqueue_test, overfill_many_times) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++)
            cqueue_enque(&myCqueue, &test_data[j]);

        cqueue_peek(&myCqueue, &peek);
        EXPECT_EQ(peek, test_data[0]);
        EXPECT_EQ(0, cqueue_is_empty(&myCqueue));
        EXPECT_EQ(5, cqueue_get_size(&myCqueue));
    }
}