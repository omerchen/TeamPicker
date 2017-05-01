#pragma once

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define TEAM_SIZE				(5)
#define TEAMS_AMOUNT			(3)
#define PLAYERS_AMOUNT			(TEAM_SIZE * TEAMS_AMOUNT)

#define STRING_MAX_SIZE			(512)
#define NAME_MAX_SIZE			(64)
#define	NULL_TERMINATOR			('\0')

#define PRECENT(value, precent)		((value * precent) / 100.0)

#define __DEBUG_MODE

#ifdef __DEBUG_MODE

#define PRINT_DEBUG(str)		printf(str)

#else

#define PRINT_DEBUG

#endif // DEBUG

#define NULL_TERMINATOR			('\0')
