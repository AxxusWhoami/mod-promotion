// Adapted from AxxusWhoami/mod-learn-spells (MIT License).
// Teaches all trainable class spells from level 1 up to the player's current level,
// including faction-specific extras (mounts, teleports, seals, etc.).

#include "LearnClassSpells.h"
#include "DisableMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

// ---------------------------------------------------------------------------
// Spells deliberately excluded from auto-teaching.
// Sourced verbatim from mod-learn-spells to keep parity with that module.
// ---------------------------------------------------------------------------
static const std::unordered_set<uint32> s_ignoreSpells =
{
    64380, 23885, 23880, 44461, 25346, 10274, 10273, 8418,  8419,  7270,
    7269,  7268,  54648, 12536, 24530, 70909, 12494, 57933, 24224, 27095,
    27096, 27097, 27099, 32841, 56131, 56160, 56161, 48153, 34754, 64844,
    64904, 48085, 33110, 48084, 28276, 27874, 27873, 7001,  49821, 53022,
    47757, 47750, 47758, 47666, 53001, 52983, 52998, 52986, 52987, 52999,
    52984, 53002, 53003, 53000, 52988, 52985, 42208, 42209, 42210, 42211,
    42212, 42213, 42198, 42937, 42938, 12484, 12485, 12486, 44461, 55361,
    55362, 34913, 43043, 43044, 38703, 38700, 27076, 42844, 42845, 64891,
    25912, 25914, 25911, 25913, 25902, 25903, 27175, 27176, 33073, 33074,
    48822, 48820, 48823, 48821, 20154, 25997, 20467, 20425, 67,    26017,
    34471, 53254, 13812, 14314, 14315, 27026, 49064, 49065, 60202, 60210,
    13797, 14298, 14299, 14300, 14301, 27024, 49053, 49054, 52399, 1742,
    24453, 53548, 53562, 52016, 26064, 35346, 57386, 57389, 57390, 57391,
    57392, 57393, 55509, 35886, 43339, 45297, 45298, 45299, 45300, 45301,
    45302, 49268, 49269, 8349,  8502,  8503,  11306, 11307, 25535, 25537,
    61650, 61654, 63685, 45284, 45286, 45287, 45288, 45289, 45290, 45291,
    45292, 45293, 45294, 45295, 45296, 49239, 49240, 26364, 26365, 26366,
    26367, 26369, 26370, 26363, 26371, 26372, 49278, 49279, 32176, 32175,
    21169, 47206, 27285, 47833, 47836, 42223, 42224, 42225, 42226, 42218,
    47817, 47818, 42231, 42232, 42233, 42230, 48466, 44203, 44205, 44206,
    44207, 44208, 48444, 48445, 33891, 52374, 57532, 59921, 52372, 49142,
    52375, 47633, 47632, 52373, 50536, 27214, 47822, 11682, 11681, 5857,
    1010,  24907, 24905, 53227, 61391, 61390, 61388, 61387, 64801, 5421,
    9635,  1178,  20186, 20185, 20184, 20187, 25899, 24406, 50581, 30708,
    48076, 62900, 62901, 62902, 59671, 50589, 66906, 66907, 24131, 23455,
    23458, 23459, 27803, 27804, 27805, 25329, 48075, 42243, 42244, 42245,
    42234, 58432, 58433, 65878, 18848, 16979, 49376, 54055, 20647, 42243,
    24131, 45470, 31898, 31804, 53733, 31803, 53742, 53725, 53726, 1804,
    348,   1455,  1456,  11687, 11688, 11689, 27222, 57946, 25306, 53652,
    53653, 53654, 7328,  10322, 10324, 20772, 20773, 48949, 48950, 33878,
    33876, 33982, 33986, 33987, 33983, 48563, 48565, 48566, 48564,
    // Dalaran Brilliance / Intellect (Dalaran NPC-sold only)
    61316, 61024,
    // Cosmetic
    28271, 28272, 61025, 61305, 61721, 61780,
    // Quest spell
    18540,
};

// ---------------------------------------------------------------------------
// Extra spells not found via SkillLineAbility, taught at specific levels.
// ---------------------------------------------------------------------------
struct ExtraSpell { uint32 spellId; TeamId faction = TEAM_NEUTRAL; };
using FamilyExtras = std::unordered_map<uint32, std::vector<ExtraSpell>>;
using LevelExtras  = std::unordered_map<uint8,  FamilyExtras>;

