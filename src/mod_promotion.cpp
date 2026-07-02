/**
 * This plugin can be used for common player customizations
*/

#include "Chat.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "GossipDef.h"
#include "Language.h"
#include "mod_promotion.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "World.h"
#include "WorldSession.h"

static bool promotionEnable, mountEnable, bagEnable, equippedbags;
static int promotionCount, moneyRewardConst, mountPromotion, bagReward;
static int classConfArmor, LevelForPromotion;

class npc_promotion : public CreatureScript
{
public:
    npc_promotion() : CreatureScript("npc_promotion") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->getClass() == CLASS_DEATH_KNIGHT)
            return true;

        if (player->GetLevel() != 1)
        {
            if (player && creature)
                SendGossipMenuFor(player, 68, creature);
            return true;
        }

        switch (player->getClass())
        {
        case CLASS_WARRIOR:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Furia", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Tanque - Proteccion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Furia", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Tanque - Proteccion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
            break;
        case CLASS_WARLOCK:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Destruccion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Destruccion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            break;
        case CLASS_DRUID:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Tanque - Guardian", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Healer - Restauracion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Equilibrio", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Tanque - Guardian", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Healer - Restauracion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Equilibrio", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
            break;
        case CLASS_HUNTER:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Punteria", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Supervivencia", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
            break;
        case CLASS_MAGE:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Escarcha", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Arcano", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
            break;
        case CLASS_ROGUE:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Sutileza", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Combate", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
            break;
        case CLASS_PRIEST:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Healer - Disciplina", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Sombras", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Healer - Sagrado", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Sombras", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
            break;
        case CLASS_PALADIN:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Tanque - Proteccion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Healer - Sagrado", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Retribucion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Tanque - Proteccion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Healer - Sagrado", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Retribucion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            break;
        case CLASS_SHAMAN:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Elemental", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP Healer - Restauracion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvP DPS - Mejora", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Elemental", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE Healer - Restauracion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "PvE DPS - Mejora", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
            break;
        default:
            break;
        }
        SendGossipMenuFor(player, 68, creature);
        return true;
    }

    void MoneyReward(Player* player)
    {
        player->ModifyMoney(sConfigMgr->GetOption<uint32>("MoneyRewardValue", 10000000));
    }

    void WarriorPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_HEAD", 41350)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_SHOULDERS", 41351)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_CHEST", 41353)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_WAIST", 41352)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_LEGS", 41347)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_FEET", 41348)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_WRISTS", 41354)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_HANDS", 41349)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_MAINHAND", 37108)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_OFFHAND", 36962)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_RANGED", 36981)), true);
    }

    void WarriorPromotionTank(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_HEAD", 41350)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_SHOULDERS", 41351)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_CHEST", 41353)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_WAIST", 41352)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_LEGS", 41347)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_FEET", 41348)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_WRISTS", 41354)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_HANDS", 41349)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_TRINKET1", 36993)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_MAINHAND", 36984)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_OFFHAND", 37107)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_RANGED", 36981)), true);
    }

    void PaladinPromotionTank(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_HEAD", 41350)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_SHOULDERS", 41351)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_CHEST", 41353)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_WAIST", 41352)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_LEGS", 41347)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_FEET", 41348)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_WRISTS", 41354)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_HANDS", 41349)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_TRINKET1", 36993)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_MAINHAND", 36984)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_OFFHAND", 37107)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_RANGED", 38363)), true);
    }

    void PaladinPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_HEAD", 42728)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_SHOULDERS", 42727)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_CHEST", 42725)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_WAIST", 42729)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_LEGS", 42726)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_FEET", 42730)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_WRISTS", 42723)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_HANDS", 42724)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_TRINKET1", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_TRINKET2", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_MAINHAND", 37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_OFFHAND", 37061)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_RANGED", 38364)), true);
    }

    void PaladinPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_HEAD", 41350)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_SHOULDERS", 41351)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_CHEST", 41353)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_WAIST", 41352)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_LEGS", 41347)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_FEET", 41348)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_WRISTS", 41354)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_HANDS", 41349)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_MAINHAND", 37108)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_RANGED", 38362)), true);
    }

    void HunterPromotion(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_HEAD", 43447)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_SHOULDERS", 43449)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_CHEST", 43445)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_WAIST", 43442)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_LEGS", 43448)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_FEET", 43443)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_WRISTS", 43444)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_HANDS", 43446)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_MAINHAND", 36980)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_RANGED", 37050)), true);
    }

    void RoguePromotion(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_HEAD", 43260)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_SHOULDERS", 43433)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_CHEST", 43434)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_WAIST", 43437)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_LEGS", 43438)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_FEET", 43439)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_WRISTS", 43435)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_HANDS", 43436)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_MAINHAND", 36944)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_OFFHAND", 37037)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_RANGED", 36981)), true);
    }

    void PriestPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_HEAD", 43971)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_SHOULDERS", 43973)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_CHEST", 43972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_WAIST", 43969)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_LEGS", 43975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_FEET", 43970)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_WRISTS", 43974)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_HANDS", 41516)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_MAINHAND", 36975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_RANGED", 37038)), true);
    }

    void PriestPromotionShadow(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_HEAD", 43971)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_SHOULDERS", 43973)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_CHEST", 43972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_WAIST", 43969)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_LEGS", 43975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_FEET", 43970)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_WRISTS", 43974)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_HANDS", 41516)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_TRINKET2", 38358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_MAINHAND", 36975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_RANGED", 37038)), true);

    }

    void ShamanPromotionCaster(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_HEAD", 43455)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_SHOULDERS", 43457)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_CHEST", 43453)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_WAIST", 43450)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_LEGS", 43456)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_FEET", 43451)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_WRISTS", 43452)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_HANDS", 43454)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_TRINKET2", 38358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_MAINHAND", 37112)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_OFFHAND", 37061)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_RANGED", 38361)), true);
    }

    void ShamanPromotionMelee(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_HEAD", 43447)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_SHOULDERS", 43449)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_CHEST", 43445)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_WAIST", 43442)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_LEGS", 43448)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_FEET", 43443)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_WRISTS", 43444)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_HANDS", 43446)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_MAINHAND", 35630)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_OFFHAND", 36944)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_RANGED", 38367)), true);
    }

    void ShamanPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_HEAD", 43455)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_SHOULDERS", 43457)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_CHEST", 43453)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_WAIST", 43450)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_LEGS", 43456)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_FEET", 43451)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_WRISTS", 43452)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_HANDS", 43454)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_MAINHAND", 37112)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_OFFHAND", 37061)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_RANGED", 38368)), true);
    }

    void MagePromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_HEAD", 43971)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_SHOULDERS", 43973)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_CHEST", 43972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_WAIST", 43969)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_LEGS", 43975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_FEET", 43970)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_WRISTS", 43974)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_HANDS", 41516)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_TRINKET2", 38358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_MAINHAND", 36975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_RANGED", 37038)), true);

    }

    void WarlockPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_HEAD", 43971)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_SHOULDERS", 43973)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_CHEST", 43972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_WAIST", 43969)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_LEGS", 43975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_FEET", 43970)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_WRISTS", 43974)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_HANDS", 41516)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_TRINKET2", 38358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_MAINHAND", 36975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_RANGED", 37038)), true);
    }

    void DruidPromotionTank(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_HEAD", 43260)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_SHOULDERS", 43433)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_CHEST", 43434)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_WAIST", 43437)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_LEGS", 43438)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_FEET", 43439)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_WRISTS", 43435)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_HANDS", 43436)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_MAINHAND", 36980)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_RANGED", 38365)), true);
    }

    void DruidPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_HEAD", 43261)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_SHOULDERS", 43262)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_CHEST", 43263)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_WAIST", 43266)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_LEGS", 43271)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_FEET", 43273)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_WRISTS", 43264)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_HANDS", 43265)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_MAINHAND", 36975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_RANGED", 38366)), true);
    }

    void DruidPromotionMelee(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_HEAD", 43260)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_NECK", 45812)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_SHOULDERS", 43433)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_CHEST", 43434)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_WAIST", 43437)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_LEGS", 43438)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_FEET", 43439)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_WRISTS", 43435)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_HANDS", 43436)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_FINGER1", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_FINGER2", 45809)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_TRINKET1", 37064)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_TRINKET2", 38359)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_BACK", 45811)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_MAINHAND", 36980)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_RANGED", 38365)), true);
    }

    void DruidPromotionCaster(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_HEAD", 43261)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_NECK", 45813)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_SHOULDERS", 43262)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_CHEST", 43263)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_WAIST", 43266)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_LEGS", 43271)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_FEET", 43273)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_WRISTS", 43264)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_HANDS", 43265)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_FINGER1", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_FINGER2", 45808)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_TRINKET1", 36972)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_TRINKET2", 38358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_BACK", 45810)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_MAINHAND", 36975)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED, (sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_RANGED", 38360)), true);
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        uint32 accountID = player->GetSession()->GetAccountId();
        QueryResult result = CharacterDatabase.Query("SELECT COUNT(`guid`) FROM `characters` WHERE `account`={}", accountID);
        Field* fields = result->Fetch();
        uint32 pjts = fields[0].Get<uint32>();

        ClearGossipMenuFor(player);

        if (promotionEnable && ((int)pjts <= promotionCount || player->GetSession()->GetSecurity() >= SEC_MODERATOR))
        {
            if (action > GOSSIP_ACTION_INFO_DEF && action <= 1034)
            {
                uint32 targetLevel = sConfigMgr->GetOption<uint32>("LevelForPromotion", 80);
                // Use SetLevel to avoid triggering "First in the Realm" achievements
                player->SetLevel(targetLevel);
                player->InitStatsForLevel(true);
                player->InitTaxiNodesForLevel();
                player->InitGlyphsForLevel();
                player->InitTalentForLevel();
                player->SetUInt32Value(PLAYER_XP, 0);
            }

            //Money 2,5k
            MoneyReward(player);

             // Skill Max
            player->UpdateSkillsToMaxSkillsForLevel();

            // Riding
            player->learnSpell(SKILL_RIDING_75);
            player->learnSpell(SKILL_RIDING_100);
            player->learnSpell(SKILL_RIDING_FLYING);
            player->learnSpell(SKILL_RIDING_ARTISING);

            creature->Whisper("You Got Your Promotion!", LANG_UNIVERSAL, player);

            if (mountEnable)
                player->learnSpell(sConfigMgr->GetOption<uint32>("mountPromotion", 42777)); //Swift Spectral Tiger
        
            //Bags
            if (bagEnable)
            {
                if (equippedbags)
                {
                    for (int slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; slot++)
                        if (Item* bag = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                            player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);

                    for (int slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; slot++)
                        player->EquipNewItem(slot, (sConfigMgr->GetOption<uint32>("bagReward.Id", 14156)), true);
                }
                else
                    player->AddItem((sConfigMgr->GetOption<uint32>("bagReward.Id", 14156)), 4);
            }

            switch (action)
            {
                case 1001:
                    WarriorPromotionDps(player);
                    break;
                case 1002: 
                    WarriorPromotionTank(player);
                    break;
                case 1003:
                    WarlockPromotionDps(player);
                    break;
                case 1004:
                    DruidPromotionTank(player);
                    break;
                case 1005:
                    DruidPromotionHeal(player);
                    break;
                case 1006:
                    DruidPromotionCaster(player);
                    break;
                case 1007:
                    HunterPromotion(player);
                    break;
                case 1008:
                    MagePromotionDps(player);
                    break;
                case 1009:
                    RoguePromotion(player);
                    break;
                case 1010:
                    PriestPromotionHeal(player);
                    break;
                case 1011:
                    PriestPromotionShadow(player);
                    break;
                case 1012:
                    PaladinPromotionTank(player);
                    break;
                case 1013:
                    PaladinPromotionHeal(player);
                    break;
                case 1014:
                    PaladinPromotionDps(player);
                    break;
                case 1015:
                    ShamanPromotionCaster(player);
                    break;
                case 1016:
                    ShamanPromotionHeal(player);
                    break;
                case 1017:
                    ShamanPromotionMelee(player);
                    break;
                case 1018:
                    WarriorPvEPromotionDps(player);
                    break;
                case 1019:
                    WarriorPvEPromotionTank(player);
                    break;
                case 1020:
                    WarlockPvEPromotionDps(player);
                    break;
                case 1021:
                    DruidPvEPromotionTank(player);
                    break;
                case 1022:
                    DruidPvEPromotionHeal(player);
                    break;
                case 1023:
                    DruidPvEPromotionBalance(player);
                    break;
                case 1024:
                    HunterPvEPromotion(player);
                    break;
                case 1025:
                    MagePvEPromotionDps(player);
                    break;
                case 1026:
                    RoguePvEPromotion(player);
                    break;
                case 1027:
                    PriestPvEPromotionHeal(player);
                    break;
                case 1028:
                    PriestPvEPromotionShadow(player);
                    break;
                case 1029:
                    PaladinPvEPromotionTank(player);
                    break;
                case 1030:
                    PaladinPvEPromotionHeal(player);
                    break;
                case 1031:
                    PaladinPvEPromotionDps(player);
                    break;
                case 1032:
                    ShamanPvEPromotionElemental(player);
                    break;
                case 1033:
                    ShamanPvEPromotionResto(player);
                    break;
                case 1034:
                    ShamanPvEPromotionEnhancement(player);
                    break;
                default:
                    break;
            }

            if (player->GetTeamId() == TEAM_ALLIANCE)
                player->TeleportTo(0, -8888.54f, 573.119f, 92.6213f, 0.731558f);
            else
                player->TeleportTo(1, 1136.16f, -4385.84f, 30.2056f, 3.06327f);
        }
        else
            SendGossipMenuFor(player, 80000, creature);

        return true;
    }

    // ==================== PvE PROMOTION FUNCTIONS ====================

    // --- WARRIOR PvE ---

    void WarriorPvEPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_HEAD",     37237)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_NECK",     37397)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_SHOULDERS",37814)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_BACK",     37647)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_CHEST",    37612)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_WRISTS",   37853)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_HANDS",    37363)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_WAIST",    37171)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_LEGS",     37193)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_FEET",     37150)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_FINGER1",  37642)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_FINGER2",  37151)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_TRINKET1", 37166)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_MAINHAND", 37852)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_OFFHAND",  36962)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_RANGED",   36981)), true);
    }

    void WarriorPvEPromotionTank(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_HEAD",     37633)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_NECK",     43282)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_SHOULDERS",37814)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_BACK",     37728)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_CHEST",    37658)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_WRISTS",   37620)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_HANDS",    37645)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_WAIST",    37241)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_LEGS",     43500)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_FEET",     37082)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_FINGER1",  37784)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_FINGER2",  37186)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_TRINKET1", 37220)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_TRINKET2", 36993)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_MAINHAND", 37401)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_OFFHAND",  43085)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_RANGED",   36981)), true);
    }

    // --- WARLOCK PvE ---

    void WarlockPvEPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_HEAD",     37109)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_BACK",     37667)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_CHEST",    37189)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_MAINHAND", 37234)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_OFFHAND",  37134)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_RANGED",   37038)), true);
    }

    // --- DRUID PvE ---

    void DruidPvEPromotionTank(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_HEAD",     37298)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_NECK",     43282)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_SHOULDERS",37647)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_BACK",     37735)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_CHEST",    37290)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_WRISTS",   37311)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_HANDS",    37362)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_WAIST",    37241)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_LEGS",     37309)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_FEET",     37310)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_FINGER1",  37784)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_FINGER2",  37186)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_TRINKET1", 37220)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_TRINKET2", 36993)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_MAINHAND", 37574)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_RANGED",   38365)), true);
    }

    void DruidPvEPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_HEAD",     37295)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_BACK",     37735)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_CHEST",    37291)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_MAINHAND", 37234)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_OFFHAND",  37718)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_RANGED",   38366)), true);
    }

    void DruidPvEPromotionBalance(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_HEAD",     37295)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_BACK",     37667)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_CHEST",    37291)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_MAINHAND", 37234)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_OFFHAND",  37134)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_RANGED",   38360)), true);
    }

    // --- HUNTER PvE ---

    void HunterPvEPromotion(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_HUNTER_HEAD",     37168)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_HUNTER_NECK",     37397)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_HUNTER_SHOULDERS",37301)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_HUNTER_BACK",     37647)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_HUNTER_CHEST",    37219)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_HUNTER_WRISTS",   37367)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_HUNTER_HANDS",    37302)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_HUNTER_WAIST",    37371)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_HUNTER_LEGS",     37218)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_HUNTER_FEET",     37303)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_HUNTER_FINGER1",  37642)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_HUNTER_FINGER2",  37151)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_HUNTER_TRINKET1", 37166)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_HUNTER_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_HUNTER_MAINHAND", 37574)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_HUNTER_RANGED",   37050)), true);
    }

    // --- MAGE PvE ---

    void MagePvEPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_HEAD",     37109)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_BACK",     37667)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_CHEST",    37189)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_MAINHAND", 37234)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_OFFHAND",  37134)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_RANGED",   37038)), true);
    }

    // --- ROGUE PvE ---

    void RoguePvEPromotion(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_ROGUE_HEAD",     37298)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_ROGUE_NECK",     37397)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_ROGUE_SHOULDERS",37301)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_ROGUE_BACK",     37647)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_ROGUE_CHEST",    37290)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_ROGUE_WRISTS",   37311)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_ROGUE_HANDS",    37302)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_ROGUE_WAIST",    37171)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_ROGUE_LEGS",     37193)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_ROGUE_FEET",     37303)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_ROGUE_FINGER1",  37642)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_ROGUE_FINGER2",  37151)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_ROGUE_TRINKET1", 37166)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_ROGUE_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_ROGUE_MAINHAND", 37852)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_ROGUE_OFFHAND",  37037)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_ROGUE_RANGED",   36981)), true);
    }

    // --- PRIEST PvE ---

    void PriestPvEPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_HEAD",     37109)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_BACK",     37735)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_CHEST",    37189)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_MAINHAND", 37234)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_OFFHAND",  37718)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_RANGED",   37038)), true);
    }

    void PriestPvEPromotionShadow(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_HEAD",     37109)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_BACK",     37667)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_CHEST",    37189)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_MAINHAND", 37234)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_OFFHAND",  37134)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_RANGED",   37038)), true);
    }

    // --- PALADIN PvE ---

    void PaladinPvEPromotionTank(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_HEAD",     37633)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_NECK",     43282)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_SHOULDERS",37814)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_BACK",     37728)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_CHEST",    37658)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_WRISTS",   37620)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_HANDS",    37645)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_WAIST",    37241)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_LEGS",     43500)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_FEET",     37082)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_FINGER1",  37784)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_FINGER2",  37186)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_TRINKET1", 37220)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_TRINKET2", 36993)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_MAINHAND", 37401)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_OFFHAND",  43085)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_RANGED",   38363)), true);
    }

    void PaladinPvEPromotionHeal(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_HEAD",     37295)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_BACK",     37735)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_CHEST",    37291)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_MAINHAND", 37401)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_OFFHAND",  37061)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_RANGED",   38364)), true);
    }

    void PaladinPvEPromotionDps(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_HEAD",     37237)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_NECK",     37397)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_SHOULDERS",37814)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_BACK",     37647)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_CHEST",    37612)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_WRISTS",   37853)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_HANDS",    37363)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_WAIST",    37241)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_LEGS",     43500)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_FEET",     37150)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_FINGER1",  37642)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_FINGER2",  37151)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_TRINKET1", 37166)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_MAINHAND", 37852)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_RANGED",   38362)), true);
    }

    // --- SHAMAN PvE ---

    void ShamanPvEPromotionElemental(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_HEAD",     37215)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_BACK",     37667)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_CHEST",    37217)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_MAINHAND", 37112)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_OFFHAND",  37134)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_RANGED",   38361)), true);
    }

    void ShamanPvEPromotionResto(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_HEAD",     37215)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_NECK",     37179)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_SHOULDERS",37357)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_BACK",     37735)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_CHEST",    37217)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_WRISTS",   37230)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_HANDS",    37358)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_WAIST",    37060)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_LEGS",     37360)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_FEET",     37361)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_FINGER1",  37182)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_FINGER2",  37624)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_TRINKET1", 37559)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_TRINKET2", 37111)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_MAINHAND", 37112)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_OFFHAND",  37718)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_RANGED",   38368)), true);
    }

    void ShamanPvEPromotionEnhancement(Player* player)
    {
        player->EquipNewItem(EQUIPMENT_SLOT_HEAD,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_HEAD",     37168)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_NECK,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_NECK",     37397)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_SHOULDERS",37301)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_BACK,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_BACK",     37647)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_CHEST,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_CHEST",    37219)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WRISTS,    (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_WRISTS",   37367)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_HANDS,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_HANDS",    37302)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_WAIST,     (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_WAIST",    37371)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_LEGS,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_LEGS",     37218)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FEET,      (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_FEET",     37303)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER1,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_FINGER1",  37642)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_FINGER2,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_FINGER2",  37151)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_TRINKET1", 37166)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_TRINKET2", 37390)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND,  (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_MAINHAND", 37852)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND,   (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_OFFHAND",  37037)), true);
        player->EquipNewItem(EQUIPMENT_SLOT_RANGED,    (sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_RANGED",   38367)), true);
    }
};

