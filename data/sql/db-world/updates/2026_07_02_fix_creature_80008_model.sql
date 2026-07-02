-- Fix: Creature 80008 (Bramido Pezuñaferrea) model changed to Tauren High Chieftain (3897)
-- Replaces the invalid warrior/shaman model (3975) with the ceremonial chieftain appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80008;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80008, 0, 3897, 1, 1, 0);
