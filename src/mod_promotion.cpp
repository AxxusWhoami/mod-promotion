/**
    Nefertumm and Stevej
    https://github.com/Nefertumm/
    https://github.com/pangolp
    https://github.com/Asmadeuxx
 */

#include "Chat.h"
#include "ChatCommand.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "GossipDef.h"
#include "Language.h"
#include "LearnClassSpells.h"
#include "mod_promotion.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "WorldSession.h"
#ifdef MODULE_PLAYERBOTS
#include "PlayerbotAI.h"
#endif
#include <algorithm>
#include <array>
#include <ctime>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

// ---------------------------------------------------------------------------
// Tables that are stable across the lifetime of the process.
// Placed at module scope so OnAfterConfigLoad can iterate them for pre-loading.
// ---------------------------------------------------------------------------

static const std::pair<uint32, const char*> kGearSets[] =
{
    { GOSSIP_ACTION_INFO_DEF +  1, "WARRIOR_DPS"   },
    { GOSSIP_ACTION_INFO_DEF +  2, "WARRIOR_TANK"  },
    { GOSSIP_ACTION_INFO_DEF +  3, "WARLOCK"       },
    { GOSSIP_ACTION_INFO_DEF +  4, "DRUID_TANK"    },
    { GOSSIP_ACTION_INFO_DEF +  5, "DRUID_HEAL"    },
    { GOSSIP_ACTION_INFO_DEF +  6, "DRUID_CASTER"  },
    { GOSSIP_ACTION_INFO_DEF +  7, "HUNTER"        },
    { GOSSIP_ACTION_INFO_DEF +  8, "MAGE"          },
    { GOSSIP_ACTION_INFO_DEF +  9, "ROGUE"         },
    { GOSSIP_ACTION_INFO_DEF + 10, "PRIEST_HEAL"   },
    { GOSSIP_ACTION_INFO_DEF + 11, "PRIEST_SHADOW" },
    { GOSSIP_ACTION_INFO_DEF + 12, "PALADIN_TANK"  },
    { GOSSIP_ACTION_INFO_DEF + 13, "PALADIN_HEAL"  },
    { GOSSIP_ACTION_INFO_DEF + 14, "PALADIN_DPS"   },
    { GOSSIP_ACTION_INFO_DEF + 15, "SHAMAN_CASTER" },
    { GOSSIP_ACTION_INFO_DEF + 16, "SHAMAN_HEAL"   },
    { GOSSIP_ACTION_INFO_DEF + 17, "SHAMAN_MELEE"  },
    { GOSSIP_ACTION_INFO_DEF + 18, "DK_TANK"       },
    { GOSSIP_ACTION_INFO_DEF + 19, "DK_DPS"        },
};

static const std::pair<EquipmentSlots, const char*> kEquipSlots[] =
{
    { EQUIPMENT_SLOT_HEAD,      "HEAD"      },
    { EQUIPMENT_SLOT_NECK,      "NECK"      },
    { EQUIPMENT_SLOT_SHOULDERS, "SHOULDERS" },
    { EQUIPMENT_SLOT_CHEST,     "CHEST"     },
    { EQUIPMENT_SLOT_WAIST,     "WAIST"     },
    { EQUIPMENT_SLOT_LEGS,      "LEGS"      },
    { EQUIPMENT_SLOT_FEET,      "FEET"      },
    { EQUIPMENT_SLOT_WRISTS,    "WRISTS"    },
    { EQUIPMENT_SLOT_HANDS,     "HANDS"     },
    { EQUIPMENT_SLOT_FINGER1,   "FINGER1"   },
    { EQUIPMENT_SLOT_FINGER2,   "FINGER2"   },
    { EQUIPMENT_SLOT_TRINKET1,  "TRINKET1"  },
    { EQUIPMENT_SLOT_TRINKET2,  "TRINKET2"  },
    { EQUIPMENT_SLOT_BACK,      "BACK"      },
    { EQUIPMENT_SLOT_MAINHAND,  "MAINHAND"  },
    { EQUIPMENT_SLOT_OFFHAND,   "OFFHAND"   },
    { EQUIPMENT_SLOT_RANGED,    "RANGED"    },
};

// Derived at compile time so adding/removing a slot above updates everything automatically.
static constexpr size_t kEquipSlotCount = std::size(kEquipSlots);

// ---------------------------------------------------------------------------
// Gossip action ranges:
//   Spec select : GOSSIP_ACTION_INFO_DEF + 1 .. +19  (one per spec)
//   Cancel      : GOSSIP_ACTION_INFO_DEF + 20         (confirmation step cancel)
//   Confirm     : spec_action + kConfirmOffset        (i.e. +101 .. +119)
// ---------------------------------------------------------------------------
static constexpr uint32 kCancelAction  = GOSSIP_ACTION_INFO_DEF + 20;
static constexpr uint32 kConfirmOffset = 100u;

// Per-class valid spec actions — at module scope to avoid re-construction on every gossip select.
static const std::unordered_map<uint8, std::vector<uint32>> kClassActions =
{
    {CLASS_WARRIOR,      {GOSSIP_ACTION_INFO_DEF +  1, GOSSIP_ACTION_INFO_DEF +  2}},
    {CLASS_WARLOCK,      {GOSSIP_ACTION_INFO_DEF +  3}},
    {CLASS_DRUID,        {GOSSIP_ACTION_INFO_DEF +  4, GOSSIP_ACTION_INFO_DEF +  5, GOSSIP_ACTION_INFO_DEF +  6}},
    {CLASS_HUNTER,       {GOSSIP_ACTION_INFO_DEF +  7}},
    {CLASS_MAGE,         {GOSSIP_ACTION_INFO_DEF +  8}},
    {CLASS_ROGUE,        {GOSSIP_ACTION_INFO_DEF +  9}},
    {CLASS_PRIEST,       {GOSSIP_ACTION_INFO_DEF + 10, GOSSIP_ACTION_INFO_DEF + 11}},
    {CLASS_PALADIN,      {GOSSIP_ACTION_INFO_DEF + 12, GOSSIP_ACTION_INFO_DEF + 13, GOSSIP_ACTION_INFO_DEF + 14}},
    {CLASS_SHAMAN,       {GOSSIP_ACTION_INFO_DEF + 15, GOSSIP_ACTION_INFO_DEF + 16, GOSSIP_ACTION_INFO_DEF + 17}},
    {CLASS_DEATH_KNIGHT, {GOSSIP_ACTION_INFO_DEF + 18, GOSSIP_ACTION_INFO_DEF + 19}},
};

