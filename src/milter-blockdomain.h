/******************************************************************************/
/*                                                                            */
/*    Copyright(C) 2016, Takao Abe.  All rights reserved.                     */
/*                                                                            */
/*    LICENSE: GPLv3 or any later version                                     */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*  ChangeLog                                                                 */
/*                                                                            */
/*  2016/05/21  1.00                                                          */
/*      First release                                                         */
/*                                                                            */
/*  2016/07/02  1.01                                                          */
/*      [Enhancement] Conf file new keyword 'syslogDebug'.                    */
/*                    Optional writing syslog priority=debug.                 */
/*      [Enhancement] Conf file new keyword 'checkMacro_'.                    */
/*                    Check value of the sendmail macro '_'.                  */
/*                                                                            */
/*  2018/01/14  1.04                                                          */
/*      [Change] Change leaf node anchors have every two characters of the    */
/*               beginning of the domain node name, from they have every one  */
/*               character of the beginning of the domain node name.          */
/*               milter-blockdomain.h  blkdom_check.c  blkdom_config.c        */
/*      [Change] Add following statistics information,                        */
/*               Node/Leaf count, Node/Leaf average chain length.             */
/*               milter-blockdomain.h - domainListType                        */
/*               blkdom_config.c - statDomainList, LoadDomainList             */
/*                                                                            */
/******************************************************************************/

#ifndef bool
#ifdef	_Bool
#define bool	_Bool
#else
#define bool	char
#endif
#endif

#ifndef TRUE
#define TRUE	(1==1)
#endif

#ifndef FALSE
#define FALSE	(!(TRUE))
#endif

#define RC_SUCCESS 0
#define RC_ERROR   1

#define MAX_CONF_LINE_LENGTH	100

#define MAX_DOMAIN_LIST         8
#define MAX_DOMAIN_NAME_LENGTH  255
#define MAX_DOMAIN_LEVEL        128

typedef struct domainLeafStruct
{
	char	*pName ;
	short	iLength ;
	struct  domainLeafStruct	*pNext ;
} domainLeafType ;

#define MAX_DOMAIN_INDEX	40
#define GET_INDEX(ch)	( ch - ( ch > 'z' ? (ch-38) : ( ch >= 'a' ? 85 : ( ch > 'Z' ? (ch-38) : ( ch >= 'A' ? 53 : ( ch > '9' ? (ch-11) : ( ch >= '0' ? 47 : ch ) ) ) ) ) ) )

typedef struct domainNodeStruct
{
	char	*pName ;
	short	iLength ;
	short	iLevel ;
	struct  domainLeafStruct	*pLeafList[MAX_DOMAIN_INDEX][MAX_DOMAIN_INDEX] ;
	struct  domainNodeStruct	*pNodeList[MAX_DOMAIN_INDEX] ;
	struct  domainNodeStruct	*pNext ;
} domainNodeType ;

typedef struct
{
	char	*sFileName ;
	struct  stat	xFileStat ;
	enum { WHITELIST, GREYLIST, BLACKLIST }	iListType ;
	bool	bSubdomain ;
	domainNodeType	oDomainRoot ;
	int 	iStatTotal, iStatTLD, iStatDepth, iStatMaxLeafChain, iStatMaxNodeChain ;
	int 	iStatNumberOfLeafAnchors, iStatTotalLeafChain, iStatAverageLeafChain ;
	int 	iStatNumberOfNodeAnchors, iStatTotalNodeChain, iStatAverageNodeChain ;
} domainListType ;

typedef struct
{
	char	*sUser ;
	char	*sSocket ;
	char	*sPidFile ;
	bool	bSubdomain ;
	bool	bCheckConnect ;
	bool	bCheckMacro_ ;
	bool	bCheckHelo ;
	bool	bCheckEnvFrom ;
	bool	bCheckEnvRcpt ;
	short	iCheckOnAndAfter ;	/* CHECK_ON_AND_AFTER_XXXX */
	char	*sMessageTempfail ;
	char	*sMessageReject ;
	char	*pSyslogFacility ;
	bool	bSyslogDebug ;
	/* Test mode */
	bool	bTestMode ;
	/* Debug log keyword */
	bool	bDebugConfigFunction ;
	bool	bDebugCheckFunction ;
} confType ;

#define CHECKPOINT_CONNECT	0
#define CHECKPOINT_HELO   	1
#define CHECKPOINT_ENVFROM	2
#define CHECKPOINT_ENVRCPT	3
#define CHECKPOINT_HEADER 	4
#define CHECKPOINT_BODY   	5

