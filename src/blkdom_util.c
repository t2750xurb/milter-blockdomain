/******************************************************************************/
/*                                                                            */
/*  Copyright(C) 2016, Takao Abe.  All rights reserved.                       */
/*                                                                            */
/*  LICENSE: GPLv3 or any later version                                       */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*  ChangeLog                                                                 */
/*                                                                            */
/*  2016/05/21  1.00                                                          */
/*      First release                                                         */
/*                                                                            */
/*  2016/07/02  1.01                                                          */
/*      [Enhancement] Support GNU build procedure.                            */
/*                    Add config.h generated by the Autoconf/Automake.        */
/*      [Enhancement] Conf file new keyword 'syslogDebug'.                    */
/*                    Optional writing syslog priority=debug.                 */
/*                                                                            */
/******************************************************************************/

#include "config.h"	/* GNU Autotools */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <syslog.h>
#include <ctype.h>
#include <sys/stat.h>

#include "milter-blockdomain.h"

/* Local data */

static	int 	iDebugLevel = 0 ;
static	bool	bSyslogDebug = FALSE ;

/**************************************************************************************************/

void setLogLevel( const int iLogLevel )
{
	iDebugLevel = iLogLevel ;
}

/**************************************************************************************************/

void setSyslogDebug( const bool bFlag )
{
	bSyslogDebug = bFlag ;
}

/**************************************************************************************************/

void openSyslog( const char *pProcessName, const char *pFacilityName )
{

	int 	iFacility = LOG_MAIL ;

	if      ( pFacilityName == NULL                  ) iFacility = LOG_MAIL   ;
	else if ( strcmp( pFacilityName, "daemon" ) == 0 ) iFacility = LOG_DAEMON ;
	else if ( strcmp( pFacilityName, "mail"   ) == 0 ) iFacility = LOG_MAIL   ;
	else if ( strcmp( pFacilityName, "user"   ) == 0 ) iFacility = LOG_USER   ;
	else if ( strcmp( pFacilityName, "local0" ) == 0 ) iFacility = LOG_LOCAL0 ;
	else if ( strcmp( pFacilityName, "local1" ) == 0 ) iFacility = LOG_LOCAL1 ;
	else if ( strcmp( pFacilityName, "local2" ) == 0 ) iFacility = LOG_LOCAL2 ;
	else if ( strcmp( pFacilityName, "local3" ) == 0 ) iFacility = LOG_LOCAL3 ;
	else if ( strcmp( pFacilityName, "local4" ) == 0 ) iFacility = LOG_LOCAL4 ;
	else if ( strcmp( pFacilityName, "local5" ) == 0 ) iFacility = LOG_LOCAL5 ;
	else if ( strcmp( pFacilityName, "local6" ) == 0 ) iFacility = LOG_LOCAL6 ;
	else if ( strcmp( pFacilityName, "local7" ) == 0 ) iFacility = LOG_LOCAL7 ;

	openlog( pProcessName, LOG_PID, iFacility ) ;

}

/**************************************************************************************************/

void logDebug( const char *format, ... )
{

	va_list	arg ;

	if ( bSyslogDebug ) {
		va_start( arg, format ) ;
		vsyslog( LOG_DEBUG, format, arg ) ;
		va_end( arg ) ;
	}

	if ( iDebugLevel > 0 ) {
		va_start( arg, format ) ;
		vprintf( format, arg ) ;
		va_end( arg ) ;
		printf( "\n" ) ;
	}

}

/**************************************************************************************************/

void logInfo( const char *format, ... )
{

	va_list	arg ;

	va_start( arg, format ) ;
	vsyslog( LOG_INFO, format, arg ) ;
	va_end( arg ) ;

	if ( iDebugLevel > 0 ) {
		va_start( arg, format ) ;
		vprintf( format, arg ) ;
		va_end( arg ) ;
		printf( "\n" ) ;
	}

}

/**************************************************************************************************/

void logWarning( const char *format, ... )
{

	va_list	arg ;

	va_start( arg, format ) ;
	vsyslog( LOG_WARNING, format, arg ) ;
	va_end( arg ) ;

	if ( iDebugLevel > 0 ) {
		va_start( arg, format ) ;
		vprintf( format, arg ) ;
		va_end( arg ) ;
		printf( "\n" ) ;
	}

}

/**************************************************************************************************/

void logError( const char *format, ... )
{

	va_list	arg ;

	va_start( arg, format ) ;
	vsyslog( LOG_ERR, format, arg ) ;
	va_end( arg ) ;

	if ( iDebugLevel > 0 ) {
		va_start( arg, format ) ;
		vprintf( format, arg ) ;
		va_end( arg ) ;
		printf( "\n" ) ;
	}

}

/**************************************************************************************************/

void logAlert( const char *format, ... )
{

	va_list	arg ;

	va_start( arg, format ) ;
	vsyslog( LOG_ALERT, format, arg ) ;
	va_end( arg ) ;

	if ( iDebugLevel > 0 ) {
		va_start( arg, format ) ;
		vprintf( format, arg ) ;
		va_end( arg ) ;
		printf( "\n" ) ;
	}

}

/**************************************************************************************************/

void strLower( char *s )
{

	for ( ; *s != 0 ; s ++ ) *s = tolower( *s ) ;

}

/**************************************************************************************************/