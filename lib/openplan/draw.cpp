#include <cairo.h>
#include <string>
#include <limits>
#include <algorithm>
#include <openplan/openplan.h>

namespace openplan
{

    bool draw_floor(const Building &b, int floor_index, const std::string &filename)
    {
        if (floor_index < 0 || floor_index >= (int)b.floors.size())
            return false;

        const int WIDTH = 1200;
        const int HEIGHT = 800;
        const int MARGIN = 50;

        cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
        cairo_t *cr = cairo_create(surface);

        // White background
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);

        const auto &floor = b.floors[floor_index];

        // Compute bounding box of walls
        float min_x = std::numeric_limits<float>::max();
        float max_x = std::numeric_limits<float>::lowest();
        float min_y = std::numeric_limits<float>::max();
        float max_y = std::numeric_limits<float>::lowest();

        for (const Wall &w : floor.walls)
        {
            min_x = std::min(min_x, std::min(w.start.x, w.end.x));
            max_x = std::max(max_x, std::max(w.start.x, w.end.x));
            min_y = std::min(min_y, std::min(w.start.y, w.end.y));
            max_y = std::max(max_y, std::max(w.start.y, w.end.y));
        }

        for (const Room &r : floor.rooms)
        {
            min_x = std::min(min_x, r.center.x - r.size.w / 2);
            max_x = std::max(max_x, r.center.x + r.size.w / 2);
            min_y = std::min(min_y, r.center.y - r.size.h / 2);
            max_y = std::max(max_y, r.center.y + r.size.h / 2);
        }

        for (const Opening &o : floor.openings)
        {
            min_x = std::min(min_x, o.position.x - o.size.w / 2);
            max_x = std::max(max_x, o.position.x + o.size.w / 2);
            min_y = std::min(min_y, o.position.y - o.size.h / 2);
            max_y = std::max(max_y, o.position.y + o.size.h / 2);
        }

        float plan_width = max_x - min_x;
        float plan_height = max_y - min_y;

        float scale_x = (WIDTH - 2.0f * MARGIN) / plan_width;
        float scale_y = (HEIGHT - 2.0f * MARGIN) / plan_height;
        float SCALE = std::min(scale_x, scale_y);

        // Move origin and flip y-axis to bottom-left origin
        cairo_translate(cr, MARGIN - min_x * SCALE, HEIGHT - MARGIN + min_y * SCALE);
        cairo_scale(cr, SCALE, -SCALE);

        // Draw walls
        cairo_set_line_width(cr, 25.0f / SCALE); // Convert to logical units
        cairo_set_source_rgb(cr, 0, 0, 0);
        for (const Wall &w : floor.walls)
        {
            cairo_move_to(cr, w.start.x, w.start.y);
            cairo_line_to(cr, w.end.x, w.end.y);
            cairo_stroke(cr);
        }

        // Draw rooms
        for (const Room &r : floor.rooms)
        {
            float x = r.center.x - r.size.w / 2;
            float y = r.center.y - r.size.h / 2;

            cairo_rectangle(cr, x, y, r.size.w, r.size.h);
            cairo_set_source_rgba(cr, 0.5, 0.8, 1.0, 0.3);
            cairo_fill_preserve(cr);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_stroke(cr);

            // Draw room label (flipped Y to fix upside-down text)
            Vec2 label = r.label_position.value_or(r.center);
            cairo_save(cr);
            cairo_scale(cr, 1, -1); // Flip Y for text
            cairo_set_font_size(cr, 24.0f / SCALE);
            cairo_move_to(cr, label.x - 30.0f / SCALE, -label.y + 10.0f / SCALE); // Adjust Y offset
            cairo_show_text(cr, r.name.c_str());
            cairo_restore(cr);
        }

        // Draw openings with margin
        for (const Opening &o : floor.openings)
        {
            float x = o.position.x - o.size.w / 2 + o.margin.left;
            float y = o.position.y - o.size.h / 2 + o.margin.top;
            float w = o.size.w - o.margin.left - o.margin.right;
            float h = o.size.h - o.margin.top - o.margin.bottom;

            if (o.type == "door")
                cairo_set_source_rgb(cr, 0.2, 0.7, 0.2);
            else if (o.type == "window")
                cairo_set_source_rgb(cr, 0.2, 0.2, 0.7);
            else
                cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);

            cairo_rectangle(cr, x, y, w, h);
            cairo_fill(cr);
        }

        cairo_surface_write_to_png(surface, filename.c_str());
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
        return true;
    }

} // namespace openplan