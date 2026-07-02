DELETE FROM `broadcast_text` WHERE `ID` = 80000;
INSERT INTO `broadcast_text` (`ID`, `LanguageID`, `MaleText`, `FemaleText`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `SoundEntriesID`, `EmotesID`, `Flags`, `VerifiedBuild`)
VALUES (80000, 0, 'Our promotion period is over. Thank you very much for play on CoRe Legacy Realms.', 'Our promotion period is over. Thank you very much for play on CoRe Legacy Realms.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `npc_text` WHERE `ID` = 80000;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`)
VALUES
  (80000,
   'Greetings, $n, Our promotion period is over. Thank you very much for play on CoRe Legacy Realms.', 'Greetings, $n, Our promotion period is over. Thank you very much for play on CoRe Legacy Realms.', 80000, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   0);

DELETE FROM `broadcast_text_locale` WHERE `ID` = 80000;
INSERT INTO `broadcast_text_locale` (`ID`, `locale`, `MaleText`, `FemaleText`, `VerifiedBuild`)
VALUES
  (80000, 'koKR', '프로모션 기간이 종료되었습니다. 서버에 함께해 주셔서 감사합니다.', '프로모션 기간이 종료되었습니다. 서버에 함께해 주셔서 감사합니다.', 0),
  (80000, 'frFR', 'Notre période de promotion est terminée. Merci beaucoup d\'être sur le serveur.', 'Notre période de promotion est terminée. Merci beaucoup d\'être sur le serveur.', 0),
  (80000, 'deDE', 'Unser Aktionszeitraum ist vorbei. Vielen Dank, dass Sie auf dem Server sind.', 'Unser Aktionszeitraum ist vorbei. Vielen Dank, dass Sie auf dem Server sind.', 0),
  (80000, 'zhCN', '我们的促销期已结束。非常感谢您在服务器上。', '我们的促销期已结束。非常感谢您在服务器上。', 0),
  (80000, 'zhTW', '我們的促銷期已結束。非常感謝您在伺服器上。', '我們的促銷期已結束。非常感謝您在伺服器上。', 0),
  (80000, 'esES', 'Nuestro período de promoción ha terminado. Muchas gracias por jugar en los reinos de CoRe Legacy.', 'Nuestro período de promoción ha terminado. Muchas gracias por jugar en los reinos de CoRe Legacy.', 0),
  (80000, 'esMX', 'Nuestro período de promoción ha terminado. Muchas gracias por jugar en los reinos de CoRe Legacy.', 'Nuestro período de promoción ha terminado. Muchas gracias por jugar en los reinos de CoRe Legacy.', 0),
  (80000, 'ruRU', 'Наш акционный период завершён. Большое спасибо, что вы на сервере.', 'Наш акционный период завершён. Большое спасибо, что вы на сервере.', 0);

DELETE FROM `npc_text_locale` WHERE `ID` = 80000;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `text0_0`, `text0_1`, `text1_0`, `text1_1`, `text2_0`, `text2_1`, `text3_0`, `text3_1`, `text4_0`, `text4_1`, `text5_0`, `text5_1`, `text6_0`, `text6_1`, `text7_0`, `text7_1`)
VALUES
  (80000, 'koKR', '안녕하세요, $n. 프로모션이 완전히 비활성화되어 있습니다.', '안녕하세요, $n. 프로모션이 완전히 비활성화되어 있습니다.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.'),
  (80000, 'frFR', 'Bonjour, $n. La promotion est totalement désactivée.', 'Bonjour, $n. La promotion est totalement désactivée.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.'),
  (80000, 'deDE', 'Willkommen, $n. Die Aktion ist vollständig deaktiviert.', 'Willkommen, $n. Die Aktion ist vollständig deaktiviert.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.'),
  (80000, 'zhCN', '你好，$n。促销活动已完全禁用。', '你好，$n。促销活动已完全禁用。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。'),
  (80000, 'zhTW', '您好，$n。促銷活動已完全停用。', '您好，$n。促銷活動已完全停用。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。'),
  (80000, 'esES', 'Saludos, $n. La Promoción está Totalmente Desactivada.', 'Saludos, $n. La Promoción está Totalmente Desactivada.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80000, 'esMX', 'Saludos, $n. La Promoción está Totalmente Desactivada.', 'Saludos, $n. La Promoción está Totalmente Desactivada.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80000, 'ruRU', 'Приветствую, $n. Акция полностью отключена.', 'Приветствую, $n. Акция полностью отключена.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.');

