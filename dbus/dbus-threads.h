/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-threads.h  D-BUS threads handling
 *
 * Copyright (C) 2002  Red Hat Inc.
 *
 * Licensed under the Academic Free License version 1.2
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#if !defined (DBUS_INSIDE_DBUS_H) && !defined (DBUS_COMPILATION)
#error "Only <dbus/dbus.h> can be included directly, this file may disappear or change contents."
#endif

#ifndef DBUS_THREADS_H
#define DBUS_THREADS_H

#include <dbus/dbus-macros.h>
#include <dbus/dbus-types.h>

DBUS_BEGIN_DECLS;

typedef struct DBusMutex DBusMutex;

typedef DBusMutex*  (* DBusMutexNewFunction)    (void);
typedef void        (* DBusMutexFreeFunction)   (DBusMutex *mutex);
typedef dbus_bool_t (* DBusMutexLockFunction)   (DBusMutex *mutex);
typedef dbus_bool_t (* DBusMutexUnlockFunction) (DBusMutex *mutex);

typedef enum 
{
  DBUS_THREAD_FUNCTIONS_NEW_MASK     = 1 << 0,
  DBUS_THREAD_FUNCTIONS_FREE_MASK    = 1 << 1,
  DBUS_THREAD_FUNCTIONS_LOCK_MASK    = 1 << 2,
  DBUS_THREAD_FUNCTIONS_UNLOCK_MASK  = 1 << 3,

  DBUS_THREAD_FUNCTIONS_ALL_MASK     = 0xf
} DBusThreadFunctionsMask;

typedef struct
{
  unsigned int mask;

  DBusMutexNewFunction mutex_new;
  DBusMutexFreeFunction mutex_free;
  DBusMutexLockFunction mutex_lock;
  DBusMutexUnlockFunction mutex_unlock;

  void (* padding1) (void);
  void (* padding2) (void);
  void (* padding3) (void);
  void (* padding4) (void);
  void (* padding5) (void);
  void (* padding6) (void);
  void (* padding7) (void);
  void (* padding8) (void);
  
} DBusThreadFunctions;


DBusMutex*  dbus_mutex_new    (void);
void        dbus_mutex_free   (DBusMutex *mutex);
dbus_bool_t dbus_mutex_lock   (DBusMutex *mutex);
dbus_bool_t dbus_mutex_unlock (DBusMutex *mutex);

dbus_bool_t dbus_threads_init (const DBusThreadFunctions *functions);

typedef struct DBusStaticMutex DBusStaticMutex;

struct DBusStaticMutex
{
  void *pad1;
  void *pad2;
  void *pad3;
  void *pad4;
};

#define DBUS_STATIC_MUTEX_INIT { NULL, NULL, NULL, NULL }

dbus_bool_t dbus_static_mutex_lock   (DBusStaticMutex *mutex);
dbus_bool_t dbus_static_mutex_unlock (DBusStaticMutex *mutex);

DBUS_END_DECLS;

#endif /* DBUS_THREADS_H */
