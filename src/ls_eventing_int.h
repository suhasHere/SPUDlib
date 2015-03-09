/**
 * \file
 * \brief
 * Eventing typedefs. private, not for use outside library and unit tests.
 * \see eventing.h
 *
 * Copyrights
 *
 * Portions created or assigned to Cisco Systems, Inc. are
 * Copyright (c) 2010 Cisco Systems, Inc.  All Rights Reserved.
 */

#pragma once

/**
 * Event binding information. This structure is created for each call to
 * ls_event_bind with a unique callback.
 */
typedef struct _ls_event_binding_t
{
    ls_event_notify_callback    cb;
    void                        *arg;
    struct _ls_event_binding_t  *next;
    bool                        unbound;
    /**
     * Binding status. True if it is already bound before an event is
     * triggered. It is false by default and marked as true at the very
     * beginning of an event trigger. Within an event trigger, false
     * implies a callback that is bound in the current event and should
     * not be executed until the next time this event is triggered.
     */
    bool                        normal_bound;
} ls_event_binding_t;

/**
 * Event triggering information. This describes a "moment in time" of an
 * event.
 */
typedef struct _ls_event_moment_t
{
    struct _ls_event_data_t          evt;
    ls_event_result_callback        result_cb;
    void                            *result_arg;
    ls_event_binding_t              *bindings;
    struct _ls_event_moment_t       *next;
} ls_event_moment_t;

/**
 * Dispatcher members. This is the structure underlying ls_event_dispatcher.
 */
typedef struct _ls_event_dispatch_t
{
    const void              *source;
    ls_htable               events;
    ls_event                running;
    /**
     * The queue of event moments.
     * NOTE: tail of the queue
     */
    ls_event_moment_t       *queue;
} ls_event_dispatch_t;
#define EXPAND_DISPATCHER(dispatch) ((ls_event_dispatch_t *)(dispatch))

/**
 * Notifier members. This is the structure underlying ls_event.
 */
typedef struct _ls_event_t
{
    ls_event_dispatch_t *dispatcher;
    const void          *source;
    const char          *name;
    ls_event_binding_t  *bindings;
} ls_event_notifier_t;
#define EXPAND_NOTIFIER(event) ((ls_event_notifier_t *)(event))