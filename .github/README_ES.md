# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore — mod-promotion

[![Build Status](https://github.com/azerothcore/mod-promotion-AzerothCore-/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-promotion-AzerothCore-)

[English](README.md) | [Español](README_ES.md)

---

## Descripción

**mod-promotion** es un módulo de AzerothCore que permite a los personajes nuevos recibir un paquete de promoción único la primera vez que se conectan en nivel 1. El paquete se entrega a través de un NPC específico por raza ("Level Up Master") ubicado en cada zona de inicio. Los Caballeros de la Muerte están excluidos de la promoción.

### Qué incluye la promoción

| Recompensa | Valor predeterminado | Configurable |
|---|---|---|
| Nivel del personaje | 80 | Sí (`LevelForPromotion`) |
| Oro | 1.000g (10.000.000 de cobre) | Sí (`MoneyRewardValue`) |
| Hechizo de montura | Swift Spectral Tiger (42277) | Sí (`mountPromotion`) |
| Mochilas (x4, equipadas automáticamente) | Frostweave Bag (41599) | Sí (`bagReward.Id`) |
| Conjunto de equipo completo | Por clase y especialización (ilvl ~200) | Sí (por ranura en config) |
| Habilidades de arma | Máximas para la clase | No |
| Habilidades de montar | Terrestre + vuelo (Artesano) | No |

El límite de promociones por cuenta es configurable (`promotion.count`, por defecto: 1).

### Conjuntos de equipo incluidos

Se incluyen dos perfiles de equipo completos por clase/especialización:

- **PvP** — Gladiator Salvaje Temporada 5 / equivalente (ilvl 200 PvP)
- **PvE** — Naxxramas 10 jugadores, Tiers Heroicos nivel 7 (ilvl 200 PvE)

Cada ranura (cabeza, cuello, hombros, espalda, pecho, muñecas, manos, cintura, piernas, pies, anillo x2, reliquia x2, mano principal, secundaria, a distancia) está cubierta para cada una de las siguientes especializaciones:

| Clase | Especializaciones |
|---|---|
| Guerrero | Tanque (Protección), DPS (Furia) |
| Paladín | Tanque (Protección), Healer (Sagrado), DPS (Retribución) |
| Cazador | DPS (Puntería / Supervivencia) |
| Pícaro | DPS (Sutileza / Combate) |
| Sacerdote | Healer (Sagrado / Disciplina), DPS (Sombras) |
| Caballero de la Muerte | Excluido de la promoción |
| Chamán | Lanzador (Elemental), Healer (Restauración), Melee (Mejora) |
| Mago | DPS (Escarcha / Arcano) |
| Brujo | DPS (Destrucción) |
| Druida | Tanque (Guardián), Healer (Restauración), Melee (Feral), Lanzador (Equilibrio) |

### NPCs de raza

Un NPC por raza jugable comparte el nombre de script `npc_promotion`. Cada NPC tiene una apariencia temática acorde con su raza y zona de inicio.

| Raza | Nombre del NPC | Entry |
|---|---|---|
| Humano | Sir Alistar | 80001 |
| Enano | Thormir Barbaferro | 80002 |
| Gnomo | Chispas Tuercarrueda | 80003 |
| Elfo de la Noche | Ilythien Cantoestelar | 80004 |
| Draenei | Vindicador Kuros | 80005 |
| Orco | Gor'thak el Curtido | 80006 |
| Troll | Jin'zaki | 80007 |
| Tauren | Bramido Pezuñaferrea | 80008 |
| No-muerto | Despertador Mortis | 80009 |
| Elfo de Sangre | Magister Vael'thor | 80010 |

Las traducciones de los NPCs (koKR, frFR, deDE, zhCN, zhTW, esES, esMX, ruRU) están incluidas en `promotion_race_npcs.sql`.

---

## Requisitos

- AzerothCore (WotLK 3.3.5a, build 12340)
- Base de datos world compatible con MySQL

---

## Instalación

```
1. Clona o copia este repositorio en el directorio modules/ de AzerothCore.
2. Vuelve a ejecutar CMake y recompila el servidor.
3. Importa los archivos SQL de data/sql/db-world/base/ en la base de datos `world`,
   de forma manual o mediante db_assembler.sh (se incluye include.sh).
4. Copia conf/mod_promotion.conf.dist a la carpeta de configuración del servidor
   y renómbralo como mod_promotion.conf. Edita los valores según necesites.
5. Inicia el worldserver — el módulo se carga automáticamente.
```

---

## Referencia de configuración

Todas las opciones se encuentran en `mod_promotion.conf`. El archivo `.dist` incluye cada opción documentada con su valor predeterminado.

### Configuración del módulo

| Opción | Tipo | Predeterminado | Descripción |
|---|---|---|---|
| `promotionEnable.enable` | bool | `true` | Activa o desactiva el módulo completo |
| `promotion.count` | int | `1` | Número máximo de promociones por cuenta |
| `LevelForPromotion` | int | `80` | Nivel otorgado al personaje |
| `MoneyRewardValue` | int | `10000000` | Oro en cobre (10 000 000 = 1 000g) |
| `mountEnable.enable` | bool | `true` | Incluir una montura en la promoción |
| `mountPromotion` | int | `42277` | ID de hechizo de la montura a aprender |
| `bagEnable.enable` | bool | `true` | Incluir mochilas en la promoción |
| `equippedbags.enable` | bool | `true` | Equipar las mochilas automáticamente |
| `bagReward.Id` | int | `41599` | ID del objeto de la mochila (x4) |

### IDs de objetos de equipo

Cada ranura de equipo para cada clase y especialización puede sobreescribirse en el archivo de configuración. El formato de la clave es:

```
EQUIPMENT_SLOT_<CLASE>_<SPEC>_<RANURA> = <id_objeto>   # PvP
PVE_<CLASE>_<SPEC>_<RANURA>            = <id_objeto>   # PvE
```

Ejemplo:
```ini
EQUIPMENT_SLOT_WARRIOR_TANK_HEAD = 41350
PVE_WARRIOR_TANK_HEAD            = 40543
```

---

## Estructura de archivos

```
mod-promotion/
├── conf/
│   └── mod_promotion.conf.dist       # Plantilla de configuración
├── data/sql/db-world/base/
│   ├── promotion_race_npcs.sql       # Plantillas de NPCs de raza + locales
│   └── text_npc.sql                  # Textos de gossip
├── src/
│   ├── mod_promotion.cpp             # Lógica principal del módulo
│   ├── mod_promotion.h               # Enumeraciones (hechizos, habilidades, ranuras)
│   └── PAC_loader.cpp                # Registro de scripts de AzerothCore
└── include.sh                        # Integración con db_assembler
```

---

## Créditos

- [Nefertumm](https://github.com/Nefertumm)
- [pangolp](https://github.com/pangolp)
- [Asmadeuxx](https://github.com/Asmadeuxx)

AzerothCore: [repositorio](https://github.com/azerothcore) · [web](http://azerothcore.org/) · [discord](https://discord.gg/PaqQRkd)
