-- Fix: Creature 80003 (Chispas Tuercarrueda) model changed to Gnomeregan Explorer (20039)
-- Replaces the gnome engineer work clothes (20469) with the Gnomeregan Peacekeeper/Explorer appearance.

DELETE FROM `creature_template_model` WHERE `CreatureID` = 80003;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES (80003, 0, 20039, 1, 1, 0);
