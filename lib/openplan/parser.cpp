#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

#include <openplan/openplan.h>

using json = nlohmann::json;

namespace openplan
{ // <<---- ADD THIS

  Building load_building(const std::string &path)
  {
    std::ifstream file(path);
    json data;
    file >> data;

    Building b;
    auto jbuilding = data["building"];
    b.name = jbuilding["name"];
    b.unit = jbuilding["unit"];

    for (const auto &jfloor : jbuilding["floors"])
    {
      Floor f;
      f.name = jfloor["name"];
      f.elevation = jfloor["elevation"];

      for (const auto &jwall : jfloor.value("walls", json::array()))
      {
        Wall w;
        w.start = {jwall["start"]["x"], jwall["start"]["y"]};
        w.end = {jwall["end"]["x"], jwall["end"]["y"]};
        w.thickness = jwall["thickness"];
        f.walls.push_back(w);
      }

      for (const auto &jroom : jfloor["rooms"])
      {
        Room r;
        r.name = jroom["name"];
        r.type = jroom["type"];
        r.center = {jroom["center"]["x"], jroom["center"]["y"]};
        r.size = {jroom["size"]["w"], jroom["size"]["h"]};
        r.height = jroom["height"];
        if (jroom.contains("label_position"))
          r.label_position = Vec2{jroom["label_position"]["x"], jroom["label_position"]["y"]};
        if (jroom.contains("roof"))
        {
          Roof ro;
          ro.slope_direction = {jroom["roof"]["slope_direction"]["x"], jroom["roof"]["slope_direction"]["y"]};
          ro.start_height = jroom["roof"]["start_height"];
          ro.end_height = jroom["roof"]["end_height"];
          r.roof = ro;
        }
        f.rooms.push_back(r);
      }

      for (const auto &jop : jfloor.value("openings", json::array()))
      {
        Opening o;
        o.type = jop["type"];
        o.position = {jop["position"]["x"], jop["position"]["y"]};
        o.size = {jop["size"]["w"], jop["size"]["h"]};
        o.wall_normal = {jop["wall_normal"]["x"], jop["wall_normal"]["y"]};
        o.margin = {jop["margin"]["top"], jop["margin"]["bottom"], jop["margin"]["left"], jop["margin"]["right"]};
        f.openings.push_back(o);
      }

      b.floors.push_back(f);
    }
    return b;
  }

} // <<---- CLOSE NAMESPACE
