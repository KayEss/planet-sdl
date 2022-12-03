#pragma once


#include <planet/affine2d.hpp>


namespace planet::sdl::ui {


    /// A grid of equally sized blocks which can break onto multiple lines
    template<typename C>
    struct grid {
        using collection_type = C;
        using box_type = typename collection_type::value_type;
        collection_type items;
        /// Padding between items in the row
        float vpadding = {}, hpadding = {};

        grid(collection_type c, float const p)
        : items{std::move(c)}, vpadding{p}, hpadding{p} {}

        affine::extents2d extents(affine::extents2d const outer) const {
            auto const cell = cell_size(outer);
            auto const w = std::floor(
                    (outer.width + hpadding) / (cell.width + hpadding));
            auto const h = std::floor(items.size() / w);
            return {w * cell.width + (w - 1) * hpadding,
                    h * cell.height + (h - 1) * vpadding};
        }

        template<typename Target>
        void draw_within(Target &t, affine::rectangle const within) {
            auto const cell = cell_size(within.extents);
            float x = {}, y = {};
            for (auto &item : items) {
                if (x > 0 and x + cell.width > within.extents.width) {
                    x = 0;
                    if (y) { y += vpadding; }
                    y += cell.height;
                }
                item.draw_within(
                        t, {affine::point2d{x, y} + within.top_left, cell});
                if (x) { x += hpadding; }
                x += cell.width;
            }
        }

      private:
        affine::extents2d cell_size(affine::extents2d const outer) const {
            float max_width = {}, max_height = {};
            for (auto const &i : items) {
                auto const ex = i.extents(outer);
                max_width = std::max(ex.width, max_width);
                max_height = std::max(ex.height, max_height);
            }
            return {max_width, max_height};
        }
    };


}
