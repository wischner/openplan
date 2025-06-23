#pragma once

#include <string>
#include <vector>
#include <optional>

namespace openplan
{

    struct Vec2
    {
        float x, y;
    };
    struct Size
    {
        float w, h;
    };
    struct Margin
    {
        float top, bottom, left, right;
    };
    struct Wall
    {
        Vec2 start, end;
        float thickness;
    };
    struct Opening
    {
        std::string type;
        Vec2 position;
        Size size;
        Vec2 wall_normal;
        Margin margin;
    };
    struct Roof
    {
        Vec2 slope_direction;
        float start_height, end_height;
    };
    struct Room
    {
        std::string name, type;
        Vec2 center;
        Size size;
        float height;
        std::optional<Vec2> label_position;
        std::optional<Roof> roof;
    };
    struct Floor
    {
        std::string name;
        float elevation;
        std::vector<Wall> walls;
        std::vector<Room> rooms;
        std::vector<Opening> openings;
    };
    struct Building
    {
        std::string name;
        std::string unit;
        std::vector<Floor> floors;
    };

    // Public API function
    Building load_building(const std::string &path);

    bool draw_floor(const Building &building, int floor_index, const std::string &filename);

} // namespace openplan
