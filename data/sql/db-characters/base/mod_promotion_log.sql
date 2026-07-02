CREATE TABLE IF NOT EXISTS `mod_promotion_log` (
    `account_id`     INT UNSIGNED NOT NULL,
    `character_guid` INT UNSIGNED NOT NULL DEFAULT 0,
    `timestamp`      INT UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='mod_promotion: one row per account that has claimed a promotion';
