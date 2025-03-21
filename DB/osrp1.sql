-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sty 25, 2024 at 08:12 PM
-- Wersja serwera: 10.4.28-MariaDB
-- Wersja PHP: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `osrp`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_areas`
--

CREATE TABLE `osrp_areas` (
  `UID` int(2) NOT NULL,
  `OUID` int(2) NOT NULL DEFAULT 0,
  `MinX` float NOT NULL DEFAULT 0,
  `MinY` float NOT NULL DEFAULT 0,
  `MaxX` float NOT NULL DEFAULT 0,
  `MaxY` float NOT NULL DEFAULT 0,
  `MaxSpeed` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_booths`
--

CREATE TABLE `osrp_booths` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Object` int(2) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Range` float NOT NULL DEFAULT 0,
  `Working` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_busstops`
--

CREATE TABLE `osrp_busstops` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '0',
  `Price` int(9) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_busstops`
--

INSERT INTO `osrp_busstops` (`UID`, `Name`, `Price`, `X`, `Y`, `Z`) VALUES
(1, 'Szpital Market', 1, 1189.56, -1359.45, 13.5597),
(2, 'Centrum', 1, 1436.24, -1660.98, 13.5469),
(3, 'Idlewood kolo stacji paliw', 1, 1893.79, -1758.74, 13.5469),
(4, 'Ganton kolo silowni', 1, 2232.69, -1738.3, 13.5469);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_cashpoints`
--

CREATE TABLE `osrp_cashpoints` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '0',
  `Object` int(2) NOT NULL DEFAULT 0,
  `IsOpen` int(1) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_cashpoints`
--

