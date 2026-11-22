# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore — mod-promotion

[English](README.md) | [Español](README_ES.md)

---

## Descripción

**mod-promotion** es un módulo de AzerothCore que otorga a los personajes nuevos un paquete de promoción único. El paquete se entrega a través de un NPC específico por raza ("Level Up Master") ubicado en cada zona de inicio. Cada cuenta solo puede reclamar la promoción una vez; el personal con acceso de Moderador o superior no tiene esa restricción.

### Qué incluye la promoción

| Recompensa | Predeterminado | Configurable |
|---|---|---|
| Nivel del personaje | 80 | Sí (`LevelForPromotion`) |
| Oro | 1.000g (10.000.000 de cobre) | Sí (`MoneyRewardValue`) |
| Montura terrestre por raza | Sí (según raza) | Sí (ID de hechizo por raza) |
| Montura de vuelo por raza | No (desactivada por defecto) | Sí (ID de hechizo por raza) |
| Mochilas × 4 (equipadas automáticamente) | Frostweave Bag (41599) | Sí (`bagReward.Id`) |
| Conjunto de equipo completo | Por clase y especialización (~ilvl 200) | Sí (por ranura en config) |
| Habilidades de arma | Máximas para la clase | No |
| Habilidades de montar | Terrestre + vuelo (Artesano) | No |
| Teletransporte a capital | Sí (Fortaleza de Tormenta / Orgrimmar) | Sí (`teleport.enable`) |
| Build de talentos óptima | Sí (auto-asignada por spec) | Sí (`talentTemplate.enable`) |

La promoción se limita a **una por cuenta** y solo puede usarse en un personaje de nivel inicial (nivel 1 para todas las clases; nivel 55 para los Caballeros de la Muerte). Las cuentas con seguridad de Moderador o superior pueden promover cualquier personaje independientemente del nivel o del historial previo.

### Conjuntos de equipo incluidos

Cada ranura (cabeza, cuello, hombros, espalda, pecho, muñecas, manos, cintura, piernas, pies, anillo × 2, reliquia × 2, mano principal, secundaria, a distancia) está cubierta para las siguientes especializaciones. Todos los IDs de objeto se leen del archivo de configuración y pueden modificarse sin recompilar.

| Clase | Especializaciones |
|---|---|
| Guerrero | Tanque (Protección), DPS (Furia) |
| Paladín | Tanque (Protección), Healer (Sagrado), DPS (Retribución) |
| Cazador | DPS (Puntería) |
| Pícaro | DPS (Sutileza) |
| Sacerdote | Healer (Disciplina), DPS (Sombras) |
| Caballero de la Muerte | Tanque (Sangre), DPS (Escarcha/Profano) |
| Chamán | Lanzador (Elemental), Healer (Restauración), Melee (Mejora) |
| Mago | DPS (Escarcha) |
| Brujo | DPS (Destrucción) |
| Druida | Tanque (Guardián), Healer (Restauración), Lanzador (Equilibrio) |

Las ranuras sin objeto definido (p. ej., mano secundaria para cazadores) se omiten silenciosamente; no es necesario establecerlas en 0.

### Plantillas de talentos

Cuando `talentTemplate.enable` es `true` (predeterminado), la promoción asigna automáticamente una build de talentos competitiva de nivel 80 para el spec seleccionado. Las builds se almacenan en la tabla `mod_promotion_talents` de la base de datos **world**:

```sql
CREATE TABLE `mod_promotion_talents` (
  `playerSpec`  VARCHAR(50)  NOT NULL DEFAULT '',
  `talentId`    INT UNSIGNED  NOT NULL DEFAULT 0,
  PRIMARY KEY (`playerSpec`, `talentId`)
);
```

