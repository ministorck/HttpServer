#ifndef PUBLICSTRUCT_H
#define PUBLICSTRUCT_H
struct ThreadModelStruct{
    void* s_id;
    bool s_state;
    QString s_explain;
    ThreadModelStruct():s_state(false)
    {

    }
};

enum SAction{
    SAction_Add = 0,
    SAction_Del,
    SAction_Update
};

#endif // PUBLICSTRUCT_H
