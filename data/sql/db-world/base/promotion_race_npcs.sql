-- ============================================================
-- Promotion Race NPCs - WoW 3.3.5a (build 12340)
-- One NPC per playable race + one for Death Knight (class-specific)
-- Alliance: Human, Dwarf, Gnome, Night Elf, Draenei
-- Horde:    Orc, Troll, Tauren, Undead, Blood Elf
-- Neutral:  Death Knight (Skip el Velocista, Acherus)
-- ============================================================
-- Display IDs reference:
--   10116 = Human male Argent Dawn Officer (full plate + tabard)
--   10125 = Dwarf male Ironforge Guard (sturdy armor + shield)
--   15880 = Gnome male Engineer (goggles + tools)
--    3679 = Night Elf male Archdruid-style (nature robes, Fandral-type)
--   17351 = Draenei male Aldor Vindicator (crystal plate armor, mace)
--   21330 = Orc male Kor'kron Guard (black imposing armor + horned shoulders)
--   10134 = Troll male Blackspear Guard (tribal armor + classic lance)
--   14457 = Tauren male Thunderbluff Brave (leather/plate armor + totem)
--   10136 = Undead male Deathstalker / Undercity Guard (dark armor + Sylvanas tabard)
--   17294 = Blood Elf male Silvermoon Magister (elegant red robes)
--   25419 = Death Knight (Ebon Blade full saronite armor, glowing eyes)
-- Equipment item IDs:
--   40408 = Claymore of the Prophet (2H sword, Naxx25)
--   39388 = Dwarven Blunderbuss variant (1H axe)
--   34481 = Arcanite Rifle (ranged)
--   35078 = Engineer's Gnomish Wrench proxy (mace)
--   11902 = Staff of Jordan (2H staff)
--   45282 = Hammer of Wrath proxy (2H mace)
--   30021 = Axe of the Gronn Lords (2H axe)
--   29956 = Trollbane (polearm)
--   29684 = Earthwarden (2H mace, druid/shaman)
--   33294 = Black Planar Edge (1H sword, dark)
--   34065 = Terokk's Shadowstaff (2H staff)
-- ============================================================

-- ----------------------------
-- ALLIANCE
-- ----------------------------

-- Human: Sir Alistar (Abadía de Villanorte)
SET @ENTRY_HUMAN    := 80001;
SET @NAME_HUMAN     := 'Sir Alistar';
SET @SUBNAME_HUMAN  := 'Level Up Master';
SET @GOSSIP_HUMAN   := 80001;
SET @MODEL_HUMAN    := 3346;
DELETE FROM `creature_template` WHERE `entry` = @ENTRY_HUMAN;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_HUMAN, 0, 0, 0, 0, 0, @NAME_HUMAN, @SUBNAME_HUMAN, NULL, @GOSSIP_HUMAN, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_HUMAN;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_HUMAN, 0, @MODEL_HUMAN, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_HUMAN;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_HUMAN, 1, 40408, 0, 0);

-- Dwarf: Thormir Barbaferro (Valle de los Fríos)
SET @ENTRY_DWARF    := 80002;
SET @NAME_DWARF     := 'Thormir Barbaferro';
SET @SUBNAME_DWARF  := 'Level Up Master';
SET @GOSSIP_DWARF   := 80002;
SET @MODEL_DWARF    := 10125;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_DWARF;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_DWARF, 0, 0, 0, 0, 0, @NAME_DWARF, @SUBNAME_DWARF, NULL, @GOSSIP_DWARF, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_DWARF;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_DWARF, 0, @MODEL_DWARF, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_DWARF;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_DWARF, 1, 39388, 0, 34481);

