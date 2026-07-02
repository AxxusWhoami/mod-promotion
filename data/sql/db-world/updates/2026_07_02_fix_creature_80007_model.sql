-- Fix: Creature 80007 (Jin'zaki) model set to Troll Witch Doctor (9528)
-- Ensures the Troll Level Up Master uses the correct voodoo mask appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80007;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80007, 0, 9528, 1, 1, 0);
