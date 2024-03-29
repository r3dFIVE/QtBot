CREATE TABLE `quotebot` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `quote_id` bigint unsigned NOT NULL DEFAULT 0,
  `chan_id` bigint unsigned NOT NULL DEFAULT 0,
  `quote` mediumtext NOT NULL,
  `author` varchar(255) NOT NULL DEFAULT 'unknown',
  `handle` varchar(255) NOT NULL DEFAULT '',
  `host` varchar(255) NOT NULL DEFAULT '',
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `rating` int(11) NOT NULL DEFAULT 0,
  `views` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`,`quote_id`),
  KEY `chan_id` (`chan_id`)
) ENGINE=MyISAM AUTO_INCREMENT=2016 DEFAULT CHARSET=latin1 PACK_KEYS=0;


-- Alter existing database backup (OLD QUOTES)

ALTER TABLE quotes.quote MODIFY `chan_id` bigint unsigned DEFAULT 0;
ALTER TABLE quotes.quote MODIFY `quote_id` bigint unsigned DEFAULT 0;