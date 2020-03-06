/**
   Description

   NOTE: These commands are only needed if you have the filebar at the
   bottom of the buffer instead of the top.

   These commands replicate the default mouse button left click,
   release, and move functions with a offset of one row so the cursor
   will be at the correct mouse position.
 */

CUSTOM_COMMAND_SIG(clearfeld_click_set_cursor_and_mark)
CUSTOM_DOC("Sets the cursor position and mark to the mouse position.")
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Mouse_State mouse = get_mouse_state(app);

    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    Face_ID face_id = get_face_id(app, buffer);
    Face_Metrics face_metrics = get_face_metrics(app, face_id);
    f32 line_height = face_metrics.line_height;
    mouse.p.y += (i32)line_height;

    i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
    view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
    view_set_mark(app, view, seek_pos(pos));
}

CUSTOM_COMMAND_SIG(clearfeld_click_set_cursor)
CUSTOM_DOC("Sets the cursor position to the mouse position.")
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Mouse_State mouse = get_mouse_state(app);

    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    Face_ID face_id = get_face_id(app, buffer);
    Face_Metrics face_metrics = get_face_metrics(app, face_id);
    f32 line_height = face_metrics.line_height;
    mouse.p.y += (i32)line_height;

    i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
    view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
    no_mark_snap_to_cursor(app, view);
}

CUSTOM_COMMAND_SIG(clearfeld_click_set_cursor_if_lbutton)
CUSTOM_DOC("If the mouse left button is pressed, sets the cursor position to the mouse position.")
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Mouse_State mouse = get_mouse_state(app);
    if(mouse.l) {
        Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
        Face_ID face_id = get_face_id(app, buffer);
        Face_Metrics face_metrics = get_face_metrics(app, face_id);
        f32 line_height = face_metrics.line_height;
        mouse.p.y += (i32)line_height;

        i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
        view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
    }
    no_mark_snap_to_cursor(app, view);
}
