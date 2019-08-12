#pragma once

#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"
#include "renderable2d.h"

namespace gengine {
    namespace graphics {

        class Simple2DRenderer : public Renderer2D
        {
        private:
            std::deque<const StaticSprite*> queue;
        public:
            void submit(const Renderable2D* renderable) override;
            void flush() override;
        };
    }
}