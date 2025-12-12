-- phpMyAdmin SQL Dump
-- version 5.2.1deb1+deb12u1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Lis 29, 2025 at 08:28 PM
-- Wersja serwera: 10.11.14-MariaDB-0+deb12u2
-- Wersja PHP: 8.2.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `srv81866`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_3DTexts`
--

CREATE TABLE `osrp_3DTexts` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `OType` int(3) NOT NULL DEFAULT 0,
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

INSERT INTO `osrp_3DTexts` (`UID`, `OUID`, `OType`, `Desc`, `Color`, `PosX`, `PosY`, `PosZ`, `Distance`, `VW`, `INT`) VALUES
(1, 0, 0, 'Zakaz postoju', 'FF0000FF', 1537.82, -1668.79, 14.1014, 30, 0, 0),
(2, 0, 0, 'Zakaz parkowania!', 'FF0000FF', 1525.52, -1447.82, 14.11, 30, 0, 0),
(3, 0, 0, 'Bankomat\n{FFFFFF}(( Wpisz /bank stoj?c bardzo blisko,\nby u?y?', '0', 0, 0, 30, 0, 0, 0),
(4, 1, 16, 'Jakiœ napis', 'FFFFFFFF', 889.797, -1338.15, 19.4569, 30, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Achievements`
--

