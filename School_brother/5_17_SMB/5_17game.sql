-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- 主機: 127.0.0.1
-- 產生時間： 2019-05-14 16:21:25
-- 伺服器版本: 10.1.28-MariaDB
-- PHP 版本： 5.6.32

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `5/17game`
--

-- --------------------------------------------------------

--
-- 資料表結構 `5/17game`
--

CREATE TABLE `5/17game` (
  `id` int(11) NOT NULL,
  `date` date NOT NULL,
  `time` time NOT NULL,
  `1` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '區域名稱',
  `2` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '生產工件',
  `3` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '使用者',
  `4` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '機台狀態',
  `5` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '震動',
  `6` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '良品數量',
  `7` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '溫度',
  `8` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '電流',
  `9` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '機械手臂',
  `10` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '輸送帶',
  `11` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '加工區',
  `12` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '檢測區',
  `13` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '機械手臂次數',
  `14` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '輸送帶次數',
  `15` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '加工區次數',
  `16` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '檢測區次數'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