static const LevelExtras s_additionalSpells =
{
    {3,  { {SPELLFAMILY_WARLOCK,  { {348}                                                   }} }},
    {6,  { {SPELLFAMILY_WARRIOR,  { {3127}                                                  }} }},
    {8,  { {SPELLFAMILY_HUNTER,   { {3127}                                                  }},
           {SPELLFAMILY_PALADIN,  { {3127}                                                  }} }},
    {10, { {SPELLFAMILY_HUNTER,   { {1515}, {6991}, {883}, {2641}                           }} }},
    {12, { {SPELLFAMILY_ROGUE,    { {3127}                                                  }},
           {SPELLFAMILY_PALADIN,  { {7328}                                                  }} }},
    {14, { {SPELLFAMILY_HUNTER,   { {6197}                                                  }} }},
    {16, { {SPELLFAMILY_ROGUE,    { {1804}                                                  }},
           {SPELLFAMILY_WARLOCK,  { {1455}                                                  }} }},
    {20, { {SPELLFAMILY_WARRIOR,  { {674},  {12678}                                         }},
           {SPELLFAMILY_HUNTER,   { {674}                                                   }},
           {SPELLFAMILY_WARLOCK,  { {5784}                                                  }},
           {SPELLFAMILY_PALADIN,  { {34769, TEAM_HORDE}, {13819, TEAM_ALLIANCE}             }},
           {SPELLFAMILY_MAGE,     { {3567,  TEAM_HORDE},  {32272, TEAM_HORDE},
                                    {3563,  TEAM_HORDE},  {3561,  TEAM_ALLIANCE},
                                    {3562,  TEAM_ALLIANCE},{32271, TEAM_ALLIANCE}           }} }},
    {24, { {SPELLFAMILY_HUNTER,   { {1462}, {19885}                                         }},
           {SPELLFAMILY_ROGUE,    { {2836}                                                  }},
           {SPELLFAMILY_WARLOCK,  { {5500}                                                  }},
           {SPELLFAMILY_SHAMAN,   { {6196}                                                  }},
           {SPELLFAMILY_PALADIN,  { {10322}                                                 }} }},
    {26, { {SPELLFAMILY_WARLOCK,  { {1456}                                                  }} }},
    {30, { {SPELLFAMILY_SHAMAN,   { {66842}                                                 }},
           {SPELLFAMILY_MAGE,     { {3566,  TEAM_HORDE},  {3565, TEAM_ALLIANCE}            }} }},
    {32, { {SPELLFAMILY_DRUID,    { {5225}                                                  }} }},
    {35, { {SPELLFAMILY_MAGE,     { {49358, TEAM_HORDE},  {49361, TEAM_HORDE},
                                    {49359, TEAM_ALLIANCE},{49360, TEAM_ALLIANCE}           }} }},
    {36, { {SPELLFAMILY_WARLOCK,  { {11687}                                                 }},
           {SPELLFAMILY_PALADIN,  { {10324}                                                 }} }},
    {40, { {SPELLFAMILY_SHAMAN,   { {66843}, {8737}                                         }},
           {SPELLFAMILY_HUNTER,   { {8737}                                                  }},
           {SPELLFAMILY_WARRIOR,  { {750}                                                   }},
           {SPELLFAMILY_PALADIN,  { {34767, TEAM_HORDE}, {23214, TEAM_ALLIANCE}, {750}      }},
           {SPELLFAMILY_WARLOCK,  { {23161}                                                 }},
           {SPELLFAMILY_DRUID,    { {20719}, {62600}                                        }},
           {SPELLFAMILY_MAGE,     { {11417, TEAM_HORDE},  {32267, TEAM_HORDE},
                                    {11418, TEAM_HORDE},  {10059, TEAM_ALLIANCE},
                                    {11416, TEAM_ALLIANCE},{32266, TEAM_ALLIANCE}           }} }},
    {46, { {SPELLFAMILY_WARLOCK,  { {11688}                                                 }} }},
    {48, { {SPELLFAMILY_PALADIN,  { {20772}                                                 }} }},
    {50, { {SPELLFAMILY_SHAMAN,   { {66844}                                                 }},
           {SPELLFAMILY_MAGE,     { {11420, TEAM_HORDE},  {11419, TEAM_ALLIANCE}           }} }},
    {56, { {SPELLFAMILY_WARLOCK,  { {11689}                                                 }} }},
    {60, { {SPELLFAMILY_MAGE,     { {35715, TEAM_HORDE},  {33690, TEAM_ALLIANCE}           }},
           {SPELLFAMILY_PALADIN,  { {20773}                                                 }} }},
    {62, { {SPELLFAMILY_MAGE,     { {25306}                                                 }} }},
    {65, { {SPELLFAMILY_MAGE,     { {35717, TEAM_HORDE},  {33691, TEAM_ALLIANCE}           }} }},
    {66, { {SPELLFAMILY_PALADIN,  { {53736, TEAM_HORDE},  {31801, TEAM_ALLIANCE}           }},
           {SPELLFAMILY_WARLOCK,  { {29858}                                                 }} }},
    {68, { {SPELLFAMILY_WARLOCK,  { {27222}                                                 }} }},
    {70, { {SPELLFAMILY_SHAMAN,   { {2825,  TEAM_HORDE},  {32182, TEAM_ALLIANCE}           }} }},
    {71, { {SPELLFAMILY_DRUID,    { {40120}                                                 }} }},
    {72, { {SPELLFAMILY_PALADIN,  { {48949}                                                 }} }},
    {79, { {SPELLFAMILY_PALADIN,  { {48950}                                                 }} }},
    {80, { {SPELLFAMILY_WARLOCK,  { {47836}, {57946}                                        }} }},
};