// ---------------------------------------------------------------------------
// Cached config values — refreshed in OnAfterConfigLoad on every load/reload.
// ---------------------------------------------------------------------------

static bool   s_promotionEnable;
static bool   s_mountGround;
static bool   s_mountFlying;
static bool   s_bagEnable;
static bool   s_equippedbags;
static bool   s_learnSpells;
static bool   s_teleportOnPromotion;
static bool   s_confirmationStep;
static bool   s_announceToWorld;
static bool   s_talentTemplateEnable;

static uint32 s_targetLevel;
static uint32 s_requiredLevel;
static uint32 s_dkRequiredLevel;
static uint32 s_minAccountAge;
static int32  s_moneyReward;
static uint32 s_bagId;

static uint32 s_allianceMapId;
static uint32 s_allianceAreaId;
static float  s_allianceX, s_allianceY, s_allianceZ, s_allianceO;
static uint32 s_hordeMapId;
static uint32 s_hordeAreaId;
static float  s_hordeX, s_hordeY, s_hordeZ, s_hordeO;

// Indexed by RACE_* constants (max value = RACE_DRAENEI = 11). Index 0 and 9 are unused.
static uint32 s_groundMount[12];
static uint32 s_flyingMount[12];

// Pre-loaded gear items: config prefix -> per-slot item IDs (parallel to kEquipSlots).
static std::unordered_map<std::string, std::array<uint32, kEquipSlotCount>> s_gearItems;

// ---------------------------------------------------------------------------
// Runtime state
// ---------------------------------------------------------------------------

// Promotion use counts: account_id -> number of promotions already claimed.
// All gossip handling runs on the world thread — no mutex needed.
static std::unordered_map<uint32, uint32> s_promotionUseCounts;

// Bonus promotion grants: account_id -> total extra uses granted by GMs.
// Loaded at startup from mod_promotion_bonus.
static std::unordered_map<uint32, uint32> s_promotionBonus;

// Accounts currently executing the promotion grant path.
// Guards against two characters from the same account claiming concurrently.
static std::unordered_set<uint32> s_promotionInProgress;

// Cached account join dates: account_id -> UNIX timestamp of joindate.
// Populated on first gossip open; never changes, so no eviction needed.
static std::unordered_map<uint32, uint32> s_accountJoinDates;

// Talent templates: spec name -> list of talent spell IDs.
// Loaded at startup from mod_promotion_talents (world DB).
static std::unordered_map<std::string, std::vector<uint32>> s_talentTemplates;

// Mangle talent + associated spells (Feral Druid workaround).
static constexpr uint32 TALENT_MANGLE      = 33917;
static constexpr uint32 SPELL_MANGLE_CAT    = 33876;
static constexpr uint32 SPELL_MANGLE_BEAR   = 33878;

// ---------------------------------------------------------------------------

static void ApplyTalentTemplate(Player* player, const std::string& spec)
{
    auto it = s_talentTemplates.find(spec);
    if (it == s_talentTemplates.end())
    {
        LOG_WARN("module", "mod_promotion: No talent template found for spec '{}'. Talents left unspent.", spec);
        return;
    }

    for (uint32 talentId : it->second)
    {
        player->learnSpellHighRank(talentId);
        player->addTalent(talentId, player->GetActiveSpecMask(), 0);

        if (talentId == TALENT_MANGLE)
        {
            player->CastSpell(player, TALENT_MANGLE, true);

            auto LearnHighestRankForLevel = [player](uint32 baseRankId)
            {
                for (uint32 id = baseRankId; id; id = sSpellMgr->GetNextSpellInChain(id))
                {
                    SpellInfo const* info = sSpellMgr->GetSpellInfo(id);
                    if (!info || info->BaseLevel > player->GetLevel())
                        break;
                    player->learnSpell(id);
                }
            };
            LearnHighestRankForLevel(SPELL_MANGLE_CAT);
            LearnHighestRankForLevel(SPELL_MANGLE_BEAR);
        }
    }

    player->InitTalentForLevel();
}

static bool IsValidActionForClass(uint8 cls, uint32 action)
{
    auto it = kClassActions.find(cls);
    if (it == kClassActions.end())
        return false;
    return std::find(it->second.begin(), it->second.end(), action) != it->second.end();
}

