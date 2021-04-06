-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- 主機: 127.0.0.1
-- 產生時間： 2017-02-23 14:25:27
-- 伺服器版本: 10.1.16-MariaDB
-- PHP 版本： 5.6.24

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `drive_bird`
--

-- --------------------------------------------------------

--
-- 資料表結構 `record`
--

CREATE TABLE `record` (
  `ID` int(20) NOT NULL,
  `DATE` date NOT NULL COMMENT '日期',
  `TIME` time NOT NULL COMMENT '時間',
  `1` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '空氣濕度',
  `2` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '空氣溫度',
  `3` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '土壤濕度',
  `4` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '土壤溫度',
  `5` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '微波感測器狀態'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 資料表的匯出資料 `record`
--

INSERT INTO `record` (`ID`, `DATE`, `TIME`, `1`, `2`, `3`, `4`, `5`) VALUES
(1, '2017-02-23', '13:58:38', '56%', '29*C', 'Label8', 'Label9', 'Label10'),
(2, '2017-02-23', '13:58:43', '56%', '29*C', 'Label8', 'Label9', 'Label10'),
(3, '2017-02-23', '13:59:26', '55*C', '28%', 'Label8', 'Label9', 'Label10'),
(4, '2017-02-23', '13:59:31', '55*C', '28%', 'Label8', 'Label9', 'Label10'),
(5, '2017-02-23', '13:59:50', '55%', '29*C', 'Label8', 'Label9', 'Label10'),
(6, '2017-02-23', '13:59:55', '55%', '29*C', 'Label8', 'Label9', 'Label10'),
(7, '2017-02-23', '14:00:00', '55%', '29*C', 'Label8', 'Label9', 'Label10'),
(8, '2017-02-23', '14:02:42', '53%', '28。C', 'Label8', 'Label9', 'Label10'),
(9, '2017-02-23', '14:04:37', '52%', '27℃', 'Label8', 'Label9', 'Label10'),
(10, '2017-02-23', '14:04:42', '52%', '27℃', 'Label8', 'Label9', 'Label10'),
(11, '2017-02-23', '14:04:46', '52%', '27℃', 'Label8', 'Label9', 'Label10'),
(12, '2017-02-23', '14:04:51', '52%', '27℃', 'Label8', 'Label9', 'Label10');

--
-- 已匯出資料表的索引
--

--
-- 資料表索引 `record`
--
ALTER TABLE `record`
  ADD PRIMARY KEY (`ID`);

--
-- 在匯出的資料表使用 AUTO_INCREMENT
--

--
-- 使用資料表 AUTO_INCREMENT `record`
--
ALTER TABLE `record`
  MODIFY `ID` int(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
