CREATE TABLE IF NOT EXISTS `mod_promotion_bonus` (
    `account_id`  INT UNSIGNED NOT NULL,
    `bonus_count` INT UNSIGNED NOT NULL DEFAULT 0,
    `added_at`    INT UNSIGNED NOT NULL DEFAULT 0,
    `added_by`    VARCHAR(12)  NOT NULL DEFAULT '',
    PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='mod_promotion: additional promotion uses granted to specific accounts';
