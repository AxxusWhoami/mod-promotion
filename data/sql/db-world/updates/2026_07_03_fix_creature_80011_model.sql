-- Fix: Creature 80011 (Skip el Velocista) missing row in creature_template_model.
-- Display 25278 = Death Knight Acherus dark plate armor.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80011;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80011, 0, 25278, 1, 1, 0);
