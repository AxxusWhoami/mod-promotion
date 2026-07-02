-- Fix: Creature 80004 (Ilythien Cantoestelar) model set to Night Elf sentinel (22490)
-- Ensures the Night Elf Level Up Master uses the correct female druid/sentinel appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80004;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80004, 0, 22490, 1, 1, 0);