/* Function prototype ( blkdom_util.c ) */

void setLogLevel  ( const int ) ;
void setSyslogDebug( const bool ) ;
void openSyslog( const char *, const char * ) ;
void logDebug  ( const char *, ... ) ;
void logInfo   ( const char *, ... ) ;
void logWarning( const char *, ... ) ;
void logError  ( const char *, ... ) ;
void logAlert  ( const char *, ... ) ;

void strLower  ( char * ) ;

/* Function prototype ( blkdom_config.c ) */

void initConf() ;
void freeConf() ;
int  LoadConf( const char * ) ;
int  LoadAllDomainList() ;
int  ReloadAllDomainList() ;
void freeAllDomainList() ;

/* Function prototype ( blkdom_check.c ) */

#define RC_NOTLISTED	0
#define RC_WHITELIST	1
#define RC_BLACKLIST	2
#define RC_GREYLIST 	3

int checkConnect( const char * ) ;
int checkHelo   ( const char * ) ;
int checkEnvFrom( const char * ) ;
int checkEnvRcpt( const char * ) ;

/* Log message */

#define ALERT_MESSAGE_STRDUP_NULL       "$s: Memory allocation error ( strdup )"
#define ALERT_MESSAGE_MALLOC_NULL       "%s: Memory allocation error ( malloc )"
#define ALERT_MESSAGE_SOCKET_ERROR      "%s: smfi_setconn error %s"
#define ALERT_MESSAGE_MILTER_FUNCTION   "%s: %s error"
#define ALERT_MESSAGE_DAEMON            "%s: Could not be daemon"

#define ERROR_MESSAGE_FILE_OPEN         "Open error %s"
#define ERROR_MESSAGE_FILE_STAT         "Stat error %s"
#define ERROR_MESSAGE_FILE_UNLINK       "Unlink error %s"
#define ERROR_MESSAGE_INET_NTOP         "inet_ntop error"
#define ERROR_MESSAGE_UNKNOWN_AF        "Unknown address family"
#define ERROR_MESSAGE_GETPWNAM          "User not found '%s'"
#define ERROR_MESSAGE_SETGID            "setgid error: %s gid=%d"
#define ERROR_MESSAGE_SETUID            "setuid error: %s uid=%d"
#define ERROR_MESSAGE_CHOWN             "chown error: %s uid=%d gid=%d"

#define ERROR_MESSAGE_INVALID_CONFIG_KEYWORD    	"Invalid config file: Line=%d [%s] : Invalid keyword"
#define ERROR_MESSAGE_INVALID_CONFIG_MISSING_1  	"Invalid config file: Line=%d [%s] [] : Missing value"
#define ERROR_MESSAGE_INVALID_CONFIG_MISSING_2  	"Invalid config file: Line=%d [%s] [%s] [] : Missing value"
#define ERROR_MESSAGE_INVALID_CONFIG_VALUE_1    	"Invalid config file: Line=%d [%s] [%s] : Invalid value"
#define ERROR_MESSAGE_INVALID_CONFIG_VALUE_2    	"Invalid config file: Line=%d [%s] [%s] [%s] : Invalid value"
#define ERROR_MESSAGE_INVALID_CONFIG_MAX_LIST   	"Invalid config file: Line=%d [%s] : Exceed max domain list"
#define ERROR_MESSAGE_INVALID_CONFIG_ERROR_COUNT	"Invalid config file: Error count = %d"

#define ERROR_MESSAGE_INVALID_DOMAINLIST_NODE_LENGTH	"Invalid domain list: Line=%d [%s] : Continuous dot"
#define ERROR_MESSAGE_INVALID_DOMAINLIST_NODE_DEPTH 	"Invalid domain list: Line=%d [%s] : Too deep domain level"

#define	WARNING_MESSAGE_INVALID_DOMAINLIST_ROOTDOMAIN	"Invalid domain list: Line=%d [%s] : Root domain"
#define	WARNING_MESSAGE_INVALID_DOMAINLIST_DUPLICATE	"Invalid domain list: Line=%d [%s] : Duplicate"

#define INFO_MESSAGE_PROGRAM_VERSION	"%s  %s  ( %s ), built on %s"
#define INFO_MESSAGE_CONFIG	"Config file %s"
#define INFO_MESSAGE_STOP	"Stop"

