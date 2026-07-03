-- Fix: Creature 80004 (Ilythien Cantoestelar) missing row in creature_template_model.
-- Display 22490 = Night Elf female sentinel/druid (leather + staff).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80004;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80004, 0, 22490, 1, 1, 0);