static std::string_view SpecLabel(uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF +  1: return "Guerrero - Furia";
        case GOSSIP_ACTION_INFO_DEF +  2: return "Guerrero - Proteccion";
        case GOSSIP_ACTION_INFO_DEF +  3: return "Brujo - Destruccion";
        case GOSSIP_ACTION_INFO_DEF +  4: return "Druida - Guardian";
        case GOSSIP_ACTION_INFO_DEF +  5: return "Druida - Restauracion";
        case GOSSIP_ACTION_INFO_DEF +  6: return "Druida - Equilibrio";
        case GOSSIP_ACTION_INFO_DEF +  7: return "Cazador - Punteria";
        case GOSSIP_ACTION_INFO_DEF +  8: return "Mago - Escarcha";
        case GOSSIP_ACTION_INFO_DEF +  9: return "Picaro - Sutileza";
        case GOSSIP_ACTION_INFO_DEF + 10: return "Sacerdote - Disciplina";
        case GOSSIP_ACTION_INFO_DEF + 11: return "Sacerdote - Sombras";
        case GOSSIP_ACTION_INFO_DEF + 12: return "Paladin - Proteccion";
        case GOSSIP_ACTION_INFO_DEF + 13: return "Paladin - Sagrado";
        case GOSSIP_ACTION_INFO_DEF + 14: return "Paladin - Retribucion";
        case GOSSIP_ACTION_INFO_DEF + 15: return "Shaman - Elemental";
        case GOSSIP_ACTION_INFO_DEF + 16: return "Shaman - Restauracion";
        case GOSSIP_ACTION_INFO_DEF + 17: return "Shaman - Mejora";
        case GOSSIP_ACTION_INFO_DEF + 18: return "Caballero de la Muerte - Sangre";
        case GOSSIP_ACTION_INFO_DEF + 19: return "Caballero de la Muerte - Escarcha";
        default:                          return "Desconocido";
    }
}

// ---------------------------------------------------------------------------

class npc_promotion : public CreatureScript
{
public:
    npc_promotion() : CreatureScript("npc_promotion") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
#ifdef MODULE_PLAYERBOTS
        if (player->IsPlayerBot())
        {
            CloseGossipMenuFor(player);
            return true;
        }
#endif
        bool const isModerator = player->GetSession()->GetSecurity() >= SEC_MODERATOR;

        switch (CheckEligibility(player, isModerator))
        {
            case PromotionCheck::Disabled:    SendGossipMenuFor(player, 80000, creature); return true;
            case PromotionCheck::WrongLevel:  SendGossipMenuFor(player, 80003, creature); return true;
            case PromotionCheck::AlreadyUsed: SendGossipMenuFor(player, 80001, creature); return true;
            case PromotionCheck::TooNew:      SendGossipMenuFor(player, 80005, creature); return true;
            case PromotionCheck::Ok:          break;
        }

        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Furia",             GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  1);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Tanque - Proteccion",     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  2);
                break;
            case CLASS_WARLOCK:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Destruccion",       GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  3);
                break;
            case CLASS_DRUID:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Tanque - Guardian",       GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  4);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Healer - Restauracion",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  5);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Equilibrio",        GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  6);
                break;
            case CLASS_HUNTER:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Punteria",          GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  7);
                break;
            case CLASS_MAGE:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Escarcha",          GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  8);
                break;
            case CLASS_ROGUE:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Sutileza",          GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  9);
                break;
            case CLASS_PRIEST:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Healer - Disciplina",     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Sombras",           GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                break;
            case CLASS_PALADIN:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Tanque - Proteccion",     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Healer - Sagrado",        GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Retribucion",       GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                break;
            case CLASS_SHAMAN:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Elemental",         GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Healer - Restauracion",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Mejora",            GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                break;
            case CLASS_DEATH_KNIGHT:
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Tanque - Sangre",         GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DPS - Escarcha/Profano",  GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                break;
            default:
                break;
        }
        SendGossipMenuFor(player, 80002, creature);
        return true;
    }

    static void SkipDKStartingArea(Player* player)
    {
        // Area 4342 = Acherus: The Ebon Hold (DK starting area).
        if (player->GetAreaId() != 4342)
            return;

        if (!player->HasItemCount(6948))
            player->AddItem(6948, true); // Hearthstone

        // All DK starting quests that award talent points, quest items, or spells.
        // Index 22 is the race-specific "A Special Surprise" quest (set below).
        // Index 32 is the team-specific final quest (set below).
        uint32 quests[33] = {
            12593, 12619, 12842, 12848, 12636, 12641, 12657, 12678, 12679, 12680,
            12687, 12698, 12701, 12706, 12716, 12719, 12720, 12722, 12724, 12725,
            12727, 12733,     0, 12751, 12754, 12755, 12756, 12757, 12779, 12801,
            13165, 13166,     0
        };

        switch (player->getRace())
        {
            case RACE_TAUREN:        quests[22] = 12739; break;
            case RACE_HUMAN:         quests[22] = 12742; break;
            case RACE_NIGHTELF:      quests[22] = 12743; break;
            case RACE_DWARF:         quests[22] = 12744; break;
            case RACE_GNOME:         quests[22] = 12745; break;
            case RACE_DRAENEI:       quests[22] = 12746; break;
            case RACE_BLOODELF:      quests[22] = 12747; break;
            case RACE_ORC:           quests[22] = 12748; break;
            case RACE_TROLL:         quests[22] = 12749; break;
            case RACE_UNDEAD_PLAYER: quests[22] = 12750; break;
            default: break;
        }

        quests[32] = (player->GetTeamId() == TEAM_ALLIANCE) ? 13188u : 13189u;

        for (uint32 questId : quests)
        {
            if (!questId)
                continue;
            if (player->GetQuestStatus(questId) == QUEST_STATUS_NONE)
            {
                Quest const* quest = sObjectMgr->GetQuestTemplate(questId);
                if (quest)
                {
                    player->AddQuest(quest, nullptr);
                    player->RewardQuest(quest, 0, player, false);
                }
            }
        }

        // Alternate reward items not selected by default from the starting quests.
        player->AddItem(38664, true); // Sky Darkener's Shroud of the Unholy (quest 12679 alt)
        player->AddItem(39322, true); // Shroud of the North Wind (quest 12679 alt)
        player->AddItem(38632, true); // Greatsword of the Ebon Blade (quest 12801 alt)
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);

