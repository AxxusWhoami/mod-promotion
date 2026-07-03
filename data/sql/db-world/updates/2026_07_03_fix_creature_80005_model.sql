-- Fix: Creature 80005 (Vindicador Kuros) missing row in creature_template_model.
-- Ensures the Draenei Exodar Explorer appearance (18937) is present.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80005;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80005, 0, 18937, 1, 1, 0);
