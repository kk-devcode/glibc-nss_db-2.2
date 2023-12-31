/* Copyright (C) 1996, 1997, 2000 Free Software Foundation, Inc.
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

#include <string.h>
#include <netinet/if_ether.h>

/* Because the `ethers' lookup does not fit so well in the scheme so
   we define a dummy struct here which helps us to use the available
   functions.  */
struct etherent
{
  const char *e_name;
  struct ether_addr e_addr;
};
struct etherent_data {};

#define ENTNAME		etherent
#define DATABASE	"ethers"
#include "files-parse.c"
LINE_PARSER
("#",
 /* Read the ethernet address: 6 x 8bit hexadecimal number.  */
 {
   size_t cnt;

   for (cnt = 0; cnt < 6; ++cnt)
     {
       unsigned int number;

       if (cnt < 5)
	 INT_FIELD (number, ISCOLON , 0, 16, (unsigned int))
       else
	 INT_FIELD (number, isspace, 1, 16, (unsigned int))

       if (number > 0xff)
	 return 0;
       result->e_addr.ether_addr_octet[cnt] = number;
     }
 };
 STRING_FIELD (result->e_name, isspace, 1);
 )


#include GENERIC

DB_LOOKUP (hostton, 1 + strlen (name), (".%s", name),
	   {
	     if (__strcasecmp (result->e_name, name) == 0)
	       break;
	   }, const char *name)

DB_LOOKUP (ntohost, 18, ("=%x:%x:%x:%x:%x:%x",
			 addr->ether_addr_octet[0], addr->ether_addr_octet[1],
			 addr->ether_addr_octet[2], addr->ether_addr_octet[3],
			 addr->ether_addr_octet[4], addr->ether_addr_octet[5]),
	   {
	     if (memcmp (&result->e_addr, addr,
			 sizeof (struct ether_addr)) == 0)
	       break;
	   }, struct ether_addr *addr)
