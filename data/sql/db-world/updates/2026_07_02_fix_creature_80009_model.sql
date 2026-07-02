-- Fix: Creature 80009 (Despertador Mortis) model corrected to valid Forsaken Deathguard (905)
-- The previous display ID (10837) does not exist in CreatureDisplayInfo.dbc (3.3.5a build 12340).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80009;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80009, 0, 905, 1, 1, 0);
