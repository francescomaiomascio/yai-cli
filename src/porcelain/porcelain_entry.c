/* SPDX-License-Identifier: Apache-2.0 */

#include <yai_cli/porcelain/porcelain.h>
#include <yai_cli/porcelain/porcelain_parse.h>
#include <yai_cli/porcelain/porcelain_help.h>
#include <yai_cli/porcelain/porcelain_errors.h>
#include <yai_cli/porcelain/porcelain_output.h>

#include <yai_cli/ops/ops_dispatch.h>

#include <stdio.h>
#include <string.h>

int yai_porcelain_run(int argc, char** argv)
{
    // 1) parse args into a normalized request
    yai_porcelain_req_t req;
    memset(&req, 0, sizeof(req));

    int prc = yai_porcelain_parse(argc, argv, &req);
    if (prc != 0) {
        // parse layer decides if it already printed a message
        // but we always return contract-violation style code
        return 2;
    }

    // 2) help routing (explicit help or no command)
    if (req.want_help || !req.command || !req.command[0]) {
        return yai_porcelain_help(&req);
    }

    // 3) dispatch to ops (registry-driven path should already have resolved canonical id)
    int rc = yai_ops_dispatch(&req);

    // 4) output / post-processing (optional: normalize to json/text)
    return yai_porcelain_output_finalize(&req, rc);
}