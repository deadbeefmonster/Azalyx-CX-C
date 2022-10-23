//
// Created by Chris Humphries on 7/11/22.
//

#ifndef BLITZKRIEG_CLI_ARGUMENTS_H
#define BLITZKRIEG_CLI_ARGUMENTS_H

#include <glib.h>
#include <glib/gi18n.h>

#include "configuration.h"

void cli_arguments_parse(gchar**, struct settings*);

#endif //BLITZKRIEG_CLI_ARGUMENTS_H
