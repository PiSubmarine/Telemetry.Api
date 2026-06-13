#include <gtest/gtest.h>

#include "PiSubmarine/Telemetry/Api/ChannelId.h"

namespace PiSubmarine::Telemetry::Api
{
    TEST(ChannelIdTest, EqualityComparesWrappedStringValue)
    {
        const ChannelId left{.Value = "motor.front-left"};
        const ChannelId same{.Value = "motor.front-left"};
        const ChannelId different{.Value = "motor.front-right"};

        EXPECT_EQ(left, same);
        EXPECT_NE(left, different);
    }
}
