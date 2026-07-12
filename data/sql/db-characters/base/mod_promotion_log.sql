CREATE TABLE IF NOT EXISTS `mod_promotion_log` (
    `id`             INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `account_id`     INT UNSIGNED NOT NULL,
    `character_guid` INT UNSIGNED NOT NULL DEFAULT 0,
    `character_name` VARCHAR(12)  NOT NULL DEFAULT '',
    `timestamp`      INT UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (`id`),
    INDEX `idx_account_id` (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='mod_promotion: one row per promotion claim (default + bonus uses)';