-- Gnome: Chispas Tuercarrueda (Valle de los Fríos)
SET @ENTRY_GNOME    := 80003;
SET @NAME_GNOME     := 'Chispas Tuercarrueda';
SET @SUBNAME_GNOME  := 'Level Up Master';
SET @GOSSIP_GNOME   := 80003;
SET @MODEL_GNOME    := 15880;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_GNOME;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_GNOME, 0, 0, 0, 0, 0, @NAME_GNOME, @SUBNAME_GNOME, NULL, @GOSSIP_GNOME, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_GNOME;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_GNOME, 0, @MODEL_GNOME, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_GNOME;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_GNOME, 1, 35078, 0, 0);

-- Night Elf: Ilythien Cantoestelar (Cañada Umbría)
SET @ENTRY_NELF     := 80004;
SET @NAME_NELF      := 'Ilythien Cantoestelar';
SET @SUBNAME_NELF   := 'Level Up Master';
SET @GOSSIP_NELF    := 80004;
SET @MODEL_NELF     := 7275;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_NELF;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_NELF, 0, 0, 0, 0, 0, @NAME_NELF, @SUBNAME_NELF, NULL, @GOSSIP_NELF, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_NELF;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_NELF, 0, @MODEL_NELF, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_NELF;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_NELF, 1, 11902, 0, 0);

-- Draenei: Vindicador Kuros (Valle Ammen)
SET @ENTRY_DRAE     := 80005;
SET @NAME_DRAE      := 'Vindicador Kuros';
SET @SUBNAME_DRAE   := 'Level Up Master';
SET @GOSSIP_DRAE    := 80005;
SET @MODEL_DRAE     := 17373;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_DRAE;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_DRAE, 0, 0, 0, 0, 0, @NAME_DRAE, @SUBNAME_DRAE, NULL, @GOSSIP_DRAE, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_DRAE;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_DRAE, 0, @MODEL_DRAE, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_DRAE;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_DRAE, 1, 45282, 0, 0);

-- ----------------------------
-- HORDE
-- ----------------------------

-- Orc: Gor'thak el Curtido (Valle de los Retos)
SET @ENTRY_ORC      := 80006;
SET @NAME_ORC       := 'Gor\'thak el Curtido';
SET @SUBNAME_ORC    := 'Level Up Master';
SET @GOSSIP_ORC     := 80006;
SET @MODEL_ORC      := 9794;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_ORC;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_ORC, 0, 0, 0, 0, 0, @NAME_ORC, @SUBNAME_ORC, NULL, @GOSSIP_ORC, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_ORC;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_ORC, 0, @MODEL_ORC, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_ORC;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_ORC, 1, 30021, 0, 0);

-- Troll: Jin'zaki (Valle de los Retos)
SET @ENTRY_TROLL    := 80007;
SET @NAME_TROLL     := 'Jin\'zaki';
SET @SUBNAME_TROLL  := 'Level Up Master';
SET @GOSSIP_TROLL   := 80007;
SET @MODEL_TROLL    := 10134;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_TROLL;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_TROLL, 0, 0, 0, 0, 0, @NAME_TROLL, @SUBNAME_TROLL, NULL, @GOSSIP_TROLL, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_TROLL;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_TROLL, 0, @MODEL_TROLL, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_TROLL;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_TROLL, 1, 29956, 0, 0);

-- Tauren: Bramido Pezuñaferrea (Campamento Narache)
SET @ENTRY_TAUREN   := 80008;
SET @NAME_TAUREN    := 'Bramido Pezuñaferrea';
SET @SUBNAME_TAUREN := 'Level Up Master';
SET @GOSSIP_TAUREN  := 80008;
SET @MODEL_TAUREN   := 3798;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_TAUREN;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_TAUREN, 0, 0, 0, 0, 0, @NAME_TAUREN, @SUBNAME_TAUREN, NULL, @GOSSIP_TAUREN, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_TAUREN;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_TAUREN, 0, @MODEL_TAUREN, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_TAUREN;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_TAUREN, 1, 29684, 0, 0);

