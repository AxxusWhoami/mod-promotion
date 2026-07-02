# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore — mod-promotion

[![Build Status](https://github.com/azerothcore/mod-promotion-AzerothCore-/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-promotion-AzerothCore-)

[English](README.md) | [Español](README_ES.md)

---

## Description

**mod-promotion** is an AzerothCore module that gives new characters a one-time promotion package. The package is delivered through a race-specific NPC ("Level Up Master") placed in each starting zone. Each account can only claim the promotion once; staff with Moderator access or higher bypass that restriction.

### What the promotion gives

| Reward | Default | Configurable |
|---|---|---|
| Character level | 80 | Yes (`LevelForPromotion`) |
| Gold | 1,000g (10,000,000 copper) | Yes (`MoneyRewardValue`) |
| Race ground mount | Yes (race-specific) | Yes (per-race spell ID) |
| Race flying mount | No (disabled by default) | Yes (per-race spell ID) |
| Bags × 4 (auto-equipped) | Frostweave Bag (41599) | Yes (`bagReward.Id`) |
| Full gear set | Class + spec specific (~ilvl 200) | Yes (per-slot via config) |
| All weapon skills | Maxed for class | No |
| Riding skills | Ground + flying (Artisan) | No |
| Teleport to capital | Yes (Stormwind / Orgrimmar) | Yes (`teleport.enable`) |

The promotion is limited to **one per account** and can only be used on a character at their starting level (level 1 for all classes; level 55 for Death Knights). Accounts with Moderator security or above can promote any character regardless of level or previous claims.

### Gear sets included

Every slot (head, neck, shoulders, back, chest, wrists, hands, waist, legs, feet, ring × 2, trinket × 2, main hand, off-hand, ranged) is covered for the following specs. All item IDs are read from the config file and can be changed without recompiling.

| Class | Specs |
|---|---|
| Warrior | Tank (Protection), DPS (Fury) |
| Paladin | Tank (Protection), Healer (Holy), DPS (Retribution) |
| Hunter | DPS (Marksmanship) |
| Rogue | DPS (Subtlety) |
| Priest | Healer (Discipline), DPS (Shadow) |
| Death Knight | Tank (Blood), DPS (Frost / Unholy) |
| Shaman | Caster (Elemental), Healer (Restoration), Melee (Enhancement) |
| Mage | DPS (Frost) |
| Warlock | DPS (Destruction) |
| Druid | Tank (Guardian), Healer (Restoration), Melee (Feral), Caster (Balance) |

Slots with no item defined (e.g. off-hand for Hunter) are silently skipped — no need to set them to 0.

### Race NPCs

One NPC per playable race uses the `npc_promotion` script. Each NPC has a thematic appearance matching its race and starting zone.

| Race | NPC Name | Entry |
|---|---|---|
| Human | Sir Alistar | 80001 |
| Dwarf | Thormir Barbaferro | 80002 |
| Gnome | Chispas Tuercarrueda | 80003 |
| Night Elf | Ilythien Cantoestelar | 80004 |
| Draenei | Vindicador Kuros | 80005 |
| Orc | Gor'thak el Curtido | 80006 |
| Troll | Jin'zaki | 80007 |
| Tauren | Bramido Pezuñaferrea | 80008 |
| Undead | Despertador Mortis | 80009 |
| Blood Elf | Magister Vael'thor | 80010 |

NPC locale translations (koKR, frFR, deDE, zhCN, zhTW, esES, esMX, ruRU) are included in `promotion_race_npcs.sql`.

---

## Requirements

- AzerothCore (WotLK 3.3.5a, build 12340)
- MySQL-compatible world **and** characters database

---

## Installation

```
1. Clone or copy this repository into the AzerothCore modules/ directory.
2. Re-run CMake and recompile the server.
3. Import the SQL files into the corresponding databases:
     data/sql/db-world/base/      → world database
     data/sql/db-characters/base/ → characters database
   Use db_assembler.sh (include.sh provided) or import manually.
4. Copy conf/mod_promotion.conf.dist to your server config folder and rename it
   to mod_promotion.conf. Edit the values as needed.
5. Start worldserver — the module loads automatically.
```

---

## Configuration reference

All options live in `mod_promotion.conf`. The `.dist` file ships with every option documented and its default value.

### Module settings

| Option | Type | Default | Description |
|---|---|---|---|
| `promotionEnable.enable` | bool | `true` | Enable or disable the entire module |
| `LevelForPromotion` | int | `80` | Level granted to the character |
| `MoneyRewardValue` | int | `10000000` | Gold in copper (10,000,000 = 1,000g) |
| `teleport.enable` | bool | `true` | Teleport to faction capital after promotion |
| `mountGround.enable` | bool | `true` | Give a race-specific ground mount |
| `mountFlying.enable` | bool | `false` | Give a race-specific flying mount |
| `bagEnable.enable` | bool | `true` | Include bags in the promotion |
| `equippedbags.enable` | bool | `true` | Auto-equip the bags |
| `bagReward.Id` | int | `41599` | Item ID of the bag to give × 4 |

### Per-race mount overrides

Ground and flying mount spell IDs can be overridden per race. Uncomment the relevant lines in the config file:

```ini
# mountGround.Human    = 470     # Brown Horse
# mountGround.Dwarf    = 6898    # Brown Ram
# mountGround.NightElf = 10789   # Striped Frostsaber
# mountGround.Gnome    = 17453   # Blue Mechanostrider
# mountGround.Draenei  = 35710   # Brown Elekk
# mountGround.BloodElf = 33660   # Red Hawkstrider
# mountGround.Orc      = 5784    # Brown Wolf
# mountGround.Undead   = 17463   # Black Skeletal Horse
# mountGround.Tauren   = 18989   # Gray Kodo
# mountGround.Troll    = 10796   # Emerald Raptor
```

### Gear item IDs

Every equipment slot for every class and spec can be overridden. The key format is:

```
EQUIPMENT_SLOT_<CLASS>_<SPEC>_<SLOT> = <item_id>
```

Examples:
```ini
EQUIPMENT_SLOT_WARRIOR_TANK_HEAD  = 41350
EQUIPMENT_SLOT_WARRIOR_TANK_CHEST = 41353
EQUIPMENT_SLOT_DK_TANK_MAINHAND   = 36984
EQUIPMENT_SLOT_DK_DPS_MAINHAND    = 37108
```

Slots not defined in the config (value absent or 0) are skipped. This is the intended way to leave optional slots (e.g. off-hand for casters) empty.

---

## Promotion eligibility

| Condition | Behaviour |
|---|---|
| Module disabled (`promotionEnable.enable = false`) | NPC shows "promotion period is over" (`npc_text 80000`) |
| Character not at starting level | NPC shows generic greeting, no options offered |
| Account already has a promotion on record | NPC shows "already claimed" message (`npc_text 80001`) |
| Account has Moderator security or higher | Bypasses level check and per-account limit |

The per-account limit is tracked in the `mod_promotion_log` table in the characters database (primary key: `account_id`, so exactly one row per account can exist).

---

## File structure

```
mod-promotion/
├── conf/
│   └── mod_promotion.conf.dist             # Configuration template
├── data/
│   ├── sql/db-world/base/
│   │   ├── promotion_race_npcs.sql         # Race NPC templates + locales
│   │   └── text_npc.sql                    # Gossip texts (IDs 80000–80001)
│   └── sql/db-characters/base/
│       └── mod_promotion_log.sql           # Per-account promotion tracking table
├── src/
│   ├── mod_promotion.cpp                   # Module logic
│   ├── mod_promotion.h                     # Enums (spells, skills, item slots)
│   └── PAC_loader.cpp                      # AzerothCore script registration
└── include.sh                              # db_assembler integration
```

---

## Credits

- [Nefertumm](https://github.com/Nefertumm)
- [pangolp](https://github.com/pangolp)
- [Asmadeuxx](https://github.com/Asmadeuxx)

AzerothCore: [repository](https://github.com/azerothcore) · [website](http://azerothcore.org/) · [discord](https://discord.gg/PaqQRkd)
