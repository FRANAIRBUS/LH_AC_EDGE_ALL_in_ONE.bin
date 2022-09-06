
--
-- Base de datos: `ESP32`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `NAMETABLE`
--

CREATE TABLE `NAMETABLE` (
  `id` int(10) UNSIGNED NOT NULL,
  `reading_time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Name` varchar(30) DEFAULT NULL,
  `Location` varchar(30) DEFAULT NULL,
  `Temp1` varchar(10) DEFAULT NULL,
  `Temp2` varchar(10) DEFAULT NULL,
  `Temp3` varchar(10) DEFAULT NULL,
  `Hum1` varchar(10) DEFAULT NULL,
  `Hum2` varchar(10) DEFAULT NULL,
  `Hum3` varchar(10) DEFAULT NULL,
  `Set1` varchar(10) DEFAULT NULL,
  `Set2` varchar(10) DEFAULT NULL,
  `Set3` varchar(10) DEFAULT NULL,
  `REL1` varchar(10) DEFAULT NULL,
  `REL2` varchar(10) DEFAULT NULL,
  `REL3` varchar(10) DEFAULT NULL,
  `REL4` varchar(10) DEFAULT NULL,
  `AUX1` varchar(10) DEFAULT NULL,
  `AUX2` varchar(10) DEFAULT NULL,
  `In1` varchar(10) DEFAULT NULL,
  `In2` varchar(10) DEFAULT NULL,
  `In3` varchar(10) DEFAULT NULL,
  `In4` varchar(10) DEFAULT NULL,
  `AL0` varchar(16) DEFAULT NULL,
  `AL1` varchar(10) DEFAULT NULL,
  `AL2` varchar(10) DEFAULT NULL,
  `AL3` varchar(10) DEFAULT NULL,
  `AL4` varchar(10) DEFAULT NULL,
  `AL5` varchar(10) DEFAULT NULL,
  `AL6` varchar(10) DEFAULT NULL,
  `AL7` varchar(10) DEFAULT NULL,
  `AL8` varchar(10) DEFAULT NULL,
  `IP` varchar(16) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

