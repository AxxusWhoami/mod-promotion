-- Fix: Creature 80010 (Magister Vael'thor) model corrected to valid Blood Elf male Magister (15826)
-- The previous display ID (17827) does not exist in CreatureDisplayInfo.dbc (3.3.5a build 12340).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80010;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80010, 0, 15826, 1, 1, 0);
