#include <db.h>

#if DB_VERSION_MAJOR > 2
extern int db_open (const char *__file, DBTYPE __type, u_int32_t __flags,
		    int __mode, void *__dbenv, void *__dbinfo, DB **__dbp);
#endif
