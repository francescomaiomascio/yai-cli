/* SPDX-License-Identifier: Apache-2.0 */

#include <assert.h>
#include <string.h>

#include "yai_cli/parse.h"

static void test_valid_root_ping(void)
{
    char *argv[] = {"yai", "root", "ping", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(3, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_COMMAND);
    assert(req.command_id != NULL);
    assert(strcmp(req.command_id, "yai.root.ping") == 0);
    assert(req.error == NULL);
}

static void test_valid_verbose_contract(void)
{
    char *argv[] = {"yai", "--verbose-contract", "root", "ping", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(4, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_COMMAND);
    assert(req.verbose_contract == 1);
    assert(strcmp(req.command_id, "yai.root.ping") == 0);
    assert(req.error == NULL);
}

static void test_builtin_lifecycle(void)
{
    char *argv[] = {"yai", "lifecycle", "up", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(3, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_COMMAND);
    assert(strcmp(req.command_id, "yai.lifecycle.up") == 0);
}

static void test_invalid_group(void)
{
    char *argv[] = {"yai", "wat", "ping", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(3, argv, &req);
    assert(rc != 0);
    assert(req.kind == YAI_PORCELAIN_KIND_ERROR);
    assert(req.error != NULL);
    assert(strcmp(req.error, "Unknown command group: wat") == 0);
    assert(req.error_hint != NULL);
    assert(strcmp(req.error_hint, "Run: yai help --groups") == 0);
}

static void test_help_group_command(void)
{
    char *argv[] = {"yai", "help", "root", "ping", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(4, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_HELP);
    assert(req.help_token != NULL);
    assert(strcmp(req.help_token, "root") == 0);
    assert(req.help_token2 != NULL);
    assert(strcmp(req.help_token2, "ping") == 0);
}

static void test_watch_parse(void)
{
    char *argv[] = {"yai", "watch", "root", "ping", "--count", "2", "--interval", "0.05", "--no-clear", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(9, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_WATCH);
    assert(req.cmd_argc == 7);
    assert(strcmp(req.cmd_argv[0], "root") == 0);
    assert(strcmp(req.cmd_argv[1], "ping") == 0);
    assert(req.watch_count == 2);
    assert(req.watch_interval_ms == 50);
    assert(req.watch_no_clear == 1);
}

static void test_watch_once_parse(void)
{
    char *argv[] = {"yai", "watch", "root", "ping", "--once", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(5, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_WATCH);
    assert(req.watch_count == 1);
}

static void test_group_without_command_prints_help(void)
{
    char *argv[] = {"yai", "root", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(2, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_HELP);
    assert(req.help_token != NULL);
    assert(strcmp(req.help_token, "root") == 0);
    assert(req.help_exit_code == 20);
}

static void test_color_mode_parse(void)
{
    char *argv[] = {"yai", "--color=never", "root", "ping", NULL};
    yai_porcelain_request_t req;
    int rc = yai_porcelain_parse_argv(4, argv, &req);
    assert(rc == 0);
    assert(req.kind == YAI_PORCELAIN_KIND_COMMAND);
    assert(req.color_mode == YAI_COLOR_NEVER);
}

int main(void)
{
    test_valid_root_ping();
    test_valid_verbose_contract();
    test_builtin_lifecycle();
    test_invalid_group();
    test_help_group_command();
    test_watch_parse();
    test_watch_once_parse();
    test_group_without_command_prints_help();
    test_color_mode_parse();
    return 0;
}