// ---------------------------------------------------------------------------

static uint32 GetSpellFamily(Player const* player)
{
    switch (player->getClass())
    {
        case CLASS_WARRIOR:     return SPELLFAMILY_WARRIOR;
        case CLASS_PALADIN:     return SPELLFAMILY_PALADIN;
        case CLASS_HUNTER:      return SPELLFAMILY_HUNTER;
        case CLASS_ROGUE:       return SPELLFAMILY_ROGUE;
        case CLASS_PRIEST:      return SPELLFAMILY_PRIEST;
        case CLASS_DEATH_KNIGHT:return SPELLFAMILY_DEATHKNIGHT;
        case CLASS_SHAMAN:      return SPELLFAMILY_SHAMAN;
        case CLASS_MAGE:        return SPELLFAMILY_MAGE;
        case CLASS_WARLOCK:     return SPELLFAMILY_WARLOCK;
        case CLASS_DRUID:       return SPELLFAMILY_DRUID;
        default:                return SPELLFAMILY_GENERIC;
    }
}

static void ApplyExtrasForLevel(Player* player, uint32 family, uint8 level)
{
    auto it = s_additionalSpells.find(level);
    if (it == s_additionalSpells.end())
        return;

    auto jt = it->second.find(family);
    if (jt == it->second.end())
        return;

    for (ExtraSpell const& es : jt->second)
    {
        if (!player->HasSpell(es.spellId) &&
            (es.faction == TEAM_NEUTRAL || es.faction == player->GetTeamId()))
            player->learnSpell(es.spellId);
    }
}

// ---------------------------------------------------------------------------
// Per-family spell cache (built once at server startup by InitSpellCache).
// Stores only spells that passed the static checks so LearnAllClassSpells
// iterates a small per-class list instead of all ~80 000 spell IDs.
// ---------------------------------------------------------------------------
struct CachedSpell
{
    SpellInfo const* info;
    SpellInfo const* prevRank; // null when spell is rank 1
    bool             isValid;  // sSpellMgr->IsSpellValid result
    bool             isTalent; // has a TalentSpellPos entry
};
static std::unordered_map<uint32 /*SpellFamilyName*/, std::vector<CachedSpell>> s_spellCache;

void InitSpellCache()
{
    s_spellCache.clear();
    for (uint32 i = 0; i < sSpellMgr->GetSpellInfoStoreSize(); ++i)
    {
        SpellInfo const* spell = sSpellMgr->GetSpellInfo(i);
        if (!spell || spell->SpellFamilyName == SPELLFAMILY_GENERIC)
            continue;
        if (s_ignoreSpells.count(spell->Id) || spell->PowerType == POWER_FOCUS)
            continue;

        bool hasValidSLA = false;
        SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(spell->Id);
        for (auto itr = bounds.first; itr != bounds.second; ++itr)
        {
            if (itr->second->Spell == spell->Id &&
                itr->second->RaceMask == 0 &&
                itr->second->AcquireMethod == 0)
            {
                hasValidSLA = true;
                break;
            }
        }
        if (!hasValidSLA)
            continue;

        CachedSpell cs;
        cs.info     = spell;
        cs.prevRank = spell->GetPrevRankSpell();
        cs.isValid  = sSpellMgr->IsSpellValid(spell);
        cs.isTalent = GetTalentSpellPos(spell->Id) != nullptr;
        s_spellCache[spell->SpellFamilyName].push_back(cs);
    }
}

void LearnAllClassSpells(Player* player)
{
    uint32 const family  = GetSpellFamily(player);
    uint8  const toLevel = player->GetLevel();

    auto cacheIt = s_spellCache.find(family);

    for (uint8 level = 1; level <= toLevel; ++level)
    {
        ApplyExtrasForLevel(player, family, level);

        if (cacheIt == s_spellCache.end())
            continue;

        for (CachedSpell const& cs : cacheIt->second)
        {
            SpellInfo const* spell = cs.info;

            if (spell->BaseLevel != uint32(level) && cs.isValid)
                continue;

            if ((spell->AttributesEx7 & SPELL_ATTR7_ALLIANCE_SPECIFIC_SPELL && player->GetTeamId() != TEAM_ALLIANCE) ||
                (spell->AttributesEx7 & SPELL_ATTR7_HORDE_SPECIFIC_SPELL   && player->GetTeamId() != TEAM_HORDE))
                continue;

            if (DisableMgr::IsDisabledFor(DISABLE_TYPE_SPELL, spell->Id, player))
                continue;

            if (cs.prevRank && !player->HasSpell(cs.prevRank->Id))
                continue;

            if (cs.isTalent && (!cs.prevRank || !player->HasSpell(cs.prevRank->Id) || spell->GetRank() == 1))
                continue;

            player->learnSpell(spell->Id);
        }
    }
}
