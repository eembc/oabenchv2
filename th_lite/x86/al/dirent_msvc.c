/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** Get autoconf definitions. */
#include "thconfig.h"
#include <string.h>
#if HAVE_ERRNO_H
#   include <errno.h>
#elif	HAVE_SYS_ERRNO_H
#   include <sys/errno.h>
#else
static int errno;
    /* FIXME: anything clever to put here? */
#define EFAULT          1
#define ENOTDIR         12
#define ENOENT          2    /* No such file or directory */
#define ENOMEM          5
#define EINVAL          22   /* Invalid argument */
#endif

#include "dirent_msvc.h"

/** @addtogroup SHAL
@{ */
/** @addtogroup dirent_msvc MSVC Dirent Routines
@{ */

/** If we are not using harness fileio, 
and compiler is flagged to have fileio, then use this code.
*/
#if		!USE_TH_FILEIO && HAVE_FILEIO

/** MSVC ONLY, calls MSVC specific libc routines. */
#if 	defined(_MSC_VER) || defined(WIN32)

#define SUFFIX	"*"
#define	SLASH	"\\"

/** Returns a pointer to a DIR structure appropriately filled in to begin
    searching a directory. */
DIR *opendir (const CHAR *szPath)
{
  DIR *nd;
  unsigned int rc;
  CHAR szFullPath[MAX_PATH];
	
  errno = 0;

  if (!szPath)
    {
      errno = EFAULT;
      return (DIR *) 0;
    }

  if (szPath[0] == '\0')
    {
      errno = ENOTDIR;
      return (DIR *) 0;
    }

  /* Attempt to determine if the given path really is a directory. */
  rc = GetFileAttributes (szPath);
  if (rc == -1)
    {
      /* call GetLastError for more error info */
      errno = ENOENT;
      return (DIR *) 0;
    }
  if (!(rc & FILE_ATTRIBUTE_DIRECTORY))
    {
      /* Error, entry exists but not a directory. */
      errno = ENOTDIR;
      return (DIR *) 0;
    }

  /* Make an absolute pathname.  */
#if defined( UNDER_CE )
  if (szPath[0] == '\\' || szPath[0] == '/')
    {
      th_sprintf (szFullPath, MAX_PATH, "%s", szPath);
      szFullPath[0] = '\\';
    }
  else
    {
      /* FIXME: if I wasn't lazy, I'd check for overflows here. */
      th_sprintf (szFullPath, MAX_PATH, "\\%s", szPath );
    }
#else
  _fullpath (szFullPath, szPath, MAX_PATH);
#endif

  /* Allocate enough space to store DIR structure and the complete
   * directory path given. */
  nd = (DIR *) th_malloc (sizeof (DIR) + strlen (szFullPath) + strlen (SLASH) +
		       strlen (SUFFIX));

  if (!nd)
    {
      /* Error, out of memory. */
      errno = ENOMEM;
      return (DIR *) 0;
    }

  /* Create the search expression. */
  strcpy (nd->dd_name, szFullPath);

  /* Add on a slash if the path does not end with one. */
  if (nd->dd_name[0] != '\0' &&
      nd->dd_name[strlen (nd->dd_name) - 1] != '/' &&
      nd->dd_name[strlen (nd->dd_name) - 1] != '\\')
    {
      strcat (nd->dd_name, SLASH);
    }

  /* Add on the search pattern */
  strcat (nd->dd_name, SUFFIX);

  /* Initialize handle to -1 so that a premature closedir doesn't try
   * to call FindClose on it. */
  nd->dd_handle = -1;

  /* Initialize the status. */
  nd->dd_stat = 0;

  /* Initialize the dirent structure. ino and reclen are invalid under
   * Win32, and name simply points at the appropriate part of the
   * findfirst_t structure. */
  nd->dd_dir.d_ino = 0;
  nd->dd_dir.d_reclen = 0;
  nd->dd_dir.d_namlen = 0;
  nd->dd_dir.d_name = nd->dd_dta.cFileName;

  return nd;
}


/** Return a pointer to a dirent structure filled with the information on the
 *  next entry in the directory.
 */