-- Undead: Despertador Mortis (Camposanto)
SET @ENTRY_UNDEAD   := 80009;
SET @NAME_UNDEAD    := 'Despertador Mortis';
SET @SUBNAME_UNDEAD := 'Level Up Master';
SET @GOSSIP_UNDEAD  := 80009;
SET @MODEL_UNDEAD   := 10973;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_UNDEAD;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_UNDEAD, 0, 0, 0, 0, 0, @NAME_UNDEAD, @SUBNAME_UNDEAD, NULL, @GOSSIP_UNDEAD, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_UNDEAD;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_UNDEAD, 0, @MODEL_UNDEAD, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_UNDEAD;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_UNDEAD, 1, 33294, 0, 0);

-- Blood Elf: Magister Vael'thor (Isla Caminante del Sol)
SET @ENTRY_BELF     := 80010;
SET @NAME_BELF      := 'Magister Vael\'thor';
SET @SUBNAME_BELF   := 'Level Up Master';
SET @GOSSIP_BELF    := 80010;
SET @MODEL_BELF     := 18189;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_BELF;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_BELF, 0, 0, 0, 0, 0, @NAME_BELF, @SUBNAME_BELF, NULL, @GOSSIP_BELF, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_BELF;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_BELF, 0, @MODEL_BELF, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_BELF;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_BELF, 1, 34065, 0, 0);

-- ----------------------------
-- NEUTRAL (Death Knight)
-- ----------------------------

-- Death Knight: Skip el Velocista (Acherus: El Levante de los Caballeros de la Muerte)
-- Faction 35 = Friendly to all, accessible by DKs of any race/faction.
SET @ENTRY_DK       := 80011;
SET @NAME_DK        := 'Skip el Velocista';
SET @SUBNAME_DK     := 'Level Up Master';
SET @GOSSIP_DK      := 80011;
SET @MODEL_DK       := 25419;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_DK;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_DK, 0, 0, 0, 0, 0, @NAME_DK, @SUBNAME_DK, NULL, @GOSSIP_DK, 83, 83, 0, 35, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_DK;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_DK, 0, @MODEL_DK, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_DK;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_DK, 1, 37108, 0, 0);

