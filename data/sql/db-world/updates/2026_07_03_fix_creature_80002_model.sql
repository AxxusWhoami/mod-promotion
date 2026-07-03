-- Fix: Creature 80002 (Thormir Barbaferro) missing row in creature_template_model.
-- Display 26047 = Dwarf male Ironforge Mountaineer (mail + rifle).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80002;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80002, 0, 26047, 1, 1, 0);
