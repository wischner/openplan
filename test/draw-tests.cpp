#include <gtest/gtest.h>
#include <openplan/openplan.h>
#include <filesystem>
#include <fstream>

#ifndef TEST_DATA_DIR
#error "TEST_DATA_DIR is not defined"
#endif

TEST(OpenPlanDrawTest, CanRenderFloorToPNG)
{
    std::string input_path = std::string(TEST_DATA_DIR) + "/plan1.json";
    std::string output_path = std::string(TEST_DATA_DIR) + "/plan1.png";

    openplan::Building building = openplan::load_building(input_path);
    bool success = openplan::draw_floor(building, 0, output_path);

    ASSERT_TRUE(success);
    ASSERT_TRUE(std::filesystem::exists(output_path));
    ASSERT_GT(std::filesystem::file_size(output_path), 0);
}

TEST(OpenPlanDrawTest, CanRenderApartmentPlan)
{
    std::string input_path = std::string(TEST_DATA_DIR) + "/plan2.json";
    std::string output_path = std::string(TEST_DATA_DIR) + "/plan2.png";

    openplan::Building building = openplan::load_building(input_path);
    bool success = openplan::draw_floor(building, 0, output_path);

    ASSERT_TRUE(success);
    ASSERT_TRUE(std::filesystem::exists(output_path));
    ASSERT_GT(std::filesystem::file_size(output_path), 0);
}

TEST(OpenPlanDrawTest, CanRenderComplexApartmentPlan)
{
    std::string input_path = std::string(TEST_DATA_DIR) + "/plan3.json";
    std::string output_path = std::string(TEST_DATA_DIR) + "/plan3.png";

    openplan::Building building = openplan::load_building(input_path);
    bool success = openplan::draw_floor(building, 0, output_path);

    ASSERT_TRUE(success);
    ASSERT_TRUE(std::filesystem::exists(output_path));
    ASSERT_GT(std::filesystem::file_size(output_path), 0);
}

TEST(OpenPlanDrawTest, CanRenderRealisticApartmentPlan)
{
    std::string input_path = std::string(TEST_DATA_DIR) + "/plan4.json";
    std::string output_path = std::string(TEST_DATA_DIR) + "/plan4.png";

    openplan::Building building = openplan::load_building(input_path);
    bool success = openplan::draw_floor(building, 0, output_path);

    ASSERT_TRUE(success);
    ASSERT_TRUE(std::filesystem::exists(output_path));
    ASSERT_GT(std::filesystem::file_size(output_path), 0);
}