-- ----------------------------
-- LOCALES: koKR, frFR, deDE, zhCN, zhTW, esES, esMX, ruRU
-- Name  = localized NPC name
-- Title = localized subname (always "Level Up Master")
-- ----------------------------
DELETE FROM `creature_template_locale` WHERE `entry` IN (80001, 80002, 80003, 80004, 80005, 80006, 80007, 80008, 80009, 80010, 80011);
INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`)
VALUES
  -- Sir Alistar (80001)
  (80001, 'koKR', '기사 알리스타르',        '레벨업 마스터',           0),
  (80001, 'frFR', 'Sire Alistar',            'Maître de Niveau',        0),
  (80001, 'deDE', 'Sir Alistar',             'Aufstiegs-Meister',       0),
  (80001, 'zhCN', '阿里斯塔爵士',            '升级大师',                0),
  (80001, 'zhTW', '艾里斯塔爵士',            '升級大師',                0),
  (80001, 'esES', 'Sir Alistar',             'Maestro de subida de nivel',      0),
  (80001, 'esMX', 'Sir Alistar',             'Maestro de subida de nivel',      0),
  (80001, 'ruRU', 'Сэр Алистар',            'Мастер Повышения',        0),

  -- Thormir Barbaferro (80002)
  (80002, 'koKR', '토르미르 아이언비어드',   '레벨업 마스터',           0),
  (80002, 'frFR', 'Thormir Barbe-de-Fer',   'Maître de Niveau',        0),
  (80002, 'deDE', 'Thormir Eisenbart',       'Aufstiegs-Meister',       0),
  (80002, 'zhCN', '托尔米尔·铁须',           '升级大师',                0),
  (80002, 'zhTW', '托爾米爾·鐵鬚',           '升級大師',                0),
  (80002, 'esES', 'Thormir Barbaferro',      'Maestro de subida de nivel',      0),
  (80002, 'esMX', 'Thormir Barbaferro',      'Maestro de subida de nivel',      0),
  (80002, 'ruRU', 'Тормир Железнобород',    'Мастер Повышения',        0),

  -- Chispas Tuercarrueda (80003)
  (80003, 'koKR', '불꽃 기어휠',             '레벨업 마스터',           0),
  (80003, 'frFR', 'Étincelles Roue-dentée', 'Maître de Niveau',        0),
  (80003, 'deDE', 'Funken Zahnrad',          'Aufstiegs-Meister',       0),
  (80003, 'zhCN', '火花·齿轮',               '升级大师',                0),
  (80003, 'zhTW', '火花·齒輪',               '升級大師',                0),
  (80003, 'esES', 'Chispas Tuercarrueda',    'Maestro de subida de nivel',      0),
  (80003, 'esMX', 'Chispas Tuercarrueda',    'Maestro de subida de nivel',      0),
  (80003, 'ruRU', 'Искра Шестерёнкин',      'Мастер Повышения',        0),

  -- Ilythien Cantoestelar (80004)
  (80004, 'koKR', '일리씨엔 별노래',         '레벨업 마스터',           0),
  (80004, 'frFR', 'Ilythien Chanteétoile',  'Maître de Niveau',        0),
  (80004, 'deDE', 'Ilythien Sternengesang', 'Aufstiegs-Meister',       0),
  (80004, 'zhCN', '伊莉希恩·星歌',           '升级大师',                0),
  (80004, 'zhTW', '伊莉希恩·星歌',           '升級大師',                0),
  (80004, 'esES', 'Ilythien Cantoestelar',   'Maestro de subida de nivel',      0),
  (80004, 'esMX', 'Ilythien Cantoestelar',   'Maestro de subida de nivel',      0),
  (80004, 'ruRU', 'Илисьен Звёздная Песнь', 'Мастер Повышения',        0),

  -- Vindicador Kuros (80005)
  (80005, 'koKR', '성전사 쿠로스',           '레벨업 마스터',           0),
  (80005, 'frFR', 'Vindicateur Kuros',       'Maître de Niveau',        0),
  (80005, 'deDE', 'Vindicator Kuros',        'Aufstiegs-Meister',       0),
  (80005, 'zhCN', '惩戒者库罗斯',            '升级大师',                0),
  (80005, 'zhTW', '懲戒者庫羅斯',            '升級大師',                0),
  (80005, 'esES', 'Vindicador Kuros',        'Maestro de subida de nivel',      0),
  (80005, 'esMX', 'Vindicador Kuros',        'Maestro de subida de nivel',      0),
  (80005, 'ruRU', 'Карающий Курос',          'Мастер Повышения',        0),

  -- Gor'thak el Curtido (80006)
  (80006, 'koKR', '고르탁 용사',             '레벨업 마스터',           0),
  (80006, 'frFR', 'Gor\'thak le Durci',      'Maître de Niveau',        0),
  (80006, 'deDE', 'Gor\'thak der Abgehärtete', 'Aufstiegs-Meister',    0),
  (80006, 'zhCN', '戈尔塔克·老兵',           '升级大师',                0),
  (80006, 'zhTW', '戈爾塔克·老兵',           '升級大師',                0),
  (80006, 'esES', 'Gor\'thak el Curtido',    'Maestro de subida de nivel',      0),
  (80006, 'esMX', 'Gor\'thak el Curtido',    'Maestro de subida de nivel',      0),
  (80006, 'ruRU', 'Гор\'так Закалённый',    'Мастер Повышения',        0),

  -- Jin'zaki (80007)
  (80007, 'koKR', '진자키',                  '레벨업 마스터',           0),
  (80007, 'frFR', 'Jin\'zaki',               'Maître de Niveau',        0),
  (80007, 'deDE', 'Jin\'zaki',               'Aufstiegs-Meister',       0),
  (80007, 'zhCN', '金扎基',                  '升级大师',                0),
  (80007, 'zhTW', '金扎基',                  '升級大師',                0),
  (80007, 'esES', 'Jin\'zaki',               'Maestro de subida de nivel',      0),
  (80007, 'esMX', 'Jin\'zaki',               'Maestro de subida de nivel',      0),
  (80007, 'ruRU', 'Джин\'заки',             'Мастер Повышения',        0),

  -- Bramido Pezuñaferrea (80008)
  (80008, 'koKR', '아이언후프 포효',          '레벨업 마스터',           0),
  (80008, 'frFR', 'Grondement Sabotferreux', 'Maître de Niveau',        0),
  (80008, 'deDE', 'Stampfer Eisenhufe',      'Aufstiegs-Meister',       0),
  (80008, 'zhCN', '铁蹄轰鸣',                '升级大师',                0),
  (80008, 'zhTW', '鐵蹄轟鳴',                '升級大師',                0),
  (80008, 'esES', 'Bramido Pezuñaferrea',    'Maestro de subida de nivel',      0),
  (80008, 'esMX', 'Bramido Pezuñaferrea',    'Maestro de subida de nivel',      0),
  (80008, 'ruRU', 'Рёв Железнокоп',         'Мастер Повышения',        0),

  -- Despertador Mortis (80009)
  (80009, 'koKR', '깨우는자 모르티스',        '레벨업 마스터',           0),
  (80009, 'frFR', 'Éveilleur Mortis',        'Maître de Niveau',        0),
  (80009, 'deDE', 'Erwecker Mortis',         'Aufstiegs-Meister',       0),
  (80009, 'zhCN', '唤醒者莫提斯',            '升级大师',                0),
  (80009, 'zhTW', '喚醒者莫提斯',            '升級大師',                0),
  (80009, 'esES', 'Despertador Mortis',      'Maestro de subida de nivel',      0),
  (80009, 'esMX', 'Despertador Mortis',      'Maestro de subida de nivel',      0),
  (80009, 'ruRU', 'Пробудитель Мортис',     'Мастер Повышения',        0),

  -- Magister Vael'thor (80010)
  (80010, 'koKR', '대마법사 바엘\'토르',      '레벨업 마스터',           0),
  (80010, 'frFR', 'Magistère Vael\'thor',    'Maître de Niveau',        0),
  (80010, 'deDE', 'Magister Vael\'thor',     'Aufstiegs-Meister',       0),
  (80010, 'zhCN', '魔导师瓦尔托',            '升级大师',                0),
  (80010, 'zhTW', '魔導師瓦爾托',            '升級大師',                0),
  (80010, 'esES', 'Magister Vael\'thor',     'Maestro de subida de nivel',      0),
  (80010, 'esMX', 'Magister Vael\'thor',     'Maestro de subida de nivel',      0),
  (80010, 'ruRU', 'Магистр Вэл\'тор',       'Мастер Повышения',        0),

  -- Skip el Velocista (80011)
  (80011, 'koKR', '스킵 질주자',             '레벨업 마스터',           0),
  (80011, 'frFR', 'Skip le Vélociste',       'Maître de Niveau',        0),
  (80011, 'deDE', 'Skip der Schnellläufer',  'Aufstiegs-Meister',       0),
  (80011, 'zhCN', '快腿·斯基普',             '升级大师',                0),
  (80011, 'zhTW', '快腿·斯基普',             '升級大師',                0),
  (80011, 'esES', 'Skip el Velocista',       'Maestro de subida de nivel',      0),
  (80011, 'esMX', 'Skip el Velocista',       'Maestro de subida de nivel',      0),
  (80011, 'ruRU', 'Скип Быстроног',         'Мастер Повышения',        0);
