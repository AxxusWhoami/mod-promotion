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
#include <algorithm>
#include <unordered_set>

static bool promotionEnable;
static bool mountGround;
static bool mountFlying;
static bool bagEnable;
static bool equippedbags;
static bool learnSpells;
static bool teleportOnPromotion;

// Accounts that have already claimed their promotion (loaded at startup).
// All gossip handling runs on the world thread — no mutex needed.
static std::unordered_set<uint32> s_promotedAccounts;

class npc_promotion : public CreatureScript
{
public:
    npc_promotion() : CreatureScript("npc_promotion") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (!promotionEnable)
        {
            SendGossipMenuFor(player, 80000, creature);
            return true;
        }

        bool const isModerator = player->GetSession()->GetSecurity() >= SEC_MODERATOR;
        bool const isDK        = player->getClass() == CLASS_DEATH_KNIGHT;
        uint8 const startLevel = isDK ? 55 : 1;

        if (!isModerator && player->GetLevel() != startLevel)
        {
            SendGossipMenuFor(player, 68, creature);
            return true;
        }

        if (!isModerator && HasUsedPromotion(player->GetSession()->GetAccountId()))
        {
            SendGossipMenuFor(player, 80001, creature);
            return true;
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
        SendGossipMenuFor(player, 68, creature);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);

        if (!promotionEnable)
        {
            SendGossipMenuFor(player, 80000, creature);
            return true;
        }

        bool const isModerator = player->GetSession()->GetSecurity() >= SEC_MODERATOR;

        if (!isModerator && HasUsedPromotion(player->GetSession()->GetAccountId()))
        {
            SendGossipMenuFor(player, 80001, creature);
            return true;
        }

        // Reject actions that don't belong to the player's class.
        if (!IsValidActionForClass(player->getClass(), action))
        {
            CloseGossipMenuFor(player);
            return true;
        }

        uint32 const targetLevel = sConfigMgr->GetOption<uint32>("LevelForPromotion", 80);
        player->SetLevel(targetLevel);
        player->InitStatsForLevel(true);
        player->InitTaxiNodesForLevel();
        player->InitGlyphsForLevel();
        player->InitTalentForLevel();
        player->SetUInt32Value(PLAYER_XP, 0);

        player->ModifyMoney(sConfigMgr->GetOption<int32>("MoneyRewardValue", 10000000));
        player->UpdateSkillsToMaxSkillsForLevel();

        if (learnSpells)
            LearnAllClassSpells(player);

        player->learnSpell(SKILL_RIDING_75);
        player->learnSpell(SKILL_RIDING_100);
        player->learnSpell(SKILL_RIDING_FLYING);
        player->learnSpell(SKILL_RIDING_ARTISING);

        creature->Whisper("¡Felicidades! Tu Promocion ha sido concedida.", LANG_UNIVERSAL, player);

        if (mountGround)
        {
            uint32 groundMount = 0;
            switch (player->getRace())
            {
                case RACE_HUMAN:         groundMount = sConfigMgr->GetOption<uint32>("mountGround.Human",    470);   break;
                case RACE_DWARF:         groundMount = sConfigMgr->GetOption<uint32>("mountGround.Dwarf",    6898);  break;
                case RACE_NIGHTELF:      groundMount = sConfigMgr->GetOption<uint32>("mountGround.NightElf", 10789); break;
                case RACE_GNOME:         groundMount = sConfigMgr->GetOption<uint32>("mountGround.Gnome",    17453); break;
                case RACE_DRAENEI:       groundMount = sConfigMgr->GetOption<uint32>("mountGround.Draenei",  35710); break;
                case RACE_BLOODELF:      groundMount = sConfigMgr->GetOption<uint32>("mountGround.BloodElf", 33660); break;
                case RACE_ORC:           groundMount = sConfigMgr->GetOption<uint32>("mountGround.Orc",      5784);  break;
                case RACE_UNDEAD_PLAYER: groundMount = sConfigMgr->GetOption<uint32>("mountGround.Undead",   17463); break;
                case RACE_TAUREN:        groundMount = sConfigMgr->GetOption<uint32>("mountGround.Tauren",   18989); break;
                case RACE_TROLL:         groundMount = sConfigMgr->GetOption<uint32>("mountGround.Troll",    10796); break;
                default: break;
            }
            if (groundMount)
                player->learnSpell(groundMount);
        }