struct dirent *readdir (DIR * dirp)
{
	errno = 0;

	/* Check for valid DIR struct. */
	if (!dirp)
	{
		errno = EFAULT;
		return (struct dirent *) 0;
    }

	if (dirp->dd_dir.d_name != dirp->dd_dta.cFileName)
	{
		/* The structure does not seem to be set up correctly. */
		errno = EINVAL;
		return (struct dirent *) 0;
	}

	if (dirp->dd_stat < 0)
	{
		/* 
		 * We have already returned all files in the directory
		 * (or the structure has an invalid dd_stat).
		 */
		return (struct dirent *) 0;
	}
	else if (dirp->dd_stat == 0)
	{
		/* We haven't started the search yet. */
		/* Start the search */
		dirp->dd_handle = (long)FindFirstFile (dirp->dd_name, &(dirp->dd_dta));

		if (dirp->dd_handle == -1)
		{
			/* Whoops! Seems there are no files in that directory. */
			dirp->dd_stat = -1;
		}
		else
		{
			dirp->dd_stat = 1;
		}
	}
	else
	{
		/* Get the next search entry. */
		if ((FindNextFile((HANDLE)dirp->dd_handle, &(dirp->dd_dta)))==0)
		{
			/* We are off the end or otherwise error. */
			FindClose ((HANDLE)dirp->dd_handle);
			dirp->dd_handle = -1;
			dirp->dd_stat = -1;
		}
		else
		{
			/* Update the status to indicate the correct number. */
			dirp->dd_stat++;
		}
	}
	if (dirp->dd_stat > 0)
	{
		/*
		 * Successfully got an entry. Everything about the file is
		 * already appropriately filled in except the length of the
		 * file name.
		 */
		dirp->dd_dir.d_namlen = (unsigned short) strlen (dirp->dd_dir.d_name);
		return &dirp->dd_dir;
	}
	return (struct dirent *) 0;
}

/** Frees up resources allocated by opendir. */
int closedir (DIR * dirp)
{
  int rc;

  errno = 0;
  rc = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return -1;
    }

  if (dirp->dd_handle != -1)
    {
      rc = FindClose ((HANDLE)dirp->dd_handle);
    }

  /* Delete the dir structure. */
  th_free (dirp);

  return rc;
}

/** Return to the beginning of the directory "stream". We simply call findclose
 *  and then reset things like an opendir.
 */
void rewinddir (DIR * dirp)
{
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (dirp->dd_handle != -1)
    {
      FindClose ((HANDLE)dirp->dd_handle);
    }

  dirp->dd_handle = -1;
  dirp->dd_stat = 0;
}

/** Returns the "position" in the "directory stream" which can be used with
 *  seekdir to go back to an old entry. We simply return the value in stat. */
long telldir (DIR * dirp)
{
	errno = 0;

	if (!dirp)
	{
		errno = EFAULT;
		return -1;
	}
	return dirp->dd_stat;
}

/**
 * seekdir
 *
 * Seek to an entry previously returned by telldir. We rewind the directory
 * and call readdir repeatedly until either dd_stat is the position number
 * or -1 (off the end). This is not perfect, in that the directory may
 * have changed while we weren't looking. But that is probably the case with
 * any such system.
 */
void seekdir (DIR * dirp, long lPos)
{
	errno = 0;

	if (!dirp)
	{
		errno = EFAULT;
		return;
	}

	if (lPos < -1)
	{
		/* Seeking to an invalid position. */
		errno = EINVAL;
		return;
	}
	else if (lPos == -1)
	{
		/* Seek past end. */
		if (dirp->dd_handle != -1)
		{
			FindClose ((HANDLE)dirp->dd_handle);
		}
		dirp->dd_handle = -1;
		dirp->dd_stat = -1;
	}
	else
	{
		/* Rewind and read forward to the appropriate index. */
		rewinddir (dirp);
		while ((dirp->dd_stat < lPos) && readdir (dirp));
	}
}

#endif /* Not _MSC_VER */

#endif /* Not !USE_TH_FILEIO && HAVE_FILEIO */
/** @} */
/** @} */