-- npc_text 80001: shown when the account has already claimed its one-time promotion
DELETE FROM `broadcast_text` WHERE `ID` = 80001;
INSERT INTO `broadcast_text` (`ID`, `LanguageID`, `MaleText`, `FemaleText`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `SoundEntriesID`, `EmotesID`, `Flags`, `VerifiedBuild`)
VALUES (80001, 0, 'I\'m sorry, adventurer. The promotion has already been claimed on your account.', 'I\'m sorry, adventurer. The promotion has already been claimed on your account.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `npc_text` WHERE `ID` = 80001;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`)
VALUES
  (80001,
   'I\'m sorry, $n. The promotion has already been claimed on your account.', 'I\'m sorry, $n. The promotion has already been claimed on your account.', 80001, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   0);

DELETE FROM `broadcast_text_locale` WHERE `ID` = 80001;
INSERT INTO `broadcast_text_locale` (`ID`, `locale`, `MaleText`, `FemaleText`, `VerifiedBuild`)
VALUES
  (80001, 'koKR', '죄송합니다, 모험가님. 이 계정에서 이미 프로모션을 사용하셨습니다.', '죄송합니다, 모험가님. 이 계정에서 이미 프로모션을 사용하셨습니다.', 0),
  (80001, 'frFR', 'Je suis désolé, aventurier. La promotion a déjà été réclamée sur ce compte.', 'Je suis désolée, aventurière. La promotion a déjà été réclamée sur ce compte.', 0),
  (80001, 'deDE', 'Es tut mir leid, Abenteurer. Die Aktion wurde auf diesem Konto bereits beansprucht.', 'Es tut mir leid, Abenteurerin. Die Aktion wurde auf diesem Konto bereits beansprucht.', 0),
  (80001, 'zhCN', '很抱歉，冒险者。该帐户已经领取过一次性升级优惠。', '很抱歉，冒险者。该帐户已经领取过一次性升级优惠。', 0),
  (80001, 'zhTW', '很抱歉，冒險者。該帳戶已經領取過一次性升級優惠。', '很抱歉，冒險者。該帳戶已經領取過一次性升級優惠。', 0),
  (80001, 'esES', 'Lo siento, aventurero. La promoción ya ha sido reclamada en esta cuenta.', 'Lo siento, aventurera. La promoción ya ha sido reclamada en esta cuenta.', 0),
  (80001, 'esMX', 'Lo siento, aventurero. La promoción ya ha sido reclamada en esta cuenta.', 'Lo siento, aventurera. La promoción ya ha sido reclamada en esta cuenta.', 0),
  (80001, 'ruRU', 'Сожалею, искатель приключений. Акция на этом аккаунте уже была использована.', 'Сожалею, искательница приключений. Акция на этом аккаунте уже была использована.', 0);

DELETE FROM `npc_text_locale` WHERE `ID` = 80001;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `text0_0`, `text0_1`, `text1_0`, `text1_1`, `text2_0`, `text2_1`, `text3_0`, `text3_1`, `text4_0`, `text4_1`, `text5_0`, `text5_1`, `text6_0`, `text6_1`, `text7_0`, `text7_1`)
VALUES
  (80001, 'koKR', '죄송합니다, $n. 이 계정에서 이미 프로모션을 사용하셨습니다.', '죄송합니다, $n. 이 계정에서 이미 프로모션을 사용하셨습니다.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.'),
  (80001, 'frFR', 'Je suis désolé, $n. La promotion a déjà été réclamée sur ce compte.', 'Je suis désolée, $n. La promotion a déjà été réclamée sur ce compte.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.'),
  (80001, 'deDE', 'Es tut mir leid, $n. Die Aktion wurde auf diesem Konto bereits beansprucht.', 'Es tut mir leid, $n. Die Aktion wurde auf diesem Konto bereits beansprucht.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.'),
  (80001, 'zhCN', '很抱歉，$n。该帐户已经领取过一次性升级优惠。', '很抱歉，$n。该帐户已经领取过一次性升级优惠。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。'),
  (80001, 'zhTW', '很抱歉，$n。該帳戶已經領取過一次性升級優惠。', '很抱歉，$n。該帳戶已經領取過一次性升級優惠。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。'),
  (80001, 'esES', 'Lo siento, $n. La promoción ya ha sido reclamada en esta cuenta.', 'Lo siento, $n. La promoción ya ha sido reclamada en esta cuenta.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80001, 'esMX', 'Lo siento, $n. La promoción ya ha sido reclamada en esta cuenta.', 'Lo siento, $n. La promoción ya ha sido reclamada en esta cuenta.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80001, 'ruRU', 'Сожалею, $n. Акция на этом аккаунте уже была использована.', 'Сожалею, $n. Акция на этом аккаунте уже была использована.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.');

