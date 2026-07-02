-- Fix: Creature 80001 (Sir Alistar) model changed to Stormwind Knight (2664)
-- Replaces the Seventh Legion soldier (25003) with the classic Alliance knight appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80001;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80001, 0, 2664, 1, 1, 0);
