/* Common database open/close routines for nss_db.
   Copyright (C) 1999, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef _NSS_DB_H
#define _NSS_DB_H	1

#include <db.h>
#include <nss.h>

/* Open the database stored in FILE.  If succesful, store the database
   handle in *DBP and return NSS_STATUS_SUCCESS.  On failure, return
   the appropriate lookup status.  */
extern enum nss_status internal_setent (const char *file, DB **dbp);

/* Close the database *DBP.  */
extern void internal_endent (DB **dbp);

#endif	/* nss_db.h */
