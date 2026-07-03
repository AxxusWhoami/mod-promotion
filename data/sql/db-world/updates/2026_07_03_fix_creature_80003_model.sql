-- Fix: Creature 80003 (Chispas Tuercarrueda) missing row in creature_template_model.
-- Display 20039 = Gnome male Gnomeregan Explorer (light armor + scout gear).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80003;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80003, 0, 20039, 1, 1, 0);
