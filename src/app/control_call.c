/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/control_call.h"

#include <cJSON.h>

#include <string.h>

static const char *infer_target_plane(const char *command_id, int argc, char **argv)
{
  for (int i = 0; i + 1 < argc; i++) {
    if (argv && argv[i] && argv[i + 1] && strcmp(argv[i], "--target-plane") == 0) {
      return argv[i + 1];
    }
  }
  if (!command_id) return "kernel";
  if (strncmp(command_id, "yai.root.", 9) == 0) return "root";
  if (strncmp(command_id, "yai.engine.", 11) == 0) return "engine";
  return "kernel";
}

char *yai_build_control_call_json(const char *command_id, int argc, char **argv)
{
  if (!command_id || !command_id[0]) return NULL;

  cJSON *root = cJSON_CreateObject();
  if (!root) return NULL;

  cJSON_AddStringToObject(root, "type", "yai.control.call.v1");
  cJSON_AddStringToObject(root, "target_plane", infer_target_plane(command_id, argc, argv));
  cJSON_AddStringToObject(root, "command_id", command_id);

  cJSON *arr = cJSON_AddArrayToObject(root, "argv");
  for (int i = 0; i < argc; i++) {
    cJSON_AddItemToArray(arr, cJSON_CreateString((argv && argv[i]) ? argv[i] : ""));
  }

  char *json = cJSON_PrintUnformatted(root);
  cJSON_Delete(root);
  return json;
}

