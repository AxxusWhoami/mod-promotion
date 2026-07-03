-- Fix: Creature 80001 (Sir Alistar) display ID corrected to a verified human male model.
-- Display 2664 is not a human appearance in WotLK 3.3.5a (build 12340).
-- Display 383 = Marshal Windsor / Stormwind Knight (human male, full plate armor).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80001;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80001, 0, 383, 1, 1, 0);
