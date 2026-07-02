-- Fix: Creature 80006 (Gor'thak el Curtido) model set to Orgrimmar Grunt (3890)
-- Ensures the Orc Level Up Master uses the correct red/black plate grunt appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80006;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80006, 0, 3890, 1, 1, 0);
