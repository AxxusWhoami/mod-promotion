-- Fix: Creature 80011 (Skip el Velocista) model set to Acherus Death Knight (25278)
-- Ensures the Death Knight Level Up Master uses the dark plate armor appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80011;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80011, 0, 25278, 1, 1, 0);
