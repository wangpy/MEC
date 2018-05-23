#include "../m_pd.h"

#include <KontrolModel.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>

static t_class *KontrolModule_class;

typedef struct _KontrolModule {
    t_object x_obj;
    t_symbol* rackId;
    t_symbol* moduleId;
    t_symbol* moduleType;
    char* modId;
    char* modType;
} t_KontrolModule;


//define pure data methods
extern "C" {
void KontrolModule_free(t_KontrolModule *);
void *KontrolModule_new(t_symbol *name, t_symbol *type);
EXTERN void KontrolModule_setup(void);
void KontrolModule_loaddefinitions(t_KontrolModule *x, t_symbol *defs);
}
// puredata methods implementation - start

void KontrolModule_free(t_KontrolModule *x) {
    free(x->modId);
    free(x->modType);
}

static bool createModule(t_KontrolModule *x) {
    auto rack = Kontrol::KontrolModel::model()->getLocalRack();
    if (rack) {
        auto rackId = rack->id();
        Kontrol::EntityId moduleId = x->modId;
        std::string moduleType = x->modType;
        Kontrol::KontrolModel::model()->createModule(Kontrol::CS_LOCAL, rackId,
            moduleId, moduleType,
            moduleType);
        rack->dumpParameters();
        x->rackId = gensym(rackId.c_str());
        x->moduleId = gensym(moduleId.c_str());
        x->moduleType = gensym(moduleType.c_str());
        return true;
    }

    return false;
}

void *KontrolModule_new(t_symbol *name, t_symbol *type) {
    t_KontrolModule *x = (t_KontrolModule *) pd_new(KontrolModule_class);
    if (name && name->s_name && type && type->s_name) {
        x->modId = strdup(name->s_name);
        x->modType = strdup(type->s_name);
        createModule(x);
    }
    return (void *) x;
}

void KontrolModule_setup(void) {
    KontrolModule_class = class_new(gensym("KontrolModule"),
                                    (t_newmethod) KontrolModule_new,
                                    (t_method) KontrolModule_free,
                                    sizeof(t_KontrolModule),
                                    CLASS_DEFAULT,
                                    A_SYMBOL, A_SYMBOL, A_NULL);
    class_addmethod(KontrolModule_class,
                    (t_method) KontrolModule_loaddefinitions, gensym("loaddefinitions"),
                    A_DEFSYMBOL, A_NULL);
}


void KontrolModule_loaddefinitions(t_KontrolModule *x, t_symbol *defs) {
    if (defs != nullptr && defs->s_name != nullptr && strlen(defs->s_name) > 0) {
        if (x->moduleId == nullptr) {
            if (!createModule(x)) {
                post("cannot create %s : No local rack found, KontrolModule needs a KontrolRack instance", x->modId);
            }
        }
        std::string file = std::string(defs->s_name);
        Kontrol::KontrolModel::model()->loadModuleDefinitions(x->rackId->s_name, x->moduleId->s_name, file);
    }
}




// puredata methods implementation - end

