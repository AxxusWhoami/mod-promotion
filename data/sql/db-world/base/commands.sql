DELETE FROM `command` WHERE `name` IN ('promotion reset', 'promotion check');
INSERT INTO `command` (`name`, `security`, `help`) VALUES
  ('promotion reset', 2, 'Syntax: .promotion reset $characterName\n\nRemoves the promotion record for the account linked to $characterName, allowing that account to claim the promotion again. Useful for testing or GM support cases.'),
  ('promotion check', 2, 'Syntax: .promotion check $characterName\n\nReports whether the account linked to $characterName has already claimed a promotion, and if so, which character claimed it and when.');
