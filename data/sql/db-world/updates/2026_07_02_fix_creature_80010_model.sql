-- Fix: Creature 80010 (Magister Vael'thor) model corrected to valid Blood Elf male Arcanist (15394)
-- Previous display IDs 17827 and 15826 are not Blood Elf models.
-- 15394 is confirmed valid: used by Arcanist Helion (entry 16588) in Sunstrider Isle (3.3.5a build 12340).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80010;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80010, 0, 15394, 1, 1, 0);
