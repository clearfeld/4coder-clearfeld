enum{
    SureToReopen_NULL = 0,
    SureToReopen_No = 1,
    SureToReopen_Yes = 2,
};


function b32
do_reopen_user_check(Application_Links *app, Buffer_ID buffer, View_ID view) {
    Scratch_Block scratch(app);
    Lister_Choice_List list = {};
    lister_choice(scratch, &list, "(N)o"  , "", KeyCode_N, SureToReopen_No);
    lister_choice(scratch, &list, "(Y)es" , "", KeyCode_Y, SureToReopen_Yes);

    Lister_Choice *choice = get_choice_from_user(app, "File has changed, reopen?", list);

    b32 do_reopen = false;
    if(choice != 0) {
        switch(choice->user_data) {
            case SureToReopen_No:
            {}
            break;

            case SureToReopen_Yes:
            {
                do_reopen = true;
            }
            break;
        }
    }

    return do_reopen;
}

function void
reopen_safely(Application_Links *app) {
    View_ID view_id = get_active_view(app, Access_ReadWriteVisible);
    Buffer_ID buffer_id = view_get_buffer(app, view_id, Access_ReadWriteVisible);
    Dirty_State dirty = buffer_get_dirty_state(app, buffer_id);

    if(HasFlag(dirty, DirtyState_UnsavedChanges) || HasFlag(dirty, DirtyState_UnloadedChanges)) {
        b32 should_reopen = do_reopen_user_check(app, buffer_id, view_id);
        if(should_reopen) {
            reopen(app);
        }
    } else {
        reopen(app);
    }
}

CUSTOM_COMMAND_SIG(reopen_buffer_safely)
CUSTOM_DOC("Check buffer state before reopening file.")
{
    reopen_safely(app);
}
