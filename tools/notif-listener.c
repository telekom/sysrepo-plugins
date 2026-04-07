//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include <sysrepo.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int exit_application = 0;

static void print_val(const sr_val_t* val)
{
    printf("  %s = ", val->xpath);
    switch (val->type) {
    case SR_STRING_T:
    case SR_BINARY_T:
    case SR_BITS_T:
    case SR_ENUM_T:
    case SR_IDENTITYREF_T:
    case SR_INSTANCEID_T:
    case SR_ANYXML_T:
    case SR_ANYDATA_T:
        printf("%s", val->data.string_val);
        break;
    case SR_BOOL_T:
        printf("%s", val->data.bool_val ? "true" : "false");
        break;
    case SR_DECIMAL64_T:
        printf("%g", val->data.decimal64_val);
        break;
    case SR_INT8_T:
        printf("%d", val->data.int8_val);
        break;
    case SR_INT16_T:
        printf("%d", val->data.int16_val);
        break;
    case SR_INT32_T:
        printf("%d", val->data.int32_val);
        break;
    case SR_INT64_T:
        printf("%ld", (long)val->data.int64_val);
        break;
    case SR_UINT8_T:
        printf("%u", val->data.uint8_val);
        break;
    case SR_UINT16_T:
        printf("%u", val->data.uint16_val);
        break;
    case SR_UINT32_T:
        printf("%u", val->data.uint32_val);
        break;
    case SR_UINT64_T:
        printf("%lu", (unsigned long)val->data.uint64_val);
        break;
    case SR_LEAF_EMPTY_T:
        printf("(empty)");
        break;
    default:
        printf("(type %d)", val->type);
        break;
    }
    printf("\n");
}

static void notif_cb(sr_session_ctx_t* session, uint32_t sub_id, const sr_ev_notif_type_t notif_type,
    const char* xpath, const sr_val_t* values, const size_t values_cnt,
    struct timespec* timestamp, void* private_data)
{
    (void)session;
    (void)sub_id;
    (void)private_data;

    const char* type_str;
    switch (notif_type) {
    case SR_EV_NOTIF_REALTIME:
        type_str = "realtime";
        break;
    case SR_EV_NOTIF_REPLAY:
        type_str = "replay";
        break;
    case SR_EV_NOTIF_REPLAY_COMPLETE:
        type_str = "replay-complete";
        break;
    case SR_EV_NOTIF_TERMINATED:
        type_str = "terminated";
        break;
    case SR_EV_NOTIF_MODIFIED:
        type_str = "modified";
        break;
    case SR_EV_NOTIF_SUSPENDED:
        type_str = "suspended";
        break;
    case SR_EV_NOTIF_RESUMED:
        type_str = "resumed";
        break;
    default:
        type_str = "unknown";
        break;
    }

    printf("[%ld.%09ld] Notification (%s): %s\n", (long)timestamp->tv_sec, timestamp->tv_nsec,
        type_str, xpath ? xpath : "(null)");

    for (size_t i = 0; i < values_cnt; i++) {
        print_val(&values[i]);
    }
    printf("\n");
    fflush(stdout);
}

static void sigint_handler(int signum)
{
    (void)signum;
    exit_application = 1;
}

int main(int argc, char** argv)
{
    const char* module = "os-metrics";
    if (argc > 1) {
        module = argv[1];
    }

    sr_conn_ctx_t* conn = NULL;
    sr_session_ctx_t* sess = NULL;
    sr_subscription_ctx_t* sub = NULL;
    int rc;

    sr_log_stderr(SR_LL_WRN);

    rc = sr_connect(SR_CONN_DEFAULT, &conn);
    if (rc != SR_ERR_OK) {
        fprintf(stderr, "sr_connect failed: %s\n", sr_strerror(rc));
        return 1;
    }

    rc = sr_session_start(conn, SR_DS_RUNNING, &sess);
    if (rc != SR_ERR_OK) {
        fprintf(stderr, "sr_session_start failed: %s\n", sr_strerror(rc));
        sr_disconnect(conn);
        return 1;
    }

    printf("Subscribing to notifications from module \"%s\"...\n", module);

    rc = sr_notif_subscribe(sess, module, NULL, 0, 0, notif_cb, NULL, 0, &sub);
    if (rc != SR_ERR_OK) {
        fprintf(stderr, "sr_notif_subscribe failed: %s\n", sr_strerror(rc));
        sr_disconnect(conn);
        return 1;
    }

    printf("Listening... (Ctrl+C to stop)\n");

    signal(SIGINT, sigint_handler);
    signal(SIGPIPE, SIG_IGN);
    while (!exit_application) {
        sleep(1);
    }

    printf("\nCleaning up...\n");
    sr_unsubscribe(sub);
    sr_disconnect(conn);
    return 0;
}
