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
--
-- NOTA: Los personajes deben estar desconectados al ejecutar este SQL.
-- Si un personaje nivel 80 está en línea, su taximask en memoria sobreescribirá
-- este cambio al guardar al desloguear. Reinicia el servidor o pide a esos
-- jugadores que relogueen para que el cambio tome efecto.

-- Vista previa: cuántos personajes nivel 80 se verán afectados.
SELECT COUNT(*) AS personajes_nivel_80 FROM `characters` WHERE `level` = 80;

-- Listado detallado (opcional, quita el comentario para revisar antes).
-- SELECT `guid`, `name`, `race`, `class`, `level` FROM `characters` WHERE `level` = 80 ORDER BY `name`;

UPDATE `characters`
   SET `taximask` = '4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 4294967295 '
 WHERE `level` = 80;
