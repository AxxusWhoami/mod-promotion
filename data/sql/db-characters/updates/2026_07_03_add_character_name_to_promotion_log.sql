ALTER TABLE `mod_promotion_log`
    ADD COLUMN `character_name` VARCHAR(12) NOT NULL DEFAULT '' AFTER `character_guid`;
