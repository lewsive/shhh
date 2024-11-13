#ifndef _SCOPE_CHECK_H
#define _SCOPE_CHECK_H
#include "ast.h"
#include "id_use.h"

extern block_t scope_check_program(block_t prog);

extern void scope_check_const_decls(const_decls_t decls);

extern void scope_check_var_decls(var_decls_t decls);

extern void scope_check_proc_decls(proc_decls_t decls);

extern void scope_check_stmts(stmts_t stmts);

#endif