        if (mountFlying)
        {
            uint32 flyingMount = 0;
            switch (player->getRace())
            {
                case RACE_HUMAN:         flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Human",    34767); break;
                case RACE_DWARF:         flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Dwarf",    34769); break;
                case RACE_NIGHTELF:      flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.NightElf", 41513); break;
                case RACE_GNOME:         flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Gnome",    34768); break;
                case RACE_DRAENEI:       flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Draenei",  34769); break;
                case RACE_BLOODELF:      flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.BloodElf", 40192); break;
                case RACE_ORC:           flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Orc",      40193); break;
                case RACE_UNDEAD_PLAYER: flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Undead",   40194); break;
                case RACE_TAUREN:        flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Tauren",   40195); break;
                case RACE_TROLL:         flyingMount = sConfigMgr->GetOption<uint32>("mountFlying.Troll",    40192); break;
                default: break;
            }
            if (flyingMount)
                player->learnSpell(flyingMount);
        }

        if (bagEnable)
        {
            uint32 const bagId = sConfigMgr->GetOption<uint32>("bagReward.Id", 14156);
            if (equippedbags)
            {
                for (int slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
                    if (Item* bag = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                        player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);

                for (int slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
                    player->EquipNewItem(slot, bagId, true);
            }
            else
                player->AddItem(bagId, 4);
        }

        static const std::pair<uint32, const char*> kGearSets[] = {
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

        for (auto const& gs : kGearSets)
        {
            if (action == gs.first)
            {
                EquipGearSet(player, gs.second);
                break;
            }
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

        if (teleportOnPromotion)
        {
            if (player->GetTeamId() == TEAM_ALLIANCE)
                player->TeleportTo(0, -8888.54f, 573.119f, 92.6213f, 0.731558f);
            else
                player->TeleportTo(1, 1136.16f, -4385.84f, 30.2056f, 3.06327f);
        }

        CloseGossipMenuFor(player);
        return true;
    }

private:
    static bool HasUsedPromotion(uint32 accountId)
    {
        return s_promotedAccounts.count(accountId) > 0;
    }

    static bool IsValidActionForClass(uint8 cls, uint32 action)
    {
        static const std::unordered_map<uint8, std::vector<uint32>> kClassActions = {
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

    static void EquipGearSet(Player* player, std::string const& prefix)
    {
        static const std::pair<EquipmentSlots, const char*> kSlots[] = {
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

        for (auto const& s : kSlots)
        {
            std::string const key = "EQUIPMENT_SLOT_" + prefix + "_" + s.second;
            uint32 const itemId = sConfigMgr->GetOption<uint32>(key, 0);
            if (itemId)
                player->EquipNewItem(s.first, itemId, true);
        }
    }
};

class mod_promotion_conf : public WorldScript
{
public:
    mod_promotion_conf() : WorldScript("mod_promotion.conf", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD,
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

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        promotionEnable     = sConfigMgr->GetOption<bool>("promotionEnable.enable", true);
        mountGround         = sConfigMgr->GetOption<bool>("mountGround.enable",     true);
        mountFlying         = sConfigMgr->GetOption<bool>("mountFlying.enable",     false);
        bagEnable           = sConfigMgr->GetOption<bool>("bagEnable.enable",       true);
        equippedbags        = sConfigMgr->GetOption<bool>("equippedbags.enable",    true);
        teleportOnPromotion = sConfigMgr->GetOption<bool>("teleport.enable",        true);
        learnSpells         = sConfigMgr->GetOption<bool>("learnSpells.enable",     true);
    }
};

void AddSC_npc_promotion()
{
    new npc_promotion();
    new mod_promotion_conf();
}