-- npc_text 80002: normal greeting shown when the player can choose a spec
DELETE FROM `broadcast_text` WHERE `ID` = 80002;
INSERT INTO `broadcast_text` (`ID`, `LanguageID`, `MaleText`, `FemaleText`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `SoundEntriesID`, `EmotesID`, `Flags`, `VerifiedBuild`)
VALUES (80002, 0, 'Greetings, adventurer! I am your Level Up Master. Choose your specialization to claim your one-time promotion package.', 'Greetings, adventurer! I am your Level Up Master. Choose your specialization to claim your one-time promotion package.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `npc_text` WHERE `ID` = 80002;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`)
VALUES
  (80002,
   'Greetings, $n! I am your Level Up Master. Choose your specialization to claim your one-time promotion package.', 'Greetings, $n! I am your Level Up Master. Choose your specialization to claim your one-time promotion package.', 80002, 0, 1, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   0);

DELETE FROM `broadcast_text_locale` WHERE `ID` = 80002;
INSERT INTO `broadcast_text_locale` (`ID`, `locale`, `MaleText`, `FemaleText`, `VerifiedBuild`)
VALUES
  (80002, 'koKR', '모험가님, 안녕하세요! 저는 당신의 레벨업 마스터입니다. 전문화를 선택하여 일회성 프로모션 패키지를 받으세요.', '모험가님, 안녕하세요! 저는 당신의 레벨업 마스터입니다. 전문화를 선택하여 일회성 프로모션 패키지를 받으세요.', 0),
  (80002, 'frFR', 'Bienvenue, aventurier ! Je suis votre Maître de Niveau. Choisissez votre spécialisation pour recevoir votre pack de promotion unique.', 'Bienvenue, aventurière ! Je suis votre Maître de Niveau. Choisissez votre spécialisation pour recevoir votre pack de promotion unique.', 0),
  (80002, 'deDE', 'Willkommen, Abenteurer! Ich bin dein Aufstiegs-Meister. Wähle deine Spezialisierung, um dein einmaliges Förderpaket zu erhalten.', 'Willkommen, Abenteurerin! Ich bin dein Aufstiegs-Meister. Wähle deine Spezialisierung, um dein einmaliges Förderpaket zu erhalten.', 0),
  (80002, 'zhCN', '欢迎，冒险者！我是你的升级大师。请选择你的专精以领取一次性促销礼包。', '欢迎，冒险者！我是你的升级大师。请选择你的专精以领取一次性促销礼包。', 0),
  (80002, 'zhTW', '歡迎，冒險者！我是你的升級大師。請選擇你的專精以領取一次性促銷禮包。', '歡迎，冒險者！我是你的升級大師。請選擇你的專精以領取一次性促銷禮包。', 0),
  (80002, 'esES', '¡Bienvenido, aventurero! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción único.', '¡Bienvenida, aventurera! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción único.', 0),
  (80002, 'esMX', '¡Bienvenido, aventurero! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción único.', '¡Bienvenida, aventurera! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción único.', 0),
  (80002, 'ruRU', 'Приветствую, искатель приключений! Я твой Мастер Повышения. Выбери специализацию, чтобы получить свой одноразовый пакет продвижения.', 'Приветствую, искательница приключений! Я твой Мастер Повышения. Выбери специализацию, чтобы получить свой одноразовый пакет продвижения.', 0);

DELETE FROM `npc_text_locale` WHERE `ID` = 80002;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `text0_0`, `text0_1`, `text1_0`, `text1_1`, `text2_0`, `text2_1`, `text3_0`, `text3_1`, `text4_0`, `text4_1`, `text5_0`, `text5_1`, `text6_0`, `text6_1`, `text7_0`, `text7_1`)
VALUES
  (80002, 'koKR', '안녕하세요, $n! 저는 당신의 레벨업 마스터입니다. 전문화를 선택하여 프로모션 패키지를 받으세요.', '안녕하세요, $n! 저는 당신의 레벨업 마스터입니다. 전문화를 선택하여 프로모션 패키지를 받으세요.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.'),
  (80002, 'frFR', 'Bienvenue, $n ! Je suis votre Maître de Niveau. Choisissez votre spécialisation pour recevoir votre pack de promotion.', 'Bienvenue, $n ! Je suis votre Maître de Niveau. Choisissez votre spécialisation pour recevoir votre pack de promotion.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.'),
  (80002, 'deDE', 'Willkommen, $n! Ich bin dein Aufstiegs-Meister. Wähle deine Spezialisierung für dein Förderpaket.', 'Willkommen, $n! Ich bin dein Aufstiegs-Meister. Wähle deine Spezialisierung für dein Förderpaket.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.'),
  (80002, 'zhCN', '你好，$n！我是你的升级大师。请选择你的专精以领取促销礼包。', '你好，$n！我是你的升级大师。请选择你的专精以领取促销礼包。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。'),
  (80002, 'zhTW', '您好，$n！我是你的升級大師。請選擇你的專精以領取促銷禮包。', '您好，$n！我是你的升級大師。請選擇你的專精以領取促銷禮包。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。'),
  (80002, 'esES', '¡Bienvenido, $n! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción.', '¡Bienvenida, $n! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80002, 'esMX', '¡Bienvenido, $n! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción.', '¡Bienvenida, $n! Soy tu Maestro de Subida de Nivel. Elige tu especialización para reclamar tu paquete de promoción.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80002, 'ruRU', 'Приветствую, $n! Я твой Мастер Повышения. Выбери специализацию для получения пакета продвижения.', 'Приветствую, $n! Я твой Мастер Повышения. Выбери специализацию для получения пакета продвижения.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.');
