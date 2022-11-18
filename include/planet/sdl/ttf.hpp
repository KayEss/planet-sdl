#pragma once


#include <planet/asset_manager.hpp>
#include <planet/sdl/handle.hpp>
#include <planet/sdl/rw_ops.hpp>
#include <planet/sdl/surface.hpp>

#include <SDL_ttf.h>


namespace planet::sdl {


    class init;


    /// Create one of these for access to the TTF rendering parts of SDL2
    class ttf {
      public:
        ttf(init &);
        ~ttf();
    };


    class font {
        rw_ops_const_memory font_data;
        handle<TTF_Font, TTF_CloseFont> pf;
        SDL_Color colour;

      public:
        font(asset_manager const &,
             char const *filename,
             std::size_t pixel_height,
             SDL_Color,
             felspar::source_location const & =
                     felspar::source_location::current());

        TTF_Font *get() const noexcept { return pf.get(); }

        surface render(char const *text) const;
        surface render(char const *text, SDL_Color) const;
    };


}
