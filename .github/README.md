# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore — mod-promotion

[![Build Status](https://github.com/azerothcore/mod-promotion-AzerothCore-/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-promotion-AzerothCore-)

[English](README.md) | [Español](README_ES.md)

---

## Description

**mod-promotion** is an AzerothCore module that lets new characters receive a one-time promotion package when they first log in at level 1. The package is delivered through a race-specific NPC ("Level Up Master") placed in each starting zone. Death Knights are excluded from the promotion.

### What the promotion gives

| Reward | Default value | Configurable |
|---|---|---|
| Character level | 80 | Yes (`LevelForPromotion`) |
| Gold | 1,000g (10,000,000 copper) | Yes (`MoneyRewardValue`) |
| Mount spell | Swift Spectral Tiger (42277) | Yes (`mountPromotion`) |
| Bags (x4, auto-equipped) | Frostweave Bag (41599) | Yes (`bagReward.Id`) |
| Full gear set | Class + spec specific (ilvl ~200) | Yes (per-slot via config) |
| Weapon skills | All maxed for class | No |
| Riding skills | Ground + flying (Artisan) | No |

The promotion limit per account is configurable (`promotion.count`, default: 1).

### Gear sets included

Two complete gear profiles per class/spec are shipped:

- **PvP** — Season 5 Savage Gladiator / equivalent (ilvl 200 PvP)
- **PvE** — Naxxramas 10-man Heroes' Tier 7 (ilvl 200 PvE)

Every slot (head, neck, shoulders, back, chest, wrists, hands, waist, legs, feet, finger x2, trinket x2, main hand, off hand, ranged) is covered for each of the following specs:

| Class | Specs |
|---|---|
| Warrior | Tank (Protection), DPS (Fury) |
| Paladin | Tank (Protection), Healer (Holy), DPS (Retribution) |
| Hunter | DPS (Marksmanship / Survival) |
| Rogue | DPS (Subtlety / Combat) |
| Priest | Healer (Holy / Discipline), DPS (Shadow) |
| Death Knight | Excluded from promotion |
| Shaman | Caster (Elemental), Healer (Restoration), Melee (Enhancement) |
| Mage | DPS (Frost / Arcane) |
| Warlock | DPS (Destruction) |
| Druid | Tank (Guardian), Healer (Restoration), Melee (Feral), Caster (Balance) |

### Race NPCs

One NPC per playable race shares the script name `npc_promotion`. Each NPC has a thematic appearance matching its race and starting zone.

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
- MySQL-compatible world database

---

## Installation

```
1. Clone or copy this repository into the AzerothCore `modules/` directory.
2. Re-run CMake and recompile the server.
3. Import the SQL files from data/sql/db-world/base/ into the `world` database,
   either manually or via db_assembler.sh (include.sh is provided).
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
| `promotion.count` | int | `1` | Maximum number of promotions per account |
| `LevelForPromotion` | int | `80` | Level granted to the character |
| `MoneyRewardValue` | int | `10000000` | Gold in copper (10 000 000 = 1 000g) |
| `mountEnable.enable` | bool | `true` | Include a mount in the promotion |
| `mountPromotion` | int | `42277` | Spell ID of the mount to learn |
| `bagEnable.enable` | bool | `true` | Include bags in the promotion |
| `equippedbags.enable` | bool | `true` | Auto-equip the bags |
| `bagReward.Id` | int | `41599` | Item ID of the bag to give (x4) |

### Gear item IDs

Every equipment slot for every class and spec can be overridden in the config file. The key format is:

```
EQUIPMENT_SLOT_<CLASS>_<SPEC>_<SLOT> = <item_id>   # PvP
PVE_<CLASS>_<SPEC>_<SLOT>            = <item_id>   # PvE
```

Example:
```ini
EQUIPMENT_SLOT_WARRIOR_TANK_HEAD = 41350
PVE_WARRIOR_TANK_HEAD            = 40543
```

---

## File structure

```
mod-promotion/
├── conf/
│   └── mod_promotion.conf.dist       # Configuration template
├── data/sql/db-world/base/
│   ├── promotion_race_npcs.sql       # Race NPC templates + locales
│   └── text_npc.sql                  # Gossip texts
├── src/
│   ├── mod_promotion.cpp             # Main module logic
│   ├── mod_promotion.h               # Enums (spells, skills, item slots)
│   └── PAC_loader.cpp                # AzerothCore script registration
└── include.sh                        # db_assembler integration
```

---

## Credits

- [Nefertumm](https://github.com/Nefertumm)
- [pangolp](https://github.com/pangolp)
- [Asmadeuxx](https://github.com/Asmadeuxx)

AzerothCore: [repository](https://github.com/azerothcore) · [website](http://azerothcore.org/) · [discord](https://discord.gg/PaqQRkd)