Cada fila es un talento (por ID de hechizo) a aprender para el spec indicado. Los nombres de spec coinciden con las entradas internas de `kGearSets` (p. ej., `WARRIOR_DPS`, `PALADIN_TANK`, `DRUID_TANK`). El módulo incluye builds preconfiguradas para los 19 specs, obtenidas del proyecto [mod-npc-talent-template](https://github.com/azerothcore/mod-npc-talent-template).

Para personalizar una build, edita las filas en `mod_promotion_talents` para ese spec y reinicia el servidor. Cuando la función está desactivada, los jugadores reciben puntos de talento sin gastar para asignarlos manualmente.

Para Druidas Ferales (`DRUID_TANK`), el talento Mangle también enseña automáticamente los hechizos asociados Mangle (Cat) y Mangle (Bear), ya que el juego no los otorga desde el talento por sí solo.

### NPCs de raza

Un NPC por raza jugable utiliza el script `npc_promotion`. Cada NPC tiene una apariencia temática acorde con su raza y zona de inicio.

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
| Caballero de la Muerte (todas las razas) | Skip el Velocista | 80011 |

Las traducciones de los NPCs (koKR, frFR, deDE, zhCN, zhTW, esES, esMX, ruRU) están incluidas en `promotion_race_npcs.sql`.

---

## Requisitos

- AzerothCore (WotLK 3.3.5a, build 12340)
- Base de datos world **y** characters compatible con MySQL

---

## Instalación

```
1. Clona o copia este repositorio en el directorio modules/ de AzerothCore.
2. Vuelve a ejecutar CMake y recompila el servidor.
3. Importa los archivos SQL en las bases de datos correspondientes:
     data/sql/db-world/base/      → base de datos world
     data/sql/db-characters/base/ → base de datos characters
   Usa db_assembler.sh (se incluye include.sh) o impórtalos manualmente.
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
| `LevelForPromotion` | int | `80` | Nivel otorgado al personaje |
| `Promotion.RequiredLevel` | int | `1` | Nivel exacto que debe tener un personaje no-CdM para reclamar |
| `Promotion.DKRequiredLevel` | int | `55` | Nivel exacto que debe tener un Caballero de la Muerte para reclamar |
| `Promotion.MinAccountAge` | int | `0` | Antigüedad mínima de la cuenta en días (0 = desactivado) |
| `Promotion.ConfirmationStep` | bool | `false` | Exigir un segundo clic de confirmación antes de conceder la promoción |
| `Promotion.AnnounceToWorld` | bool | `false` | Enviar un mensaje global cuando un jugador obtenga la promoción |
| `MoneyRewardValue` | int | `10000000` | Oro en cobre (10.000.000 = 1.000g) |
| `learnSpells.enable` | bool | `true` | Enseñar todos los hechizos entrenables de la clase al promover |
| `talentTemplate.enable` | bool | `true` | Asignar automáticamente una build de talentos óptima para el spec seleccionado |
| `teleport.enable` | bool | `true` | Teletransportar a la capital de facción tras la promoción |
| `mountGround.enable` | bool | `true` | Otorgar una montura terrestre según la raza |
| `mountFlying.enable` | bool | `false` | Otorgar una montura de vuelo según la raza |
| `bagEnable.enable` | bool | `true` | Incluir mochilas en la promoción |
| `equippedbags.enable` | bool | `true` | Equipar las mochilas automáticamente |
| `bagReward.Id` | int | `41599` | ID del objeto de la mochila × 4 |

### Anulación de monturas por raza

Los IDs de hechizo de las monturas terrestres y de vuelo pueden modificarse por raza. Descomenta las líneas correspondientes en el archivo de configuración:

```ini
# mountGround.Human    = 470     # Caballo marrón
# mountGround.Dwarf    = 6898    # Carnero marrón
# mountGround.NightElf = 10789   # Frostsaber rayado
# mountGround.Gnome    = 17453   # Mecano-andador azul
# mountGround.Draenei  = 35710   # Elekk marrón
# mountGround.BloodElf = 33660   # Halcón-jinete rojo
# mountGround.Orc      = 5784    # Lobo marrón
# mountGround.Undead   = 17463   # Caballo esquelético negro
# mountGround.Tauren   = 18989   # Kodo gris
# mountGround.Troll    = 10796   # Raptor esmeralda
```

### IDs de objetos de equipo

Cada ranura de equipo para cada clase y especialización puede sobreescribirse. El formato de la clave es:

```
EQUIPMENT_SLOT_<CLASE>_<SPEC>_<RANURA> = <id_objeto>
```

Ejemplos:
```ini
EQUIPMENT_SLOT_WARRIOR_TANK_HEAD  = 41350
EQUIPMENT_SLOT_WARRIOR_TANK_CHEST = 41353
EQUIPMENT_SLOT_DK_TANK_MAINHAND   = 36984
EQUIPMENT_SLOT_DK_DPS_MAINHAND    = 37108
```

Las ranuras no definidas en la configuración (clave ausente o valor 0) se omiten. Esta es la forma correcta de dejar vacíos los slots opcionales (p. ej., mano secundaria para lanzadores).

---

## Elegibilidad para la promoción

| Condición | Comportamiento |
|---|---|
| Módulo desactivado (`promotionEnable.enable = false`) | El NPC muestra "el período de promoción ha terminado" (`npc_text 80000`) |
| El personaje no está en el nivel inicial | El NPC muestra el mensaje de nivel incorrecto (`npc_text 80003`) |
| La cuenta ya tiene una promoción registrada | El NPC muestra "ya reclamada" (`npc_text 80001`) |
| La cuenta es más nueva que `Promotion.MinAccountAge` días | El NPC muestra "cuenta demasiado nueva" (`npc_text 80005`) |
| La cuenta tiene seguridad de Moderador o superior | Omite la comprobación de nivel y el límite por cuenta |

El límite por cuenta se registra en la tabla `mod_promotion_log` de la base de datos de personajes (clave primaria: `account_id`, por lo que solo puede existir una fila por cuenta).

---

## Estructura de archivos

```
mod-promotion/
├── conf/
│   └── mod_promotion.conf.dist             # Plantilla de configuración
├── data/
│   ├── sql/db-world/base/
│   │   ├── promotion_race_npcs.sql         # Plantillas de NPCs de raza + locales
│   │   ├── text_npc.sql                    # Textos de gossip (IDs 80000–80005)
│   │   └── mod_promotion_talents.sql       # Builds de talentos para todos los specs
│   └── sql/db-characters/base/
│       └── mod_promotion_log.sql           # Tabla de seguimiento de promociones por cuenta
├── src/
│   ├── mod_promotion.cpp                   # Lógica del módulo
│   ├── mod_promotion.h                     # Enumeraciones (hechizos, habilidades, ranuras)
│   └── PAC_loader.cpp                      # Registro de scripts de AzerothCore
└── include.sh                              # Integración con db_assembler
```

---

## Créditos

- [Nefertumm](https://github.com/Nefertumm)
- [pangolp](https://github.com/pangolp)
- [Asmadeuxx](https://github.com/Asmadeuxx)

AzerothCore: [repositorio](https://github.com/azerothcore) · [web](http://azerothcore.org/) · [discord](https://discord.gg/PaqQRkd)
