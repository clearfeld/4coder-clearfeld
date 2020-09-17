global b32 use_relative_line_number_mode = false;

function void
draw_relative_line_number_margin(Application_Links *app, View_ID view_id, Buffer_ID buffer, Face_ID face_id, Text_Layout_ID text_layout_id, Rect_f32 margin)
{
    ProfileScope(app, "clearfeld - draw relative line number margin");

    Scratch_Block scratch(app);
    FColor line_color = fcolor_id(defcolor_line_numbers_text);

    Rect_f32 prev_clip = draw_set_clip(app, margin);
    draw_rectangle_fcolor(app, margin, 0.f, fcolor_id(defcolor_line_numbers_back));

    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    i64 line_count = buffer_get_line_count(app, buffer);
    i64 line_count_digit_count = digit_count_from_integer(line_count, 10);

    Buffer_Cursor cursor_top = view_compute_cursor(app, view_id, seek_pos(visible_range.min));
    i64 top_line = cursor_top.line;

    FColor current_line_color = fcolor_id(defcolor_cursor);

    i64 cursor_line = view_get_cursor_pos(app, view_id);
    Buffer_Cursor cursor_current_line = view_compute_cursor(app, view_id, seek_pos(cursor_line));
    cursor_line = cursor_current_line.line;

    Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(visible_range.first));
    i64 line_number = cursor.line;

    i64 below_count = cursor_line - top_line;
    i64 above_count = 1;

    Buffer_Cursor cursor_opl = view_compute_cursor(app, view_id, seek_pos(visible_range.one_past_last));
    i64 one_past_last_line_number = cursor_opl.line + 1;

    for (;line_number < one_past_last_line_number &&
          line_number < line_count;)
    {
        Range_f32 line_y = text_layout_line_on_screen(app, text_layout_id, line_number);
        Vec2_f32 p = V2f32(margin.x0, line_y.min);
        Temp_Memory_Block temp(scratch);
        // TODO: replace push_fancy_stringf with the below to avoid
        // using the temp memory block and be more inline with the new draw line number
        // margin function in 4.1.6
        //
        // Fancy_String fstring = {};
        // fill_fancy_string(&fstring, 0, line_color, 0, 0, digit_string);
        // draw_fancy_string(app, face_id, fcolor_zero(), &fstring, p);

        Fancy_String *string;
        if(line_number < cursor_line) {
            string = push_fancy_stringf(scratch, 0, line_color, "%*lld",
                                        line_count_digit_count, below_count);
            --below_count;
        } else if(line_number > cursor_line) {
            string = push_fancy_stringf(scratch, 0, line_color, "%*lld",
                                        line_count_digit_count, above_count);
            ++above_count;
        } else {
			string = push_fancy_stringf(scratch, 0, current_line_color, "%*lld",
                                        line_count_digit_count, line_number);
        }

        draw_fancy_string(app, face_id, fcolor_zero(), string, p);
        line_number += 1;
    }

    draw_set_clip(app, prev_clip);
}

CUSTOM_COMMAND_SIG(toggle_relative_line_number_mode)
CUSTOM_DOC("Toggle relative line numbers.")
{
    use_relative_line_number_mode = !use_relative_line_number_mode;
    if(use_relative_line_number_mode) {
        log_string(app, string_u8_litexpr("Toggle: relative_line_number_mode - on\n"));
    } else {
        log_string(app, string_u8_litexpr("Toggle: relative_line_number_mode - off\n"));
    }
}
