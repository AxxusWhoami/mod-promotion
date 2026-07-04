-- Update creature display IDs for all 11 promotion race NPCs.
-- Replaces generic placeholder models with lore-accurate, visually distinct appearances.
-- 80001 Human        : 10116  Argent Dawn Officer
-- 80002 Dwarf         : 10125  Ironforge Guard
-- 80003 Gnome         : 15880  Gnome Engineer (goggles + tools)
-- 80004 Night Elf     : 3679   Archdruid (nature robes, Fandral-type)
-- 80005 Draenei       : 17351  Aldor Vindicator (crystal plate)
-- 80006 Orc           : 21330  Kor'kron Guard (black plate)
-- 80007 Troll         : 10134  Blackspear Guard (tribal + lance)
-- 80008 Tauren        : 14457  Thunderbluff Brave (leather/plate)
-- 80009 Undead        : 10136  Deathstalker / Undercity Guard
-- 80010 Blood Elf     : 17294  Silvermoon Magister (red robes)
-- 80011 Death Knight  : 25419  Ebon Blade (saronite armor)

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80001;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80001, 0, 10116, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80002;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80002, 0, 10125, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80003;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80003, 0, 15880, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80004;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80004, 0, 3679, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80005;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80005, 0, 17351, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80006;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80006, 0, 21330, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80007;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80007, 0, 10134, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80008;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80008, 0, 14457, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80009;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80009, 0, 10136, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80010;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80010, 0, 17294, 1, 1, 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80011;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80011, 0, 25419, 1, 1, 0);
