#include <unity.h>

#include "Event.h"


void test_example()
{
    DefaultLogSink logSink;
    Logger logger(logSink);
    CurrentState state;
    Buffer buffer(logger);
    Event event(state, buffer, logger);

    Command cmd1;
    cmd1.source = Controller;
    cmd1.type = Movement;

    Command cmd2;
    cmd2.source = Keyboard;
    cmd2.type = Movement;

    buffer.push(cmd1);
    buffer.push(cmd2);

    TEST_ASSERT_EQUAL(buffer.commands[0].type,Movement);
    TEST_ASSERT_EQUAL(buffer.commands[1].type,Movement);
}


void setup()
{
    UNITY_BEGIN();

    RUN_TEST(test_example);

    UNITY_END();
}

void loop()
{
}