INSERT INTO `osrp_cashpoints` (`UID`, `Name`, `Object`, `IsOpen`, `X`, `Y`, `Z`, `Distance`) VALUES
(1, 'Bankomat', 0, 1, 661.782, -1328.34, 13.6108, 2),
(2, 'Bankomat', 0, 1, 664.434, -1329.04, 13.6238, 2),
(3, 'Bankomat', 0, 1, 675.836, -1327.88, 13.6795, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_contacts`
--

CREATE TABLE `osrp_contacts` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `Number` int(7) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_contacts`
--

INSERT INTO `osrp_contacts` (`UID`, `Number`) VALUES
(1, 8308890);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_doors`
--

CREATE TABLE `osrp_doors` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `OUID` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '0',
  `EnterX` float NOT NULL DEFAULT 0,
  `EnterY` float NOT NULL DEFAULT 0,
  `EnterZ` float NOT NULL DEFAULT 0,
  `ExitX` float NOT NULL DEFAULT 0,
  `ExitY` float NOT NULL DEFAULT 0,
  `ExitZ` float NOT NULL DEFAULT 0,
  `PickupID` int(2) NOT NULL DEFAULT 0,
  `Open` int(1) NOT NULL DEFAULT 0,
  `Tax` int(1) NOT NULL DEFAULT 0,
  `TaxDate` varchar(24) NOT NULL DEFAULT '\\0',
  `TaxCost` int(3) NOT NULL DEFAULT 0,
  `Dimensions` int(1) NOT NULL DEFAULT 0,
  `Objects` int(3) NOT NULL DEFAULT 0,
  `MaxObjects` int(3) NOT NULL DEFAULT 0,
  `Texts` int(3) NOT NULL DEFAULT 0,
  `MaxTexts` int(3) NOT NULL DEFAULT 0,
  `Security` int(1) NOT NULL DEFAULT 0,
  `SecurityName` varchar(32) NOT NULL DEFAULT '\\0',
  `VW` int(9) NOT NULL DEFAULT 0,
  `INT` int(9) NOT NULL DEFAULT 0,
  `Type` int(2) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_doors`
--

INSERT INTO `osrp_doors` (`UID`, `OUID`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `ExitX`, `ExitY`, `ExitZ`, `PickupID`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Dimensions`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `SecurityName`, `VW`, `INT`, `Type`) VALUES
(1, 1, 'Hotel', 881.574, -1336.08, 13.5469, 942.172, -16.5428, 1000.93, 1, 1, 1, '\\0', 0, 0, 0, 0, 0, 0, 0, '\\0', 1, 2, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_gaspumps`
--

CREATE TABLE `osrp_gaspumps` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `SID` int(2) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_gaspumps`
--

INSERT INTO `osrp_gaspumps` (`UID`, `SID`, `X`, `Y`, `Z`, `Distance`) VALUES
(1, 1, 1940.73, -1767.32, 13.3906, 4),
(2, 1, 1940.73, -1771.38, 13.3906, 4),
(3, 1, 1940.73, -1774.35, 13.3906, 4),
(4, 1, 1940.69, -1778.36, 13.3906, 4),
(5, 2, -97.9225, -1173.39, 2.3911, 4),
(6, 2, -92.9576, -1161.43, 2.212, 4),
(7, 2, -86.0421, -1164.7, 2.2441, 4),
(8, 2, -90.9616, -1176.28, 2.1791, 4);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groupitems`
--

CREATE TABLE `osrp_groupitems` (
  `UID` int(3) NOT NULL,
  `OUID` int(2) NOT NULL DEFAULT 0,
  `ID` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(64) NOT NULL DEFAULT '\\0',
  `Price` int(5) NOT NULL DEFAULT 0,
  `Amount` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groups`
--

CREATE TABLE `osrp_groups` (
  `UID` int(9) NOT NULL DEFAULT 0,
  `OUID` int(9) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\0',
  `Tag` varchar(8) NOT NULL DEFAULT '\0',
  `Date` varchar(32) NOT NULL DEFAULT '\\0',
  `Type` int(2) NOT NULL DEFAULT 0,
  `Members` int(2) NOT NULL DEFAULT 0,
  `VehsLimit` int(2) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `PayDay` int(9) NOT NULL DEFAULT 0,
  `Doors` int(9) NOT NULL DEFAULT 0,
  `Flags` int(9) NOT NULL DEFAULT 0,
  `Color` int(9) NOT NULL DEFAULT 0,
  `ChatOOC` int(1) NOT NULL DEFAULT 1,
  `ChatIC` int(1) NOT NULL DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_groups`
--

INSERT INTO `osrp_groups` (`UID`, `OUID`, `Name`, `Tag`, `Date`, `Type`, `Members`, `VehsLimit`, `Money`, `PayDay`, `Doors`, `Flags`, `Color`, `ChatOOC`, `ChatIC`) VALUES
(1, 1, 'Szkola Jazdy LS', 'SJLS', '\\0', 2, 0, 0, 0, 0, 0, 0, 0, 1, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_items`
--

CREATE TABLE `osrp_items` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `ID` int(2) NOT NULL DEFAULT 0,
  `OUID` int(2) NOT NULL DEFAULT 0,
  `VUID` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\0',
  `Values` int(9) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Used` int(1) NOT NULL DEFAULT 0,
  `Place` int(2) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_players`
--

CREATE TABLE `osrp_players` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `GUID` int(2) NOT NULL DEFAULT 0,
  `CharId` int(1) NOT NULL DEFAULT 0,
  `AccName` varchar(24) NOT NULL DEFAULT '\0',
  `CharName` varchar(24) NOT NULL DEFAULT '\0',
  `CharName2` varchar(24) NOT NULL DEFAULT '\0',
  `Pass` varchar(32) NOT NULL DEFAULT '\0',
  `IP` varchar(16) NOT NULL DEFAULT '\0',
  `DateReg` varchar(64) NOT NULL DEFAULT '\0',
  `LastDate` varchar(64) NOT NULL DEFAULT '\0',
  `Blocked` int(1) NOT NULL DEFAULT 0,
  `Gold` int(1) NOT NULL DEFAULT 0,
  `Rank` int(1) NOT NULL DEFAULT 0,
  `Sex` int(1) NOT NULL DEFAULT 0,
  `Strength` int(5) NOT NULL DEFAULT 0,
  `Hours` int(9) NOT NULL DEFAULT 0,
  `Minutes` int(2) NOT NULL DEFAULT 0,
  `Seconds` int(2) NOT NULL DEFAULT 0,
  `HP` float NOT NULL DEFAULT 0,
  `AP` float NOT NULL DEFAULT 0,
  `Bans` int(9) NOT NULL DEFAULT 0,
  `Kicks` int(9) NOT NULL DEFAULT 0,
  `Warns` int(9) NOT NULL DEFAULT 0,
  `VW` int(2) NOT NULL DEFAULT 0,
  `INT` int(2) NOT NULL DEFAULT 0,
  `Skin` int(3) NOT NULL DEFAULT 0,
  `LastSkin` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `Bank` int(9) NOT NULL DEFAULT 0,
  `BW` int(5) NOT NULL DEFAULT 0,
  `AJ` int(5) NOT NULL DEFAULT 0,
  `AL` int(5) NOT NULL DEFAULT 0,
  `DriverLicense` int(2) NOT NULL DEFAULT 0,
  `PisSkill` int(2) NOT NULL DEFAULT 0,
  `DglSkill` int(2) NOT NULL DEFAULT 0,
  `ShtgSkill` int(2) NOT NULL DEFAULT 0,
  `M4Skill` int(2) NOT NULL DEFAULT 0,
  `GOV` int(2) NOT NULL DEFAULT 0,
  `Hotel` int(2) NOT NULL DEFAULT 0,
  `IdCard` int(9) NOT NULL DEFAULT 0,
  `Detention` int(5) NOT NULL DEFAULT 0,
  `PDP` int(5) NOT NULL DEFAULT 0,
  `TelNum` int(9) NOT NULL DEFAULT 0,
  `BankAcc` int(9) NOT NULL DEFAULT 0,
  `GroupDesc` varchar(128) NOT NULL DEFAULT '\0',
  `Group` int(2) NOT NULL DEFAULT 0,
  `Area` int(2) NOT NULL DEFAULT 0,
  `Duty` int(5) NOT NULL DEFAULT 0,
  `Traveled` float NOT NULL DEFAULT 0,
  `Doors` int(2) NOT NULL DEFAULT 0,
  `Audio` int(1) NOT NULL DEFAULT 0,
  `ChatStyle` int(1) NOT NULL DEFAULT 0,
  `Computer` int(1) NOT NULL DEFAULT 0,
  `WalkAnim` int(1) NOT NULL DEFAULT 0,
  `Screen` int(1) NOT NULL DEFAULT 0,
  `StyleFight` int(1) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Desc` varchar(128) NOT NULL DEFAULT '\0'
) ENGINE=MyISAM DEFAULT CHARSET=latin2 COLLATE=latin2_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_settings`
--

CREATE TABLE `osrp_settings` (
  `AllAccounts` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_settings`
--

INSERT INTO `osrp_settings` (`AllAccounts`) VALUES
(0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_stations`
--

CREATE TABLE `osrp_stations` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\0',
  `Price` int(9) NOT NULL DEFAULT 0,
  `IsOpen` int(1) NOT NULL DEFAULT 0,
  `GasPumps` int(9) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `osrp_stations`
--

INSERT INTO `osrp_stations` (`UID`, `Name`, `Price`, `IsOpen`, `GasPumps`, `X`, `Y`, `Z`, `Distance`) VALUES
(1, 'Stacja paliw Idlewood', 12, 1, 4, 1940.73, -1771.38, 13.3906, 50),
(2, 'Stacja paliw Flint County', 5, 1, 4, -91.1946, -1169.85, 2.4179, 50);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_vehicles`
--

CREATE TABLE `osrp_vehicles` (
  `UID` int(2) NOT NULL DEFAULT 0,
  `ID` int(2) NOT NULL DEFAULT 0,
  `OUID` int(2) NOT NULL DEFAULT 0,
  `GUID` int(3) NOT NULL DEFAULT 0,
  `CharName` varchar(24) NOT NULL DEFAULT '\0',
  `ModelID` int(3) NOT NULL DEFAULT 0,
  `Color1` int(3) NOT NULL DEFAULT 0,
  `Color2` int(3) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Angle` float NOT NULL DEFAULT 0,
  `Fuel` float NOT NULL DEFAULT 0,
  `Lock` int(1) NOT NULL DEFAULT 0,
  `Engine` int(1) NOT NULL DEFAULT 0,
  `EngineHealth` float NOT NULL DEFAULT 0,
  `Spawned` int(1) NOT NULL DEFAULT 0,
  `Lights` int(1) NOT NULL DEFAULT 0,
  `Mileage` float NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '\0',
  `Plate` varchar(32) NOT NULL DEFAULT '\0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `osrp_areas`
--
ALTER TABLE `osrp_areas`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_booths`
--
ALTER TABLE `osrp_booths`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groupitems`
--
ALTER TABLE `osrp_groupitems`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_players`
--
ALTER TABLE `osrp_players`
  ADD PRIMARY KEY (`UID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
