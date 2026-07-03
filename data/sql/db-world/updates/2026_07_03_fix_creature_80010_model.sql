-- Fix: Creature 80010 (Magister Vael'thor) missing row in creature_template_model.
-- Display 15394 = Blood Elf male Arcanist (arcane robes, Sunstrider Isle).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80010;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80010, 0, 15394, 1, 1, 0);
