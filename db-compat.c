/* Compatibility functions for Berkeley DB 3.
   Copyright (C) 2000 Free Software Foundation, Inc.
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

#include <assert.h>
#include <db.h>
#include <fcntl.h>

#if DB_VERSION_MAJOR > 2

#include "db-compat.h"

int
db_open (const char *file, DBTYPE type, u_int32_t flags, int mode,
	 void *dbenv, void *dbinfo, DB **dbp)
{
  DB *db;
  int err;

  assert (dbenv == NULL);
  assert (dbinfo == NULL);

  err = db_create (&db, NULL, 0);
  if (err)
    return err;

  err = db->open (db, file, NULL, type, flags, mode);
  if (err)
    {
      db->close (db, 0);
      return err;
    }

  *dbp = db;
  return 0;
}

#endif