class mod_promotion_conf : public WorldScript
{
public:
    mod_promotion_conf() : WorldScript("mod_promotion.conf", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD
    }) { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            // Config For Module
            promotionEnable = sConfigMgr->GetOption<bool>("promotionEnable.enable", true);
            promotionCount = sConfigMgr->GetOption<uint32>("promotion.count", 1);
            moneyRewardConst = sConfigMgr->GetOption<uint32>("MoneyRewardValue", 10000000);
            LevelForPromotion = sConfigMgr->GetOption<uint32>("LevelForPromotion", 80);
            mountPromotion = sConfigMgr->GetOption<uint32>("mountPromotion", 42277);
            mountEnable = sConfigMgr->GetOption<bool>("mountEnable.enable", true);
            bagEnable = sConfigMgr->GetOption<bool>("bagEnable.enable", true);
            equippedbags = sConfigMgr->GetOption<bool>("equippedbags.enable", true);
            bagReward = sConfigMgr->GetOption<uint32>("bagReward.Id", 14156);

            /*
            * ARMOR CONFIGURATION FOR CLASSES
            */
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_HEAD", 41350);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_SHOULDERS", 41351);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_CHEST", 41353);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_WAIST", 41352);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_LEGS", 41347);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_FEET", 41348);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_WRISTS", 41354);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_HANDS", 41349);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_TRINKET1", 36993);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_MAINHAND", 36984);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_OFFHAND", 37107);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_TANK_RANGED", 36981);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_HEAD", 41350);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_SHOULDERS", 41351);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_CHEST", 41353);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_WAIST", 41352);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_LEGS", 41347);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_FEET", 41348);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_WRISTS", 41354);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_HANDS", 41349);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_MAINHAND", 37108);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_OFFHAND", 36962);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARRIOR_DPS_RANGED", 36981);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_HEAD", 41350);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_SHOULDERS", 41351);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_CHEST", 41353);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_WAIST", 41352);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_LEGS", 41347);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_FEET", 41348);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_WRISTS", 41354);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_HANDS", 41349);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_TRINKET1", 36993);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_MAINHAND", 36984);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_OFFHAND", 37107);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_TANK_RANGED", 38363);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_HEAD", 42728);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_SHOULDERS", 42727);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_CHEST", 42725);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_WAIST", 42729);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_LEGS", 42726);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_FEET", 42730);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_WRISTS", 42723);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_HANDS", 42724);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_TRINKET1", 37111);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_TRINKET2", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_MAINHAND", 37060);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_OFFHAND", 37061);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_HEAL_RANGED", 38364);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_HEAD", 41350);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_SHOULDERS", 41351);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_CHEST", 41353);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_WAIST", 41352);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_LEGS", 41347);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_FEET", 41348);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_WRISTS", 41354);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_HANDS", 41349);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_MAINHAND", 37108);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PALADIN_DPS_RANGED", 38362);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_HEAD", 43447);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_SHOULDERS", 43449);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_CHEST", 43445);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_WAIST", 43442);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_LEGS", 43448);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_FEET", 43443);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_WRISTS", 43444);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_HANDS", 43446);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_MAINHAND", 36980);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_HUNTER_RANGED", 37050);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_HEAD", 43260);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_SHOULDERS", 43433);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_CHEST", 43434);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_WAIST", 43437);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_LEGS", 43438);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_FEET", 43439);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_WRISTS", 43435);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_HANDS", 43436);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_MAINHAND", 36944);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_OFFHAND", 37037);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_ROGUE_RANGED", 36981);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_HEAD", 43971);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_SHOULDERS", 43973);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_CHEST", 43972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_WAIST", 43969);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_LEGS", 43975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_FEET", 43970);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_WRISTS", 43974);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_HANDS", 41516);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_TRINKET2", 37111);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_MAINHAND", 36975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_HEAL_RANGED", 37038);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_HEAD", 43971);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_SHOULDERS", 43973);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_CHEST", 43972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_WAIST", 43969);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_LEGS", 43975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_FEET", 43970);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_WRISTS", 43974);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_HANDS", 41516);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_TRINKET2", 38358);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_MAINHAND", 36975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_PRIEST_SHADOW_RANGED", 37038);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_HEAD", 43455);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_SHOULDERS", 43457);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_CHEST", 43453);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_WAIST", 43450);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_LEGS", 43456);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_FEET", 43451);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_WRISTS", 43452);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_HANDS", 43454);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_TRINKET2", 38358);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_MAINHAND", 37112);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_OFFHAND", 37061);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_CASTER_RANGED", 38361);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_HEAD", 43447);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_SHOULDERS", 43449);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_CHEST", 43445);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_WAIST", 43442);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_LEGS", 43448);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_FEET", 43443);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_WRISTS", 43444);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_HANDS", 43446);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_MAINHAND", 35630);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_OFFHAND", 36944);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_MELEE_RANGED", 38367);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_HEAD", 43455);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_SHOULDERS", 43457);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_CHEST", 43453);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_WAIST", 43450);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_LEGS", 43456);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_FEET", 43451);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_WRISTS", 43452);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_HANDS", 43454);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_TRINKET2", 37111);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_MAINHAND", 37112);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_OFFHAND", 37061);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_SHAMAN_HEAL_RANGED", 38368);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_HEAD", 43971);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_SHOULDERS", 43973);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_CHEST", 43972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_WAIST", 43969);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_LEGS", 43975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_FEET", 43970);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_WRISTS", 43974);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_HANDS", 41516);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_TRINKET2", 38358);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_MAINHAND", 36975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_MAGE_RANGED", 37038);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_HEAD", 43971);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_SHOULDERS", 43973);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_CHEST", 43972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_WAIST", 43969);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_LEGS", 43975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_FEET", 43970);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_WRISTS", 43974);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_HANDS", 41516);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_TRINKET2", 38358);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_MAINHAND", 36975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_WARLOCK_RANGED", 37038);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_HEAD", 43260);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_SHOULDERS", 43433);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_CHEST", 43434);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_WAIST", 43437);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_LEGS", 43438);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_FEET", 43439);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_WRISTS", 43435);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_HANDS", 43436);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_MAINHAND", 36980);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_TANK_RANGED", 38365);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_HEAD", 43261);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_SHOULDERS", 43262);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_CHEST", 43263);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_WAIST", 43266);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_LEGS", 43271);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_FEET", 43273);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_WRISTS", 43264);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_HANDS", 43265);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_TRINKET2", 37111);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_MAINHAND", 36975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_HEAL_RANGED", 38366);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_HEAD", 43260);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_NECK", 45812);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_SHOULDERS", 43433);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_CHEST", 43434);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_WAIST", 43437);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_LEGS", 43438);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_FEET", 43439);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_WRISTS", 43435);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_HANDS", 43436);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_FINGER1", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_FINGER2", 45809);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_TRINKET1", 37064);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_TRINKET2", 38359);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_BACK", 45811);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_MAINHAND", 36980);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_MELEE_RANGED", 38365);

            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_HEAD", 43261);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_NECK", 45813);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_SHOULDERS", 43262);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_CHEST", 43263);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_WAIST", 43266);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_LEGS", 43271);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_FEET", 43273);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_WRISTS", 43264);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_HANDS", 43265);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_FINGER1", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_FINGER2", 45808);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_TRINKET1", 36972);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_TRINKET2", 38358);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_BACK", 45810);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_MAINHAND", 36975);
            classConfArmor = sConfigMgr->GetOption<uint32>("EQUIPMENT_SLOT_DRUID_CASTER_RANGED", 38360);

            // PvE Warrior DPS
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_HEAD", 40543);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_SHOULDERS", 40544);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_BACK", 40524);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_CHEST", 40545);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_WRISTS", 40327);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_HANDS", 40541);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_WAIST", 40324);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_LEGS", 40542);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_FEET", 40300);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_TRINKET1", 40256);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_TRINKET2", 40431);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_MAINHAND", 40402);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_DPS_RANGED", 40323);
            // PvE Warrior Tank
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_HEAD", 40543);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_SHOULDERS", 40544);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_BACK", 40525);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_CHEST", 40545);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_WRISTS", 40328);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_HANDS", 40541);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_WAIST", 40325);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_LEGS", 40542);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_FEET", 40421);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_TRINKET1", 40257);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_TRINKET2", 40254);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_MAINHAND", 40189);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_OFFHAND", 37107);
            sConfigMgr->GetOption<uint32>("PVE_WARRIOR_TANK_RANGED", 36981);
            // PvE Warlock DPS
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_HEAD", 40479);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_SHOULDERS", 40481);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_BACK", 40603);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_CHEST", 40478);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_WRISTS", 40260);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_HANDS", 40480);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_WAIST", 40483);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_LEGS", 40482);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_FEET", 40484);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_FINGER1", 40423);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_FINGER2", 40034);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_TRINKET2", 39229);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_MAINHAND", 40194);
            sConfigMgr->GetOption<uint32>("PVE_WARLOCK_DPS_RANGED", 37038);
            // PvE Druid Tank
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_HEAD", 40460);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_SHOULDERS", 40462);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_BACK", 40524);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_CHEST", 40461);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_WRISTS", 40465);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_HANDS", 40458);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_WAIST", 40474);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_LEGS", 40463);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_FEET", 40464);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_TRINKET1", 40257);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_TRINKET2", 40254);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_MAINHAND", 36980);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_TANK_RANGED", 38365);
            // PvE Druid Heal
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_HEAD", 40466);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_SHOULDERS", 40468);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_BACK", 40604);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_CHEST", 40467);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_WRISTS", 40465);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_HANDS", 40469);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_WAIST", 40475);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_LEGS", 40470);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_FEET", 40471);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_FINGER1", 40107);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_FINGER2", 40423);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_TRINKET2", 37111);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_MAINHAND", 40258);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_HEAL_RANGED", 38366);
            // PvE Druid Balance
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_HEAD", 40466);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_SHOULDERS", 40468);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_BACK", 40603);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_CHEST", 40467);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_WRISTS", 40465);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_HANDS", 40469);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_WAIST", 40483);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_LEGS", 40470);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_FEET", 40471);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_FINGER1", 40423);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_FINGER2", 40034);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_TRINKET2", 39229);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_MAINHAND", 39753);
            sConfigMgr->GetOption<uint32>("PVE_DRUID_BALANCE_RANGED", 38360);
            // PvE Hunter
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_HEAD", 40504);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_SHOULDERS", 40506);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_BACK", 40524);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_CHEST", 40503);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_WRISTS", 40515);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_HANDS", 40502);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_WAIST", 40516);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_LEGS", 40505);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_FEET", 40517);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_TRINKET1", 40256);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_TRINKET2", 40431);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_MAINHAND", 36980);
            sConfigMgr->GetOption<uint32>("PVE_HUNTER_RANGED", 40345);
            // PvE Mage DPS
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_HEAD", 40470);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_SHOULDERS", 40472);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_BACK", 40603);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_CHEST", 40469);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_WRISTS", 40260);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_HANDS", 40471);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_WAIST", 40483);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_LEGS", 40473);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_FEET", 40484);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_FINGER1", 40423);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_FINGER2", 40034);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_TRINKET2", 39229);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_MAINHAND", 40194);
            sConfigMgr->GetOption<uint32>("PVE_MAGE_DPS_RANGED", 37038);
            // PvE Rogue
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_HEAD", 40489);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_SHOULDERS", 40490);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_BACK", 40524);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_CHEST", 40488);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_WRISTS", 40465);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_HANDS", 40492);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_WAIST", 40474);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_LEGS", 40491);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_FEET", 40464);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_FINGER2", 40107);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_TRINKET1", 40256);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_TRINKET2", 40431);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_MAINHAND", 39714);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_OFFHAND", 39715);
            sConfigMgr->GetOption<uint32>("PVE_ROGUE_RANGED", 36981);
            // PvE Priest Heal
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_HEAD", 40456);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_SHOULDERS", 40457);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_BACK", 40604);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_CHEST", 40455);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_WRISTS", 40260);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_HANDS", 40453);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_WAIST", 40485);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_LEGS", 40454);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_FEET", 40486);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_FINGER1", 40107);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_FINGER2", 40423);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_TRINKET2", 37111);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_MAINHAND", 40258);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_HEAL_RANGED", 40275);
            // PvE Priest Shadow
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_HEAD", 40456);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_SHOULDERS", 40457);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_BACK", 40603);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_CHEST", 40455);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_WRISTS", 40260);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_HANDS", 40453);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_WAIST", 40483);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_LEGS", 40454);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_FEET", 40484);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_FINGER1", 40423);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_FINGER2", 40034);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_TRINKET2", 39229);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_MAINHAND", 40194);
            sConfigMgr->GetOption<uint32>("PVE_PRIEST_SHADOW_RANGED", 40275);
            // PvE Paladin Tank
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_HEAD", 40568);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_SHOULDERS", 40569);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_BACK", 40525);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_CHEST", 40570);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_WRISTS", 40328);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_HANDS", 40566);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_WAIST", 40325);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_LEGS", 40567);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_FEET", 40421);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_TRINKET1", 40257);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_TRINKET2", 40254);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_MAINHAND", 40189);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_OFFHAND", 37107);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_TANK_RANGED", 38363);
            // PvE Paladin Heal
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_HEAD", 40568);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_SHOULDERS", 40569);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_BACK", 40604);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_CHEST", 40570);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_WRISTS", 40328);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_HANDS", 40566);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_WAIST", 40487);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_LEGS", 40567);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_FEET", 40488);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_FINGER1", 40107);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_FINGER2", 40423);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_TRINKET2", 37111);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_MAINHAND", 40258);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_OFFHAND", 37061);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_HEAL_RANGED", 38364);
            // PvE Paladin DPS
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_HEAD", 40568);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_SHOULDERS", 40569);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_BACK", 40524);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_CHEST", 40570);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_WRISTS", 40327);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_HANDS", 40566);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_WAIST", 40324);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_LEGS", 40567);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_FEET", 40300);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_TRINKET1", 40256);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_TRINKET2", 40431);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_MAINHAND", 40402);
            sConfigMgr->GetOption<uint32>("PVE_PALADIN_DPS_RANGED", 38362);
            // PvE Shaman Elemental
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_HEAD", 40508);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_SHOULDERS", 40510);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_BACK", 40603);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_CHEST", 40507);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_WRISTS", 40515);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_HANDS", 40509);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_WAIST", 40516);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_LEGS", 40511);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_FEET", 40517);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_FINGER1", 40423);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_FINGER2", 40034);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_TRINKET2", 39229);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_MAINHAND", 40258);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_OFFHAND", 37061);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ELEMENTAL_RANGED", 38361);
            // PvE Shaman Resto
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_HEAD", 40508);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_NECK", 40396);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_SHOULDERS", 40510);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_BACK", 40604);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_CHEST", 40507);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_WRISTS", 40515);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_HANDS", 40509);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_WAIST", 40516);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_LEGS", 40511);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_FEET", 40517);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_FINGER1", 40107);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_FINGER2", 40423);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_TRINKET1", 40432);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_TRINKET2", 37111);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_MAINHAND", 40258);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_OFFHAND", 37061);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_RESTO_RANGED", 38368);
            // PvE Shaman Enhancement
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_HEAD", 40508);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_NECK", 40679);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_SHOULDERS", 40510);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_BACK", 40524);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_CHEST", 40507);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_WRISTS", 40515);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_HANDS", 40509);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_WAIST", 40516);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_LEGS", 40511);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_FEET", 40517);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_FINGER1", 39401);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_FINGER2", 40718);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_TRINKET1", 40256);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_TRINKET2", 40431);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_MAINHAND", 39714);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_OFFHAND", 39715);
            sConfigMgr->GetOption<uint32>("PVE_SHAMAN_ENHANCE_RANGED", 38367);
        }
    }
};

void AddSC_npc_promotion()
{
    new npc_promotion();
    new mod_promotion_conf();
}