#ifdef MODULE_PLAYERBOTS
        if (player->IsPlayerBot())
        {
            CloseGossipMenuFor(player);
            return true;
        }
#endif
        bool const isModerator = player->GetSession()->GetSecurity() >= SEC_MODERATOR;

        // Guard against forged packets and edge cases that bypass OnGossipHello.
        switch (CheckEligibility(player, isModerator))
        {
            case PromotionCheck::Disabled:    SendGossipMenuFor(player, 80000, creature); return true;
            case PromotionCheck::WrongLevel:  CloseGossipMenuFor(player);                 return true;
            case PromotionCheck::AlreadyUsed: SendGossipMenuFor(player, 80001, creature); return true;
            case PromotionCheck::TooNew:      CloseGossipMenuFor(player);                 return true;
            case PromotionCheck::Ok:          break;
        }

        // Confirmation step: intercept spec selection, show confirm/cancel menu, then unwrap.
        if (s_confirmationStep)
        {
            if (action == kCancelAction)
            {
                CloseGossipMenuFor(player);
                return true;
            }

            // First click: spec chosen but not yet confirmed — show the confirmation menu.
            if (action > GOSSIP_ACTION_INFO_DEF && action <= GOSSIP_ACTION_INFO_DEF + 19)
            {
                if (!IsValidActionForClass(player->getClass(), action))
                {
                    CloseGossipMenuFor(player);
                    return true;
                }
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Si, confirmar promocion.", GOSSIP_SENDER_MAIN, action + kConfirmOffset);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "No, cancelar.",            GOSSIP_SENDER_MAIN, kCancelAction);
                SendGossipMenuFor(player, 80004, creature);
                return true;
            }

            // Second click: confirmed action — unwrap to original spec action.
            if (action > GOSSIP_ACTION_INFO_DEF + kConfirmOffset &&
                action <= GOSSIP_ACTION_INFO_DEF + kConfirmOffset + 19)
            {
                action -= kConfirmOffset;
            }
            else
            {
                CloseGossipMenuFor(player);
                return true;
            }
        }

        // Reject actions that don't belong to the player's class.
        if (!IsValidActionForClass(player->getClass(), action))
        {
            CloseGossipMenuFor(player);
            return true;
        }

        // Atomically claim a promotion use BEFORE granting rewards.
        // The in-progress set also blocks a second character on the same account
        // from slipping through CheckEligibility while the first grant is executing.
        uint32 const accountId = player->GetSession()->GetAccountId();
        if (!isModerator)
        {
            if (s_promotionInProgress.count(accountId))
            {
                CloseGossipMenuFor(player);
                return true;
            }
            uint32 const used  = s_promotionUseCounts[accountId];
            uint32 const bonus = s_promotionBonus.count(accountId) ? s_promotionBonus[accountId] : 0u;
            uint32 const allowed = 1 + bonus;
            if (used >= allowed)
            {
                CloseGossipMenuFor(player);
                return true;
            }
            s_promotionInProgress.insert(accountId);
            s_promotionUseCounts[accountId] = used + 1;
        }

        // ---- Grant rewards ------------------------------------------------

        // GiveLevel (not SetLevel) so the LFG/dungeon-finder system and all
        // internal bookkeeping are notified of the level change. SetLevel is a
        // raw field setter that leaves LFG dungeon access stale and locked.
        player->GiveLevel(static_cast<uint8>(s_targetLevel));
        player->InitStatsForLevel(true);
        player->InitTaxiNodesForLevel();
        player->InitGlyphsForLevel();
        player->InitTalentForLevel();

        if (s_talentTemplateEnable)
        {
            for (auto const& gs : kGearSets)
            {
                if (action == gs.first)
                {
                    ApplyTalentTemplate(player, gs.second);
                    break;
                }
            }
        }

        player->SetUInt32Value(PLAYER_XP, 0);

        player->ModifyMoney(s_moneyReward);
        player->UpdateSkillsToMaxSkillsForLevel();

        if (s_learnSpells)
            LearnAllClassSpells(player);

        player->learnSpell(SKILL_RIDING_75);
        player->learnSpell(SKILL_RIDING_100);
        player->learnSpell(SKILL_RIDING_FLYING);
        player->learnSpell(SKILL_RIDING_ARTISING);

        creature->Whisper("¡Felicidades! Tu Promocion ha sido concedida.", LANG_UNIVERSAL, player);

        if (s_mountGround)
        {
            uint8  const race  = player->getRace();
            uint32 const spell = (static_cast<size_t>(race) < std::size(s_groundMount)) ? s_groundMount[race] : 0;
            if (spell)
                player->learnSpell(spell);
        }

        if (s_mountFlying)
        {
            uint8  const race  = player->getRace();
            uint32 const spell = (static_cast<size_t>(race) < std::size(s_flyingMount)) ? s_flyingMount[race] : 0;
            if (spell)
                player->learnSpell(spell);
        }

        if (s_bagEnable)
        {
            if (s_equippedbags)
            {
                // Only destroy a bag if it is completely empty to avoid data loss.
                for (int slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
                {
                    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                    {
                        if (Bag* bag = item->ToBag())
                            if (bag->GetFreeSlots() < bag->GetBagSize())
                                continue;
                        player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
                    }
                }
                // Equip in every slot that is now free.
                for (int slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
                    if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                        player->EquipNewItem(slot, s_bagId, true);
            }
            else
                player->AddItem(s_bagId, 4);
        }

        for (auto const& gs : kGearSets)
        {
            if (action == gs.first)
            {
                EquipGearSet(player, creature, gs.second);
                break;
            }
        }

        if (player->getClass() == CLASS_SHAMAN)
        {
            static const uint32 kTotems[] = { 5175, 5176, 5177, 5178 };
            for (uint32 totem : kTotems)
                if (!player->HasItemCount(totem))
                    player->AddItem(totem, 1);
        }

        if (player->getClass() == CLASS_DEATH_KNIGHT)
            SkipDKStartingArea(player);

        // ---- Persist & announce -------------------------------------------

        std::string const playerName = player->GetName();

        if (!isModerator)
        {
            // EscapeString prevents a malformed name from breaking the query.
            std::string safeName = playerName;
            CharacterDatabase.EscapeString(safeName);

            CharacterDatabase.Execute(
                "INSERT INTO mod_promotion_log (account_id, character_guid, character_name, timestamp) VALUES ({}, {}, '{}', UNIX_TIMESTAMP())",
                accountId,
                player->GetGUID().GetCounter(),
                safeName);

            LOG_INFO("module", "mod_promotion: Promotion granted — account {} character {} (guid {})",
                accountId, playerName, player->GetGUID().GetCounter());
        }
        else
        {
            LOG_INFO("module", "mod_promotion: Promotion granted by GM bypass — account {} character {} (guid {})",
                accountId, playerName, player->GetGUID().GetCounter());
        }

        if (s_announceToWorld)
        {
            std::string msg = "|cffFFD700[Promocion]|r " + playerName + " (" + std::string(SpecLabel(action)) + ") ha obtenido la Promocion de Nivel!";
            ChatHandler(nullptr).SendGlobalSysMessage(msg.c_str());
        }

        // ---- Teleport & homebind ------------------------------------------

        if (s_teleportOnPromotion)
        {
            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                WorldLocation loc(s_allianceMapId, s_allianceX, s_allianceY, s_allianceZ, s_allianceO);
                player->SetHomebind(loc, s_allianceAreaId);
                player->TeleportTo(s_allianceMapId, s_allianceX, s_allianceY, s_allianceZ, s_allianceO);
            }
            else
            {
                WorldLocation loc(s_hordeMapId, s_hordeX, s_hordeY, s_hordeZ, s_hordeO);
                player->SetHomebind(loc, s_hordeAreaId);
                player->TeleportTo(s_hordeMapId, s_hordeX, s_hordeY, s_hordeZ, s_hordeO);
            }
        }

        player->SaveToDB(false, false);
        if (!isModerator)
            s_promotionInProgress.erase(accountId);
        CloseGossipMenuFor(player);
        return true;
    }

