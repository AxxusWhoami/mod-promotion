-- Fix: Creature 80009 (Despertador Mortis) model corrected to valid Forsaken male hooded robe (2842)
-- Previous display IDs 10837 and 905 do not exist in CreatureDisplayInfo.dbc (3.3.5a build 12340).
-- 2842 is confirmed valid: used by Shadow Priest Sarvis (entry 1236) in Deathknell.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80009;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80009, 0, 2842, 1, 1, 0);
