
AM_CPPFLAGS	= -I$(top_srcdir)/include

bin_PROGRAMS	= brd picocoin blkscan blkstats rawtx

noinst_LIBRARIES= libnode.a

libnode_a_SOURCES=	\
	peerman.c	\
	peerman.h

brd_SOURCES=		\
	brd.c		\
	brd.h

brd_LDFLAGS = $(AM_LDFLAGS) -static

brd_LDADD	= libnode.a ../lib/libccoin.la \
		  @CRYPTO_LIBS@ @GMP_LIBS@ @EVENT_LIBS@



picocoin_SOURCES=	\
	aes.c		\
	main.c		\
	net.c		\
	fakepoll.h	\
	picocoin.h	\
	wallet.c wallet.h

picocoin_LDADD	= libnode.a ../lib/libccoin.la \
		  @CRYPTO_LIBS@ @GMP_LIBS@ @ARGP_LIBS@ \
		  @EVENT_LIBS@ @JANSSON_LIBS@

picocoin_LDFLAGS = $(AM_LDFLAGS) -static

blkscan_LDADD	= ../lib/libccoin.la \
		  @CRYPTO_LIBS@ @GMP_LIBS@ @ARGP_LIBS@
blkstats_LDADD	= ../lib/libccoin.la \
		  @CRYPTO_LIBS@ @GMP_LIBS@ @ARGP_LIBS@
blkstats_LDFLAGS = $(AM_LDFLAGS) -static

rawtx_LDADD	= ../lib/libccoin.la \
		  @CRYPTO_LIBS@ @GMP_LIBS@ @ARGP_LIBS@ @JANSSON_LIBS@
rawtx_LDFLAGS = $(AM_LDFLAGS) -static
