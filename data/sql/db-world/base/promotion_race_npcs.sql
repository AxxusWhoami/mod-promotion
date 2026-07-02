-- ============================================================
-- Promotion Race NPCs - WoW 3.3.5a (build 12340)
-- One NPC per playable race (except Death Knight)
-- Alliance: Human, Dwarf, Gnome, Night Elf, Draenei
-- Horde:    Orc, Troll, Tauren, Undead, Blood Elf
-- ============================================================
-- Display IDs reference:
--   25003 = Human male Seventh Legion soldier (plate + tabard)
--   26047 = Dwarf male Ironforge Mountaineer (mail + rifle)
--   20469 = Gnome male engineer (work clothes + goggles)
--   22490 = Night Elf female sentinel/druid (leather + staff)
--   21267 = Draenei male Vindicator (crystal plate + hammer)
--    3890 = Orc male Orgrimmar Grunt (red/black plate + axe)
--    9528 = Troll male Witch Doctor (voodoo mask + lances)
--    3975 = Tauren male warrior/shaman (heavy plate + totem)
--   10837 = Forsaken male Apothecary/Deathguard (dark armor)
--   17827 = Blood Elf male Magister (crimson robes/mail)
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
SET @SUBNAME_HUMAN  := 'Caballero de la Séptima Legión';
SET @GOSSIP_HUMAN   := 80001;
SET @MODEL_HUMAN    := 25003;
SET @EQUIP_HUMAN    := 80001;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_HUMAN;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_HUMAN, 0, 0, 0, 0, 0, @NAME_HUMAN, @SUBNAME_HUMAN, NULL, @GOSSIP_HUMAN, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_HUMAN;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_HUMAN, 0, @MODEL_HUMAN, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_HUMAN;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_HUMAN, @EQUIP_HUMAN, 40408, 0, 0);

-- Dwarf: Thormir Barbaferro (Valle de los Fríos)
SET @ENTRY_DWARF    := 80002;
SET @NAME_DWARF     := 'Thormir Barbaferro';
SET @SUBNAME_DWARF  := 'Explorador del Valle de los Fríos';
SET @GOSSIP_DWARF   := 80002;
SET @MODEL_DWARF    := 26047;
SET @EQUIP_DWARF    := 80002;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_DWARF;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_DWARF, 0, 0, 0, 0, 0, @NAME_DWARF, @SUBNAME_DWARF, NULL, @GOSSIP_DWARF, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_DWARF;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_DWARF, 0, @MODEL_DWARF, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_DWARF;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_DWARF, @EQUIP_DWARF, 39388, 0, 34481);

-- Gnome: Chispas Tuercarrueda (Valle de los Fríos)
SET @ENTRY_GNOME    := 80003;
SET @NAME_GNOME     := 'Chispas Tuercarrueda';
SET @SUBNAME_GNOME  := 'Ingeniero Jefe de Gnomeregan';
SET @GOSSIP_GNOME   := 80003;
SET @MODEL_GNOME    := 20469;
SET @EQUIP_GNOME    := 80003;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_GNOME;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_GNOME, 0, 0, 0, 0, 0, @NAME_GNOME, @SUBNAME_GNOME, NULL, @GOSSIP_GNOME, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_GNOME;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_GNOME, 0, @MODEL_GNOME, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_GNOME;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_GNOME, @EQUIP_GNOME, 35078, 0, 0);

-- Night Elf: Ilythien Cantoestelar (Cañada Umbría)
SET @ENTRY_NELF     := 80004;
SET @NAME_NELF      := 'Ilythien Cantoestelar';
SET @SUBNAME_NELF   := 'Centinela Ancestral';
SET @GOSSIP_NELF    := 80004;
SET @MODEL_NELF     := 22490;
SET @EQUIP_NELF     := 80004;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_NELF;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_NELF, 0, 0, 0, 0, 0, @NAME_NELF, @SUBNAME_NELF, NULL, @GOSSIP_NELF, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_NELF;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_NELF, 0, @MODEL_NELF, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_NELF;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_NELF, @EQUIP_NELF, 11902, 0, 0);

-- Draenei: Vindicador Kuros (Valle Ammen)
SET @ENTRY_DRAE     := 80005;
SET @NAME_DRAE      := 'Vindicador Kuros';
SET @SUBNAME_DRAE   := 'Vindicador del Exodar';
SET @GOSSIP_DRAE    := 80005;
SET @MODEL_DRAE     := 21267;
SET @EQUIP_DRAE     := 80005;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_DRAE;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_DRAE, 0, 0, 0, 0, 0, @NAME_DRAE, @SUBNAME_DRAE, NULL, @GOSSIP_DRAE, 83, 83, 0, 1802, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_DRAE;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_DRAE, 0, @MODEL_DRAE, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_DRAE;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_DRAE, @EQUIP_DRAE, 45282, 0, 0);

