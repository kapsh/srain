#ifndef __SRAIN_APP_H
#define __SRAIN_APP_H

#include <gtk/gtk.h>
#include "srain_chan.h"

#define SRAIN_TYPE_APP (srain_app_get_type())
#define SRAIN_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), SRAIN_TYPE_APP, SrainApp))

typedef int (*ServerJoinFunc) (void *server, const char *chan_name);
typedef int (*ServerPartFunc) (void *server, const char *chan_name);
typedef int (*ServerSendFunc) (void *server, const char *target, const char *msg);
typedef int (*ServerCmdFunc) (void *server, const char *source, const char *cmd);

struct _SrainApp {
    GtkApplication parent;

    ServerJoinFunc server_join;
    ServerPartFunc server_part;
    ServerSendFunc server_send;
    ServerCmdFunc server_cmd;
};

struct _SrainAppClass {
    GtkApplicationClass parent_class;
};

typedef struct _SrainApp SrainApp;
typedef struct _SrainAppClass SrainAppClass;

GType srain_app_get_type(void);
SrainApp *srain_app_new(void);

SrainChan* srain_app_add_chan(void *server, const char *server_name, const char *chan_name);
void srain_app_rm_chan(SrainChan *chan);
void srain_app_sys_msg(SrainChan *chan, const char *msg, SysMsgType type);
void srain_app_send_msg(SrainChan *chan, const char *msg);
void srain_app_recv_msg(SrainChan *chan, const char *nick, const char *id, const char *msg);
int srain_app_user_list_add(SrainChan *chan, const char *nick, IRCUserType type, int notify);
int srain_app_user_list_rm(SrainChan *chan, const char *nick, const char *reason);
int srain_app_user_list_rename(SrainChan *chan, const char *old_nick, const char *new_nick);
void srain_app_set_topic(SrainChan *chan, const char *topic);

#endif /* __SRAIN_APP_H */
