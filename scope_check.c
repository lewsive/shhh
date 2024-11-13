#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "id_attrs.h"
#include "file_location.h"
#include "ast.h"
#include "utilities.h"
#include "symtab.h"
#include "scope_check.h"



block_t scope_check_program(block_t prog){
    symtab_enter_scope();

    scope_check_const_decls(prog.const_decls);
    scope_check_var_decls(prog.var_decls);
    scope_check_proc_decls(prog.proc_decls);
    scope_check_stmts(prog.stmts);

    symtab_leave_scope();
    return prog;
}

//scope checks const_decls
void scope_check_const_decls(const_decls_t decls){
    const_decl_t* constDecl = decls.start;
    while(constDecl != NULL){
        //chech each def in def_list
        const_def_t* constDef = constDecl->const_def_list.start;

        while(constDef != NULL){
            const char* name = constDef->ident.name;

            id_attrs *attrs = create_id_attrs(*constDef->ident.file_loc, constant_idk, symtab_scope_loc_count());

            //check for already declared error
            if(!symtab_declared_in_current_scope(name) && attrs != NULL){
                symtab_insert(name, attrs);
            }
            else{
                int kind = symtab_lookup(name)->attrs->kind;//gets the type of what the name was declared as originally

                //checks if the previously declared name was a constant or a variable
                if(kind == 0){ //constant
                    bail_with_prog_error(*constDef->file_loc, "constant \"%s\" is already declared as a constant", name);
                }
                else{ //variable 
                    bail_with_prog_error(*constDef->file_loc, "constant \"%s\" is already declared as a variable", name);
                }
            }
            //scope_check_const_delc(*constDecl->next); I don't think we need this
            constDef = constDef->next;
        }
        constDecl = constDecl->next;
    }
}

void scope_check_var_decls(var_decls_t decls)
{
    //implement kind of same as constant check
    var_decl_t* varDecl = decls.var_decls;

    while(varDecl != NULL){
        ident_t *identLi = varDecl->ident_list.start;

        while(identLi != NULL){
            const char* name = identLi->name;

            id_attrs *attrs = create_id_attrs(*identLi->file_loc, variable_idk, symtab_scope_loc_count());

             //check for already declared error
            if(!symtab_declared_in_current_scope(name) && attrs != NULL){
                symtab_insert(name, attrs);
            }
            else{
                int kind = symtab_lookup(name)->attrs->kind; //gets the type of what the name was declared as originally

                //checks if the previously declared name was a constant or a variable
                if(kind == 0){ //constant
                    bail_with_prog_error(*identLi->file_loc, "variable \"%s\" is already declared as a constant", name);
                }
                else{ //variable 
                    bail_with_prog_error(*identLi->file_loc, "variable \"%s\" is already declared as a variable", name);
                }
            }

            identLi=identLi->next;

        }
        varDecl = varDecl->next;
    }
    
}

void scope_check_proc_decls(proc_decls_t decls)
{

}

void scope_check_stmts(stmts_t stmts)
{

}