-- ----------------------------
-- HORDE
-- ----------------------------

-- Orc: Gor'thak el Curtido (Valle de los Retos)
SET @ENTRY_ORC      := 80006;
SET @NAME_ORC       := 'Gor\'thak el Curtido';
SET @SUBNAME_ORC    := 'Sargento de Orgrimmar';
SET @GOSSIP_ORC     := 80006;
SET @MODEL_ORC      := 3890;
SET @EQUIP_ORC      := 80006;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_ORC;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_ORC, 0, 0, 0, 0, 0, @NAME_ORC, @SUBNAME_ORC, NULL, @GOSSIP_ORC, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_ORC;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_ORC, 0, @MODEL_ORC, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_ORC;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_ORC, @EQUIP_ORC, 30021, 0, 0);

-- Troll: Jin'zaki (Valle de los Retos)
SET @ENTRY_TROLL    := 80007;
SET @NAME_TROLL     := 'Jin\'zaki';
SET @SUBNAME_TROLL  := 'Médico Brujo Darkspear';
SET @GOSSIP_TROLL   := 80007;
SET @MODEL_TROLL    := 9528;
SET @EQUIP_TROLL    := 80007;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_TROLL;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_TROLL, 0, 0, 0, 0, 0, @NAME_TROLL, @SUBNAME_TROLL, NULL, @GOSSIP_TROLL, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_TROLL;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_TROLL, 0, @MODEL_TROLL, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_TROLL;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_TROLL, @EQUIP_TROLL, 29956, 0, 0);

-- Tauren: Bramido Pezuñaferrea (Campamento Narache)
SET @ENTRY_TAUREN   := 80008;
SET @NAME_TAUREN    := 'Bramido Pezuñaferrea';
SET @SUBNAME_TAUREN := 'Guerrero Caminasol';
SET @GOSSIP_TAUREN  := 80008;
SET @MODEL_TAUREN   := 3975;
SET @EQUIP_TAUREN   := 80008;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_TAUREN;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_TAUREN, 0, 0, 0, 0, 0, @NAME_TAUREN, @SUBNAME_TAUREN, NULL, @GOSSIP_TAUREN, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_TAUREN;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_TAUREN, 0, @MODEL_TAUREN, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_TAUREN;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_TAUREN, @EQUIP_TAUREN, 29684, 0, 0);

-- Undead: Despertador Mortis (Camposanto)
SET @ENTRY_UNDEAD   := 80009;
SET @NAME_UNDEAD    := 'Despertador Mortis';
SET @SUBNAME_UNDEAD := 'Boticario de la Sociedad Real';
SET @GOSSIP_UNDEAD  := 80009;
SET @MODEL_UNDEAD   := 10837;
SET @EQUIP_UNDEAD   := 80009;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_UNDEAD;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_UNDEAD, 0, 0, 0, 0, 0, @NAME_UNDEAD, @SUBNAME_UNDEAD, NULL, @GOSSIP_UNDEAD, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_UNDEAD;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_UNDEAD, 0, @MODEL_UNDEAD, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_UNDEAD;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_UNDEAD, @EQUIP_UNDEAD, 33294, 0, 0);

-- Blood Elf: Magister Vael'thor (Isla Caminante del Sol)
SET @ENTRY_BELF     := 80010;
SET @NAME_BELF      := 'Magister Vael\'thor';
SET @SUBNAME_BELF   := 'Magister de Quel\'Thalas';
SET @GOSSIP_BELF    := 80010;
SET @MODEL_BELF     := 17827;
SET @EQUIP_BELF     := 80010;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY_BELF;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES (@ENTRY_BELF, 0, 0, 0, 0, 0, @NAME_BELF, @SUBNAME_BELF, NULL, @GOSSIP_BELF, 83, 83, 0, 1735, 1, 1, 1, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 1, 768, 2048, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 'npc_promotion', 12340);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY_BELF;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (@ENTRY_BELF, 0, @MODEL_BELF, 1, 1, 0);

DELETE FROM `creature_equip_template` WHERE `CreatureID` = @ENTRY_BELF;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`)
VALUES (@ENTRY_BELF, @EQUIP_BELF, 34065, 0, 0);
