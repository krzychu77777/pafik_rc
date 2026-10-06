#include <Arduino.h>
#include <unity.h>

#include "Event.cpp"


void test_example()
{
    CurrentState state;
    Event event(state);

    String input[5] = {"a","b","c","d","e"};
    event.testing_setter(input);

    String output[5];
    event.copy_buffer_to(output);

    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL_STRING(input[i].c_str(), output[i].c_str());
    }
}


void setup()
{
    delay(2000);

    UNITY_BEGIN();

    RUN_TEST(test_example);

    UNITY_END();
}

void loop()
{
}