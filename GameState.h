#pragma once
#include "Game.h"
#include "FileHandler.h"

class GameState {
protected:
    Game& game;

public:
    friend std::ostream& operator<<(std::ostream& os, GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);


    GameState(Game& game) : game(game) {}

    ShipManager shipmanager_from_json(const json& save_file);
    GameField field_from_json(const json& save_file, ShipManager& SManager);
    AbilityManager abilitymanager_from_json(const json& save_file);

    bool save(const std::string& file_name);
    bool load(const std::string& file_name);
};

