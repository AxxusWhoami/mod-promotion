-- Fix: Creature 80008 (Bramido Pezuñaferrea) display ID corrected to a verified Tauren male model.
-- Display 3897 is an Orc model in WotLK 3.3.5a (build 12340), not Tauren.
-- Display 4883 = Cairne Bloodhoof / Tauren High Chieftain (ceremonial male Tauren).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80008;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80008, 0, 4883, 1, 1, 0);
