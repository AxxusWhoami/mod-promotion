-- Fix: Creature 80007 (Jin'zaki) missing row in creature_template_model.
-- Display 9528 = Troll male Witch Doctor (voodoo mask + lances).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80007;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80007, 0, 9528, 1, 1, 0);
