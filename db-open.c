/* Common database routines for nss_db.
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
#include <errno.h>
#include <fcntl.h>

#include "db-compat.h"

#include "nss_db.h"

/* Set the `FD_CLOEXEC' flag of FD.  Return 0 on success, or -1 on
   error with `errno' set. */
static int
set_cloexec_flag (int fd)
{
  int oldflags = fcntl (fd, F_GETFD, 0);

  if (oldflags < 0)
    return oldflags;

  oldflags |= FD_CLOEXEC;

  return fcntl (fd, F_SETFD, oldflags);
}

/* Open the database stored in FILE.  If succesful, store the database
   handle in *DBP and return NSS_STATUS_SUCCESS.  On failure, return
   the appropriate lookup status.  */
enum nss_status
internal_setent (const char *file, DB **dbp)
{
  DB *db;
  int err;
  int fd;

  if (*dbp)
    return NSS_STATUS_SUCCESS;

  err = db_open (file, DB_BTREE, DB_RDONLY, 0, NULL, NULL, &db);
  if (err != 0)
    {
      if (err > 0)
	__set_errno (err);
      return NSS_STATUS_UNAVAIL;
    }

  /* We have to make sure the file is `closed on exec'.  */
  err = db->fd (db, &fd);
  if (err)
    goto fail;
  if (set_cloexec_flag (fd) < 0)
    goto fail;

  *dbp = db;
  return NSS_STATUS_SUCCESS;

 fail:
  db->close (db, 0);
  if (err > 0)
    __set_errno (err);
  return NSS_STATUS_UNAVAIL;
}

/* Close the database *DBP.  */
void
internal_endent (DB **dbp)
{
  DB *db = *dbp;

  if (db != NULL)
    {
      db->close (db, 0);
      *dbp = NULL;
    }
}
