global b32 highlight_region_active = false;

FColor region_highlight_color = fcolor_argb(1.f, 0.5f, 0.5f, 0.2f);

void
clearfeld_draw_highlight_region(Application_Links *app, View_ID view_id,
                                Text_Layout_ID text_layout_id, Rect_f32 rect)
{
    i64 cursor_pos = view_get_cursor_pos(app, view_id);
    i64 mark_pos = view_get_mark_pos(app, view_id);

    Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_pos));
    Buffer_Cursor mark = view_compute_cursor(app, view_id, seek_pos(mark_pos));

    Rect_f32 cursor_char_rect = text_layout_character_on_screen(app, text_layout_id, cursor_pos);
    Rect_f32 mark_char_rect = text_layout_character_on_screen(app, text_layout_id, mark_pos);

    if(cursor.line > mark.line) {
        draw_rectangle_fcolor(app,
                              {
                                  rect.x0, mark_char_rect.y1,
                                  rect.x1, cursor_char_rect.y0
                              },
                              0, region_highlight_color);
        //mark
        draw_rectangle_fcolor(app,
                              {
                                  mark_char_rect.x1, mark_char_rect.y0,
                                  rect.x1, mark_char_rect.y1
                              },
                              0, region_highlight_color);
        //cursor
        draw_rectangle_fcolor(app,
                              {
                                  cursor_char_rect.x0, cursor_char_rect.y0,
                                  rect.x0, cursor_char_rect.y1
                              },
                              0, region_highlight_color);

    } else if(cursor.line < mark.line) {
        draw_rectangle_fcolor(app,
                              {
                                  rect.x0, cursor_char_rect.y1,
                                  rect.x1, mark_char_rect.y0
                              },
                              0, region_highlight_color);

        //mark
        draw_rectangle_fcolor(app,
                              {
                                  mark_char_rect.x0, mark_char_rect.y0,
                                  rect.x0, mark_char_rect.y1
                              },
                              0, region_highlight_color);
        //cursor
        draw_rectangle_fcolor(app,
                              {
                                  cursor_char_rect.x1, cursor_char_rect.y0,
                                  rect.x1, cursor_char_rect.y1
                              },
                              0, region_highlight_color);
    } else {
        if(cursor.col > mark.col) {
            draw_rectangle_fcolor(app,
                                  {
                                      cursor_char_rect.x0, cursor_char_rect.y0,
                                      mark_char_rect.x1, mark_char_rect.y1
                                  },
                                  0, region_highlight_color);
        } else if(cursor.col < mark.col) {
            draw_rectangle_fcolor(app,
                                  {
                                      mark_char_rect.x0, mark_char_rect.y0,
                                      cursor_char_rect.x1, cursor_char_rect.y1
                                  },
                                  0, region_highlight_color);
        }
    }
}

CUSTOM_COMMAND_SIG(emacs_style_region_highlight_quit)
CUSTOM_DOC("Stop the highlight of the given region (purely visual, region still active)")
{
    highlight_region_active = false;
}

CUSTOM_COMMAND_SIG(clearfeld_set_mark)
CUSTOM_DOC("Set mark and highlight region")
{
    set_mark(app);
    highlight_region_active = true;
}