private:
    enum class PromotionCheck { Ok, Disabled, WrongLevel, AlreadyUsed, TooNew };

    static PromotionCheck CheckEligibility(Player* player, bool isModerator)
    {
        if (!s_promotionEnable)
            return PromotionCheck::Disabled;
        if (isModerator)
            return PromotionCheck::Ok;

        bool const isDK = player->getClass() == CLASS_DEATH_KNIGHT;
        bool const wrongLevel = isDK
            ? player->GetLevel() < s_dkRequiredLevel
            : player->GetLevel() < s_requiredLevel;
        if (wrongLevel)
            return PromotionCheck::WrongLevel;

        if (s_promotionUseCounts.count(player->GetSession()->GetAccountId()))
        {
            uint32 const used  = s_promotionUseCounts[player->GetSession()->GetAccountId()];
            uint32 const bonus = s_promotionBonus.count(player->GetSession()->GetAccountId())
                ? s_promotionBonus[player->GetSession()->GetAccountId()] : 0u;
            uint32 const allowed = 1 + bonus;
            if (used >= allowed)
                return PromotionCheck::AlreadyUsed;
        }

        if (s_minAccountAge > 0)
        {
            uint32 const accountId = player->GetSession()->GetAccountId();

            uint32 joindate = 0;
            auto cacheIt = s_accountJoinDates.find(accountId);
            if (cacheIt != s_accountJoinDates.end())
            {
                joindate = cacheIt->second;
            }
            else
            {
                QueryResult result = LoginDatabase.Query(
                    "SELECT UNIX_TIMESTAMP(joindate) FROM account WHERE id = {}", accountId);
                if (result)
                    joindate = result->Fetch()[0].Get<uint32>();
                s_accountJoinDates[accountId] = joindate;
            }

            if (joindate)
            {
                auto const ageDays = static_cast<uint32>((std::time(nullptr) - static_cast<time_t>(joindate)) / 86400);
                if (ageDays < s_minAccountAge)
                    return PromotionCheck::TooNew;
            }
        }

        return PromotionCheck::Ok;
    }

    // Equips the pre-loaded gear set for the given config prefix.
    // Whispers the player if any slot could not be filled (e.g. Unique-Equipped conflict).
    static void EquipGearSet(Player* player, Creature* creature, const char* prefix)
    {
        auto it = s_gearItems.find(prefix);
        if (it == s_gearItems.end())
        {
            LOG_ERROR("module", "mod_promotion: EquipGearSet — gear set prefix '{}' not found in cache. Check OnAfterConfigLoad.", prefix);
            creature->Whisper("Algunos objetos no pudieron ser equipados. Notifica a un administrador.", LANG_UNIVERSAL, player);
            return;
        }

        bool anyFailed = false;
        for (size_t i = 0; i < kEquipSlotCount; ++i)
        {
            uint32 const itemId = it->second[i];
            if (!itemId)
                continue;
            if (!player->EquipNewItem(kEquipSlots[i].first, itemId, true))
                anyFailed = true;
        }

        if (anyFailed)
            creature->Whisper("Algunos objetos no pudieron ser equipados. Notifica a un administrador.", LANG_UNIVERSAL, player);
    }
};

// ---------------------------------------------------------------------------
// GM command: .promotion reset <name>
// Removes the promotion record so the account can claim again (testing / support).
// ---------------------------------------------------------------------------

class cmd_promotion : public CommandScript
{
public:
    cmd_promotion() : CommandScript("cmd_promotion") { }

