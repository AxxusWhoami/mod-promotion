-- Enseña todas las rutas de vuelo a los personajes nivel 80.
-- Ejecutar contra la base de datos de personajes (p.ej. acore_characters).
--
-- En AzerothCore el taximask es una columna TEXT directamente en `characters`,
-- formada por 14 valores uint32 separados por espacios. Cada bit corresponde
-- a un nodo de vuelo (TaxiNodes.dbc). Poniendo los 14 a 0xFFFFFFFF se cubren
-- todos los nodos de los 4 continentes (Reinos del Este, Kalimdor, Terrallende,
-- Rascanorte). Los bits de la facción contraria son inofensivos: el servidor
-- los ignora al usar el maestro de vuelo, así que la misma máscara sirve para
-- Horda y Alianza.

UPDATE `characters`
   SET `taximask` = '4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 '
 WHERE `level` = 80;
