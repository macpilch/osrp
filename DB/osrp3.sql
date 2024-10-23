-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 07, 2024 at 08:13 PM
-- Wersja serwera: 10.4.32-MariaDB
-- Wersja PHP: 8.2.12

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
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `MinX` float NOT NULL DEFAULT 0,
  `MinY` float NOT NULL DEFAULT 0,
  `MaxX` float NOT NULL DEFAULT 0,
  `MaxY` float NOT NULL DEFAULT 0,
  `MaxSpeed` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_booths`
--

CREATE TABLE `osrp_booths` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\n',
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Range` float NOT NULL DEFAULT 0,
  `Working` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_busstops`
--

CREATE TABLE `osrp_busstops` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Price` int(6) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_cashpoints`
--

CREATE TABLE `osrp_cashpoints` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `IsOpen` int(1) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_contacts`
--

CREATE TABLE `osrp_contacts` (
  `UID` int(3) NOT NULL,
  `Name` varchar(24) NOT NULL DEFAULT '\\0',
  `Number` int(7) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_doors`
--

CREATE TABLE `osrp_doors` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `EnterX` float NOT NULL DEFAULT 0,
  `EnterY` float NOT NULL DEFAULT 0,
  `EnterZ` float NOT NULL DEFAULT 0,
  `ExitX` float NOT NULL DEFAULT 0,
  `ExitY` float NOT NULL DEFAULT 0,
  `ExitZ` float NOT NULL DEFAULT 0,
  `Open` int(1) NOT NULL DEFAULT 0,
  `Tax` int(1) NOT NULL DEFAULT 0,
  `TaxDate` varchar(24) NOT NULL DEFAULT '\\0',
  `TaxCost` int(9) NOT NULL DEFAULT 0,
  `Dimensions` int(6) NOT NULL DEFAULT 0,
  `Objects` int(9) NOT NULL DEFAULT 0,
  `MaxObjects` int(9) NOT NULL DEFAULT 0,
  `Texts` int(9) NOT NULL DEFAULT 0,
  `MaxTexts` int(9) NOT NULL DEFAULT 0,
  `Security` int(3) NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0,
  `Type` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_doors`
--

INSERT INTO `osrp_doors` (`UID`, `OUID`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `ExitX`, `ExitY`, `ExitZ`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Dimensions`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `VW`, `INT`, `Type`) VALUES
(1, 1, 'Hotel 52', 881.574, -1336.08, 13.5469, 942.172, -16.5428, 1000.93, 1, 1, '\\0', 1, 0, 0, 0, 0, 0, 0, 1, 2, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_gaspumps`
--

CREATE TABLE `osrp_gaspumps` (
  `UID` int(3) NOT NULL,
  `SID` int(3) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groupitems`
--

CREATE TABLE `osrp_groupitems` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `ID` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(64) NOT NULL DEFAULT '\\0',
  `Price` int(5) NOT NULL DEFAULT 0,
  `Amount` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groups`
--

CREATE TABLE `osrp_groups` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Tag` varchar(8) NOT NULL DEFAULT '\\0',
  `Date` varchar(32) NOT NULL DEFAULT '\\0',
  `Type` int(2) NOT NULL DEFAULT 0,
  `Members` int(3) NOT NULL DEFAULT 0,
  `VehsLimit` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `PayDay` int(9) NOT NULL DEFAULT 0,
  `Door` int(3) NOT NULL DEFAULT 0,
  `Flags` int(9) NOT NULL DEFAULT 0,
  `Color` int(6) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_groups`
--

INSERT INTO `osrp_groups` (`UID`, `OUID`, `Name`, `Tag`, `Date`, `Type`, `Members`, `VehsLimit`, `Money`, `PayDay`, `Door`, `Flags`, `Color`) VALUES
(1, 1, 'LSPD', 'LSPD', '17.03.2024', 0, 1, 20, 1000, 100, 0, 4, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_items`
--

CREATE TABLE `osrp_items` (
  `UID` int(3) NOT NULL,
  `ID` int(3) NOT NULL DEFAULT 0,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Value1` int(3) NOT NULL DEFAULT 0,
  `Value2` int(3) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Used` int(1) NOT NULL DEFAULT 0,
  `Place` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_items`
--

INSERT INTO `osrp_items` (`UID`, `ID`, `OUID`, `Name`, `Value1`, `Value2`, `PosX`, `PosY`, `PosZ`, `Used`, `Place`) VALUES
(1, 0, 1, 'Rolki', 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_players`
--

CREATE TABLE `osrp_players` (
  `UID` int(3) NOT NULL,
  `GUID` int(3) NOT NULL DEFAULT 0,
  `CharId` int(1) NOT NULL DEFAULT 0,
  `AccName` varchar(24) NOT NULL DEFAULT '\0',
  `CharName` varchar(24) NOT NULL DEFAULT '\0',
  `CharName2` varchar(24) NOT NULL DEFAULT '\0',
  `Pass` varchar(32) NOT NULL DEFAULT '\0',
  `IP` varchar(16) NOT NULL DEFAULT '\0',
  `DateReg` varchar(64) NOT NULL DEFAULT '\0',
  `LastDate` varchar(64) NOT NULL DEFAULT '\0',
  `Gold` int(1) NOT NULL DEFAULT 0,
  `Rank` int(1) NOT NULL DEFAULT 0,
  `GM` int(1) NOT NULL DEFAULT 0,
  `Sex` int(1) NOT NULL DEFAULT 0,
  `Strength` int(5) NOT NULL DEFAULT 3000,
  `Hours` int(9) NOT NULL DEFAULT 0,
  `Minutes` int(2) NOT NULL DEFAULT 0,
  `Seconds` int(2) NOT NULL DEFAULT 0,
  `HP` float NOT NULL DEFAULT 100,
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
  `IdCard` int(1) NOT NULL DEFAULT 0,
  `Detention` int(5) NOT NULL DEFAULT 0,
  `PDP` int(5) NOT NULL DEFAULT 0,
  `TelNum` int(7) NOT NULL DEFAULT 0,
  `BankAcc` int(8) NOT NULL DEFAULT 0,
  `GroupDesc` varchar(128) NOT NULL DEFAULT '-',
  `Group0` int(2) NOT NULL DEFAULT 0,
  `Group1` int(3) NOT NULL DEFAULT 0,
  `Group2` int(3) NOT NULL DEFAULT 0,
  `Group3` int(3) NOT NULL DEFAULT 0,
  `Group4` int(3) NOT NULL DEFAULT 0,
  `Duty` int(5) NOT NULL DEFAULT 0,
  `Traveled` float NOT NULL DEFAULT 0,
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

--
-- Dumping data for table `osrp_players`
--

INSERT INTO `osrp_players` (`UID`, `GUID`, `CharId`, `AccName`, `CharName`, `CharName2`, `Pass`, `IP`, `DateReg`, `LastDate`, `Gold`, `Rank`, `GM`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `Bans`, `Kicks`, `Warns`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `BW`, `AJ`, `AL`, `DriverLicense`, `PisSkill`, `DglSkill`, `ShtgSkill`, `M4Skill`, `GOV`, `Hotel`, `IdCard`, `Detention`, `PDP`, `TelNum`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Duty`, `Traveled`, `Audio`, `ChatStyle`, `Computer`, `WalkAnim`, `Screen`, `StyleFight`, `X`, `Y`, `Z`, `Desc`) VALUES
(1, 1, 1, 'steeZ', 'Danny Walker', 'Danny_Walker', '1234', '127.0.0.1', '21/02/2024 19:57:21', '21/02/2024 19:57:21', 1, 4, 1, 0, 3000, 0, 12, 9, 100, 0, 0, 0, 0, 0, 0, 291, 291, 50, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 882.956, -1333.07, 13.2188, '\0');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_races`
--

CREATE TABLE `osrp_races` (
  `UID` int(3) NOT NULL,
  `Name` varchar(64) NOT NULL DEFAULT '\\0',
  `Created` int(1) NOT NULL DEFAULT 0,
  `Besetments` int(3) NOT NULL DEFAULT 0,
  `CPS` int(3) NOT NULL DEFAULT 0,
  `Players` int(3) NOT NULL DEFAULT 0,
  `CP0` float NOT NULL DEFAULT 0,
  `CP1` decimal(9,0) NOT NULL DEFAULT 0,
  `CP2` float NOT NULL DEFAULT 0,
  `CP3` float NOT NULL DEFAULT 0,
  `CP4` float NOT NULL DEFAULT 0,
  `CP5` float NOT NULL DEFAULT 0,
  `CP6` float NOT NULL DEFAULT 0,
  `CP7` float NOT NULL DEFAULT 0,
  `CP8` float NOT NULL DEFAULT 0,
  `CP9` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_settings`
--

CREATE TABLE `osrp_settings` (
  `AllAccounts` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_stations`
--

CREATE TABLE `osrp_stations` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Price` int(9) NOT NULL DEFAULT 0,
  `IsOpen` int(1) NOT NULL DEFAULT 0,
  `GasPumps` int(3) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_vehicles`
--

CREATE TABLE `osrp_vehicles` (
  `UID` int(3) NOT NULL,
  `ID` int(3) NOT NULL DEFAULT 0,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `GUID` int(3) NOT NULL DEFAULT 0,
  `CharName` varchar(24) NOT NULL DEFAULT '\\0',
  `ModelId` int(3) NOT NULL DEFAULT 0,
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
  `Desc` varchar(64) NOT NULL DEFAULT '\\0',
  `Plate` varchar(32) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_vehicles`
--

INSERT INTO `osrp_vehicles` (`UID`, `ID`, `OUID`, `GUID`, `CharName`, `ModelId`, `Color1`, `Color2`, `X`, `Y`, `Z`, `Angle`, `Fuel`, `Lock`, `Engine`, `EngineHealth`, `Spawned`, `Lights`, `Mileage`, `Desc`, `Plate`) VALUES
(1, 1, 1, 0, 'Danny Walker', 411, 209, 173, 882.959, -1333.1, 13.2156, 9.01773, 40, 0, 0, 1000, 1, 0, 0, '', 'Test.');

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
-- Indeksy dla tabeli `osrp_busstops`
--
ALTER TABLE `osrp_busstops`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_cashpoints`
--
ALTER TABLE `osrp_cashpoints`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_contacts`
--
ALTER TABLE `osrp_contacts`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_doors`
--
ALTER TABLE `osrp_doors`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_gaspumps`
--
ALTER TABLE `osrp_gaspumps`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groupitems`
--
ALTER TABLE `osrp_groupitems`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groups`
--
ALTER TABLE `osrp_groups`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_items`
--
ALTER TABLE `osrp_items`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_players`
--
ALTER TABLE `osrp_players`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_races`
--
ALTER TABLE `osrp_races`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_stations`
--
ALTER TABLE `osrp_stations`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_vehicles`
--
ALTER TABLE `osrp_vehicles`
  ADD PRIMARY KEY (`UID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `osrp_areas`
--
ALTER TABLE `osrp_areas`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_booths`
--
ALTER TABLE `osrp_booths`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_busstops`
--
ALTER TABLE `osrp_busstops`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_cashpoints`
--
ALTER TABLE `osrp_cashpoints`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_contacts`
--
ALTER TABLE `osrp_contacts`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_doors`
--
ALTER TABLE `osrp_doors`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_gaspumps`
--
ALTER TABLE `osrp_gaspumps`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_groupitems`
--
ALTER TABLE `osrp_groupitems`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_groups`
--
ALTER TABLE `osrp_groups`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_items`
--
ALTER TABLE `osrp_items`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_players`
--
ALTER TABLE `osrp_players`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_races`
--
ALTER TABLE `osrp_races`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_stations`
--
ALTER TABLE `osrp_stations`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_vehicles`
--
ALTER TABLE `osrp_vehicles`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
