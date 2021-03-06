/*
 * Copyright (C) 2014 Helium Systems Inc.
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <pthread.h>
#include <stdint.h>
#include <ruby.h>

struct helium_queued_callback {
  uint64_t sender_mac;
  char *message;
  size_t count;
  helium_connection_t *conn;

  // TODO: pthread mutexen are notoriously inefficient
  // let's look and see if libuv's are any faster.
  pthread_mutex_t mutex;
  pthread_cond_t cond;

  struct helium_queued_callback *next;
};

struct helium_waiter_t {
  struct helium_queued_callback *callback;
  _Bool abort;
};
