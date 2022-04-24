AM_CFLAGS = -std=gnu99 -Wall

sbin_PROGRAMS = milter-blockdomain
milter_blockdomain_SOURCES = milter-blockdomain.c milter-blockdomain.h blkdom_config.c blkdom_check.c blkdom_util.c
milter_blockdomain_LDFLAGS = -pthread
milter_blockdomain_LDADD = -lmilter
