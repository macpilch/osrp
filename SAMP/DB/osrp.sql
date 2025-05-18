-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Maj 10, 2025 at 06:13 PM
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
-- Struktura tabeli dla tabeli `osrp_3dtexts`
--

CREATE TABLE `osrp_3dtexts` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Type` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '\\0',
  `Color` varchar(10) NOT NULL DEFAULT '\\0',
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_3dtexts`
--

INSERT INTO `osrp_3dtexts` (`UID`, `OUID`, `Type`, `Desc`, `Color`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES
(1, 0, 0, 'Zakaz postoju', 'FF0000FF', 1537.82, -1668.79, 14.1014, 30, 0, 0),
(2, 0, 0, 'Zakaz parkowania!', 'FF0000FF', 1525.52, -1447.82, 14.11, 30, 0, 0),
(3, 0, 0, 'Bankomat\\n{FFFFFF}(( Wpisz /bank stojąc bardzo blisko,\\nby użyć ', '\\0', 0, 0, 0, 30, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_animations`
--

CREATE TABLE `osrp_animations` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `AnimLib` varchar(32) NOT NULL DEFAULT '\\0',
  `AnimName` varchar(32) NOT NULL DEFAULT '\\0',
  `Delta` float NOT NULL DEFAULT 4.1,
  `Loop` int(1) NOT NULL DEFAULT 0,
  `LockX` int(1) NOT NULL DEFAULT 0,
  `LockY` int(1) NOT NULL DEFAULT 0,
  `Freeze` int(1) NOT NULL DEFAULT 0,
  `Time` int(1) NOT NULL DEFAULT 0,
  `Forcesync` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_animations`
--

INSERT INTO `osrp_animations` (`UID`, `Name`, `AnimLib`, `AnimName`, `Delta`, `Loop`, `LockX`, `LockY`, `Freeze`, `Time`, `Forcesync`) VALUES
(1, 'idz1', 'PED', 'WALK_gang1', 4.1, 1, 1, 1, 1, 1, 1),
(2, 'idz2', 'PED', 'WALK_gang2', 4.1, 1, 1, 1, 1, 1, 1),
(3, 'idz3', 'PED', 'WOMAN_walksexy', 4.1, 1, 1, 1, 1, 1, 1),
(4, 'idz4', 'PED', 'WOMAN_walkfatold', 4.1, 1, 1, 1, 1, 1, 1),
(5, 'stopani', 'CARRY', 'crry_prtial', 4.1, 0, 0, 0, 0, 0, 0),
(6, 'idz5', 'PED', 'Walk_Wuzi', 4.1, 1, 1, 1, 1, 1, 1),
(7, 'idz6', 'PED', 'WALK_player', 6, 1, 1, 1, 1, 1, 1),
(8, 'pa', 'KISSING', 'gfwave2', 6, 0, 0, 0, 0, 0, 0),
(9, 'zmeczony', 'PED', 'IDLE_tired', 4.1, 1, 0, 0, 0, 0, 0),
(10, 'umyjrece', 'INT_HOUSE', 'wash_up', 4.1, 0, 0, 0, 0, 0, 0),
(11, 'medyk', 'MEDIC', 'CPR', 4.1, 0, 0, 0, 0, 0, 0),
(12, 'ranny', 'SWEET', 'Sweet_injuredloop', 4.1, 1, 0, 0, 1, 1, 1),
(13, 'salutuj', 'ON_LOOKERS', 'lkup_in', 4.1, 0, 1, 1, 1, 0, 1),
(14, 'wtf', 'RIOT', 'RIOT_ANGRY', 4.1, 0, 1, 1, 1, 1, 1),
(15, 'spoko', 'GANGS', 'prtial_gngtlkD', 4.1, 0, 0, 0, 0, 0, 0),
(16, 'napad', 'SHOP', 'ROB_Loop_Threat', 4.1, 1, 0, 0, 1, 1, 1),
(17, 'krzeslo', 'PED', 'SEAT_idle', 5, 1, 0, 0, 1, 1, 1),
(18, 'szukaj', 'COP_AMBIENT', 'Copbrowse_loop', 4.1, 1, 0, 0, 0, 0, 1),
(19, 'lornetka', 'ON_LOOKERS', 'shout_loop', 4.1, 1, 0, 0, 0, 0, 1),
(20, 'oh', 'MISC', 'plyr_shkhead', 4.1, 0, 0, 0, 0, 0, 0),
(21, 'oh2', 'OTB', 'wtchrace_lose', 4.1, 0, 1, 1, 0, 0, 0),
(22, 'wyciagnij', 'FOOD', 'SHP_Tray_Lift', 4.1, 0, 0, 0, 0, 0, 0),
(23, 'zdziwiony', 'PED', 'facsurp', 4.1, 0, 1, 1, 1, 1, 1),
(24, 'recemaska', 'POLICE', 'crm_drgbst_01', 6, 1, 0, 0, 1, 0, 1),
(25, 'krzeslojem', 'FOOD', 'FF_Sit_Eat1', 4.1, 1, 0, 0, 0, 0, 1),
(26, 'idle', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(27, 'czekam', 'GRAVEYARD', 'prst_loopa', 4.1, 1, 0, 0, 1, 1, 1),
(28, 'garda', 'FIGHT_D', 'FightD_IDLE', 4.1, 1, 1, 1, 1, 0, 1),
(29, 'barman2', 'BAR', 'BARman_idle', 4.1, 0, 0, 0, 0, 0, 0),
(30, 'fotel', 'INT_HOUSE', 'LOU_Loop', 4.1, 1, 0, 0, 1, 1, 1),
(31, 'napraw', 'CAR', 'Fixn_Car_Loop', 4.1, 1, 0, 0, 1, 1, 1),
(32, 'barman', 'BAR', 'Barserve_loop', 4.1, 1, 0, 0, 0, 0, 1),
(33, 'opieraj', 'GANGS', 'leanIDLE', 4.1, 1, 0, 0, 1, 1, 1),
(34, 'bar.nalej', 'BAR', 'Barserve_glass', 4.1, 0, 0, 0, 0, 0, 0),
(35, 'ramiona', 'COP_AMBIENT', 'Coplook_loop', 4.1, 1, 0, 0, 1, 0, 1),
(36, 'bar.wez', 'BAR', 'Barserve_bottle', 4.1, 0, 0, 0, 0, 0, 0),
(37, 'chowaj', 'PED', 'cower', 3, 1, 0, 0, 0, 0, 1),
(38, 'wez', 'BAR', 'Barserve_give', 4.1, 0, 0, 0, 0, 0, 0),
(39, 'fuck', 'PED', 'fucku', 4.1, 0, 0, 0, 0, 0, 0),
(40, 'klepnij', 'SWEET', 'sweet_ass_slap', 6, 0, 0, 0, 0, 0, 0),
(41, 'cmon', 'RYDER', 'RYD_Beckon_01', 4.1, 0, 1, 1, 0, 0, 1),
(42, 'daj', 'DEALER', 'DEALER_DEAL', 8, 0, 0, 0, 0, 0, 0),
(43, 'pij', 'VENDING', 'VEND_Drink2_P', 4.1, 1, 1, 1, 1, 0, 1),
(44, 'start', 'CAR', 'flag_drop', 4.1, 0, 0, 0, 0, 0, 0),
(45, 'karta', 'HEIST9', 'Use_SwipeCard', 4.1, 0, 0, 0, 0, 0, 0),
(46, 'spray', 'GRAFFITI', 'spraycan_fire', 4.1, 1, 0, 0, 0, 0, 1),
(47, 'odejdz', 'POLICE', 'CopTraf_Left', 4.1, 0, 0, 0, 0, 0, 0),
(48, 'fotelk', 'JST_BUISNESS', 'girl_02', 4.1, 1, 0, 0, 1, 1, 1),
(49, 'chodz', 'POLICE', 'CopTraf_Come', 4.1, 0, 0, 0, 0, 0, 0),
(50, 'stop', 'POLICE', 'CopTraf_Stop', 4.1, 0, 0, 0, 0, 0, 0),
(51, 'drapjaja', 'MISC', 'Scratchballs_01', 4.1, 1, 0, 0, 0, 0, 1),
(52, 'opieraj2', 'MISC', 'Plyrlean_loop', 4.1, 1, 0, 0, 0, 0, 1),
(53, 'bitchslap', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(54, 'popchnij', 'GANGS', 'shake_cara', 4.1, 0, 0, 0, 0, 0, 0),
(55, 'rzuc', 'GRENADE', 'WEAPON_throwu', 3, 0, 0, 0, 0, 0, 0),
(56, 'rap1', 'RAPPING', 'RAP_A_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(57, 'rap2', 'RAPPING', 'RAP_C_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(58, 'rap3', 'RAPPING', 'RAP_B_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(59, 'rap4', 'GANGS', 'prtial_gngtlkH', 4.1, 1, 0, 0, 1, 1, 1),
(60, 'glowka', 'WAYFARER', 'WF_Fwd', 4.1, 0, 0, 0, 0, 0, 0),
(61, 'skop', 'FIGHT_D', 'FightD_G', 4.1, 0, 0, 0, 0, 0, 0),
(62, 'siad', 'BEACH', 'ParkSit_M_loop', 4.1, 1, 0, 0, 0, 0, 1),
(63, 'krzeslo2', 'FOOD', 'FF_Sit_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(64, 'krzeslo3', 'INT_OFFICE', 'OFF_Sit_Idle_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(65, 'krzeslo4', 'INT_OFFICE', 'OFF_Sit_Bored_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(66, 'krzeslo5', 'INT_OFFICE', 'OFF_Sit_Type_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(67, 'padnij', 'PED', 'KO_shot_front', 4.1, 0, 1, 1, 1, 0, 1),
(68, 'taichi2', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(69, 'unik', 'PED', 'EV_dive', 4.1, 0, 1, 1, 1, 0, 1),
(70, 'crack', 'CRACK', 'crckdeth2', 4.1, 1, 0, 0, 0, 0, 1),
(71, 'bomb', 'BOMBER', 'BOM_Plant', 4.1, 0, 0, 0, 0, 0, 1),
(72, 'cpaj', 'SHOP', 'ROB_Shifty', 4.1, 0, 0, 0, 0, 0, 1),
(73, 'rece', 'ROB_BANK', 'SHP_HandsUp_Scr', 4.1, 0, 1, 1, 1, 1, 1),
(74, 'tancz1', '-', '-', 0, 5, 0, 0, 0, 0, 2),
(75, 'tancz2', '-', '-', 0, 6, 0, 0, 0, 0, 2),
(76, 'tancz3', '-', '-', 0, 7, 0, 0, 0, 0, 2),
(77, 'tancz4', '-', '-', 0, 8, 0, 0, 0, 0, 2),
(78, 'tancz5', 'STRIP', 'STR_Loop_A', 2, 1, 0, 0, 0, 0, 1),
(79, 'pijak', 'PED', 'WALK_DRUNK', 4.1, 1, 1, 1, 1, 1, 1),
(80, 'nie', 'GANGS', 'Invite_No', 4.1, 0, 0, 0, 0, 0, 0),
(81, 'lokiec', 'CAR', 'Sit_relaxed', 4.1, 1, 1, 1, 1, 0, 1),
(82, 'go', 'RIOT', 'RIOT_PUNCHES', 4.1, 0, 0, 0, 0, 0, 0),
(83, 'stack1', 'GHANDS', 'gsign2LH', 4.1, 0, 0, 0, 0, 0, 0),
(84, 'lez3', 'BEACH', 'ParkSit_W_loop', 4.1, 1, 0, 0, 0, 0, 1),
(85, 'lez1', 'BEACH', 'bather', 4.1, 1, 0, 0, 0, 0, 1),
(86, 'lez2', 'BEACH', 'Lay_Bac_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(87, 'padnij2', 'PED', 'KO_skid_front', 4.1, 0, 1, 1, 1, 0, 1),
(88, 'bat', 'CRACK', 'Bbalbat_Idle_01', 4.1, 1, 1, 1, 1, 1, 1),
(89, 'bat2', 'CRACK', 'Bbalbat_Idle_02', 4.1, 0, 1, 1, 1, 1, 1),
(90, 'stack2', 'GHANDS', 'gsign2', 4.1, 0, 1, 1, 1, 1, 1),
(91, 'stack3', 'GHANDS', 'gsign4', 4.1, 0, 1, 1, 1, 1, 1),
(92, 'taichi', 'PARK', 'Tai_Chi_Loop', 4.1, 1, 0, 0, 0, 0, 1),
(93, 'kosz1', 'BSKTBALL', 'BBALL_idleloop', 4.1, 1, 0, 0, 0, 0, 1),
(94, 'kosz2', 'BSKTBALL', 'BBALL_Jump_Shot', 4.1, 0, 0, 0, 0, 0, 1),
(95, 'kosz3', 'BSKTBALL', 'BBALL_pickup', 4.1, 0, 0, 0, 0, 0, 1),
(96, 'kosz4', 'BSKTBALL', 'BBALL_def_loop', 4.1, 1, 0, 0, 0, 0, 1),
(97, 'kosz5', 'BSKTBALL', 'BBALL_Dnk', 4.1, 0, 0, 0, 0, 0, 1),
(98, 'papieros', 'SMOKING', 'M_smklean_loop', 4.1, 1, 0, 0, 0, 0, 1),
(99, 'wymiotuj', 'FOOD', 'EAT_Vomit_P', 3, 0, 0, 0, 0, 0, 1),
(100, 'fuck2', 'RIOT', 'RIOT_FUKU', 4.1, 0, 0, 0, 0, 0, 0),
(101, 'koks', 'PED', 'IDLE_HBHB', 4.1, 1, 0, 0, 1, 0, 1),
(102, 'idz7', 'PED', 'WOMAN_walkshop', 4.1, 1, 1, 1, 1, 1, 1),
(103, 'cry', 'GRAVEYARD', 'mrnF_loop', 4.1, 1, 0, 0, 1, 0, 1),
(104, 'rozciagaj', 'PLAYIDLES', 'stretch', 4.1, 0, 0, 0, 0, 0, 1),
(105, 'cellin', '-', '-', 0, 11, 0, 0, 0, 0, 2),
(106, 'cellout', '-', '-', 0, 13, 0, 0, 0, 0, 2),
(107, 'bagaznik', 'POOL', 'POOL_Place_White', 4.1, 0, 0, 0, 1, 0, 1),
(108, 'wywaz', 'GANGS', 'shake_carK', 4.1, 0, 0, 0, 0, 0, 0),
(109, 'skradajsie', 'PED', 'Player_Sneak', 6, 1, 1, 1, 1, 1, 1),
(110, 'przycisk', 'CRIB', 'CRIB_use_switch', 4.1, 0, 0, 0, 0, 0, 1),
(111, 'tancz6', 'DANCING', 'DAN_down_A', 4.1, 1, 0, 0, 0, 0, 1),
(112, 'tancz7', 'DANCING', 'DAN_left_A', 4.1, 1, 0, 0, 0, 0, 1),
(113, 'idz8', 'PED', 'walk_shuffle', 4.1, 1, 1, 1, 1, 1, 1),
(114, 'stack4', 'LOWRIDER', 'prtial_gngtlkB', 4.1, 0, 0, 0, 0, 0, 1),
(115, 'stack5', 'LOWRIDER', 'prtial_gngtlkC', 4.1, 0, 1, 1, 1, 1, 1),
(116, 'stack6', 'LOWRIDER', 'prtial_gngtlkD', 4.1, 0, 0, 0, 0, 0, 0),
(117, 'stack7', 'LOWRIDER', 'prtial_gngtlkE', 4.1, 0, 0, 0, 0, 0, 1),
(118, 'stack8', 'LOWRIDER', 'prtial_gngtlkF', 4.1, 0, 0, 0, 0, 0, 1),
(119, 'stack9', 'LOWRIDER', 'prtial_gngtlkG', 4.1, 0, 0, 0, 0, 0, 1),
(120, 'stack10', 'LOWRIDER', 'prtial_gngtlkH', 4.1, 0, 1, 1, 1, 1, 1),
(121, 'tancz8', 'DANCING', 'dnce_m_d', 4.1, 1, 0, 0, 0, 0, 1),
(122, 'kasjer', 'INT_SHOP', 'shop_cashier', 4.1, 0, 0, 0, 0, 0, 1),
(123, 'idz9', 'WUZI', 'wuzi_walk', 4.1, 1, 1, 1, 1, 1, 1),
(124, 'taxi', 'MISC', 'hiker_pose', 4.1, 0, 0, 0, 1, 0, 1),
(125, 'wskaz', 'ON_LOOKERS', 'pointup_loop', 4.1, 0, 0, 0, 1, 0, 1),
(126, 'wskaz2', 'ON_LOOKERS', 'point_loop', 4.1, 0, 0, 0, 1, 0, 1),
(127, 'podpisz', 'OTB', 'betslp_loop', 4.1, 0, 0, 0, 0, 0, 1),
(128, 'natrzyj', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(129, 'sex1', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(130, 'bp_up_a', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(131, 'bp_up_s', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(132, 'bp_up_b', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(133, 'bp_down', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(134, 'bp_geton2', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0),
(135, 'seat', '\\0', '\\0', 4.1, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_areas`
--

CREATE TABLE `osrp_areas` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Type` int(3) NOT NULL DEFAULT 0,
  `OType` int(3) NOT NULL DEFAULT 0,
  `MinX` float NOT NULL DEFAULT 0,
  `MinY` float NOT NULL DEFAULT 0,
  `MinZ` float NOT NULL DEFAULT 0,
  `MaxX` float NOT NULL DEFAULT 0,
  `MaxY` float NOT NULL DEFAULT 0,
  `MaxZ` float NOT NULL DEFAULT 0,
  `MaxSpeed` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_areas`
--

INSERT INTO `osrp_areas` (`UID`, `OUID`, `Type`, `OType`, `MinX`, `MinY`, `MinZ`, `MaxX`, `MaxY`, `MaxZ`, `MaxSpeed`) VALUES
(1, 1, 0, 0, 802.279, -1310.05, 0, 911.834, -1337.22, 0, 80);

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
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_busstops`
--

INSERT INTO `osrp_busstops` (`UID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`) VALUES
(1, 'Market', 818.535, -1336.01, 13.5726, 0, 0, -90),
(2, 'LSPD', 1522.38, -1690.79, 13.5806, 0, 0, 180),
(3, 'Glen Park', 2021.58, -1253.79, 23.9838, 0, 0, 90),
(4, 'Idlewood', 2096.57, -1765.92, 13.6383, 0, 0, 345.744),
(5, 'Ganton', 2193.65, -1751.04, 13.592, 0, 0, 0),
(6, 'a', 2386.6, -1978.54, 13.5872, 0, 0, -90),
(7, 'b', 2263.92, -1334.06, 23.9175, 0, 0, 180),
(8, 'c', 955.214, -957.125, 39.9099, -3, 0, 100.231),
(9, 'd', 1149.96, -1412.8, 13.7671, 0, 0, -90),
(10, 'e', 2232.4, -1145.27, 25.7338, 0, 0, 255.112),
(11, 'f', 1286.76, -1387.89, 13.5146, 0, 0, 90),
(12, 'g', 681.996, -1413.42, 13.5785, 0, 0, -90);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_cashpoints`
--

CREATE TABLE `osrp_cashpoints` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `IsOpen` int(1) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_cashpoints`
--

INSERT INTO `osrp_cashpoints` (`UID`, `Name`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES
(1, 'Market', 1, 837.508, -1338.88, 6.8208, 0, 0, 0, 3, 0, 0),
(2, 'Hotel 52', 1, 897.71, -1338.53, 19.121, 0, 0, -90, 3, 100, 0);

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
-- Struktura tabeli dla tabeli `osrp_dimensions`
--

CREATE TABLE `osrp_dimensions` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL,
  `MinX` float NOT NULL,
  `MinY` float NOT NULL,
  `MinZ` float NOT NULL,
  `MaxX` float NOT NULL,
  `MaxY` float NOT NULL,
  `MaxZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_dimensions`
--

INSERT INTO `osrp_dimensions` (`UID`, `OUID`, `MinX`, `MinY`, `MinZ`, `MaxX`, `MaxY`, `MaxZ`) VALUES
(1, 1, 898.4, -1342.4, 18.3, 854.8, -1322.1, 19.3),
(2, 2, 111, 111, 111, 111, 111, 111);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_doors`
--

CREATE TABLE `osrp_doors` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `OType` int(3) NOT NULL DEFAULT 0,
  `Type` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `EnterX` float NOT NULL DEFAULT 0,
  `EnterY` float NOT NULL DEFAULT 0,
  `EnterZ` float NOT NULL DEFAULT 0,
  `EnterAng` float NOT NULL DEFAULT 0,
  `ExitX` float NOT NULL DEFAULT 0,
  `ExitY` float NOT NULL DEFAULT 0,
  `ExitZ` float NOT NULL DEFAULT 0,
  `ExitAng` float NOT NULL DEFAULT 0,
  `Cost` int(3) NOT NULL DEFAULT 0,
  `Passing` int(1) NOT NULL DEFAULT 0,
  `Open` int(1) NOT NULL DEFAULT 0,
  `Tax` int(9) NOT NULL DEFAULT 0,
  `TaxDate` varchar(16) NOT NULL DEFAULT 'Brak',
  `TaxCost` int(9) NOT NULL DEFAULT 0,
  `Objects` int(9) NOT NULL DEFAULT 0,
  `MaxObjects` int(9) NOT NULL DEFAULT 0,
  `Texts` int(9) NOT NULL DEFAULT 0,
  `MaxTexts` int(9) NOT NULL DEFAULT 0,
  `Security` int(1) NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_doors`
--

INSERT INTO `osrp_doors` (`UID`, `OUID`, `OType`, `Type`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `EnterAng`, `ExitX`, `ExitY`, `ExitZ`, `ExitAng`, `Cost`, `Passing`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `VW`, `INT`) VALUES
(1, 1, 16, 2, 'Hotel 52', 893.161, -1336.08, 13.5469, 0, 897.469, -1339.92, 19.4569, 0, 0, 0, 1, 12121212, '2025/04/14', 10, 1, 1, 1, 1, 1, 100, 0),
(2, 100, 16, 4, 'Victim', 887.345, -1336.08, 13.5469, 178.288, 893.161, -1336.08, 13.5469, 357.542, 0, 0, 1, 1, '111111', 0, 0, 0, 0, 0, 0, 101, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_grouporders`
--

CREATE TABLE `osrp_grouporders` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL,
  `DName` varchar(32) NOT NULL DEFAULT '\\0',
  `IName` varchar(32) NOT NULL DEFAULT '\\0',
  `Owner` varchar(24) NOT NULL DEFAULT '\\0',
  `Kind` int(3) NOT NULL,
  `Value1` int(5) NOT NULL DEFAULT 0,
  `Value2` int(5) NOT NULL DEFAULT 0,
  `Price` int(3) NOT NULL DEFAULT 0,
  `Amount` int(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groupperms`
--

CREATE TABLE `osrp_groupperms` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `PermOOC` int(1) NOT NULL DEFAULT 0,
  `PermIC` int(1) NOT NULL DEFAULT 0,
  `PermMegaphone` int(1) NOT NULL DEFAULT 0,
  `PermName` int(1) NOT NULL DEFAULT 0,
  `PermTag` int(1) NOT NULL DEFAULT 0,
  `PermDept` int(1) NOT NULL DEFAULT 0,
  `PermGPS` int(1) NOT NULL DEFAULT 0,
  `PermRope` int(1) NOT NULL DEFAULT 0,
  `PermWithdraw` int(1) NOT NULL DEFAULT 0,
  `PermNews` int(1) NOT NULL DEFAULT 0,
  `PermBlockCar` int(1) NOT NULL DEFAULT 0,
  `PermGangZone` int(1) NOT NULL DEFAULT 0,
  `PermBuyList` int(1) NOT NULL DEFAULT 0,
  `PermDetention` int(1) NOT NULL DEFAULT 0,
  `PermRobbery` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_groupperms`
--

INSERT INTO `osrp_groupperms` (`UID`, `OUID`, `PermOOC`, `PermIC`, `PermMegaphone`, `PermName`, `PermTag`, `PermDept`, `PermGPS`, `PermRope`, `PermWithdraw`, `PermNews`, `PermBlockCar`, `PermGangZone`, `PermBuyList`, `PermDetention`, `PermRobbery`) VALUES
(1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groups`
--

CREATE TABLE `osrp_groups` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Date` varchar(32) NOT NULL DEFAULT '\\0',
  `Type` int(2) NOT NULL DEFAULT 0,
  `Members` int(3) NOT NULL DEFAULT 0,
  `VehsLimit` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `Color` varchar(8) NOT NULL DEFAULT '\\0',
  `Register` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_groups`
--

INSERT INTO `osrp_groups` (`UID`, `Name`, `Date`, `Type`, `Members`, `VehsLimit`, `Money`, `Color`, `Register`) VALUES
(1, 'LSPD', '13.03.2025', 1, 5, 100, 121551, '0000FF', 1),
(2, 'Taxi', '11111', 14, 1, 10, 1111, 'FFFF00AA', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_grouptasks`
--

CREATE TABLE `osrp_grouptasks` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(128) NOT NULL DEFAULT '\\0',
  `Date` varchar(64) NOT NULL DEFAULT '\\0',
  `Caller` varchar(24) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_grouptasks`
--

INSERT INTO `osrp_grouptasks` (`UID`, `OUID`, `Desc`, `Date`, `Caller`) VALUES
(6, 2, 'a', '03:38 18/04/2025', 'Danny Walker');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groupthings`
--

CREATE TABLE `osrp_groupthings` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Value1` int(5) NOT NULL DEFAULT 0,
  `Value2` int(5) NOT NULL DEFAULT 0,
  `Price` int(5) NOT NULL DEFAULT 0,
  `Amount` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_groupthings`
--

INSERT INTO `osrp_groupthings` (`UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Price`, `Amount`) VALUES
(1, 1, 5, 'MP5', 29, 50, 10, 97);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_groupvehicles`
--

CREATE TABLE `osrp_groupvehicles` (
  `UID` int(3) NOT NULL,
  `GUID` int(2) NOT NULL,
  `OUID` int(2) NOT NULL,
  `Veh0` int(2) NOT NULL,
  `Veh1` int(2) NOT NULL,
  `Veh2` int(2) NOT NULL DEFAULT 0,
  `Veh3` int(2) NOT NULL DEFAULT 0,
  `Veh4` int(2) NOT NULL DEFAULT 0,
  `Veh5` int(2) NOT NULL DEFAULT 0,
  `Veh6` int(2) NOT NULL DEFAULT 0,
  `Veh7` int(2) NOT NULL DEFAULT 0,
  `Veh8` int(2) NOT NULL DEFAULT 0,
  `Veh9` int(2) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_notes`
--

CREATE TABLE `osrp_notes` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_objects`
--

CREATE TABLE `osrp_objects` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Type` int(1) NOT NULL DEFAULT 0,
  `Creator` int(3) NOT NULL DEFAULT 0,
  `Gate` int(1) NOT NULL DEFAULT 0,
  `ModelId` int(9) NOT NULL DEFAULT 0,
  `Spared` int(5) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `GateX` float NOT NULL DEFAULT 0,
  `GateY` float NOT NULL DEFAULT 0,
  `GateZ` float NOT NULL DEFAULT 0,
  `Texture` int(1) NOT NULL DEFAULT 0,
  `MatIndex` int(3) NOT NULL DEFAULT 0,
  `MatType` int(1) NOT NULL DEFAULT -1,
  `MatColor` int(3) NOT NULL DEFAULT 0,
  `MatModel` int(9) NOT NULL DEFAULT 0,
  `MatTxdName` varchar(32) NOT NULL DEFAULT '\\0',
  `MatTexName` varchar(32) NOT NULL DEFAULT '\\0',
  `MatSize` int(3) NOT NULL DEFAULT 0,
  `MatFontSize` int(3) NOT NULL DEFAULT 0,
  `MatBold` int(3) NOT NULL DEFAULT 0,
  `MatFColor` int(3) NOT NULL DEFAULT 0,
  `MatBColor` int(3) NOT NULL DEFAULT 0,
  `MatAlign` int(3) NOT NULL DEFAULT 0,
  `MatFont` varchar(32) NOT NULL DEFAULT '\\0',
  `MatText` varchar(32) NOT NULL DEFAULT '\\0',
  `Distance` float NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_objects`
--

INSERT INTO `osrp_objects` (`UID`, `OUID`, `Type`, `Creator`, `Gate`, `ModelId`, `Spared`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `GateX`, `GateY`, `GateZ`, `Texture`, `MatIndex`, `MatType`, `MatColor`, `MatModel`, `MatTxdName`, `MatTexName`, `MatSize`, `MatFontSize`, `MatBold`, `MatFColor`, `MatBColor`, `MatAlign`, `MatFont`, `MatText`, `Distance`, `VW`, `INT`) VALUES
(7, 1, 16, 1, 0, 14771, 0, 875.472, -1336.66, 20.4803, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, '\\0', '\\0', 0, 0, 0, 0, 0, 0, '\\0', '\\0', 100, 100, 0),
(12, 1, 16, 1, 0, 19464, 0, 893.921, -1338.81, 19.4569, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, '\\0', '\\0', 0, 0, 0, 0, 0, 0, '\\0', '\\0', 100, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_penalties`
--

CREATE TABLE `osrp_penalties` (
  `UID` int(3) NOT NULL,
  `SUID` int(3) NOT NULL DEFAULT 0,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `IP` varchar(16) NOT NULL DEFAULT '\\0',
  `Type` int(3) NOT NULL DEFAULT 0,
  `Days` int(3) NOT NULL DEFAULT 0,
  `Date` varchar(64) NOT NULL DEFAULT '\\0',
  `Reason` varchar(128) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_players`
--

CREATE TABLE `osrp_players` (
  `UID` int(3) NOT NULL,
  `GUID` int(3) NOT NULL DEFAULT 0,
  `CharNum` int(1) NOT NULL DEFAULT 0,
  `AccName` varchar(24) NOT NULL DEFAULT '\0',
  `CharName` varchar(24) NOT NULL DEFAULT '\0',
  `Pass` varchar(32) NOT NULL DEFAULT '\0',
  `IP` varchar(16) NOT NULL DEFAULT '\0',
  `DateReg` varchar(64) NOT NULL DEFAULT '\0',
  `LastDate` varchar(64) NOT NULL DEFAULT '-',
  `GS` int(9) NOT NULL DEFAULT 0,
  `Rank` int(1) NOT NULL DEFAULT 0,
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
  `AJS` int(9) NOT NULL DEFAULT 0,
  `VW` int(2) NOT NULL DEFAULT 0,
  `INT` int(2) NOT NULL DEFAULT 0,
  `Skin` int(3) NOT NULL DEFAULT 0,
  `LastSkin` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `Bank` int(9) NOT NULL DEFAULT 0,
  `Debt` int(9) NOT NULL DEFAULT 0,
  `PistSkill` int(9) NOT NULL DEFAULT 0,
  `SemiSkill` int(9) NOT NULL DEFAULT 0,
  `AutomSkill` int(9) NOT NULL DEFAULT 0,
  `ShotgSkill` int(9) NOT NULL DEFAULT 0,
  `RifleSkill` int(9) NOT NULL DEFAULT 0,
  `BW` int(5) NOT NULL DEFAULT 0,
  `AJ` int(5) NOT NULL DEFAULT 0,
  `AL` int(5) NOT NULL DEFAULT 0,
  `DrvLicAttempts` int(3) NOT NULL DEFAULT 0,
  `GOV` int(2) NOT NULL DEFAULT 0,
  `Hotel` int(2) NOT NULL DEFAULT 0,
  `HotelPaid` int(4) NOT NULL DEFAULT 0,
  `IdCard` int(1) NOT NULL DEFAULT 0,
  `DriverLicense` int(2) NOT NULL DEFAULT 0,
  `Detention` int(5) NOT NULL DEFAULT 0,
  `PDP` int(5) NOT NULL DEFAULT 0,
  `TelNum` int(7) NOT NULL DEFAULT 0,
  `TelNetwork` int(3) NOT NULL DEFAULT 0,
  `BankAcc` int(8) NOT NULL DEFAULT 0,
  `GroupDesc` varchar(128) NOT NULL DEFAULT '-',
  `Group0` int(2) NOT NULL DEFAULT 0,
  `Group1` int(3) NOT NULL DEFAULT 0,
  `Group2` int(3) NOT NULL DEFAULT 0,
  `Group3` int(3) NOT NULL DEFAULT 0,
  `Group4` int(3) NOT NULL DEFAULT 0,
  `Perm0` int(9) NOT NULL DEFAULT 0,
  `Perm1` int(9) NOT NULL DEFAULT 0,
  `Perm2` int(9) NOT NULL DEFAULT 0,
  `Perm3` int(9) NOT NULL DEFAULT 0,
  `Perm4` int(9) NOT NULL DEFAULT 0,
  `PayDay0` int(9) NOT NULL DEFAULT 0,
  `PayDay1` int(9) NOT NULL DEFAULT 0,
  `PayDay2` int(9) NOT NULL DEFAULT 0,
  `PayDay3` int(9) NOT NULL DEFAULT 0,
  `PayDay4` int(9) NOT NULL DEFAULT 0,
  `Duty0` int(9) NOT NULL DEFAULT 0,
  `Duty1` int(9) NOT NULL DEFAULT 0,
  `Duty2` int(9) NOT NULL DEFAULT 0,
  `Duty3` int(9) NOT NULL DEFAULT 0,
  `Duty4` int(9) NOT NULL DEFAULT 0,
  `CasualJob` int(1) NOT NULL DEFAULT 0,
  `Traveled` float NOT NULL DEFAULT 0,
  `Addiction` float NOT NULL DEFAULT 0,
  `Door` int(3) NOT NULL DEFAULT 0,
  `Audio` int(1) NOT NULL DEFAULT 0,
  `ChatStyle` int(1) NOT NULL DEFAULT 0,
  `Computer` int(1) NOT NULL DEFAULT 0,
  `WalkAnim` int(1) NOT NULL DEFAULT 0,
  `StyleFight` int(1) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '-'
) ENGINE=MyISAM DEFAULT CHARSET=latin2 COLLATE=latin2_general_ci;

--
-- Dumping data for table `osrp_players`
--

INSERT INTO `osrp_players` (`UID`, `GUID`, `CharNum`, `AccName`, `CharName`, `Pass`, `IP`, `DateReg`, `LastDate`, `GS`, `Rank`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `Bans`, `Kicks`, `Warns`, `AJS`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `Debt`, `PistSkill`, `SemiSkill`, `AutomSkill`, `ShotgSkill`, `RifleSkill`, `BW`, `AJ`, `AL`, `DrvLicAttempts`, `GOV`, `Hotel`, `HotelPaid`, `IdCard`, `DriverLicense`, `Detention`, `PDP`, `TelNum`, `TelNetwork`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Perm0`, `Perm1`, `Perm2`, `Perm3`, `Perm4`, `PayDay0`, `PayDay1`, `PayDay2`, `PayDay3`, `PayDay4`, `Duty0`, `Duty1`, `Duty2`, `Duty3`, `Duty4`, `CasualJob`, `Traveled`, `Addiction`, `Door`, `Audio`, `ChatStyle`, `Computer`, `WalkAnim`, `StyleFight`, `PosX`, `PosY`, `PosZ`, `Desc`) VALUES
(1, 1, 1, 'steeZ', 'Danny Walker', '81DC9BDB52D04DC20036DBD8313ED055', '127.0.0.1', '24.07.2022 12:00:00', '09/05/2025 21:36:57', 496, 11, 0, 3000, 14, 17, 27, 100, 0, 1, 8, 0, 7, 100, 0, 78, 78, 40, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 2368759, 0, 39481086, 'LSPD, LSPD, LSPD, LSPD, ', 1, 2, 0, 0, 0, 10, 0, 0, 0, 0, 100, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 316870, 0.2, 1, 1, 1, 1, 1, 0, 133.821, -67.8108, 1.57812, 'Nic'),
(2, 2, 1, 'steeZ2', 'Cyrus Arca', '81DC9BDB52D04DC20036DBD8313ED055', '127.0.0.1', '26/03/2025 22:49:15', '15/04/2025 12:08:18', 8, 0, 0, 3000, 0, 8, 56, 5, 0, 0, 0, 0, 7, 1, 0, 291, 291, 60, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41019591, '-', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 1, 1, 1, 0, 1, 1, 1178.27, -1171.68, 86.8455, '');

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
  `AllAccounts` int(9) NOT NULL DEFAULT 0,
  `AllCharacters` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_settings`
--

INSERT INTO `osrp_settings` (`AllAccounts`, `AllCharacters`) VALUES
(4, 4);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_things`
--

CREATE TABLE `osrp_things` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Value1` int(3) NOT NULL DEFAULT 0,
  `Value2` int(3) NOT NULL DEFAULT 0,
  `Value3` int(3) NOT NULL DEFAULT 0,
  `Value4` int(3) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Used` int(1) NOT NULL DEFAULT 0,
  `Term` int(9) NOT NULL DEFAULT 0,
  `Place` int(1) NOT NULL DEFAULT 0,
  `VW` int(5) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_things`
--

INSERT INTO `osrp_things` (`UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Value3`, `Value4`, `PosX`, `PosY`, `PosZ`, `Used`, `Term`, `Place`, `VW`, `INT`) VALUES
(18, 65535, 25, 'Ubranie (26)', 26, 0, 0, 0, 1318930000, -834215000, 1318930000, 1, 0, 2, 0, 0),
(19, 1, 25, 'Ubranie (78)', 78, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0),
(26, 1, 40, 'Telefon', 0, 20, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0),
(27, 1, 25, 'Ubranie (230)', 230, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(30, 1, 6, 'Woda', 20, 30, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(31, 1, 6, 'Woda', 20, 30, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(32, 1, 6, 'Woda', 20, 30, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(33, 1, 6, 'Woda', 20, 30, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(38, 1, 3, 'Kij', 3, 0, 0, 0, 0, 0, 0, 0, 1746817259, 1, 0, 0),
(39, 1, 3, 'Kij', 3, 1, 0, 0, 0, 0, 0, 0, 1746817266, 1, 0, 0),
(40, 1, 5, 'Kij', 5, 1, 0, 0, 0, 0, 0, 0, 1744398078, 1, 0, 0),
(41, 65535, 3, 'Kij', 5, 1, 0, 0, 1318930000, -834215000, 1318930000, 0, 1746817546, 2, 0, 0),
(42, 1, 45, 'Rolki', 4343, 3433, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0),
(44, 1, 5, 'MP5', 29, 50, 0, 0, 0, 0, 0, 0, 1745112923, 1, 0, 0),
(45, 1, 5, 'MP5', 29, 50, 0, 0, 0, 0, 0, 0, 1745112923, 1, 0, 0),
(46, 1, 45, 'Rolki', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_vehicles`
--

CREATE TABLE `osrp_vehicles` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Type` int(1) NOT NULL DEFAULT 0,
  `ModelId` int(3) NOT NULL DEFAULT 0,
  `Color1` int(3) NOT NULL DEFAULT 0,
  `Color2` int(3) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Angle` float NOT NULL DEFAULT 0,
  `Fuel` float NOT NULL DEFAULT 0,
  `Lock` int(1) NOT NULL DEFAULT 0,
  `Engine` int(1) NOT NULL DEFAULT 0,
  `EngineHealth` float NOT NULL DEFAULT 0,
  `Spawned` int(1) NOT NULL DEFAULT 0,
  `LightsOn` int(1) NOT NULL DEFAULT 0,
  `Window` int(1) NOT NULL DEFAULT 0,
  `Alarm` int(1) NOT NULL DEFAULT 0,
  `Immo` int(1) NOT NULL DEFAULT 0,
  `CBRadio` int(1) NOT NULL DEFAULT 0,
  `Audio` int(1) NOT NULL DEFAULT 0,
  `Limiter` int(1) NOT NULL DEFAULT 0,
  `Panels` int(3) NOT NULL DEFAULT 0,
  `Doors` int(3) NOT NULL DEFAULT 0,
  `Lights` int(3) NOT NULL DEFAULT 0,
  `Tires` int(3) NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0,
  `Paintjob` int(1) NOT NULL DEFAULT -1,
  `Nitro` int(1) NOT NULL DEFAULT 0,
  `Repair` float NOT NULL DEFAULT 0,
  `Mileage` float NOT NULL DEFAULT 0,
  `Block` int(1) NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '\\0',
  `Plate` varchar(32) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_vehicles`
--

INSERT INTO `osrp_vehicles` (`UID`, `OUID`, `Type`, `ModelId`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Angle`, `Fuel`, `Lock`, `Engine`, `EngineHealth`, `Spawned`, `LightsOn`, `Window`, `Alarm`, `Immo`, `CBRadio`, `Audio`, `Limiter`, `Panels`, `Doors`, `Lights`, `Tires`, `VW`, `INT`, `Paintjob`, `Nitro`, `Repair`, `Mileage`, `Block`, `Desc`, `Plate`) VALUES
(1, 1, 9, 400, 0, 0, 1380.54, -1736.86, 13.5137, 86.5751, 19.33, 0, 1, 1000, 0, 1, 0, 0, 0, 0, 0, 0, 33554432, 16777728, 0, 0, 0, 0, -1, 0, 0, 116.381, 0, 'LSPD', ''),
(2, 1, 9, 491, 136, 197, 1203.98, -1397.61, 13.0391, 241.871, 55.9574, 0, 1, 1000, 1, 1, 0, 0, 0, 0, 0, 0, 1048592, 0, 4, 0, 0, 0, -1, 0, 0, 82.7023, 0, '', '');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_wholesales`
--

CREATE TABLE `osrp_wholesales` (
  `UID` int(4) NOT NULL,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `ThingKind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(128) NOT NULL DEFAULT '\\0',
  `Price` int(9) NOT NULL DEFAULT 0,
  `Value1` int(9) NOT NULL DEFAULT 0,
  `Value2` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `osrp_3dtexts`
--
ALTER TABLE `osrp_3dtexts`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_animations`
--
ALTER TABLE `osrp_animations`
  ADD PRIMARY KEY (`UID`);

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
-- Indeksy dla tabeli `osrp_dimensions`
--
ALTER TABLE `osrp_dimensions`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_doors`
--
ALTER TABLE `osrp_doors`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_grouporders`
--
ALTER TABLE `osrp_grouporders`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groupperms`
--
ALTER TABLE `osrp_groupperms`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groups`
--
ALTER TABLE `osrp_groups`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_grouptasks`
--
ALTER TABLE `osrp_grouptasks`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groupthings`
--
ALTER TABLE `osrp_groupthings`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_groupvehicles`
--
ALTER TABLE `osrp_groupvehicles`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_notes`
--
ALTER TABLE `osrp_notes`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_objects`
--
ALTER TABLE `osrp_objects`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_penalties`
--
ALTER TABLE `osrp_penalties`
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
-- Indeksy dla tabeli `osrp_things`
--
ALTER TABLE `osrp_things`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_vehicles`
--
ALTER TABLE `osrp_vehicles`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_wholesales`
--
ALTER TABLE `osrp_wholesales`
  ADD PRIMARY KEY (`UID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `osrp_3dtexts`
--
ALTER TABLE `osrp_3dtexts`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `osrp_animations`
--
ALTER TABLE `osrp_animations`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=136;

--
-- AUTO_INCREMENT for table `osrp_areas`
--
ALTER TABLE `osrp_areas`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_booths`
--
ALTER TABLE `osrp_booths`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_busstops`
--
ALTER TABLE `osrp_busstops`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `osrp_cashpoints`
--
ALTER TABLE `osrp_cashpoints`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_contacts`
--
ALTER TABLE `osrp_contacts`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_dimensions`
--
ALTER TABLE `osrp_dimensions`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_doors`
--
ALTER TABLE `osrp_doors`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_grouporders`
--
ALTER TABLE `osrp_grouporders`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_groupperms`
--
ALTER TABLE `osrp_groupperms`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_groups`
--
ALTER TABLE `osrp_groups`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_grouptasks`
--
ALTER TABLE `osrp_grouptasks`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `osrp_groupthings`
--
ALTER TABLE `osrp_groupthings`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_groupvehicles`
--
ALTER TABLE `osrp_groupvehicles`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_notes`
--
ALTER TABLE `osrp_notes`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_objects`
--
ALTER TABLE `osrp_objects`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `osrp_penalties`
--
ALTER TABLE `osrp_penalties`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `osrp_players`
--
ALTER TABLE `osrp_players`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_races`
--
ALTER TABLE `osrp_races`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_things`
--
ALTER TABLE `osrp_things`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;

--
-- AUTO_INCREMENT for table `osrp_vehicles`
--
ALTER TABLE `osrp_vehicles`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `osrp_wholesales`
--
ALTER TABLE `osrp_wholesales`
  MODIFY `UID` int(4) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
