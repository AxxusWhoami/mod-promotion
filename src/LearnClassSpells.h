#pragma once
#include "Player.h"

// Builds the per-family spell index from sSpellMgr. Must be called once at
// server startup (after SpellMgr is loaded) before LearnAllClassSpells is used.
void InitSpellCache();

// Teaches all trainable class spells from level 1 up to player->GetLevel().
// Mirrors the logic of mod-learn-spells (AxxusWhoami/mod-learn-spells).
void LearnAllClassSpells(Player* player);
