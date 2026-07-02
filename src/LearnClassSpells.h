#pragma once
#include "Player.h"

// Teaches all class spells from level 1 up to player->GetLevel().
// Mirrors the logic of mod-learn-spells (AxxusWhoami/mod-learn-spells).
void LearnAllClassSpells(Player* player);
