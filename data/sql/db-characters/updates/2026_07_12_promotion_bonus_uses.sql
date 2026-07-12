-- Migration: allow multiple promotion claims per account (default 1 + bonus grants)
-- Applies to databases that already have the original mod_promotion_log table.

-- 1. Add an auto-increment id column if it does not exist.
SET @col_exists = (SELECT COUNT(*) FROM information_schema.COLUMNS
    WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'mod_promotion_log' AND COLUMN_NAME = 'id');
SET @sql = IF(@col_exists = 0,
    'ALTER TABLE `mod_promotion_log` ADD COLUMN `id` INT UNSIGNED NOT NULL AUTO_INCREMENT FIRST, ADD INDEX `idx_account_id` (`account_id`)',
    'SELECT 1');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- 2. Drop the old primary key constraint on account_id (if it is the PK).
SET @pk_is_account = (SELECT COUNT(*) FROM information_schema.KEY_COLUMN_USAGE
    WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'mod_promotion_log'
      AND CONSTRAINT_NAME = 'PRIMARY' AND COLUMN_NAME = 'account_id');
SET @sql = IF(@pk_is_account > 0,
    'ALTER TABLE `mod_promotion_log` DROP PRIMARY KEY, ADD PRIMARY KEY (`id`)',
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
