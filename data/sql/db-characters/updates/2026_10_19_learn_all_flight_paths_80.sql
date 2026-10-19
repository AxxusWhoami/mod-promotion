-- Teach every flight path to all level-80 characters.
-- Run against the characters database (e.g. acore_characters).
--
-- The taxi mask is a space-separated list of 8 x uint32 bitmasks.
-- Each bit corresponds to a taxi node ID. Setting all bits to 0xFFFFFFFF
-- covers every node on all four continents (Eastern Kingdoms, Kalimdor,
-- Outland, Northrend). Unknown/unused bits are ignored at runtime.

UPDATE `character_taxi`
   SET `mask` = '4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295'
 WHERE `guid` IN (SELECT `guid` FROM `characters` WHERE `level` = 80);