    Acore::ChatCommands::ChatCommandTable GetCommands() const override
    {
        static Acore::ChatCommands::ChatCommandTable promotionCommandTable =
        {
            { "reset", HandlePromotionReset, SEC_GAMEMASTER, Acore::ChatCommands::Console::No  },
            { "check", HandlePromotionCheck, SEC_GAMEMASTER, Acore::ChatCommands::Console::Yes },
            { "add",   HandlePromotionAdd,   SEC_ADMINISTRATOR, Acore::ChatCommands::Console::Yes },
        };
        static Acore::ChatCommands::ChatCommandTable commandTable =
        {
            { "promotion", promotionCommandTable }
        };
        return commandTable;
    }

    static bool HandlePromotionReset(ChatHandler* handler, std::string const& playerName)
    {
        if (playerName.empty())
        {
            handler->SendSysMessage("Usage: .promotion reset <characterName>");
            handler->SetSentErrorMessage(true);
            return false;
        }

        std::string safeName = playerName;
        CharacterDatabase.EscapeString(safeName);

        QueryResult result = CharacterDatabase.Query(
            "SELECT account FROM characters WHERE name = '{}'", safeName);

        if (!result)
        {
            handler->PSendSysMessage("Character '{}' not found.", playerName);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 const accountId = result->Fetch()[0].Get<uint32>();

        CharacterDatabase.Execute(
            "DELETE FROM mod_promotion_log WHERE account_id = {}", accountId);
        CharacterDatabase.Execute(
            "DELETE FROM mod_promotion_bonus WHERE account_id = {}", accountId);
        s_promotionUseCounts.erase(accountId);
        s_promotionBonus.erase(accountId);

        handler->PSendSysMessage("Promotion reset for account {} (character '{}').", accountId, playerName);
        LOG_INFO("module", "mod_promotion: Promotion reset by GM {} for account {} (character '{}')",
            handler->GetSession() ? handler->GetSession()->GetPlayer()->GetName() : "Console",
            accountId, playerName);
        return true;
    }

    static bool HandlePromotionCheck(ChatHandler* handler, std::string const& playerName)
    {
        if (playerName.empty())
        {
            handler->SendSysMessage("Usage: .promotion check <characterName>");
            handler->SetSentErrorMessage(true);
            return false;
        }

        std::string safeName = playerName;
        CharacterDatabase.EscapeString(safeName);

        QueryResult charResult = CharacterDatabase.Query(
            "SELECT account FROM characters WHERE name = '{}'", safeName);

        if (!charResult)
        {
            handler->PSendSysMessage("Character '{}' not found.", playerName);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 const accountId = charResult->Fetch()[0].Get<uint32>();

        uint32 const used  = s_promotionUseCounts.count(accountId) ? s_promotionUseCounts[accountId] : 0u;
        uint32 const bonus = s_promotionBonus.count(accountId) ? s_promotionBonus[accountId] : 0u;
        uint32 const allowed = 1 + bonus;
        uint32 const remaining = (used >= allowed) ? 0u : (allowed - used);

        handler->PSendSysMessage("Account {} (character '{}'): {} used / {} allowed ({} remaining).",
            accountId, playerName, used, allowed, remaining);

        if (bonus > 0)
        {
            QueryResult bonusResult = CharacterDatabase.Query(
                "SELECT bonus_count, FROM_UNIXTIME(added_at), added_by FROM mod_promotion_bonus WHERE account_id = {}",
                accountId);
            if (bonusResult)
            {
                auto const* bf       = bonusResult->Fetch();
                uint32 const count   = bf[0].Get<uint32>();
                std::string addedAt  = bf[1].Get<std::string>();
                std::string addedBy  = bf[2].Get<std::string>();
                handler->PSendSysMessage("  Bonus grants: +{} (added on {} by '{}').", count, addedAt, addedBy);
            }
        }

        QueryResult logResult = CharacterDatabase.Query(
            "SELECT character_name, FROM_UNIXTIME(timestamp) FROM mod_promotion_log WHERE account_id = {} ORDER BY timestamp",
            accountId);

        if (logResult)
        {
            do
            {
                auto const* fields    = logResult->Fetch();
                std::string claimedBy = fields[0].Get<std::string>();
                std::string claimedAt = fields[1].Get<std::string>();
                handler->PSendSysMessage("  Claimed by '{}' on {}.", claimedBy, claimedAt);
            }
            while (logResult->NextRow());
        }

        return true;
    }

    static bool HandlePromotionAdd(ChatHandler* handler, uint32 accountId, uint32 count)
    {
        if (count == 0)
        {
            handler->SendSysMessage("Usage: .promotion add <accountId> <count>");
            handler->SetSentErrorMessage(true);
            return false;
        }

        std::string gmName = handler->GetSession() ? handler->GetSession()->GetPlayer()->GetName() : "Console";
        CharacterDatabase.EscapeString(gmName);

        // DirectExecute so the DB row is committed before the in-memory counter is updated.
        // A plain async Execute could leave the DB behind on a crash, causing the bonus to vanish on next restart.
        CharacterDatabase.DirectExecute(
            "INSERT INTO mod_promotion_bonus (account_id, bonus_count, added_at, added_by) \
             VALUES ({}, {}, UNIX_TIMESTAMP(), '{}') \
             ON DUPLICATE KEY UPDATE bonus_count = bonus_count + VALUES(bonus_count), added_at = VALUES(added_at), added_by = VALUES(added_by)",
            accountId, count, gmName);

        s_promotionBonus[accountId] += count;

        handler->PSendSysMessage("Added {} bonus promotion(s) to account {}. Total bonus: {} (allowed: {}).",
            count, accountId, s_promotionBonus[accountId], 1 + s_promotionBonus[accountId]);

        LOG_INFO("module", "mod_promotion: GM {} added {} bonus promotion(s) to account {} (total bonus: {})",
            gmName, count, accountId, s_promotionBonus[accountId]);

        return true;
    }
};

// ---------------------------------------------------------------------------

class mod_promotion_conf : public WorldScript
{
public:
    mod_promotion_conf() : WorldScript("mod_promotion.conf", {
        WORLDHOOK_ON_AFTER_CONFIG_LOAD,
        WORLDHOOK_ON_STARTUP
    }) { }

    void OnStartup() override
    {
        // Load promotion use counts: account_id -> COUNT(*) from mod_promotion_log.
        s_promotionUseCounts.clear();
        QueryResult logResult = CharacterDatabase.Query(
            "SELECT account_id, COUNT(*) FROM mod_promotion_log GROUP BY account_id");
        if (logResult)
            do
            {
                auto const* fields = logResult->Fetch();
                s_promotionUseCounts[fields[0].Get<uint32>()] = fields[1].Get<uint32>();
            }
            while (logResult->NextRow());

        // Load bonus promotion grants: account_id -> bonus_count from mod_promotion_bonus.
        s_promotionBonus.clear();
        QueryResult bonusResult = CharacterDatabase.Query(
            "SELECT account_id, bonus_count FROM mod_promotion_bonus");
        if (bonusResult)
            do
            {
                auto const* fields = bonusResult->Fetch();
                s_promotionBonus[fields[0].Get<uint32>()] = fields[1].Get<uint32>();
            }
            while (bonusResult->NextRow());

        // Validate that the configured bag reward exists in the world database.
        if (s_bagEnable && s_bagId)
        {
            QueryResult bagCheck = WorldDatabase.Query(
                "SELECT 1 FROM item_template WHERE entry = {}", s_bagId);
            if (!bagCheck)
                LOG_ERROR("module", "mod_promotion: bagReward.Id {} does not exist in item_template — bags will not be granted!", s_bagId);
        }

        // Pre-build the per-family spell index used by LearnAllClassSpells.
        InitSpellCache();

        // Load talent templates from the world database.
        s_talentTemplates.clear();
        QueryResult talentResult = WorldDatabase.Query(
            "SELECT `playerSpec`, `talentId` FROM `mod_promotion_talents`");
        if (talentResult)
        {
            do
            {
                auto const* fields = talentResult->Fetch();
                std::string spec = fields[0].Get<std::string>();
                uint32 talentId = fields[1].Get<uint32>();
                s_talentTemplates[spec].push_back(talentId);
            }
            while (talentResult->NextRow());
        }

        // Warn about any configured spec that has no talent template.
        for (auto const& gs : kGearSets)
        {
            if (s_talentTemplates.find(gs.second) == s_talentTemplates.end())
                LOG_WARN("module", "mod_promotion: No talent template found for spec '{}' in `mod_promotion_talents`. "
                    "Players selecting this spec will receive unspent talent points.", gs.second);
        }
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        s_promotionEnable     = sConfigMgr->GetOption<bool>("promotionEnable.enable",      true);
        s_mountGround         = sConfigMgr->GetOption<bool>("mountGround.enable",           true);
        s_mountFlying         = sConfigMgr->GetOption<bool>("mountFlying.enable",          false);
        s_bagEnable           = sConfigMgr->GetOption<bool>("bagEnable.enable",             true);
        s_equippedbags        = sConfigMgr->GetOption<bool>("equippedbags.enable",          true);
        // Clear the join-date cache on every reload so MinAccountAge changes take effect
        // immediately without requiring a server restart.
        s_accountJoinDates.clear();

        s_teleportOnPromotion = sConfigMgr->GetOption<bool>("teleport.enable",              true);
        s_learnSpells         = sConfigMgr->GetOption<bool>("learnSpells.enable",           true);
        s_confirmationStep    = sConfigMgr->GetOption<bool>("Promotion.ConfirmationStep",  false);
        s_announceToWorld     = sConfigMgr->GetOption<bool>("Promotion.AnnounceToWorld",   false);
        s_talentTemplateEnable = sConfigMgr->GetOption<bool>("talentTemplate.enable",      true);

        s_targetLevel     = sConfigMgr->GetOption<uint32>("LevelForPromotion",           80);
        s_requiredLevel   = sConfigMgr->GetOption<uint32>("Promotion.RequiredLevel",       1);
        s_dkRequiredLevel = sConfigMgr->GetOption<uint32>("Promotion.DKRequiredLevel",    55);
        s_minAccountAge   = sConfigMgr->GetOption<uint32>("Promotion.MinAccountAge",    0);
        s_moneyReward     = sConfigMgr->GetOption<int32> ("MoneyRewardValue",    10000000);
        s_bagId           = sConfigMgr->GetOption<uint32>("bagReward.Id",           14156);

        // Clamp values to the valid WotLK level range to prevent silent overflows.
        if (s_targetLevel == 0 || s_targetLevel > 80)
        {
            LOG_ERROR("module", "mod_promotion: LevelForPromotion {} is out of range [1-80]; using 80.", s_targetLevel);
            s_targetLevel = 80;
        }
        if (s_requiredLevel == 0 || s_requiredLevel > 80)
        {
            LOG_ERROR("module", "mod_promotion: Promotion.RequiredLevel {} is out of range [1-80]; using 1.", s_requiredLevel);
            s_requiredLevel = 1;
        }
        if (s_requiredLevel >= s_targetLevel)
            LOG_WARN("module", "mod_promotion: Promotion.RequiredLevel ({}) >= LevelForPromotion ({}) — non-DK players can never claim a promotion with this config.", s_requiredLevel, s_targetLevel);
        if (s_dkRequiredLevel == 0 || s_dkRequiredLevel > 80)
        {
            LOG_ERROR("module", "mod_promotion: Promotion.DKRequiredLevel {} is out of range [1-80]; using 55.", s_dkRequiredLevel);
            s_dkRequiredLevel = 55;
        }
        if (s_dkRequiredLevel >= s_targetLevel)
            LOG_WARN("module", "mod_promotion: Promotion.DKRequiredLevel ({}) >= LevelForPromotion ({}) — Death Knights can never claim a promotion with this config.", s_dkRequiredLevel, s_targetLevel);
        if (s_dkRequiredLevel < s_requiredLevel)
            LOG_WARN("module", "mod_promotion: Promotion.DKRequiredLevel ({}) < Promotion.RequiredLevel ({}) — Death Knights can bypass the required-level gate that applies to all other classes. Set DKRequiredLevel >= RequiredLevel to close this gap.", s_dkRequiredLevel, s_requiredLevel);

        s_allianceMapId  = sConfigMgr->GetOption<uint32>("teleport.Alliance.MapId",  0);
        s_allianceAreaId = sConfigMgr->GetOption<uint32>("teleport.Alliance.AreaId", 1519); // Stormwind City
        s_allianceX      = sConfigMgr->GetOption<float> ("teleport.Alliance.X",    -8888.54f);
        s_allianceY      = sConfigMgr->GetOption<float> ("teleport.Alliance.Y",     573.119f);
        s_allianceZ      = sConfigMgr->GetOption<float> ("teleport.Alliance.Z",     92.6213f);
        s_allianceO      = sConfigMgr->GetOption<float> ("teleport.Alliance.O",     0.731558f);

        s_hordeMapId  = sConfigMgr->GetOption<uint32>("teleport.Horde.MapId",  1);
        s_hordeAreaId = sConfigMgr->GetOption<uint32>("teleport.Horde.AreaId", 1637); // Orgrimmar
        s_hordeX      = sConfigMgr->GetOption<float> ("teleport.Horde.X",      1495.47f);
        s_hordeY      = sConfigMgr->GetOption<float> ("teleport.Horde.Y",     -4415.04f);
        s_hordeZ      = sConfigMgr->GetOption<float> ("teleport.Horde.Z",      22.9895f);
        s_hordeO      = sConfigMgr->GetOption<float> ("teleport.Horde.O",      0.0894835f);

        s_groundMount[RACE_HUMAN]         = sConfigMgr->GetOption<uint32>("mountGround.Human",    470);
        s_groundMount[RACE_DWARF]         = sConfigMgr->GetOption<uint32>("mountGround.Dwarf",    6898);
        s_groundMount[RACE_NIGHTELF]      = sConfigMgr->GetOption<uint32>("mountGround.NightElf", 10789);
        s_groundMount[RACE_GNOME]         = sConfigMgr->GetOption<uint32>("mountGround.Gnome",    17453);
        s_groundMount[RACE_DRAENEI]       = sConfigMgr->GetOption<uint32>("mountGround.Draenei",  35710);
        s_groundMount[RACE_BLOODELF]      = sConfigMgr->GetOption<uint32>("mountGround.BloodElf", 33660);
        s_groundMount[RACE_ORC]           = sConfigMgr->GetOption<uint32>("mountGround.Orc",      5784);
        s_groundMount[RACE_UNDEAD_PLAYER] = sConfigMgr->GetOption<uint32>("mountGround.Undead",   17463);
        s_groundMount[RACE_TAUREN]        = sConfigMgr->GetOption<uint32>("mountGround.Tauren",   18989);
        s_groundMount[RACE_TROLL]         = sConfigMgr->GetOption<uint32>("mountGround.Troll",    10796);

        s_flyingMount[RACE_HUMAN]         = sConfigMgr->GetOption<uint32>("mountFlying.Human",    34767);
        s_flyingMount[RACE_DWARF]         = sConfigMgr->GetOption<uint32>("mountFlying.Dwarf",    34769);
        s_flyingMount[RACE_NIGHTELF]      = sConfigMgr->GetOption<uint32>("mountFlying.NightElf", 41513);
        s_flyingMount[RACE_GNOME]         = sConfigMgr->GetOption<uint32>("mountFlying.Gnome",    34768);
        s_flyingMount[RACE_DRAENEI]       = sConfigMgr->GetOption<uint32>("mountFlying.Draenei",  34769);
        s_flyingMount[RACE_BLOODELF]      = sConfigMgr->GetOption<uint32>("mountFlying.BloodElf", 40192);
        s_flyingMount[RACE_ORC]           = sConfigMgr->GetOption<uint32>("mountFlying.Orc",      40193);
        s_flyingMount[RACE_UNDEAD_PLAYER] = sConfigMgr->GetOption<uint32>("mountFlying.Undead",   40194);
        s_flyingMount[RACE_TAUREN]        = sConfigMgr->GetOption<uint32>("mountFlying.Tauren",   40195);
        s_flyingMount[RACE_TROLL]         = sConfigMgr->GetOption<uint32>("mountFlying.Troll",    40192);

        // Pre-load all gear set items from config to avoid string construction during promotion.
        s_gearItems.clear();
        for (auto const& gs : kGearSets)
        {
            std::array<uint32, kEquipSlotCount> items{};
            for (size_t i = 0; i < kEquipSlotCount; ++i)
            {
                std::string const key = std::string("EQUIPMENT_SLOT_") + gs.second + "_" + kEquipSlots[i].second;
                items[i] = sConfigMgr->GetOption<uint32>(key, 0);
            }
            s_gearItems[gs.second] = items;
        }
    }
};

void AddSC_npc_promotion()
{
    new npc_promotion();
    new mod_promotion_conf();
    new cmd_promotion();
}
