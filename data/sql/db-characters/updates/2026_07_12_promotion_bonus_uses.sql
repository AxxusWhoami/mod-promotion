-- Migration: allow multiple promotion claims per account (default 1 + bonus grants)
-- Supports both fresh installations and databases with the original mod_promotion_log table.

-- Ensure the log exists when the update file is applied before the base files.
CREATE TABLE IF NOT EXISTS `mod_promotion_log` (
    `id`             INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `account_id`     INT UNSIGNED NOT NULL,
    `character_guid` INT UNSIGNED NOT NULL DEFAULT 0,
    `character_name` VARCHAR(12)  NOT NULL DEFAULT '',
    `timestamp`      INT UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (`id`),
    INDEX `idx_account_id` (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='mod_promotion: one row per promotion claim (default + bonus uses)';

-- 1. Drop the old primary key on account_id and add an auto-increment id column
--    as the new primary key, plus an index on account_id — all in one statement
--    so the AUTO_INCREMENT column is a key from the moment it is created.
SET @pk_is_account = (SELECT COUNT(*) FROM information_schema.KEY_COLUMN_USAGE
    WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'mod_promotion_log'
      AND CONSTRAINT_NAME = 'PRIMARY' AND COLUMN_NAME = 'account_id');
SET @sql = IF(@pk_is_account > 0,
    'ALTER TABLE `mod_promotion_log` DROP PRIMARY KEY, ADD COLUMN `id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY FIRST, ADD INDEX `idx_account_id` (`account_id`)',
    'SELECT 1');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- 2. If the id column already exists but the index does not (partial migration re-run).
SET @idx_exists = (SELECT COUNT(*) FROM information_schema.STATISTICS
    WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'mod_promotion_log' AND INDEX_NAME = 'idx_account_id');
SET @sql = IF(@idx_exists = 0,
    'ALTER TABLE `mod_promotion_log` ADD INDEX `idx_account_id` (`account_id`)',
    'SELECT 1');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- 3. Create the bonus table.
CREATE TABLE IF NOT EXISTS `mod_promotion_bonus` (
    `account_id`  INT UNSIGNED NOT NULL,
    `bonus_count` INT UNSIGNED NOT NULL DEFAULT 0,
    `added_at`    INT UNSIGNED NOT NULL DEFAULT 0,
    `added_by`    VARCHAR(12)  NOT NULL DEFAULT '',
    PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='mod_promotion: additional promotion uses granted to specific accounts';
