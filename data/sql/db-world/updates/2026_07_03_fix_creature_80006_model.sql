-- Fix: Creature 80006 (Gor'thak el Curtido) missing row in creature_template_model.
-- Display 3890 = Orc male Orgrimmar Grunt (red/black plate + axe).

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80006;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80006, 0, 3890, 1, 1, 0);