CREATE TABLE `osrp_Achievements` (
  `UID` int(3) NOT NULL,
  `ID` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Desc` varchar(128) NOT NULL DEFAULT '\\0',
  `Reward` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_Achievements`
--

INSERT INTO `osrp_Achievements` (`UID`, `ID`, `Name`, `Desc`, `Reward`) VALUES
(1, 1, 'Małżeństwo', 'Stań przy ślubnym kobiercu ze swoją drugą połówką', 500),
(2, 2, 'Kolekcjoner', 'Zostań właścicielem 12-stu pojazdów', 2000),
(3, 3, 'Własne cztery kółka', 'Stań się właścicielem pierwszego pojazdu', 350),
(4, 4, 'Uczciwie zarobione pieniądze', 'Zarób swoje pierwsze dolary uzyskując premię z oferty', 100),
(5, 5, 'Przywódca', 'Zostań wybrany liderem frakcji', 2500),
(6, 6, 'Lokalny dyktator', 'Stwórz własną organizację', 1800),
(7, 7, 'Biznesmen', 'Załóż własny biznes', 1500),
(8, 8, 'Duża firma', 'Prowadź przedsiębiorstwo liczące 70 pracowników', 2300),
(9, 9, 'Średnia firma', 'Zatrudnij 35-ciu pracowników', 1750),
(10, 10, 'Mała firma', 'Daj pracę pierwszym 15-stu osobom', 1550);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Animations`
--

CREATE TABLE `osrp_Animations` (
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
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Type` int(3) NOT NULL DEFAULT 0,
  `OType` int(3) NOT NULL DEFAULT 0,
  `Color` varchar(10) NOT NULL DEFAULT '',
  `MinX` float NOT NULL DEFAULT 0,
  `MinY` float NOT NULL DEFAULT 0,
  `MinZ` float NOT NULL DEFAULT 0,
  `MaxX` float NOT NULL DEFAULT 0,
  `MaxY` float NOT NULL DEFAULT 0,
  `MaxZ` float NOT NULL DEFAULT 0,
  `MaxSpeed` int(3) NOT NULL DEFAULT 0,
  `Dimension` int(9) NOT NULL DEFAULT 0,
  `Cost` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Areas`
--

INSERT INTO `osrp_Areas` (`UID`, `OUID`, `Type`, `OType`, `Color`, `MinX`, `MinY`, `MinZ`, `MaxX`, `MaxY`, `MaxZ`, `MaxSpeed`, `Dimension`, `Cost`) VALUES
(1, 1, 0, 0, '', 802.279, -1310.05, 0, 911.834, -1337.22, 0, 80, 10, 10),
(2, 1, 0, 0, '', 952.256, -1310.73, 1, 788.555, -1162.5, 0, 999, 10, 75);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Booths`
--

CREATE TABLE `osrp_Booths` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\n',
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Range` float NOT NULL DEFAULT 0,
  `Working` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Booths`
--

INSERT INTO `osrp_Booths` (`UID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Range`, `Working`) VALUES
(1, 'Market', 823.333, -1333.1, 13.2193, 0, 0, 0, 2, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_BusStops`
--

CREATE TABLE `osrp_BusStops` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
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

INSERT INTO `osrp_BusStops` (`UID`, `OUID`, `Name`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`) VALUES
(1, 0, 'LS LOve', 1150.8, -1408.73, 13.5236, 0, 0, 0),
(2, 0, 'Market', 819.095, -1335.89, 13.5096, 0, 0, -90),
(3, 0, 'LSPD', 1522.38, -1690.79, 13.5806, 0, 0, 180),
(4, 0, 'Glen Park', 2021.58, -1253.79, 23.9838, 0, 0, 90),
(5, 0, 'Idlewood', 2096.57, -1765.92, 13.6383, 0, 0, 345.744),
(6, 0, 'Ganton', 2193.65, -1751.04, 13.592, 0, 0, 0),
(7, 0, 'a', 2386.6, -1978.54, 13.5872, 0, 0, -90),
(8, 0, 'b', 2263.92, -1334.06, 23.9175, 0, 0, 180),
(9, 0, 'c', 955.214, -957.125, 39.9099, -3, 0, 100.231),
(10, 0, 'd', 1149.96, -1412.8, 13.7671, 0, 0, -90),
(11, 0, 'e', 2232.4, -1145.27, 25.7338, 0, 0, 255.112),
(12, 0, 'f', 1286.76, -1387.89, 13.5146, 0, 0, 90),
(13, 0, 'g', 681.996, -1413.42, 13.5785, 0, 0, -90);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_CashPoints`
--

CREATE TABLE `osrp_CashPoints` (
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
-- Dumping data for table `osrp_CashPoints`
--

INSERT INTO `osrp_CashPoints` (`UID`, `Name`, `IsOpen`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Distance`, `VW`, `INT`) VALUES
(1, 'Market', 1, 837.508, -1338.88, 6.8208, 0, 0, 0, 2, 0, 0),
(2, 'Hotel 52', 1, 897.71, -1338.53, 19.121, 0, 0, -90, 2, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Contacts`
--

CREATE TABLE `osrp_Contacts` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(24) NOT NULL DEFAULT '\\0',
  `Number` int(7) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Contacts`
--

INSERT INTO `osrp_Contacts` (`UID`, `OUID`, `Name`, `Number`) VALUES
(1, 5, 'danny', 9710073),
(2, 1, 'Ziomek', 8512455);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Doors`
--

CREATE TABLE `osrp_Doors` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `OType` int(3) NOT NULL DEFAULT 0,
  `Type` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `EnterX` float NOT NULL DEFAULT 0,
  `EnterY` float NOT NULL DEFAULT 0,
  `EnterZ` float NOT NULL DEFAULT 0,
  `EnterA` float NOT NULL DEFAULT 0,
  `ExitX` float NOT NULL DEFAULT 0,
  `ExitY` float NOT NULL DEFAULT 0,
  `ExitZ` float NOT NULL DEFAULT 0,
  `ExitA` float NOT NULL DEFAULT 0,
  `MinX` float NOT NULL DEFAULT 0,
  `MinY` float NOT NULL DEFAULT 0,
  `MaxX` float NOT NULL DEFAULT 0,
  `MaxY` float NOT NULL DEFAULT 0,
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
  `Audio` int(1) NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Doors`
--

INSERT INTO `osrp_Doors` (`UID`, `OUID`, `OType`, `Type`, `Name`, `EnterX`, `EnterY`, `EnterZ`, `EnterA`, `ExitX`, `ExitY`, `ExitZ`, `ExitA`, `MinX`, `MinY`, `MaxX`, `MaxY`, `Cost`, `Passing`, `Open`, `Tax`, `TaxDate`, `TaxCost`, `Objects`, `MaxObjects`, `Texts`, `MaxTexts`, `Security`, `Audio`, `VW`, `INT`) VALUES
(1, 1, 9, 2, 'steez', 893.161, -1336.08, 13.5469, 0, 897.469, -1339.92, 19.4569, 0, 898.4, -1342.4, 854.8, -1322.1, 2, 1, 1, 1765049738, '2025/11/05', 10, 9, 1, 1, 1, 1, 0, 100, 0),
(2, 100, 16, 4, 'Victim', 887.345, -1336.08, 13.5469, 178.288, 227.527, -8.1367, 1002.21, 83.8058, 900, 900, 900, 900, 0, 0, 1, 1766254780, '2025/11/19', 0, 0, 0, 0, 0, 0, 0, 101, 5),
(3, 1, 9, 1, 'Sklep', 881.565, -1336.08, 13.5469, 176.698, 881.786, -1337.48, 17.5418, 178.288, 22, 222, 222, 222, 0, 0, 1, 1766254780, 'Brak', 12, 0, 0, 0, 0, 1, 0, 102, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupOrders`
--

CREATE TABLE `osrp_GroupOrders` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL,
  `DName` varchar(32) NOT NULL DEFAULT '\\0',
  `IName` varchar(32) NOT NULL DEFAULT '\\0',
  `Owner` varchar(24) NOT NULL DEFAULT '\\0',
  `Kind` int(3) NOT NULL,
  `Value1` int(5) NOT NULL DEFAULT 0,
  `Value2` int(5) NOT NULL DEFAULT 0,
  `Price` int(3) NOT NULL DEFAULT 0,
  `Amount` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_GroupOrders`
--

INSERT INTO `osrp_GroupOrders` (`UID`, `OUID`, `DName`, `IName`, `Owner`, `Kind`, `Value1`, `Value2`, `Price`, `Amount`) VALUES
(1, 1, 'Hotel 52', 'MP5', 'Danny Walker', 3, 29, 100, 1, 22);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupPerms`
--

CREATE TABLE `osrp_GroupPerms` (
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
-- Dumping data for table `osrp_GroupPerms`
--

INSERT INTO `osrp_GroupPerms` (`UID`, `OUID`, `PermOOC`, `PermIC`, `PermMegaphone`, `PermName`, `PermTag`, `PermDept`, `PermGPS`, `PermRope`, `PermWithdraw`, `PermNews`, `PermBlockCar`, `PermGangZone`, `PermBuyList`, `PermDetention`, `PermRobbery`) VALUES
(1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Groups`
--

CREATE TABLE `osrp_Groups` (
  `UID` int(3) NOT NULL,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Date` varchar(16) NOT NULL DEFAULT '\\0',
  `Type` int(2) NOT NULL DEFAULT 0,
  `Members` int(3) NOT NULL DEFAULT 0,
  `VehLimit` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `Color` varchar(8) NOT NULL DEFAULT '\\0',
  `Registered` int(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Groups`
--

INSERT INTO `osrp_Groups` (`UID`, `Name`, `Date`, `Type`, `Members`, `VehLimit`, `Money`, `Color`, `Registered`) VALUES
(1, 'LSPD', '13.03.2025', 1, 7, 100, 122991, '0000FF', 1),
(2, 'Taxi', '11111', 14, 1, 10, 1111, 'FFFF00AA', 1),
(3, 'LosSantosTaxises', '2025/11/026', 10, 0, 5, 1000, 'FFFF00', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupSets`
--

CREATE TABLE `osrp_GroupSets` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(3) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '\\0',
  `Value1` int(5) NOT NULL DEFAULT 0,
  `Value2` int(5) NOT NULL DEFAULT 0,
  `Price` int(5) NOT NULL DEFAULT 0,
  `Amount` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_GroupTasks`
--

CREATE TABLE `osrp_GroupTasks` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(128) NOT NULL DEFAULT '\\0',
  `Date` varchar(64) NOT NULL DEFAULT '\\0',
  `Caller` varchar(24) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_GroupTasks`
--

INSERT INTO `osrp_GroupTasks` (`UID`, `OUID`, `Desc`, `Date`, `Caller`) VALUES
(9, 1, 'sraka', '17:07 18/11/2025', 'Danny Walker'),
(10, 1, 'sasas', '17:16 18/11/2025', 'Danny Walker'),
(11, 1, 'sraka', '23:10 22/11/2025', 'Danny Walker'),
(12, 1, 'aaaaaaaa', '16:08 24/11/2025', 'Danny Walker'),
(13, 1, 'Sraka', '11:38 26/11/2025', 'Danny Walker'),
(14, 1, 'aaaaaaaa', '12:10 26/11/2025', 'Danny Walker'),
(15, 3, 'aaaaaaaaa', '12:11 26/11/2025', 'Danny Walker');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Notes`
--

CREATE TABLE `osrp_Notes` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Objects`
--

CREATE TABLE `osrp_Objects` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `OType` int(1) NOT NULL DEFAULT 0,
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
-- Dumping data for table `osrp_Objects`
--

INSERT INTO `osrp_Objects` (`UID`, `OUID`, `OType`, `Gate`, `ModelId`, `Spared`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `GateX`, `GateY`, `GateZ`, `Texture`, `MatIndex`, `MatType`, `MatColor`, `MatModel`, `MatTxdName`, `MatTexName`, `MatSize`, `MatFontSize`, `MatBold`, `MatFColor`, `MatBColor`, `MatAlign`, `MatFont`, `MatText`, `Distance`, `VW`, `INT`) VALUES
(722, 1, 1, 0, 995, 0, 830.815, -1340.01, 9.9755, 0, 0, 90, 0, 0, 0, 0, 0, -1, 0, 0, '', '0', 0, 0, 0, 0, 0, 0, '', '50', 0, 0, 0),
(723, 1, 1, 0, 995, 0, 828.844, -1343.26, 10.4165, 0, 0, 90, 0, 0, 0, 0, 0, -1, 0, 0, '', '0', 0, 0, 0, 0, 0, 0, '', '0', 0, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Penalties`
--

CREATE TABLE `osrp_Penalties` (
  `UID` int(3) NOT NULL,
  `SUID` int(3) NOT NULL DEFAULT 0,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `IP` varchar(16) NOT NULL DEFAULT '\\0',
  `Type` int(3) NOT NULL DEFAULT 0,
  `Days` int(3) NOT NULL DEFAULT 0,
  `Time` varchar(32) NOT NULL DEFAULT '\\0',
  `Date` varchar(32) NOT NULL DEFAULT '\\0',
  `Reason` varchar(128) NOT NULL DEFAULT '\\0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_Penalties`
--

INSERT INTO `osrp_Penalties` (`UID`, `SUID`, `OUID`, `IP`, `Type`, `Days`, `Time`, `Date`, `Reason`) VALUES
(1, 0, 1, '127.0.0.1', 4, 24, '23:05:006', '22.11.2025', 'SpeedHack V 0.804946 -0.024136 0.000902'),
(4, 0, 1, '127.0.0.1', 2, 0, '12:10:056', '26.11.2025', '4 commands in 3. seconds.');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Players`
--

CREATE TABLE `osrp_Players` (
  `UID` int(3) NOT NULL,
  `GUID` int(3) NOT NULL DEFAULT 0,
  `CharNum` int(1) NOT NULL DEFAULT 0,
  `AccName` varchar(24) NOT NULL DEFAULT '\0',
  `CharName` varchar(24) NOT NULL DEFAULT '\0',
  `Pass` varchar(65) NOT NULL DEFAULT '',
  `Salt` varchar(17) NOT NULL DEFAULT '',
  `IP` varchar(16) NOT NULL DEFAULT '\0',
  `DateReg` varchar(64) NOT NULL DEFAULT '-',
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
  `Achi0` int(1) NOT NULL DEFAULT 0,
  `Achi1` int(1) NOT NULL DEFAULT 0,
  `Achi2` int(1) NOT NULL DEFAULT 0,
  `Achi3` int(1) NOT NULL DEFAULT 0,
  `Achi4` int(1) NOT NULL DEFAULT 0,
  `Achi5` int(1) NOT NULL DEFAULT 0,
  `Achi6` int(1) NOT NULL DEFAULT 0,
  `Achi7` int(1) NOT NULL DEFAULT 0,
  `Achi8` int(1) NOT NULL DEFAULT 0,
  `Achi9` int(1) NOT NULL DEFAULT 0,
  `Achi10` int(1) NOT NULL DEFAULT 0,
  `Achi11` int(1) NOT NULL DEFAULT 0,
  `Achi12` int(1) NOT NULL DEFAULT 0,
  `Achi13` int(1) NOT NULL DEFAULT 0,
  `Achi14` int(1) NOT NULL DEFAULT 0,
  `Achi15` int(1) NOT NULL DEFAULT 0,
  `Achi16` int(1) NOT NULL DEFAULT 0,
  `Achi17` int(1) NOT NULL DEFAULT 0,
  `Achi18` int(1) NOT NULL DEFAULT 0,
  `Achi19` int(1) NOT NULL DEFAULT 0,
  `Achi20` int(1) NOT NULL DEFAULT 0,
  `Achi21` int(1) NOT NULL DEFAULT 0,
  `BW` int(5) NOT NULL DEFAULT 0,
  `AJ` int(5) NOT NULL DEFAULT 0,
  `Hotel` int(2) NOT NULL DEFAULT 0,
  `HotelPaid` int(4) NOT NULL DEFAULT 0,
  `GOV` int(1) NOT NULL DEFAULT 0,
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
  `ChatStyle` int(1) NOT NULL DEFAULT 0,
  `Computer` int(1) NOT NULL DEFAULT 0,
  `WalkAnim` int(1) NOT NULL DEFAULT 0,
  `StyleFight` int(1) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Desc` varchar(64) NOT NULL DEFAULT ' '
) ENGINE=MyISAM DEFAULT CHARSET=latin2 COLLATE=latin2_general_ci;

--
-- Dumping data for table `osrp_Players`
--

INSERT INTO `osrp_Players` (`UID`, `GUID`, `CharNum`, `AccName`, `CharName`, `Pass`, `Salt`, `IP`, `DateReg`, `LastDate`, `GS`, `Rank`, `Sex`, `Strength`, `Hours`, `Minutes`, `Seconds`, `HP`, `AP`, `VW`, `INT`, `Skin`, `LastSkin`, `Money`, `Bank`, `Debt`, `PistSkill`, `SemiSkill`, `AutomSkill`, `ShotgSkill`, `RifleSkill`, `Achi0`, `Achi1`, `Achi2`, `Achi3`, `Achi4`, `Achi5`, `Achi6`, `Achi7`, `Achi8`, `Achi9`, `Achi10`, `Achi11`, `Achi12`, `Achi13`, `Achi14`, `Achi15`, `Achi16`, `Achi17`, `Achi18`, `Achi19`, `Achi20`, `Achi21`, `BW`, `AJ`, `Hotel`, `HotelPaid`, `GOV`, `DriverLicense`, `Detention`, `PDP`, `TelNum`, `TelNetwork`, `BankAcc`, `GroupDesc`, `Group0`, `Group1`, `Group2`, `Group3`, `Group4`, `Perm0`, `Perm1`, `Perm2`, `Perm3`, `Perm4`, `PayDay0`, `PayDay1`, `PayDay2`, `PayDay3`, `PayDay4`, `Duty0`, `Duty1`, `Duty2`, `Duty3`, `Duty4`, `CasualJob`, `Traveled`, `Addiction`, `Door`, `ChatStyle`, `Computer`, `WalkAnim`, `StyleFight`, `PosX`, `PosY`, `PosZ`, `Desc`) VALUES
(1, 1, 1, 'steeZ', 'Danny Walker', '772BB3EE96CC14BF0FD34E33303379E414E718A45FA87D22267C10B5734566BA', '1f:}ANwL;9KuGD8o', '127.0.0.1', '13/08/2025 22:31:32', '26/11/2025 12:12:11', 112, 11, 0, 3035, 6, 35, 34, 100, 0, 0, 0, 275, 48, 628, 0, 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 9710073, 0, 53, 'LSPD, ', 1, 3, 0, 0, 0, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 222843, 0, 2, 1, 1, -1, 0, 859.963, -1321.97, 13.5522, 'Test Danki'),
(2, 1, 2, 'steeZ', 'August Anasetti', '70EE61AEE2F2653EFDE224AF6138D083CA15611E0D12C0A06B0D5A1BF8C144FC', 'l`uz?<yCDfbOaaK8', '127.0.0.1', '17/08/2025 16:27:43', '06/09/2025 22:35:38', 0, 0, 0, 3000, 0, 0, 57, 100, 0, 0, 0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8420659, 0, 38276981, '-', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1934.72, -1777.96, 13.3828, ' '),
(3, 1, 3, 'Deadly_Pedobear', 'Abdiel Abate', '6F80C507784894531530A080A4B3AFAFF130D3CC21CDC4A4263BD894E8734FB4', ']BvBmXJ<L0_ouZLA', '89.133.92.23', '05/11/2025 18:25:05', '05/11/2025 19:00:04', 0, 11, 0, 3000, 0, 23, 38, 9, 0, 0, 0, 291, 291, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, -1, 1, 898.681, -1322.1, 13.5453, ' '),
(6, 5, 1, 'MisterMagik', 'Thomas Paker', '381E72FBDA719A6025F51DAC7E4FCBC1D7F229FEA61214C7D5F921F29AB9C75B', '_<UDq6GJax4US=^V', '83.27.186.181', '17/11/2025 22:14:16', '17/11/2025 23:19:29', 0, 11, 0, 3000, 0, 34, 31, 100, 0, 0, 0, 275, 291, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4579554, 0, 67393836, '-LSPD, ', 1, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 614.091, 0, 2, 1, 0, -1, 1, 53.8577, -216.647, 1.59784, ' ');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Races`
--

CREATE TABLE `osrp_Races` (
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
(6, 6);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Things`
--

CREATE TABLE `osrp_Things` (
  `UID` int(3) NOT NULL DEFAULT 0,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `Kind` int(2) NOT NULL DEFAULT 0,
  `Name` varchar(32) NOT NULL DEFAULT '',
  `Value1` int(9) NOT NULL DEFAULT 0,
  `Value2` int(9) NOT NULL DEFAULT 0,
  `Value3` int(9) NOT NULL DEFAULT 0,
  `Value4` int(9) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Used` int(1) NOT NULL DEFAULT 0,
  `Term` int(9) NOT NULL DEFAULT 0,
  `Place` int(1) NOT NULL DEFAULT 0,
  `VW` int(3) NOT NULL DEFAULT 0,
  `INT` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `osrp_Things`
--

INSERT INTO `osrp_Things` (`UID`, `OUID`, `Kind`, `Name`, `Value1`, `Value2`, `Value3`, `Value4`, `PosX`, `PosY`, `PosZ`, `Used`, `Term`, `Place`, `VW`, `INT`) VALUES
(1, 1, 45, 'Rolki', 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(3, 6, 2, 'Casio', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(4, 65535, 0, 'Test', 0, 0, 0, 0, 1318930000, -834215000, 1318930000, 0, 0, 2, 0, 0),
(5, 2, 25, 'Ubranie', 25, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(6, 1, 3, 'Opr', 41, 10099, 0, 0, 0, 0, 0, 0, 1768570923, 1, 0, 0),
(7, 6, 3, 'MP5', 29, 0, 0, 0, 0, 0, 0, 0, 1768573531, 1, 0, 0),
(8, 3, 45, 'Rolki', 20, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(9, 3, 5, 'Food', 100, 0, 0, 0, 0, 0, 0, 0, 1762716437, 1, 0, 0),
(10, 3, 3, 'Deagle', 24, 100, 0, 0, 0, 0, 0, 0, 1770233402, 1, 0, 0),
(11, 1, 3, 'Deagle', 24, 88, 0, 0, 0, 0, 0, 0, 1770233405, 1, 0, 0),
(12, 4, 45, 'Rolki', 20, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(13, 4, 45, 'Rolki', 20, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(14, 5, 45, 'Rolki', 20, 5, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(15, 6, 45, 'Rolki', 20, 6, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0),
(16, 6, 3, 'Deagle', 24, 0, 0, 0, 0, 0, 0, 0, 1771283166, 1, 0, 0),
(17, 1, 3, 'Deagle', 24, 0, 0, 0, 0, 0, 0, 0, 1771283171, 1, 0, 0),
(18, 1, 3, 'Baseball', 5, 1, 0, 0, 0, 0, 0, 0, 1771283236, 1, 0, 0),
(21, 7, 45, 'Rolki', 20, 7, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(23, 1, 25, 'Ubranie (161)', 161, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(24, 1, 25, 'Ubranie (48)', 48, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(2617708, 7, 40, 'Nokia', 10, 10, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0),
(4579554, 6, 40, 'Telefonik', 100, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0),
(8512455, 5, 40, 'Nokia', 10, -2, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0),
(9710073, 1, 40, 'Telefon', 0, 6, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_Vehicles`
--

CREATE TABLE `osrp_Vehicles` (
  `UID` int(3) NOT NULL,
  `OUID` int(3) NOT NULL DEFAULT 0,
  `OType` int(1) NOT NULL DEFAULT 0,
  `HostUID` int(3) NOT NULL DEFAULT 0,
  `SubOUID` int(3) NOT NULL DEFAULT 0,
  `ModelID` int(3) NOT NULL DEFAULT 0,
  `Color1` int(3) NOT NULL DEFAULT 0,
  `Color2` int(3) NOT NULL DEFAULT 0,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Angle` float NOT NULL DEFAULT 0,
  `Fuel` float NOT NULL DEFAULT 0,
  `Lock` int(1) NOT NULL DEFAULT 1,
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
  `Launched` int(1) NOT NULL DEFAULT 0,
  `Armor` int(1) NOT NULL DEFAULT 0,
  `Mileage` float NOT NULL DEFAULT 0,
  `Block` int(1) NOT NULL DEFAULT 0,
  `Premium` int(1) NOT NULL DEFAULT 0,
  `Plate` varchar(32) NOT NULL DEFAULT ' ',
  `Desc` varchar(64) NOT NULL DEFAULT ' '
) ENGINE=InnoDB DEFAULT CHARSET=latin2 COLLATE=latin2_bin;

--
-- Dumping data for table `osrp_Vehicles`
--

INSERT INTO `osrp_Vehicles` (`UID`, `OUID`, `OType`, `HostUID`, `SubOUID`, `ModelID`, `Color1`, `Color2`, `PosX`, `PosY`, `PosZ`, `Angle`, `Fuel`, `Lock`, `Engine`, `EngineHealth`, `Spawned`, `LightsOn`, `Window`, `Alarm`, `Immo`, `CBRadio`, `Audio`, `Limiter`, `Panels`, `Doors`, `Lights`, `Tires`, `VW`, `INT`, `Paintjob`, `Nitro`, `Repair`, `Launched`, `Armor`, `Mileage`, `Block`, `Premium`, `Plate`, `Desc`) VALUES
(4, 1, 9, 0, 0, 400, 1, 1, 844.276, -1325.94, 13.6346, 100.322, 31.1771, 0, 0, 1000, 1, 1, 0, 0, 0, 0, 0, 0, 36896819, 33686020, 5, 0, 0, 0, -1, 0, 0, 0, 0, 113.512, 0, 0, '', 'asasas');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `osrp_WholeSales`
--

CREATE TABLE `osrp_WholeSales` (
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
-- Indeksy dla tabeli `osrp_3DTexts`
--
ALTER TABLE `osrp_3DTexts`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Achievements`
--
ALTER TABLE `osrp_Achievements`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Animations`
--
ALTER TABLE `osrp_Animations`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Areas`
--
ALTER TABLE `osrp_Areas`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Booths`
--
ALTER TABLE `osrp_Booths`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_BusStops`
--
ALTER TABLE `osrp_BusStops`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_CashPoints`
--
ALTER TABLE `osrp_CashPoints`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Contacts`
--
ALTER TABLE `osrp_Contacts`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Doors`
--
ALTER TABLE `osrp_Doors`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_GroupOrders`
--
ALTER TABLE `osrp_GroupOrders`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_GroupPerms`
--
ALTER TABLE `osrp_GroupPerms`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Groups`
--
ALTER TABLE `osrp_Groups`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_GroupSets`
--
ALTER TABLE `osrp_GroupSets`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_GroupTasks`
--
ALTER TABLE `osrp_GroupTasks`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Objects`
--
ALTER TABLE `osrp_Objects`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Penalties`
--
ALTER TABLE `osrp_Penalties`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Players`
--
ALTER TABLE `osrp_Players`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Things`
--
ALTER TABLE `osrp_Things`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_Vehicles`
--
ALTER TABLE `osrp_Vehicles`
  ADD PRIMARY KEY (`UID`);

--
-- Indeksy dla tabeli `osrp_WholeSales`
--
ALTER TABLE `osrp_WholeSales`
  ADD PRIMARY KEY (`UID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `osrp_3DTexts`
--
ALTER TABLE `osrp_3DTexts`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `osrp_Achievements`
--
ALTER TABLE `osrp_Achievements`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `osrp_Animations`
--
ALTER TABLE `osrp_Animations`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=136;

--
-- AUTO_INCREMENT for table `osrp_Areas`
--
ALTER TABLE `osrp_Areas`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_Booths`
--
ALTER TABLE `osrp_Booths`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_BusStops`
--
ALTER TABLE `osrp_BusStops`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `osrp_CashPoints`
--
ALTER TABLE `osrp_CashPoints`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_Contacts`
--
ALTER TABLE `osrp_Contacts`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `osrp_Doors`
--
ALTER TABLE `osrp_Doors`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `osrp_GroupOrders`
--
ALTER TABLE `osrp_GroupOrders`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_GroupPerms`
--
ALTER TABLE `osrp_GroupPerms`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `osrp_Groups`
--
ALTER TABLE `osrp_Groups`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `osrp_GroupSets`
--
ALTER TABLE `osrp_GroupSets`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `osrp_GroupTasks`
--
ALTER TABLE `osrp_GroupTasks`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `osrp_Objects`
--
ALTER TABLE `osrp_Objects`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=724;

--
-- AUTO_INCREMENT for table `osrp_Penalties`
--
ALTER TABLE `osrp_Penalties`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `osrp_Players`
--
ALTER TABLE `osrp_Players`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `osrp_Vehicles`
--
ALTER TABLE `osrp_Vehicles`
  MODIFY `UID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `osrp_WholeSales`
--
ALTER TABLE `osrp_WholeSales`
  MODIFY `UID` int(4) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
