#include <gtest/gtest.h>
#include <filesystem>

#include <openplan/openplan.h>

namespace fs = std::filesystem;

using namespace openplan;

// Helper to get the full path to test data file
std::string test_data_path(const std::string &filename)
{
    return (fs::path(TEST_DATA_DIR) / filename).string();
}

TEST(OpenPlanParserTest, CanLoadBuilding)
{
    auto building = load_building(test_data_path("plan1.json"));

    EXPECT_EQ(building.name, "Test Residence");
    EXPECT_EQ(building.unit, "cm");
    ASSERT_EQ(building.floors.size(), 2);
}

TEST(OpenPlanParserTest, GroundFloorHasExpectedWallsRoomsOpenings)
{
    auto building = load_building(test_data_path("plan1.json"));
    const auto &floor = building.floors[0];

    EXPECT_EQ(floor.name, "Ground Floor");
    EXPECT_EQ(floor.elevation, 0);
    EXPECT_EQ(floor.walls.size(), 4);
    EXPECT_EQ(floor.rooms.size(), 2);
    EXPECT_EQ(floor.openings.size(), 2);

    EXPECT_EQ(floor.rooms[0].name, "Living Room");
    EXPECT_EQ(floor.rooms[1].name, "Hall");
}

TEST(OpenPlanParserTest, AtticRoomHasSlopedRoof)
{
    auto building = load_building(test_data_path("plan1.json"));
    const auto &attic = building.floors[1];

    EXPECT_EQ(attic.name, "Attic");
    ASSERT_EQ(attic.rooms.size(), 1);
    const auto &bedroom = attic.rooms[0];
    ASSERT_TRUE(bedroom.roof.has_value());

    auto roof = bedroom.roof.value();
    EXPECT_FLOAT_EQ(roof.start_height, 120);
    EXPECT_FLOAT_EQ(roof.end_height, 200);
    EXPECT_FLOAT_EQ(roof.slope_direction.x, 1);
    EXPECT_FLOAT_EQ(roof.slope_direction.y, 0);
}
