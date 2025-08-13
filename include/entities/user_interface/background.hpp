#pragma once

#include "../../types.hpp"
#include "ui_entity.hpp"

class Background : public UIEntity {
   public:
    Background(GameCore *game_core);

    ~Background() override;
};
