-- Fix: Creature 80005 (Vindicador Kuros) model changed to Exodar Explorer (18937)
-- Replaces the Draenei Vindicator crystal plate (21267) with lighter explorer/traveler appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80005;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80005, 0, 18937, 1, 1, 0);
