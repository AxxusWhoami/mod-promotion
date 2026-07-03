/**
    Nefertumm and Stevej
    https://github.com/Nefertumm/
    https://github.com/pangolp
    https://github.com/Asmadeuxx
 */

#include "Chat.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "GossipDef.h"
#include "Language.h"
#include "LearnClassSpells.h"
#include "mod_promotion.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "World.h"
#include "WorldSession.h"
#ifdef MODULE_PLAYERBOTS
#include "PlayerbotAI.h"
#endif
#include <algorithm>
#include <array>
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
static constexpr size_t kEquipSlotCount = 17;

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

static uint32 s_targetLevel;
static int32  s_moneyReward;
static uint32 s_bagId;

static uint32 s_allianceMapId;
static float  s_allianceX, s_allianceY, s_allianceZ, s_allianceO;
static uint32 s_hordeMapId;
static float  s_hordeX, s_hordeY, s_hordeZ, s_hordeO;

// Indexed by RACE_* constants (max value = RACE_DRAENEI = 11). Index 0 and 9 are unused.
static uint32 s_groundMount[12];
static uint32 s_flyingMount[12];

// Pre-loaded gear items: config prefix -> per-slot item IDs (parallel to kEquipSlots).
static std::unordered_map<std::string, std::array<uint32, kEquipSlotCount>> s_gearItems;

// ---------------------------------------------------------------------------
// Runtime state
// ---------------------------------------------------------------------------

// Accounts that have already claimed their promotion (loaded at startup).
// All gossip handling runs on the world thread — no mutex needed.
static std::unordered_set<uint32> s_promotedAccounts;

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
            case PromotionCheck::Ok:          break;
        }

        // Reject actions that don't belong to the player's class.
        if (!IsValidActionForClass(player->getClass(), action))
        {
            CloseGossipMenuFor(player);
            return true;
        }

        player->SetLevel(s_targetLevel);
        player->InitStatsForLevel(true);
        player->InitTaxiNodesForLevel();
        player->InitGlyphsForLevel();
        player->InitTalentForLevel();
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
            uint8 const race  = player->getRace();
            uint32 const spell = (race < std::size(s_groundMount)) ? s_groundMount[race] : 0;
            if (spell)
                player->learnSpell(spell);
        }

        if (s_mountFlying)
        {
            uint8 const race  = player->getRace();
            uint32 const spell = (race < std::size(s_flyingMount)) ? s_flyingMount[race] : 0;
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

        if (!isModerator)
        {
            uint32 const accountId = player->GetSession()->GetAccountId();
            CharacterDatabase.Execute(
                "INSERT IGNORE INTO mod_promotion_log (account_id, character_guid, timestamp) VALUES ({}, {}, UNIX_TIMESTAMP())",
                accountId,
                player->GetGUID().GetCounter());
            s_promotedAccounts.insert(accountId);
        }

        if (s_teleportOnPromotion)
        {
            if (player->GetTeamId() == TEAM_ALLIANCE)
                player->TeleportTo(s_allianceMapId, s_allianceX, s_allianceY, s_allianceZ, s_allianceO);
            else
                player->TeleportTo(s_hordeMapId, s_hordeX, s_hordeY, s_hordeZ, s_hordeO);
        }

        player->SaveToDB();
        CloseGossipMenuFor(player);
        return true;
    }

private:
    enum class PromotionCheck { Ok, Disabled, WrongLevel, AlreadyUsed };

    static PromotionCheck CheckEligibility(Player* player, bool isModerator)
    {
        if (!s_promotionEnable)
            return PromotionCheck::Disabled;
        if (isModerator)
            return PromotionCheck::Ok;

        bool const isDK = player->getClass() == CLASS_DEATH_KNIGHT;
        if (player->GetLevel() != (isDK ? 55u : 1u))
            return PromotionCheck::WrongLevel;

        if (HasUsedPromotion(player->GetSession()->GetAccountId()))
            return PromotionCheck::AlreadyUsed;

        return PromotionCheck::Ok;
    }

    static bool HasUsedPromotion(uint32 accountId)
    {
        return s_promotedAccounts.count(accountId) > 0;
    }

    static bool IsValidActionForClass(uint8 cls, uint32 action)
    {
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
        auto it = kClassActions.find(cls);
        if (it == kClassActions.end())
            return false;
        return std::find(it->second.begin(), it->second.end(), action) != it->second.end();
    }

    // Equips the pre-loaded gear set for the given config prefix.
    // Whispers the player if any slot could not be filled (e.g. Unique-Equipped conflict).
    static void EquipGearSet(Player* player, Creature* creature, const char* prefix)
    {
        auto it = s_gearItems.find(prefix);
        if (it == s_gearItems.end())
            return;

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

class mod_promotion_conf : public WorldScript
{
public:
    mod_promotion_conf() : WorldScript("mod_promotion.conf", {
        WORLDHOOK_ON_AFTER_CONFIG_LOAD,
        WORLDHOOK_ON_STARTUP
    }) { }

    void OnStartup() override
    {
        // Populate the in-memory set from existing log rows.
        QueryResult result = CharacterDatabase.Query(
            "SELECT DISTINCT account_id FROM mod_promotion_log");
        if (result)
            do { s_promotedAccounts.insert(result->Fetch()[0].Get<uint32>()); }
            while (result->NextRow());

        // Pre-build the per-family spell index used by LearnAllClassSpells.
        InitSpellCache();
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        s_promotionEnable     = sConfigMgr->GetOption<bool>("promotionEnable.enable", true);
        s_mountGround         = sConfigMgr->GetOption<bool>("mountGround.enable",     true);
        s_mountFlying         = sConfigMgr->GetOption<bool>("mountFlying.enable",     false);
        s_bagEnable           = sConfigMgr->GetOption<bool>("bagEnable.enable",       true);
        s_equippedbags        = sConfigMgr->GetOption<bool>("equippedbags.enable",    true);
        s_teleportOnPromotion = sConfigMgr->GetOption<bool>("teleport.enable",        true);
        s_learnSpells         = sConfigMgr->GetOption<bool>("learnSpells.enable",     true);

        s_targetLevel = sConfigMgr->GetOption<uint32>("LevelForPromotion", 80);
        s_moneyReward = sConfigMgr->GetOption<int32> ("MoneyRewardValue",  10000000);
        s_bagId       = sConfigMgr->GetOption<uint32>("bagReward.Id",      14156);

        s_allianceMapId = sConfigMgr->GetOption<uint32>("teleport.Alliance.MapId", 0);
        s_allianceX     = sConfigMgr->GetOption<float> ("teleport.Alliance.X",    -8888.54f);
        s_allianceY     = sConfigMgr->GetOption<float> ("teleport.Alliance.Y",     573.119f);
        s_allianceZ     = sConfigMgr->GetOption<float> ("teleport.Alliance.Z",     92.6213f);
        s_allianceO     = sConfigMgr->GetOption<float> ("teleport.Alliance.O",     0.731558f);

        s_hordeMapId = sConfigMgr->GetOption<uint32>("teleport.Horde.MapId",  1);
        s_hordeX     = sConfigMgr->GetOption<float> ("teleport.Horde.X",      1136.16f);
        s_hordeY     = sConfigMgr->GetOption<float> ("teleport.Horde.Y",     -4385.84f);
        s_hordeZ     = sConfigMgr->GetOption<float> ("teleport.Horde.Z",      30.2056f);
        s_hordeO     = sConfigMgr->GetOption<float> ("teleport.Horde.O",      3.06327f);

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
}
