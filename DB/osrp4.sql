-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Mar 20, 2025 at 12:20 PM
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
-- Struktura tabeli dla tabeli `osrp_3DTexts`
--

CREATE TABLE `osrp_3DTexts` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
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
-- Dumping data for table `osrp_3DTexts`
--

INSERT INTO `osrp_3DTexts` (`UID`, `OUID`, `Kind`, `Desc`, `Color`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES
(1, 0, 0, 'Zakaz postoju', 'FF0000FF', 1537.82, -1668.79, 14.1014, 30, 0, 0),
(2, 0, 0, 'Zakaz parkowania!', 'FF0000FF', 1525.52, -1447.82, 14.11, 30, 0, 0),
(3, 0, 0, 'Bankomat\\n{FFFFFF}(( Wpisz /bank stojąc bardzo blisko,\\nby użyć ', '\\0', 0, 0, 0, 30, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Animations`
--

CREATE TABLE `osrp_Animations` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Dumping data for table `osrp_Animations`
--

INSERT INTO `osrp_Animations` (`UID`, `Name`, `AnimLib`, `AnimName`, `Delta`, `Loop`, `LockX`, `LockY`, `Freeze`, `Time`, `Forcesync`) VALUES
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
-- Struktura tabeli dla tabeli `osrp_Areas`
--

CREATE TABLE `osrp_Areas` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `MinX` float NOT NULL DEFAULT 0,
  `MinY` float NOT NULL DEFAULT 0,
  `MaxX` float NOT NULL DEFAULT 0,
  `MaxY` float NOT NULL DEFAULT 0,
  `MaxSpeed` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Areas`
--

INSERT INTO `osrp_Areas` (`UID`, `OUID`, `MinX`, `MinY`, `MaxX`, `MaxY`, `MaxSpeed`) VALUES
(1, 1, 802.279, -1310.05, 911.834, -1337.22, 80);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Booths`
--

CREATE TABLE `osrp_Booths` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Name` varchar(32) NOT NULL DEFAULT '\\n',
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Range` float NOT NULL DEFAULT 0,
  `Working` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_BusStops`
--

CREATE TABLE `osrp_BusStops` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_BusStops`
--

INSERT INTO `osrp_BusStops` (`UID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`) VALUES
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
-- Struktura tabeli dla tabeli `osrp_CashPoints`
--

CREATE TABLE `osrp_CashPoints` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Dumping data for table `osrp_CashPoints`
--

INSERT INTO `osrp_CashPoints` (`UID`, `Name`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES
(1, 'Market', 1, 837.508, -1338.88, 6.8208, 0, 0, 0, 3, 0, 0),
(2, 'Hotel 52', 1, 897.71, -1338.53, 19.121, 0, 0, -90, 3, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Contacts`
--

CREATE TABLE `osrp_Contacts` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Name` varchar(24) NOT NULL DEFAULT '\\0',
  `Number` int(7) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Dimensions`
--

CREATE TABLE `osrp_Dimensions` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL,
  `MinX` float NOT NULL,
  `MinY` float NOT NULL,
  `MinZ` float NOT NULL,
  `MaxX` float NOT NULL,
  `MaxY` float NOT NULL,
  `MaxZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_Dimensions`
--

INSERT INTO `osrp_Dimensions` (`UID`, `OUID`, `MinX`, `MinY`, `MinZ`, `MaxX`, `MaxY`, `MaxZ`) VALUES
(1, 1, 898.418, -1342.41, 18.3583, 854.81, -1322.18, 19.3583);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_doors`
--

CREATE TABLE `osrp_Doors` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `OKind` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
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
  `Objects` int(9) NOT NULL DEFAULT 0,
  `MaxObjects` int(9) NOT NULL DEFAULT 0,
  `Texts` int(9) NOT NULL DEFAULT 0,
  `MaxTexts` int(9) NOT NULL DEFAULT 0,
  `Security` int(3) NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Doors`
--

INSERT INTO `osrp_Doors` (`UID`, `OUID`, `OKind`, `Kind`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `ExitX`, `ExitY`, `ExitZ`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `VW`, `INT`) VALUES
(1, 1, 1, 1, 'Hotel 52', 893.161, -1336.08, 13.5469, 897.469, -1339.92, 19.4569, 1, 1, '27.10.2024', 10, 1, 1, 1, 1, 1, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupThings`
--

CREATE TABLE `osrp_GroupThings` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Value1` int(5) NOT NULL DEFAULT 0,
  `Value2` int(5) NOT NULL DEFAULT 0,
  `Price` int(5) NOT NULL DEFAULT 0,
  `Amount` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_GroupThings`
--

INSERT INTO `osrp_GroupThings` (`UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Price`, `Amount`) VALUES
(1, 1, 21, 'MP5', 29, 50, 10, 100);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupOrders`
--

CREATE TABLE `osrp_GroupOrders` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Struktura tabeli dla tabeli `osrp_GroupPerms`
--

CREATE TABLE `osrp_GroupPerms` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Dumping data for table `osrp_GroupPerms`
--

INSERT INTO `osrp_GroupPerms` (`UID`, `OUID`, `PermOOC`, `PermIC`, `PermMegaphone`, `PermName`, `PermTag`, `PermDept`, `PermGPS`, `PermRope`, `PermWithdraw`, `PermNews`, `PermBlockCar`, `PermGangZone`, `PermBuyList`, `PermDetention`, `PermRobbery`) VALUES
(1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Groups`
--

CREATE TABLE `osrp_Groups` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Tag` varchar(8) NOT NULL DEFAULT '\\0',
  `Date` varchar(32) NOT NULL DEFAULT '\\0',
  `Kind` int(2) NOT NULL DEFAULT 0,
  `Members` int(3) NOT NULL DEFAULT 0,
  `VehsLimit` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `Door` int(3) NOT NULL DEFAULT 0,
  `Color` varchar(8) NOT NULL DEFAULT '\\0',
  `Register` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Groups`
--

INSERT INTO `osrp_Groups` (`UID`, `Name`, `Tag`, `Date`, `Kind`, `Members`, `VehsLimit`, `Money`, `Door`, `Color`, `Register`) VALUES
(1, 'LSPD', 'LSPD', '13.03.2025', 1, 1, 100, 121221, 1, '0000FF', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupTasks`
--

CREATE TABLE `osrp_GroupTasks` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(128) NOT NULL DEFAULT '\\0',
  `Date` varchar(64) NOT NULL DEFAULT '\\0',
  `Caller` varchar(24) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_GroupTasks`
--

INSERT INTO `osrp_GroupTasks` (`UID`, `OUID`, `Desc`, `Date`, `Caller`) VALUES
(1, 1, 'Witam', '17:19 13/03/2025', 'Danny Walker');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupVehicles`
--

CREATE TABLE `osrp_GroupVehicles` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Struktura tabeli dla tabeli `osrp_Things`
--

CREATE TABLE `osrp_Things` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Value1` int(3) NOT NULL DEFAULT 0,
  `Value2` int(3) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Used` int(1) NOT NULL DEFAULT 0,
  `Term` int(9) NOT NULL DEFAULT 0,
  `Place` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Things`
--

INSERT INTO `osrp_Things` (`UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `PosX`, `PosY`, `PosZ`, `Used`, `Term`, `Place`) VALUES
(1, 1, 1, 'Rolki', 40, 20, 0, 0, 0, 0, 0, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Notes`
--

CREATE TABLE `osrp_Notes` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Objects`
--

CREATE TABLE `osrp_Objects` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(1) NOT NULL DEFAULT 0,
  `ModelId` int(9) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Distance` float NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_Objects`
--

INSERT INTO `osrp_Objects` (`UID`, `OUID`, `Kind`, `ModelId`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES
(1, 0, 0, 1233, 1537.82, -1668.79, 14.1014, 0, 0, 0, 400, 0, 0),
(2, 0, 0, 1233, 1525.52, -1447.82, 14.11, 0, 0, 180, 400, 0, 0),
(3, 0, 0, 1233, 1298.4, -1389.64, 13.5231, 0, 0, -90, 400, 0, 0),
(4, 0, 0, 1233, 1190.02, -1330.28, 13.714, 0, 0, 0, 400, 0, 0),
(5, 0, 0, 1234, 820.88, -1332.59, 13.5432, 0, 0, 180, 400, 0, 0),
(6, 0, 0, 1234, 1068.25, -1384.09, 13.654, 0, 0, -90, 400, 0, 0),
(7, 0, 0, 1234, 1067.67, -1360.76, 13.654, 0, 0, -90, 400, 0, 0),
(8, 0, 0, 968, 1544.71, -1630.92, 13.1809, 0, 90, 90, 400, 0, 0),
(9, 0, 0, 994, 1544.66, -1623.77, 12.539, 0, 0, 90, 400, 0, 0),
(10, 0, 0, 996, 1821.65, -1743.6, 13.0191, 0, 0, 90, 400, 0, 0),
(11, 0, 0, 4526, 1944.7, -1766.2, 14.3973, 0, 0, 90, 400, 0, 0),
(12, 0, 0, 971, 778.27, -1384.91, 12.8952, 0, 0, 358.979, 400, 0, 0),
(13, 0, 0, 971, 777.393, -1330.24, 12.8952, 0, 0, 358.979, 400, 0, 0),
(14, 0, 0, 8843, 840.226, -1335.51, 12.6303, 0, 0, -90, 400, 0, 0),
(15, 0, 0, 8843, 1034.19, -1409.84, 11.88, 2.66, 0, 0, 400, 0, 0),
(16, 0, 0, 8843, 1028.2, -1407.27, 12.1836, 0, 0, -90, 400, 0, 0),
(17, 0, 0, 8843, 1028.31, -1403.28, 12.0836, 1, 2, -90, 400, 0, 0),
(18, 0, 0, 8843, 1079.62, -1399.72, 12.5278, 1, 0, 0, 400, 0, 0),
(19, 0, 0, 8843, 1085.19, -1397.9, 12.5878, 0, 0, 90, 400, 0, 0),
(20, 0, 0, 18880, 1046.16, -1415.64, 11.3057, 0, 0, 122.209, 400, 0, 0),
(21, 0, 0, 1283, 1064.06, -1416.44, 15.7109, 0, 0, 0, 400, 0, 0),
(22, 0, 0, 1283, 1046.35, -1407.15, 15.7109, 356.858, 0, -1.5708, 400, 0, 0),
(23, 0, 0, 1438, 2104.09, -1763.58, 12.5607, 0, 0, 180, 400, 0, 0),
(24, 0, 0, 13296, 2121.27, -1774.65, 15.6079, 0, 0, 269.407, 400, 0, 0),
(25, 0, 0, 3465, 2115.59, -1777.77, 13.784, 0, 0, 0, 400, 0, 0),
(26, 0, 0, 3465, 2115.63, -1773.13, 13.784, 0, 0, 0, 400, 0, 0),
(27, 0, 0, 1415, 2124.94, -1762.67, 12.6809, 0, 0, 180, 400, 0, 0),
(28, 0, 0, 1432, 2127.37, -1761.06, 12.6801, 0, 0, 186.569, 400, 0, 0),
(29, 0, 0, 1709, 2115.62, -1788.56, 12.5408, 0, 0, 180, 400, 0, 0),
(30, 0, 0, 3460, 2100.17, -1778, 16.4867, 0, 0, 251.667, 400, 0, 0),
(31, 0, 0, 3460, 2107.19, -1762.9, 16.4867, 0, 0, 251.667, 400, 0, 0),
(32, 0, 0, 947, 2107.12, -1789.65, 14.6556, 0, -6, 0, 400, 0, 0),
(33, 0, 0, 1257, 2193.65, -1751.04, 13.592, 0, 0, 0, 400, 0, 0),
(34, 0, 0, 1259, 2215.51, -1731.07, 27.6019, 0, 0, 62.403, 400, 0, 0),
(35, 0, 0, 851, 2102.62, -1766.66, 12.8251, 0, 0, 0, 400, 0, 0),
(36, 0, 0, 1441, 2120.15, -1789.79, 13.1959, 0, 0, 180, 400, 0, 0),
(37, 0, 0, 1372, 2102.99, -1790.44, 12.9227, -90, 0, 90, 400, 0, 0),
(38, 0, 0, 17070, 2117.83, -1783.3, 12.3976, 0, 0, 356.115, 400, 0, 0),
(39, 0, 0, 7389, 1115.62, -1372.97, 14.008, 0, 0, 180.244, 400, 0, 0),
(40, 0, 0, 2942, 837.508, -1338.88, 6.8208, 0, 0, 0, 400, 0, 0),
(41, 0, 0, 6965, 1350.13, -1400.42, 15.7689, 0, 0, 0, 400, 0, 0),
(42, 0, 0, 19603, 1344.33, -1402.95, 12.3597, 0, 0, 0, 400, 0, 0),
(43, 0, 0, 19603, 1356.12, -1403.42, 12.3397, 0, 0, 0, 400, 0, 0),
(44, 0, 0, 19603, 1352.42, -1400.34, 12.4197, 0, 0, 0, 400, 0, 0),
(45, 0, 0, 19603, 1345.53, -1405.23, 12.3397, 0, 0, 0, 400, 0, 0),
(46, 0, 0, 19603, 1355.98, -1398.3, 12.4197, 0, 0, 0, 400, 0, 0),
(47, 0, 0, 19603, 1343.78, -1397.79, 12.3997, 0, 0, 0, 400, 0, 0),
(48, 0, 0, 19603, 1354.43, -1405.3, 12.3397, 0, 0, 0, 400, 0, 0),
(49, 0, 0, 19603, 1347.54, -1406.55, 12.3797, 0, 0, 0, 400, 0, 0),
(50, 0, 0, 19603, 1357.42, -1400.33, 12.3397, 0, 0, 0, 400, 0, 0),
(51, 0, 0, 19603, 1352.18, -1406.84, 12.3597, 0, 0, 0, 400, 0, 0),
(52, 0, 0, 19603, 1350.55, -1405.29, 12.3597, 0, 0, 0, 400, 0, 0),
(53, 0, 0, 19603, 1347.41, -1400.35, 12.4197, 0, 0, 0, 400, 0, 0),
(54, 0, 0, 19603, 1345.7, -1395.41, 12.4197, 0, 0, 0, 400, 0, 0),
(55, 0, 0, 19603, 1354.74, -1395.65, 12.4197, 0, 0, 0, 400, 0, 0),
(56, 0, 0, 19603, 1352.44, -1395.35, 12.4197, 0, 0, 0, 400, 0, 0),
(57, 0, 0, 19603, 1342.84, -1400.34, 12.3597, 0, 0, 0, 400, 0, 0),
(58, 0, 0, 19603, 1352.08, -1394.17, 12.4397, 0, 0, 0, 400, 0, 0),
(59, 0, 0, 19603, 1347.45, -1395.35, 12.4197, 0, 0, 0, 400, 0, 0),
(60, 0, 0, 19603, 1348.37, -1393.89, 12.4397, 0, 0, 0, 400, 0, 0),
(61, 0, 0, 1374, 2292.58, -1144.32, 26.8103, 100, 180, 0, 400, 0, 0),
(62, 0, 0, 1374, 2207.94, -1726.14, 13.6511, 80, 0, 180, 400, 0, 0),
(63, 0, 0, 1374, 2195.07, -1738.03, 13.6511, 80, 0, 0, 400, 0, 0),
(64, 0, 0, 1374, 2282.3, -1155.12, 26.9063, 80, 0, 359.697, 400, 0, 0),
(65, 0, 0, 1375, 2292.31, -1143.61, 27.3524, 0, 0, 90, 400, 0, 0),
(66, 0, 0, 1375, 2282.54, -1155.64, 27.3524, 0, 0, -90, 400, 0, 0),
(67, 1, 1, 14771, 875.482, -1336.66, 20.4803, 0, 0, 0, 300, 100, 0),
(68, 1, 16, 1233, 895.339, -1338.66, 19.4569, 0, 0, 0, 1137180000, 0, 0),
(69, 1, 16, 19379, 885.805, -1338.94, 19.4569, 0, 0, 0, 1137180000, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Penalties`
--

CREATE TABLE `osrp_Penalties` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `SUID` int(3) NOT NULL DEFAULT 0,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `IP` varchar(16) NOT NULL DEFAULT '\\0',
  `Kind` int(3) NOT NULL DEFAULT 0,
  `Days` int(3) NOT NULL DEFAULT 0,
  `Date` varchar(64) NOT NULL DEFAULT '\\0',
  `Reason` varchar(128) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_Penalties`
--

INSERT INTO `osrp_Penalties` (`UID`, `SUID`, `OUID`, `IP`, `Kind`, `Days`, `Date`, `Reason`) VALUES
(5, 65535, 1, '', 2, 0, '10:02:26 20.03.2025', 'Unfreeze~n~~w~Ruch o 0.1j podczas zamrozenia pieszo.');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Players`
--

CREATE TABLE `osrp_Players` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Dumping data for table `osrp_Players`
--

INSERT INTO `osrp_Players` (`UID`, `GUID`, `CharNum`, `AccName`, `CharName`, `Pass`, `IP`, `DateReg`, `LastDate`, `GS`, `Rank`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `Bans`, `Kicks`, `Warns`, `AJS`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `Debt`, `PistSkill`, `SemiSkill`, `AutomSkill`, `ShotgSkill`, `RifleSkill`, `BW`, `AJ`, `AL`, `DrvLicAttempts`, `GOV`, `Hotel`, `HotelPaid`, `IdCard`, `DriverLicense`, `Detention`, `PDP`, `TelNum`, `TelNetwork`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Perm0`, `Perm1`, `Perm2`, `Perm3`, `Perm4`, `PayDay0`, `PayDay1`, `PayDay2`, `PayDay3`, `PayDay4`, `CasualJob`, `Traveled`, `Addiction`, `Door`, `Audio`, `ChatStyle`, `Computer`, `WalkAnim`, `StyleFight`, `PosX`, `PosY`, `PosZ`, `Desc`) VALUES
(1, 1, 1, 'steeZ', 'Danny Walker', '827ccb0eea8a706c4c34a16891f84e7b', '', '15/03/2025 23:28:10', '20/03/2025 10:10:38', 51, 11, 1, 3000, 0, 48, 47, 100, 0, 0, 4, 0, 1, 0, 0, 1, 217, 70, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 2892192, 0, 10886510, '-', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2456.82, 0, 1, 1, 1, 0, 1, 1, 858.436, -1314.88, 13.556, 'Test');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Races`
--

CREATE TABLE `osrp_Races` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
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
-- Struktura tabeli dla tabeli `osrp_Settings`
--

CREATE TABLE `osrp_Settings` (
  `AllAccounts` int(9) NOT NULL DEFAULT 0,
  `AllCharacters` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Settings`
--

INSERT INTO `osrp_Settings` (`AllAccounts`, `AllCharacters`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Vehicles`
--

CREATE TABLE `osrp_Vehicles` (
  `UID` int(3) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(1) NOT NULL DEFAULT 0,
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
-- Dumping data for table `osrp_Vehicles`
--

INSERT INTO `osrp_Vehicles` (`UID`, `OUID`, `Kind`, `ModelId`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Angle`, `Fuel`, `Lock`, `Engine`, `EngineHealth`, `Spawned`, `LightsOn`, `Window`, `Alarm`, `Immo`, `CBRadio`, `Audio`, `Limiter`, `Panels`, `Doors`, `Lights`, `Tires`, `VW`, `INT`, `Paintjob`, `Nitro`, `Repair`, `Mileage`, `Block`, `Desc`, `Plate`) VALUES
(1, 1, 9, 400, 0, 0, 858.436, -1314.88, 13.556, 88.6971, 39.1545, 0, 0, 840.688, 1, 1, 0, 0, 0, 0, 0, 0, 1048592, 0, 4, 0, 0, 0, -1, 0, 0, 19.2687, 0, 'Test', '');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_WholeSales`
--

CREATE TABLE `osrp_WholeSales` (
  `UID` int(4) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `ItemKind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(128) NOT NULL DEFAULT '\\0',
  `Price` int(9) NOT NULL DEFAULT 0,
  `Value1` int(9) NOT NULL DEFAULT 0,
  `Value2` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_WholeSales`
--

INSERT INTO `osrp_WholeSales` (`UID`, `Kind`, `ItemKind`, `Name`, `Price`, `Value1`, `Value2`) VALUES
(1, 0, 1, 'Rolki', 0, 0, 0),
(2, 0, 2, 'Piwo', 0, 0, 0),
(3, 0, 3, 'Wino', 0, 0, 0),
(4, 0, 3, 'Vodka', 0, 0, 0),
(5, 0, 3, 'Sake Maki', 0, 0, 0),
(6, 0, 3, 'CubaLibre', 0, 0, 0),
(7, 0, 3, 'Mojito', 0, 0, 0),
(8, 0, 4, 'Sprunk', 0, 0, 0),
(9, 0, 4, 'Cappuccino', 0, 0, 0),
(10, 0, 4, 'Coca-Cola', 0, 0, 0),
(11, 0, 4, 'Pepsi', 0, 0, 0),
(12, 0, 4, 'Energy drink', 0, 0, 0),
(13, 0, 4, 'Herbata', 0, 0, 0),
(14, 0, 4, 'Kawa', 0, 0, 0),
(15, 0, 4, 'Woda Mineralna', 0, 0, 0),
(16, 0, 5, 'Marlboro', 0, 1, 0),
(17, 0, 5, 'Cygaro', 0, 1, 0),
(18, 0, 6, 'Teczka', 0, 0, 0),
(19, 0, 7, 'Torba', 0, 0, 0),
(20, 0, 8, 'Notatnik', 0, 0, 0),
(21, 0, 10, 'Heroina', 0, 0, 0),
(22, 0, 11, 'Anadrall', 0, 0, 0),
(23, 0, 12, 'Joint (marihuana)', 0, 0, 0),
(26, 0, 13, 'Ubranie 3 (dla mafii)', 0, 3, 0),
(27, 0, 13, 'Ubranie 6 (dla gangow)', 0, 6, 0),
(28, 0, 13, 'Ubranie 83 (dla gangow)', 0, 83, 0),
(29, 0, 13, 'Ubranie 86 (dla gangow)', 0, 86, 0),
(30, 0, 13, 'Ubranie 102 (dla gangow)', 0, 102, 0),
(31, 0, 13, 'Ubranie 103 (dla gangow)', 0, 103, 0),
(32, 0, 13, 'Ubranie 104 (dla gangow)', 0, 104, 0),
(33, 0, 13, 'Ubranie 105 (dla gangow)', 0, 105, 0),
(34, 0, 13, 'Ubranie 106 (dla gangow)', 0, 106, 0),
(35, 0, 13, 'Ubranie 107 (dla gangow)', 0, 107, 0),
(36, 0, 13, 'Ubranie 108 (dla gangow)', 0, 108, 0),
(37, 0, 13, 'Ubranie 109 (dla gangow)', 0, 109, 0),
(38, 0, 13, 'Ubranie 110 (dla gangow)', 0, 110, 0),
(39, 0, 13, 'Ubranie 111 (dla mafii)', 0, 111, 0),
(40, 0, 13, 'Ubranie 112 (dla mafii)', 0, 112, 0),
(41, 0, 13, 'Ubranie 113 (dla mafii)', 0, 113, 0),
(42, 0, 13, 'Ubranie 114 (dla gangow)', 0, 114, 0),
(43, 0, 13, 'Ubranie 115 (dla gangow)', 0, 115, 0),
(44, 0, 13, 'Ubranie 116 (dla gangow)', 0, 116, 0),
(45, 0, 13, 'Ubranie 117 (dla mafii)', 0, 117, 0),
(46, 0, 13, 'Ubranie 118 (dla mafii)', 0, 118, 0),
(47, 0, 13, 'Ubranie 119 (dla mafii)', 0, 119, 0),
(48, 0, 13, 'Ubranie 120 (dla mafii)', 0, 120, 0),
(49, 0, 13, 'Ubranie 121 (dla mafii)', 0, 121, 0),
(50, 0, 13, 'Ubranie 122 (dla mafii)', 0, 122, 0),
(51, 0, 13, 'Ubranie 123 (dla mafii)', 0, 123, 0),
(52, 0, 13, 'Ubranie 124 (dla mafii)', 0, 124, 0),
(53, 0, 13, 'Ubranie 125 (dla mafii)', 0, 125, 0),
(54, 0, 13, 'Ubranie 126 (dla mafii)', 0, 126, 0),
(55, 0, 13, 'Ubranie 127 (dla mafii)', 0, 127, 0),
(56, 0, 13, 'Ubranie 143 (dla gangow)', 0, 143, 0),
(57, 0, 13, 'Ubranie 149 (dla gangow)', 0, 149, 0),
(58, 0, 13, 'Ubranie 155 (restauracji)', 0, 155, 0),
(59, 0, 13, 'Ubranie 165 (dla ochrony)', 0, 165, 0),
(60, 0, 13, 'Ubranie 166 (dla ochrony)', 0, 166, 0),
(61, 0, 13, 'Ubranie 167 (restauracji)', 0, 167, 0),
(62, 0, 13, 'Ubranie 173 (dla gangow)', 0, 173, 0),
(63, 0, 13, 'Ubranie 174 (dla gangow)', 0, 174, 0),
(64, 0, 13, 'Ubranie 175 (dla gangow)', 0, 175, 0),
(65, 0, 13, 'Ubranie 176 (dla gangow)', 0, 176, 0),
(66, 0, 13, 'Ubranie 177 (dla gangow)', 0, 177, 0),
(67, 0, 13, 'Ubranie 179 (dla gangow)', 0, 179, 0),
(68, 0, 13, 'Ubranie 195 (dla gangow)', 0, 195, 0),
(69, 0, 13, 'Ubranie 205 (restauracji)', 0, 205, 0),
(70, 0, 13, 'Ubranie 208 (dla mafii)', 0, 208, 0),
(71, 0, 13, 'Ubranie 224 (dla mafii)', 0, 224, 0),
(72, 0, 13, 'Ubranie 225 (dla mafii)', 0, 225, 0),
(73, 0, 13, 'Ubranie 227 (dla mafii)', 0, 227, 0),
(74, 0, 13, 'Ubranie 228 (dla mafii)', 0, 228, 0),
(75, 0, 13, 'Ubranie 247 (dla gangow)', 0, 247, 0),
(76, 0, 13, 'Ubranie 248 (dla gangow)', 0, 248, 0),
(77, 0, 13, 'Ubranie 249 (dla gangow)', 0, 249, 0),
(78, 0, 13, 'Ubranie 254 (dla gangow)', 0, 254, 0),
(79, 0, 13, 'Ubranie 258 (dla mafii)', 0, 258, 0),
(80, 0, 13, 'Ubranie 259 (dla mafii)', 0, 259, 0),
(81, 0, 13, 'Ubranie 265 (dla porzadkowych)', 0, 265, 0),
(82, 0, 13, 'Ubranie 266 (dla porzadkowych)', 0, 266, 0),
(83, 0, 13, 'Ubranie 267 (dla porzadkowych)', 0, 267, 0),
(84, 0, 13, 'Ubranie 269 (dla gangow)', 0, 269, 0),
(85, 0, 13, 'Ubranie 270 (dla gangow)', 0, 270, 0),
(86, 0, 13, 'Ubranie 271 (dla gangow)', 0, 271, 0),
(87, 0, 13, 'Ubranie 272 (dla mafii)', 0, 272, 0),
(88, 0, 13, 'Ubranie 273 (dla gangow)', 0, 273, 0),
(89, 0, 13, 'Ubranie 274 (dla porzadkowych', 0, 274, 0),
(90, 0, 13, 'Ubranie 275 (dla porzadkowych)', 0, 275, 0),
(91, 0, 13, 'Ubranie 276 (dla porzadkowych)', 0, 276, 0),
(92, 0, 13, 'Ubranie 277 (dla porzadkowych)', 0, 277, 0),
(93, 0, 13, 'Ubranie 278 (dla porzadkowych)', 0, 278, 0),
(94, 0, 13, 'Ubranie 279 (dla porzadkowych)', 0, 279, 0),
(95, 0, 13, 'Ubranie 280 (dla porzadkowych)', 0, 280, 0),
(96, 0, 13, 'Ubranie 281 (dla porzadkowych)', 0, 281, 0),
(97, 0, 13, 'Ubranie 282 (dla porzadkowych)', 0, 282, 0),
(98, 0, 13, 'Ubranie 283 (dla porzadkowych)', 0, 283, 0),
(99, 0, 13, 'Ubranie 284 (dla porzadkowych)', 0, 284, 0),
(100, 0, 13, 'Ubranie 285 (dla porzadkowych)', 0, 285, 0),
(101, 0, 13, 'Ubranie 286 (dla porzadkowych)', 0, 286, 0),
(102, 0, 13, 'Ubranie 287 (dla porzadkowych)', 0, 287, 0),
(103, 0, 13, 'Ubranie 288 (dla porzadkowych)', 0, 288, 0),
(104, 0, 13, 'Ubranie 291 (dla gangow)', 0, 291, 0),
(105, 0, 13, 'Ubranie 292 (dla gangow)', 0, 292, 0),
(106, 0, 13, 'Ubranie 293 (dla gangow)', 0, 293, 0),
(107, 0, 13, 'Ubranie 294 (dla mafii)', 0, 294, 0),
(108, 0, 13, 'Ubranie 295 (dla gangow)', 0, 295, 0),
(109, 0, 13, 'Ubranie 296 (dla gangow)', 0, 296, 0),
(110, 0, 13, 'Ubranie 297 (dla gangow)', 0, 297, 0),
(111, 0, 14, 'Telefon', 0, 0, 0),
(112, 0, 14, 'Nokia 8110', 0, 0, 0),
(113, 0, 14, 'Smartfon', 0, 0, 0),
(114, 0, 15, 'Doladowanie 20', 0, 20, 0),
(115, 0, 16, 'Kostka', 0, 6, 0),
(116, 0, 17, 'Maska', 0, 1, 3000),
(117, 0, 18, 'Czarna bandana', 0, 0, 0),
(118, 0, 19, 'Rekawice', 0, 0, 0),
(119, 0, 20, 'Kamizelka', 0, 0, 0),
(120, 0, 21, 'Kastet', 0, 1, 1),
(121, 0, 21, 'Palka', 0, 3, 1),
(122, 0, 21, 'Noz', 0, 4, 1),
(123, 0, 21, 'Kij baseballowy', 0, 5, 1),
(124, 0, 21, 'Paralizator', 0, 23, 1),
(125, 0, 21, 'Tagger', 0, 41, 1),
(126, 0, 21, 'Kwiaty', 0, 14, 1),
(127, 0, 21, 'Koktajl molotova', 0, 18, 5),
(128, 0, 21, 'Pistolet', 0, 22, 50),
(129, 0, 21, 'Desert Eagle', 0, 24, 50),
(130, 0, 21, 'Glock 19', 0, 22, 50),
(131, 0, 21, 'Shotgun', 0, 25, 50),
(132, 0, 21, 'UZI', 0, 28, 50),
(133, 0, 21, 'MP5', 0, 29, 50),
(134, 0, 21, 'AK-47', 0, 30, 50),
(135, 0, 21, 'M4', 0, 31, 50),
(136, 0, 21, 'TEC9', 0, 32, 50),
(137, 0, 21, 'Karabin', 0, 33, 50),
(138, 0, 21, 'Snajperka', 0, 34, 50),
(139, 0, 21, 'Spadochron', 0, 46, 1),
(140, 0, 21, 'Mat Wybuchowe', 0, 39, 5),
(141, 0, 22, 'Ammo DE', 0, 24, 50),
(142, 0, 22, 'Ammo strzelby', 0, 25, 50),
(143, 0, 22, 'Ammo MP5', 0, 29, 50),
(144, 0, 22, 'Ammo AK47', 0, 30, 50),
(145, 0, 22, 'Ammo M4', 0, 31, 50),
(146, 0, 22, 'Ammo Tec9', 0, 32, 50),
(147, 0, 23, 'Batonik', 0, 0, 0),
(148, 0, 23, 'Bulka', 0, 0, 0),
(149, 0, 23, 'Pizza', 0, 0, 0),
(150, 0, 23, 'Cheeseburger', 0, 0, 0),
(151, 0, 23, 'Sajgonki', 0, 0, 0),
(152, 0, 23, 'Zapiekanka', 0, 0, 0),
(153, 0, 23, 'Frytki', 0, 0, 0),
(154, 0, 23, 'Grove Burger', 0, 0, 0),
(155, 0, 23, 'Hamburger', 0, 0, 0),
(156, 0, 23, 'Hotdog', 0, 0, 0),
(157, 0, 23, 'Kebab', 0, 0, 0),
(158, 0, 23, 'Lody', 0, 0, 0),
(159, 0, 23, 'Lody w kubku', 0, 0, 0),
(160, 0, 23, 'Lod czekoladowy', 0, 0, 0),
(161, 0, 23, 'Lod smietankowy', 0, 0, 0),
(162, 0, 23, 'Lod truskawkowy', 0, 0, 0),
(163, 0, 23, 'Kanapka z kurczakiem', 0, 0, 0),
(164, 0, 23, 'Longer', 0, 0, 0),
(165, 0, 23, 'Nachos z serem', 0, 0, 0),
(166, 0, 23, 'Nalesnik', 0, 0, 0),
(167, 0, 23, 'Nalesniki', 0, 0, 0),
(168, 0, 23, 'Paczek', 0, 0, 0),
(169, 0, 23, 'Paczek Afro', 0, 0, 0),
(170, 0, 23, 'Paczek Zlotawy', 0, 0, 0),
(171, 0, 23, 'Donut', 0, 0, 0),
(172, 0, 23, 'Sushi', 0, 0, 0),
(173, 0, 23, 'Lasagne', 0, 0, 0),
(174, 0, 23, 'Nuggetsy', 0, 0, 0),
(175, 0, 23, 'Spaghetti', 0, 0, 0),
(176, 0, 23, 'Taco', 0, 0, 0),
(177, 0, 0, 'Tortilla', 0, 0, 0),
(178, 0, 24, 'Discman', 0, 0, 0),
(179, 0, 25, 'Boombox', 0, 0, 0),
(180, 0, 26, 'Radio Party', 0, 0, 0),
(181, 0, 26, 'CD', 0, 0, 0),
(182, 0, 29, 'Lek', 0, 0, 0),
(183, 0, 29, 'Vitamina C', 0, 0, 0),
(184, 0, 30, 'Alarm', 0, 0, 0),
(185, 0, 30, 'Audio', 0, 0, 0),
(186, 0, 30, 'CB Radio', 0, 0, 0),
(187, 0, 30, 'Immobiliser', 0, 0, 0),
(188, 0, 30, 'Limiter', 0, 0, 0),
(190, 0, 31, 'Roof Scop', 1200, 0, 0),
(191, 0, 31, 'Vinyl Blade', 1400, 0, 0),
(192, 0, 31, 'Cover, Blade', 1400, 0, 0),
(193, 0, 31, 'S.top Savanna', 1400, 0, 0),
(194, 0, 31, 'XFlow Stratum', 1400, 0, 0),
(195, 0, 31, 'Alien Stratum', 1450, 0, 0),
(196, 0, 31, 'X-Flow Flash', 1500, 0, 0),
(197, 0, 31, 'H.top Savanna', 1500, 0, 0),
(198, 0, 31, 'X-Flow Uranus', 1500, 0, 0),
(199, 0, 31, 'Alien Flash', 1600, 0, 0),
(200, 0, 31, 'Alien Uranus', 1600, 0, 0),
(201, 0, 31, 'X-Flow Jester', 1700, 0, 0),
(202, 0, 31, 'X-Flow Sultan', 1700, 0, 0),
(203, 0, 31, 'Alien Sultan', 1800, 0, 0),
(204, 0, 31, 'Alien Jester', 1800, 0, 0),
(205, 0, 31, 'X-Flow Elegy', 1900, 0, 0),
(206, 0, 31, 'Pro', 2200, 0, 0),
(207, 0, 31, 'Alpha', 2250, 0, 0),
(208, 0, 31, 'Fury', 2440, 0, 0),
(209, 0, 31, 'Race', 2450, 0, 0),
(210, 0, 31, 'Win', 2500, 0, 0),
(211, 0, 31, 'X-Flow Flash', 2550, 0, 0),
(212, 0, 31, 'Drag', 2600, 0, 0),
(213, 0, 31, 'Alien Flash', 2600, 0, 0),
(214, 0, 31, 'Champ', 2640, 0, 0),
(215, 0, 31, 'Worx', 2645, 0, 0),
(216, 0, 31, 'Alien Stratum', 2700, 0, 0),
(217, 0, 31, 'X-Flow Jester', 2750, 0, 0),
(218, 0, 31, 'X-flow Elegy', 2790, 0, 0),
(219, 0, 31, 'X-Flow Stratum', 2800, 0, 0),
(220, 0, 31, 'Alien Elegy', 2810, 0, 0),
(221, 0, 31, 'Alien Jester', 2880, 0, 0),
(222, 0, 31, 'X-Flow Sultan', 2890, 0, 0),
(223, 0, 31, 'Alien Uranus', 2940, 0, 0),
(224, 0, 31, 'Alien Sultan', 2950, 0, 0),
(225, 0, 31, 'X-Flow Uranus', 2950, 0, 0),
(226, 0, 31, 'Offroad', 2200, 0, 0),
(227, 0, 31, 'Access', 2250, 0, 0),
(228, 0, 31, 'Rimshine', 2400, 0, 0),
(229, 0, 31, 'Atomic', 2400, 0, 0),
(230, 0, 31, 'Virtual', 2410, 0, 0),
(231, 0, 31, 'Import', 2500, 0, 0),
(232, 0, 31, 'Shadow', 2500, 0, 0),
(233, 0, 31, 'Ahab', 2560, 0, 0),
(234, 0, 31, 'Grove', 2700, 0, 0),
(235, 0, 31, 'Mega', 2750, 0, 0),
(236, 0, 31, 'Cutter', 2750, 0, 0),
(237, 0, 31, 'Classic', 2950, 0, 0),
(238, 0, 31, 'Wires', 3000, 0, 0),
(239, 0, 31, 'Switch', 3100, 0, 0),
(240, 0, 31, 'Twist', 3170, 0, 0),
(241, 0, 31, 'Trance', 3500, 0, 0),
(242, 0, 31, 'Dollar', 4200, 0, 0),
(243, 0, 31, 'XFlow Stratum', 4900, 0, 0),
(244, 0, 31, 'Alien Sultan', 5300, 0, 0),
(245, 0, 31, 'Tornado Stamin', 5550, 0, 0),
(246, 0, 31, 'Tornado Chrome', 5800, 0, 0),
(247, 0, 31, 'Broadway Stamin', 6700, 0, 0),
(248, 0, 31, 'Uranus XFlow', 6800, 0, 0),
(249, 0, 31, 'Blade Stamin', 6800, 0, 0),
(250, 0, 31, 'Blade Chrome', 6800, 0, 0),
(251, 0, 31, 'XFlow Flash', 6900, 0, 0),
(252, 0, 31, 'Uranus Alien', 7000, 0, 0),
(253, 0, 31, 'Remington Stami', 7200, 0, 0),
(254, 0, 31, 'Broadway Chrome', 7200, 0, 0),
(255, 0, 31, 'Alien Flash', 7300, 0, 0),
(256, 0, 31, 'Remington Chrom', 7400, 0, 0),
(257, 0, 31, 'XFlow Sultan', 7900, 0, 0),
(258, 0, 31, 'XFlow Elegy', 8200, 0, 0),
(259, 0, 31, 'Savanna Stamin', 8400, 0, 0),
(260, 0, 31, 'Alien Sultan', 8500, 0, 0),
(261, 0, 31, 'XFlow Jester', 8500, 0, 0),
(262, 0, 31, 'Alien Jester', 8900, 0, 0),
(263, 0, 31, 'Savanna Chrome', 8900, 0, 0),
(264, 0, 31, 'Alien Elegy', 9000, 0, 0),
(265, 0, 31, 'Hydraulika', 0, 0, 0),
(266, 0, 32, 'Kogut', 0, 0, 0),
(267, 0, 34, 'Zderzak przedni', 0, 0, 0),
(268, 0, 35, 'Zderzak tylny', 0, 0, 0),
(269, 0, 36, 'Drzwi kierowcy', 0, 0, 0),
(270, 0, 37, 'Drzwi pasazera', 0, 0, 0),
(271, 0, 38, 'Bagaznik', 0, 0, 0),
(272, 0, 39, 'Maska samochodowa', 0, 1, 0),
(273, 0, 40, 'Opona (LP)', 0, 0, 0),
(274, 0, 41, 'Opona (PP)', 0, 0, 0),
(275, 0, 42, 'Opona (PT)', 0, 0, 0),
(276, 0, 43, 'Opona (LT)', 0, 0, 0),
(277, 0, 44, 'Swiatlo (LP)', 0, 0, 0),
(278, 0, 45, 'Swiatlo (PP)', 0, 0, 0),
(279, 0, 46, 'Kanister', 0, 0, 0),
(280, 0, 47, 'Karnet silowy', 0, 0, 0),
(281, 0, 48, 'Linka holownicza', 0, 0, 0),
(282, 0, 21, 'Canon 450D', 0, 43, 1),
(283, 0, 49, 'Casio', 0, 0, 0),
(284, 0, 22, 'Karta pamieci', 0, 0, 0),
(285, 0, 0, 'Latarka', 0, 0, 0),
(286, 0, 51, 'Loteria', 0, 0, 0),
(287, 0, 0, 'Mebel', 0, 0, 0),
(288, 0, 0, 'Naboj lakieru', 0, 0, 0),
(289, 0, 0, 'Napis 3D', 0, 0, 0),
(290, 0, 50, 'Wytrych', 0, 0, 0),
(291, 0, 52, 'Landstalker', 0, 400, 0),
(292, 0, 52, 'Buffalo', 0, 402, 0),
(293, 0, 52, 'Perenniel', 0, 404, 0),
(294, 0, 52, 'Sentinel', 0, 405, 0),
(295, 0, 52, 'Stretch', 0, 409, 0),
(296, 0, 52, 'Manana', 0, 410, 0),
(297, 0, 52, 'Infernus', 0, 411, 0),
(298, 0, 52, 'Voodoo', 0, 412, 0),
(299, 0, 52, 'Pony', 0, 413, 0),
(300, 0, 52, 'Mule', 0, 414, 0),
(301, 0, 52, 'Cheetah', 0, 415, 0),
(302, 0, 52, 'Ambulance', 0, 416, 0),
(303, 0, 52, 'Moonbeam', 0, 418, 0),
(304, 0, 52, 'Esperanto', 0, 419, 0),
(305, 0, 52, 'Taxi', 0, 420, 0),
(306, 0, 52, 'Washington', 0, 421, 0),
(307, 0, 52, 'Bobcat', 0, 422, 0),
(308, 0, 52, 'BF Injection', 0, 424, 0),
(309, 0, 52, 'Premier', 0, 426, 0),
(310, 0, 52, 'Securicar', 0, 428, 0),
(311, 0, 52, 'Banshee', 0, 429, 0),
(312, 0, 52, 'Previon', 0, 436, 0),
(313, 0, 52, 'Coach', 0, 437, 0),
(314, 0, 52, 'Cabbie', 0, 438, 0),
(315, 0, 52, 'Stallion', 0, 439, 0),
(316, 0, 52, 'Admiral', 0, 445, 0),
(317, 0, 52, 'Squalo', 0, 446, 0),
(318, 0, 52, 'Turismo', 0, 451, 0),
(319, 0, 52, 'Speeder', 0, 452, 0),
(320, 0, 52, 'Reefer', 0, 453, 0),
(321, 0, 52, 'Tropic', 0, 454, 0),
(322, 0, 52, 'Yankee', 0, 456, 0),
(323, 0, 52, 'Solair', 0, 458, 0),
(324, 0, 52, 'PCJ-600', 0, 461, 0),
(325, 0, 52, 'Faggio', 0, 462, 0),
(326, 0, 52, 'Freeway', 0, 463, 0),
(327, 0, 52, 'Glendale', 0, 466, 0),
(328, 0, 52, 'Sanchez', 0, 468, 0),
(329, 0, 52, 'Patriot', 0, 470, 0),
(330, 0, 52, 'Quad', 0, 471, 0),
(331, 0, 52, 'Coastguard', 0, 472, 0),
(332, 0, 52, 'Hermes', 0, 474, 0),
(333, 0, 52, 'Sabre', 0, 475, 0),
(334, 0, 52, 'ZR-350', 0, 477, 0),
(335, 0, 52, 'Walton', 0, 478, 0),
(336, 0, 52, 'Comet', 0, 480, 0),
(337, 0, 52, 'BMX', 0, 481, 0),
(338, 0, 52, 'Burrito', 0, 482, 0),
(339, 0, 52, 'Camper', 0, 483, 0),
(340, 0, 52, 'Marquis', 0, 484, 0),
(341, 0, 52, 'Maverick', 0, 487, 0),
(342, 0, 52, 'Virgo', 0, 491, 0),
(343, 0, 52, 'Jetmax', 0, 493, 0),
(344, 0, 52, 'Sandking', 0, 495, 0),
(345, 0, 52, 'Blista', 0, 496, 0),
(346, 0, 52, 'Boxville', 0, 498, 0),
(347, 0, 52, 'Mesa', 0, 500, 0),
(348, 0, 52, 'Rancher', 0, 505, 0),
(349, 0, 52, 'Elegant', 0, 507, 0),
(350, 0, 52, 'Journey', 0, 508, 0),
(351, 0, 52, 'Bike', 0, 509, 0),
(352, 0, 52, 'MTB', 0, 510, 0),
(353, 0, 52, 'Nebula', 0, 516, 0),
(354, 0, 52, 'Majestic', 0, 517, 0),
(355, 0, 52, 'FCR-900', 0, 521, 0),
(356, 0, 52, 'NRG-500', 0, 522, 0),
(357, 0, 52, 'Tow Truck', 0, 525, 0),
(358, 0, 52, 'Willard', 0, 529, 0),
(359, 0, 52, 'Feltzer', 0, 533, 0),
(360, 0, 52, 'Remington', 0, 534, 0),
(361, 0, 52, 'Slamvan', 0, 535, 0),
(362, 0, 52, 'Vincent', 0, 540, 0),
(363, 0, 52, 'Hustler', 0, 545, 0),
(364, 0, 52, 'Intruder', 0, 546, 0),
(365, 0, 52, 'Primo', 0, 547, 0),
(366, 0, 52, 'Tampa', 0, 549, 0),
(367, 0, 52, 'Sunrise', 0, 550, 0),
(368, 0, 52, 'Merit', 0, 551, 0),
(369, 0, 52, 'Yosemite', 0, 554, 0),
(370, 0, 52, 'Windsor', 0, 555, 0),
(371, 0, 52, 'Uranus', 0, 558, 0),
(372, 0, 52, 'Jester', 0, 559, 0),
(373, 0, 52, 'Sultan', 0, 560, 0),
(374, 0, 52, 'Stratum', 0, 561, 0),
(375, 0, 52, 'Elegy', 0, 562, 0),
(376, 0, 52, 'Flash', 0, 565, 0),
(377, 0, 52, 'Tahoma', 0, 566, 0),
(378, 0, 52, 'Mower', 0, 572, 0),
(379, 0, 52, 'Broadway', 0, 575, 0),
(380, 0, 52, 'Tornado', 0, 576, 0),
(381, 0, 52, 'DFT-30', 0, 578, 0),
(382, 0, 52, 'Huntley', 0, 579, 0),
(383, 0, 52, 'Stafford', 0, 580, 0),
(384, 0, 52, 'BF-400', 0, 581, 0),
(385, 0, 52, 'Emperor', 0, 585, 0),
(386, 0, 52, 'Wayfarer', 0, 586, 0),
(387, 0, 52, 'Euros', 0, 587, 0),
(388, 0, 52, 'Hot-dog', 0, 588, 0),
(389, 0, 52, 'Club', 0, 589, 0),
(390, 0, 52, 'Dodo', 0, 593, 0),
(391, 0, 52, 'Alpha', 0, 602, 0),
(392, 0, 52, 'Phoenix', 0, 603, 0),
(393, 0, 33, 'Cialo', 0, 0, 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
