-- Grant RBAC_PERM_JOIN_DUNGEON_FINDER (permission ID 6) to accounts that lost it.
-- Run this for each affected account ID, or for all accounts if unsure:
--
--   INSERT INTO rbac_account_permissions (accountId, permissionId, realmId, granted)
--   VALUES (<accountId>, 6, -1, 1)
--   ON DUPLICATE KEY UPDATE granted = 1;
--
-- To grant to ALL accounts at once (safe — this is the default permission for normal players):
INSERT INTO rbac_account_permissions (accountId, permissionId, realmId, granted)
SELECT id, 6, -1, 1 FROM account
ON DUPLICATE KEY UPDATE granted = 1;
