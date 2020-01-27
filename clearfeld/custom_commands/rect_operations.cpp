#include <sstream>
#include <iostream>
#include <vector>

// TODO: IMPORTANT: remove std::string vector and sstream and use 4coder internal string types and functions
// TODO: IMPORTANT: check against different line endings

CUSTOM_COMMAND_SIG(kill_rect)
CUSTOM_DOC("Cuts the content between the mark and cursor as a rectangle.")
{
    Scratch_Block scratch(app);
    View_ID view_id = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer_id = view_get_buffer(app, view_id, Access_ReadVisible);

    i64 cursor_pos = view_get_cursor_pos(app, view_id);
    i64 mark_pos = view_get_mark_pos(app, view_id);

    Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_pos));
    Buffer_Cursor mark = view_compute_cursor(app, view_id, seek_pos(mark_pos));

	i64 start_line, end_line;
	i64 start_pos, end_pos;

	if (cursor.line > mark.line) {
		start_line = mark.line;
		end_line = cursor.line;
	} else {
		start_line = cursor.line;
		end_line = mark.line;
	}

	if (cursor.col > mark.col) {
		start_pos = mark.col;
		end_pos = cursor.col;
	} else {
		start_pos = cursor.col;
		end_pos = mark.col;
	}

	std::string a;

	for (i64 i = start_line; i < end_line + 1; ++i) {
		String_Const_u8 current_line = push_buffer_line(app, scratch, buffer_id, i);

		view_set_mark(app, view_id, seek_line_col(i, start_pos));
		view_set_cursor(app, view_id, seek_line_col(i, end_pos));

		// NOTE: start_pos - 1 to capute the char under the mark/cursor
		for (i64 j = start_pos - 1; j < end_pos; ++j) {
			if (current_line.str[j] == '\0') {
				a += "";
			}
			else {
				a += current_line.str[j];
            }
		}

		a += "\n";
		
		// TODO: IMPORTANT: figure out how to perform actions without having 
		// each one go onto the undo stack
		delete_range(app);
		delete_char(app);
	}

	clipboard_post(app, 0, SCu8((char*)a.c_str()));
}

CUSTOM_COMMAND_SIG(copy_rect)
CUSTOM_DOC("Copies the content between the mark and cursor as a rectangle.")
{
	Scratch_Block scratch(app);
	View_ID view_id = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer_id = view_get_buffer(app, view_id, Access_ReadVisible);

	i64 cursor_pos = view_get_cursor_pos(app, view_id);
	i64 mark_pos = view_get_mark_pos(app, view_id);

	Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_pos));
	Buffer_Cursor mark = view_compute_cursor(app, view_id, seek_pos(mark_pos));

	i64 start_line, end_line;
	i64 start_pos, end_pos;

	if (cursor.line > mark.line) {
		start_line = mark.line;
		end_line = cursor.line;
	} else {
		start_line = cursor.line;
		end_line = mark.line;
	}

	if (cursor.col > mark.col) {
		start_pos = mark.col;
		end_pos = cursor.col;
	} else {
		start_pos = cursor.col;
		end_pos = mark.col;
	}

	std::string a;

	for (i64 i = start_line; i < end_line + 1; ++i) {
		String_Const_u8 current_line = push_buffer_line(app, scratch, buffer_id, i);

		// NOTE: start_pos - 1 to capute the char under the mark/cursor
		for (i64 j = start_pos - 1; j < end_pos; ++j) {
			if (current_line.str[j] == '\0') {
				a += "";
			}
			else {
				a += current_line.str[j];
			}
		}

		a += "\n";
	}

	clipboard_post(app, 0, SCu8((char*)a.c_str()));
}

CUSTOM_COMMAND_SIG(paste_rect_repeating)
CUSTOM_DOC("Pastes the content at the top of the clipboard as a rectangle (repeats).")
{
	Scratch_Block scratch(app);
	String_Const_u8 clipboard_string = push_clipboard_index(app, scratch, 0, 0);
	
	std::vector<std::string> strings;
	std::istringstream f((char *)clipboard_string.str);
	std::string s;
	while (getline(f, s, '\n')) {
		strings.push_back(s);
	}

	View_ID view_id = get_active_view(app, Access_ReadVisible);
	
	i64 cursor_pos = view_get_cursor_pos(app, view_id);
	i64 mark_pos = view_get_mark_pos(app, view_id);

	Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_pos));
	Buffer_Cursor mark = view_compute_cursor(app, view_id, seek_pos(mark_pos));

	i64 start_line, end_line;

	if (cursor.line > mark.line) {
		start_line = mark.line;
		end_line = cursor.line;
	}
	else {
		start_line = cursor.line;
		end_line = mark.line;
	}

	if (cursor.col != mark.col) {
		// Maybe draw a red fade to indicate error?
		return;
	}

	size_t st = strings.size();
	int j = 0;

	for (i64 i = start_line; i < end_line + 1; ++i) {
		view_set_cursor(app, view_id, seek_line_col(i, cursor.col));
		write_text(app, SCu8((char *)strings.at(j).c_str()));
		++j;
		if (j == st) {
			j = 0;
		}
	}
}

CUSTOM_COMMAND_SIG(paste_rect_naive)
CUSTOM_DOC("Pastes the content at the top of the clipboard as a rectangle.")
{
	Scratch_Block scratch(app);
	String_Const_u8 clipboard_string = push_clipboard_index(app, scratch, 0, 0);

	std::vector<std::string> strings;
	std::istringstream f((char*)clipboard_string.str);
	std::string s;
	while (getline(f, s, '\n')) {
		strings.push_back(s);
	}

	View_ID view_id = get_active_view(app, Access_ReadVisible);

	i64 cursor_pos = view_get_cursor_pos(app, view_id);
	i64 mark_pos = view_get_mark_pos(app, view_id);

	Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_pos));
	Buffer_Cursor mark = view_compute_cursor(app, view_id, seek_pos(mark_pos));

	i64 start_line, end_line;

	if (cursor.line > mark.line) {
		start_line = mark.line;
		end_line = cursor.line;
	}
	else {
		start_line = cursor.line;
		end_line = mark.line;
	}

	if (cursor.col != mark.col) {
		// Maybe draw a red fade to indicate error?
		return;
	}

	size_t st = strings.size();
	int j = 0;

	for (i64 i = start_line; i < end_line + 1; ++i) {
		view_set_cursor(app, view_id, seek_line_col(i, cursor.col));
		write_text(app, SCu8((char*)strings.at(j).c_str()));
		++j;
		if (j == st) {
			break;
		}
	}
}