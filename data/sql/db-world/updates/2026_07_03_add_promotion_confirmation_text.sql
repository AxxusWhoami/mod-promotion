-- npc_text 80004: shown during the optional confirmation step (Promotion.ConfirmationStep = true)

DELETE FROM `broadcast_text` WHERE `ID` = 80004;
INSERT INTO `broadcast_text` (`ID`, `LanguageID`, `MaleText`, `FemaleText`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `SoundEntriesID`, `EmotesID`, `Flags`, `VerifiedBuild`)
VALUES (80004, 0, 'Are you sure you want to claim your one-time promotion? This action cannot be undone.', 'Are you sure you want to claim your one-time promotion? This action cannot be undone.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `npc_text` WHERE `ID` = 80004;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`)
VALUES
  (80004,
   'Are you sure you want to claim your one-time promotion, $n? This action cannot be undone.', 'Are you sure you want to claim your one-time promotion, $n? This action cannot be undone.', 80004, 0, 1, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   'Greetings, $n.', 'Greetings, $n.', 50429, 0, 0, 0, 0, 0, 0, 0, 0,
   0);

DELETE FROM `broadcast_text_locale` WHERE `ID` = 80004;
INSERT INTO `broadcast_text_locale` (`ID`, `locale`, `MaleText`, `FemaleText`, `VerifiedBuild`)
VALUES
  (80004, 'esES', '¿Estás seguro de que deseas reclamar tu promoción única, $n? Esta acción no puede deshacerse.', '¿Estás segura de que deseas reclamar tu promoción única, $n? Esta acción no puede deshacerse.', 0),
  (80004, 'esMX', '¿Estás seguro de que deseas reclamar tu promoción única, $n? Esta acción no puede deshacerse.', '¿Estás segura de que deseas reclamar tu promoción única, $n? Esta acción no puede deshacerse.', 0),
  (80004, 'ruRU', 'Вы уверены, что хотите получить свою одноразовую акцию, $n? Это действие нельзя отменить.', 'Вы уверены, что хотите получить свою одноразовую акцию, $n? Это действие нельзя отменить.', 0),
  (80004, 'frFR', 'Êtes-vous sûr de vouloir réclamer votre promotion unique, $n ? Cette action ne peut pas être annulée.', 'Êtes-vous sûre de vouloir réclamer votre promotion unique, $n ? Cette action ne peut pas être annulée.', 0),
  (80004, 'deDE', 'Bist du sicher, dass du deine einmalige Förderung beanspruchen möchtest, $n? Diese Aktion kann nicht rückgängig gemacht werden.', 'Bist du sicher, dass du deine einmalige Förderung beanspruchen möchtest, $n? Diese Aktion kann nicht rückgängig gemacht werden.', 0),
  (80004, 'zhCN', '你确定要领取你的一次性促销，$n？此操作无法撤销。', '你确定要领取你的一次性促销，$n？此操作无法撤销。', 0),
  (80004, 'zhTW', '你確定要領取你的一次性促銷，$n？此操作無法撤銷。', '你確定要領取你的一次性促銷，$n？此操作無法撤銷。', 0),
  (80004, 'koKR', '$n, 일회성 프로모션을 받으시겠습니까? 이 작업은 취소할 수 없습니다.', '$n, 일회성 프로모션을 받으시겠습니까? 이 작업은 취소할 수 없습니다.', 0);

DELETE FROM `npc_text_locale` WHERE `ID` = 80004;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `text0_0`, `text0_1`, `text1_0`, `text1_1`, `text2_0`, `text2_1`, `text3_0`, `text3_1`, `text4_0`, `text4_1`, `text5_0`, `text5_1`, `text6_0`, `text6_1`, `text7_0`, `text7_1`)
VALUES
  (80004, 'esES', '¿Estás seguro/a de que deseas reclamar tu promoción, $n? Esta acción no puede deshacerse.', '¿Estás seguro/a de que deseas reclamar tu promoción, $n? Esta acción no puede deshacerse.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80004, 'esMX', '¿Estás seguro/a de que deseas reclamar tu promoción, $n? Esta acción no puede deshacerse.', '¿Estás seguro/a de que deseas reclamar tu promoción, $n? Esta acción no puede deshacerse.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.', 'Saludos, $n.'),
  (80004, 'ruRU', 'Вы уверены, что хотите получить акцию, $n? Это действие нельзя отменить.', 'Вы уверены, что хотите получить акцию, $n? Это действие нельзя отменить.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.', 'Приветствую, $n.'),
  (80004, 'frFR', 'Êtes-vous sûr de vouloir réclamer votre promotion, $n ? Cette action est irréversible.', 'Êtes-vous sûre de vouloir réclamer votre promotion, $n ? Cette action est irréversible.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.', 'Bonjour, $n.'),
  (80004, 'deDE', 'Bist du sicher, $n? Diese Aktion kann nicht rückgängig gemacht werden.', 'Bist du sicher, $n? Diese Aktion kann nicht rückgängig gemacht werden.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.', 'Willkommen, $n.'),
  (80004, 'zhCN', '$n，你确定要领取促销？此操作无法撤销。', '$n，你确定要领取促销？此操作无法撤销。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。', '你好，$n。'),
  (80004, 'zhTW', '$n，你確定要領取促銷？此操作無法撤銷。', '$n，你確定要領取促銷？此操作無法撤銷。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。', '您好，$n。'),
  (80004, 'koKR', '$n, 프로모션을 받으시겠습니까? 이 작업은 취소할 수 없습니다.', '$n, 프로모션을 받으시겠습니까? 이 작업은 취소할 수 없습니다.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.', '안녕하세요, $n.');
