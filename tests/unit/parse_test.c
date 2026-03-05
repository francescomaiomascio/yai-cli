/* SPDX-License-Identifier: Apache-2.0 */

#include <assert.h>
#include <string.h>

#include "yai_cli/porcelain/porcelain_parse.h"

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
    assert(strcmp(req.error, "unknown command group") == 0);
    assert(req.error_hint != NULL);
    assert(strcmp(req.error_hint, "yai help --groups") == 0);
}

int main(void)
{
    test_valid_root_ping();
    test_valid_verbose_contract();
    test_builtin_lifecycle();
    test_invalid_group();
    return 0;
}
