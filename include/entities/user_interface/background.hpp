#pragma once

#include "entities/user_interface/ui_entity.hpp"

class Background : public UIEntity {
   public:
    Background(GameCore *game_core);

    ~Background() override;
};
