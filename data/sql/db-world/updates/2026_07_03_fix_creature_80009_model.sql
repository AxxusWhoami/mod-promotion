-- Fix: Creature 80009 (Despertador Mortis) missing row in creature_template_model.
-- Ensures the Forsaken male hooded robe appearance (2842) is present.
-- Display 2842 = Shadow Priest Sarvis-type (confirmed valid in build 12340).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80009;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80009, 0, 2842, 1, 1, 0);
