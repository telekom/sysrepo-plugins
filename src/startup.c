#include "startup.h"
#include "common.h"
#include "libyang/tree_data.h"
#include "ly_tree.h"

#include <sysrepo.h>
#include <unistd.h>
#include <errno.h>

// helpers

typedef int (*system_startup_load_cb)(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node);

static int system_startup_load_hostname(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node);
static int system_startup_load_contact(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node);
static int system_startup_load_location(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node);
static int system_startup_load_timezone_name(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node);

////

int system_startup_load_data(system_ctx_t *ctx, sr_session_ctx_t *session)
{
	int error = 0;

	const struct ly_ctx *ly_ctx = NULL;
	struct lyd_node *system_container_node = NULL;
	sr_conn_ctx_t *conn_ctx = NULL;

	system_startup_load_cb system_container_callbacks[] = {
		system_startup_load_hostname,
		system_startup_load_contact,
		system_startup_load_location,
		system_startup_load_timezone_name,
	};

	conn_ctx = sr_session_get_connection(session);
	ly_ctx = sr_acquire_context(conn_ctx);
	if (ly_ctx == NULL) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "Unable to get ly_ctx variable");
		goto error_out;
	}

	// load system container info
	error = system_ly_tree_create_system_container(ly_ctx, &system_container_node);
	for (size_t i = 0; i < ARRAY_SIZE(system_container_callbacks); i++) {
		error = system_container_callbacks[i](ctx, session, ly_ctx, system_container_node);
		if (error) {
			SRPLG_LOG_ERR(PLUGIN_NAME, "Node creation callback for system container node failed");
			goto error_out;
		}
	}

	error = sr_edit_batch(session, system_container_node, "merge");
	if (error != SR_ERR_OK) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "sr_edit_batch() error (%d): %s", error, sr_strerror(error));
		goto error_out;
	}

	error = sr_apply_changes(session, 0);
	if (error != 0) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "sr_apply_changes() error (%d): %s", error, sr_strerror(error));
		goto error_out;
	}

	goto out;

error_out:
	error = -1;

out:
	if (system_container_node) {
		lyd_free_tree(system_container_node);
	}
	sr_release_context(conn_ctx);
	return error;
}

int system_startup_apply_data(system_ctx_t *ctx, sr_session_ctx_t *session)
{
	int error = 0;
	return error;
}

static int system_startup_load_hostname(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node)
{
	int error = 0;
	char hostname_buffer[SYSTEM_HOSTNAME_LENGTH_MAX] = {0};

	error = gethostname(hostname_buffer, sizeof(hostname_buffer));
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "gethostname() error: %s", strerror(errno));
		goto error_out;
	}

	error = system_ly_tree_create_hostname(ly_ctx, parent_node, hostname_buffer);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "system_ly_tree_create_hostname() error (%d)", error);
		goto error_out;
	}

	goto out;

error_out:
	error = -1;

out:
	return error;
}

static int system_startup_load_contact(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node)
{
	int error = 0;
	return error;
}

static int system_startup_load_location(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node)
{
	int error = 0;
	return error;
}

static int system_startup_load_timezone_name(system_ctx_t *ctx, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx, struct lyd_node *parent_node)
{
	int error = 0;
	char timezone_name_buffer[PATH_MAX] = {0};
	char timezone_path_buffer[PATH_MAX] = {0};
	struct lyd_node *clock_container_node = NULL;

	ssize_t len = 0;
	size_t start = 0;

	len = readlink(SYSTEM_LOCALTIME_FILE, timezone_path_buffer, sizeof(timezone_path_buffer) - 1);
	if (len == -1) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "readlink() error");
		goto error_out;
	}

	// terminate path
	timezone_path_buffer[len] = 0;

	// assert start is equal to the timezone dir path
	if (strncmp(timezone_path_buffer, SYSTEM_TIMEZONE_DIR, sizeof(SYSTEM_TIMEZONE_DIR) - 1) != 0) {
		goto error_out;
	}

	// fetch the rest of the path into timezone_name_buffer
	start = sizeof(SYSTEM_TIMEZONE_DIR);
	strcpy(timezone_name_buffer, &timezone_path_buffer[start]);

	// setup clock container
	error = system_ly_tree_create_clock_container(ly_ctx, parent_node, &clock_container_node);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "system_ly_tree_create_clock_container() error (%d)", error);
		goto error_out;
	}

	// set timezone-name leaf
	error = system_ly_tree_create_timezone_name(ly_ctx, clock_container_node, timezone_name_buffer);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "system_ly_tree_create_timezone_name() error (%d)", error);
		goto error_out;
	}

	goto out;

error_out:
	error = -1;

out:
	return error;
}