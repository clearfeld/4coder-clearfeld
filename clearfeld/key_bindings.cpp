//#include "hydra.cpp"

#include "custom_commands/reopen_safely.cpp"
#include "custom_commands/other_panel_commands.cpp"
#include "custom_commands/rect_operations.cpp"
//#include "custom_commands/align_regexp.cpp"
#include "custom_commands/windmove.cpp"

#if OS_WINDOWS
# define CLEARFELD_KEYCODE_RIGHT_META KeyCode_Alt
#elif OS_MAC
# define CLEARFELD_KEYCODE_RIGHT_META KeyCode_Command
//#elif OS_LINUX
//#define SLASH KeyCode_
#else
# error No support for this platform.
#endif


function void
clearfeld_set_bindings(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id)
{
    MappingScope();
    //~ Global

    SelectMapping(mapping);
    SelectMap(global_id);
    {
        BindCore(default_startup, CoreCode_Startup);
        BindCore(default_try_exit, CoreCode_TryExit);

        //( (kbd "M-j") #'imenu)
        // ;; editing
        // ( (kbd "M-z") #'yas-next-field-or-maybe-expand)
        // ( (kbd "M-Z") #'yas-expand)
        // ( (kbd "C-S-D") #'kill-word)
        // ( (kbd "C-d") #'delete-forward-char)
        // ( (kbd "<M-backspace>") #'backward-kill-word)
        // ( (kbd "M-d") #'delete-forward-char)
        // ( (kbd "M-D") #'kill-word)
        // ( (kbd "M-5") #'upcase-word)
        // ( (kbd "M-/") #'c-mark-function)
        // ( (kbd "M-.") #'fill-paragraph)
        // ;; compliation and find errors
        // ( (kbd "M-m")  #'make-without-asking-small)
        // ( (kbd "M-M")  #'make-without-asking-full)
        // ( (kbd "<f5>") #'first-error)
        // ( (kbd "<f6>") #'previous-error)
        // ( (kbd "<f7>") #'next-error)
        // ( (kbd "M-n")  #'next-error)
        // ( (kbd "M-N")  #'previous-error)
        //( (kbd "M-\\") #'load-todo-file)
        //( (kbd "M-T")  #'load-log)
        // ;; Alignment
        // ( (kbd "M-=") #'align-regexp)

        // testing
        // Bind(hydra_chord_test, KeyCode_1, KeyCode_Control);
        // Bind(open_default_keybindings_cheatsheet, KeyCode_F2);

        // Macro
        Bind(keyboard_macro_start_recording, KeyCode_LeftBracket, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(keyboard_macro_finish_recording, KeyCode_RightBracket, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(keyboard_macro_replay, KeyCode_Quote, CLEARFELD_KEYCODE_RIGHT_META);

        // TODO: Add to hydra
        // Bind(toggle_filebar, KeyCode_B, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(command_lister,                KeyCode_X, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(project_command_lister,        KeyCode_X, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        // Bind(project_go_to_root_directory,  KeyCode_H, KeyCode_Control);
        // Bind(goto_next_jump,                KeyCode_N, CLEARFELD_KEYCODE_RIGHT_META);
        // Bind(goto_prev_jump,                KeyCode_N, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        // Bind(goto_first_jump,               KeyCode_M, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        // Bind(project_fkey_command, KeyCode_F1);
        // ...
        // Bind(project_fkey_command, KeyCode_F16);

        // Arrow based keys
        Bind(move_up_to_blank_line_skip_whitespace, KeyCode_Up, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_down_to_blank_line_skip_whitespace, KeyCode_Down, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(move_line_up, KeyCode_Up, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(move_line_down, KeyCode_Down, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        // TODO: add buffer movement as well with shift modifier
        Bind(windmove_panel_up, KeyCode_Up, KeyCode_Control);
        Bind(windmove_panel_down, KeyCode_Down, KeyCode_Control);
        Bind(windmove_panel_left, KeyCode_Left, KeyCode_Control);
        Bind(windmove_panel_right, KeyCode_Right, KeyCode_Control);

        Bind(windmove_panel_swap_up, KeyCode_Up, KeyCode_Control, KeyCode_Shift);
        Bind(windmove_panel_swap_down, KeyCode_Down, KeyCode_Control, KeyCode_Shift);
        Bind(windmove_panel_swap_left, KeyCode_Left, KeyCode_Control, KeyCode_Shift);
        Bind(windmove_panel_swap_right, KeyCode_Right, KeyCode_Control, KeyCode_Shift);

        Bind(seek_beginning_of_line, KeyCode_Home);
        Bind(seek_end_of_line, KeyCode_End);

        Bind(page_up, KeyCode_PageUp);
        Bind(page_down, KeyCode_PageDown);
        Bind(goto_beginning_of_file, KeyCode_PageUp, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(goto_end_of_file, KeyCode_PageDown, CLEARFELD_KEYCODE_RIGHT_META);

        // buffer shortcuts
        Bind(reopen_buffer_safely, KeyCode_R, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(kill_buffer, KeyCode_K, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(save, KeyCode_S, CLEARFELD_KEYCODE_RIGHT_META);

        // panel shortcuts
        Bind(open_panel_vsplit, KeyCode_3, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(open_panel_hsplit, KeyCode_3, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(close_panel, KeyCode_0, CLEARFELD_KEYCODE_RIGHT_META);

        // TODO:
        //Bind(close_all_except_active_panel, KeyCode_0, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        Bind(change_active_panel, KeyCode_W, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(change_active_panel_backwards, KeyCode_W, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        // TODO
        // Bind(shrink_panel_h, KeyCode_4, CLEARFELD_KEYCODE_RIGHT_META);
        // Bind(shrink_panel_v, KeyCode_4, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        // Bind(enlarge_panel_h, KeyCode_5, CLEARFELD_KEYCODE_RIGHT_META);
        // Bind(enlarge_panel_v, KeyCode_5, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        Bind(interactive_open_or_new, KeyCode_F, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(interactive_open_or_new_other_panel, KeyCode_F, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        Bind(interactive_switch_buffer, KeyCode_B, CLEARFELD_KEYCODE_RIGHT_META);
        // TODO: FIXME: Busted
        Bind(interactive_switch_buffer_other_panel, KeyCode_B, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        Bind(comment_line_toggle, KeyCode_Semicolon, CLEARFELD_KEYCODE_RIGHT_META);
        // TODO
        //Bind(add_comment_end_of_line, KeyCode_Semicolon, CLEARFELD_KEYCODE_RIGHT_META);
        // TODO replace comment_line_toggle with the below
        // ((kbd "M-;") #'comment-or-uncomment-region-or-line)

        // NOTE: look into function for range move lines
        Bind(auto_indent_range, KeyCode_Tab, KeyCode_Control);
        // TODO bind auto_indent_whole_file

        Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(delete_alpha_numeric_boundary, KeyCode_Delete, CLEARFELD_KEYCODE_RIGHT_META);
        // TODO
        //Bind(delete_alpha_numeric_boundary_forward, );

        Bind(set_mark, KeyCode_Space, KeyCode_Control);
        Bind(cursor_mark_swap, KeyCode_Space, KeyCode_Control, KeyCode_Shift);

        Bind(query_replace, KeyCode_O, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(replace_in_range, KeyCode_O, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        // text editing shortcuts
        Bind(copy, KeyCode_Q, KeyCode_Control);
        Bind(cut, KeyCode_W, KeyCode_Control);
        Bind(paste_and_indent, KeyCode_F, KeyCode_Control);
        //Bind(paste_next_and_indent, KeyCode_F, KeyCode_Control, KeyCode_Shift);
        Bind(undo, KeyCode_U, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(redo, KeyCode_Y, KeyCode_Control);
        Bind(delete_line, KeyCode_L, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(duplicate_line, KeyCode_L, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        // misc
        Bind(toggle_fullscreen, KeyCode_F11);
        Bind(goto_line, KeyCode_G, CLEARFELD_KEYCODE_RIGHT_META);

        // hydra chords
        // Bind(hydra_text_sizing, KeyCode_9, KeyCode_Menu);
        // Bind(hydra_bookmark, KeyCode_B, KeyCode_Menu);
        // Bind(hydra_misc, KeyCode_R, KeyCode_Menu);
        // Bind(hydra_eyebrowse, KeyCode_E, KeyCode_Menu);
        // Bind(hydra_kurecolor, KeyCode_C, KeyCode_Menu);
        // Bind(hydra_code_folding, KeyCode_V, KeyCode_Menu);
        // Bind(hydra_modes_toggle, KeyCode_M, KeyCode_Menu);
        // Bind(hydra_yasnippets, KeyCode_Y, KeyCode_Menu);
        // Bind(hydra_modes_test_command, KeyCode_0, KeyCode_Menu);

        // TODO: create hydra for rect operations
        // Bind(kill_rect, KeyCode_Y, KeyCode_Menu);
        // Bind(copy_rect, KeyCode_U, KeyCode_Menu);
        // Bind(paste_rect_naive, KeyCode_I, KeyCode_Menu);
        // Bind(paste_rect_repeating, KeyCode_O, KeyCode_Menu);

        //Bind(align_regexp, KeyCode_2, KeyCode_Menu);
        //Bind(emmet_expand, KeyCode_2, KeyCode_Menu);

        BindMouseWheel(mouse_wheel_scroll);
        BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);

        Bind(exit_4coder, KeyCode_F4, CLEARFELD_KEYCODE_RIGHT_META);
    }

    //~ File
    SelectMap(file_id);
    ParentMap(global_id);
    {
        Bind(delete_char,            KeyCode_Delete);
        Bind(backspace_char,         KeyCode_Backspace);

        Bind(move_up,                KeyCode_Up);
        Bind(move_down,              KeyCode_Down);
        Bind(move_left,              KeyCode_Left);
        Bind(move_right,             KeyCode_Right);

        Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(delete_alpha_numeric_boundary, KeyCode_Delete, CLEARFELD_KEYCODE_RIGHT_META);
        //Bind(snipe_backward_whitespace_or_token_boundary, KeyCode_Backspace, CLEARFELD_KEYCODE_RIGHT_META);
        //Bind(snipe_forward_whitespace_or_token_boundary,  KeyCode_Delete, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(goto_line, KeyCode_G, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(set_mark, KeyCode_Space, KeyCode_Control);
        // Bind(cursor_mark_swap, KeyCode_M, KeyCode_Control);

        // Bind(center_view,                 KeyCode_E, KeyCode_Control);
        // Bind(left_adjust_view,            KeyCode_E, KeyCode_Control, KeyCode_Shift);

        Bind(search, KeyCode_S, KeyCode_Control);
        // Bind(reverse_search, KeyCode_R, KeyCode_Control);

        // TODO: make a lister for the yasnippets loaded on a per language basis or file
        // Bind(snippet_lister, KeyCode_J, KeyCode_Control);

        Bind(if_read_only_goto_position, KeyCode_Return);
        Bind(if_read_only_goto_position_same_panel, KeyCode_Return, KeyCode_Shift);

        BindTextInput(write_text_input);
        BindMouse(click_set_cursor_and_mark, MouseCode_Left);
        BindMouseRelease(click_set_cursor, MouseCode_Left);
        BindCore(click_set_cursor_and_mark, CoreCode_ClickActivateView);
        BindMouseMove(click_set_cursor_if_lbutton);

        //Bind(open_default_keybindings_cheatsheet, KeyCode_F2);
        Bind(move_up_to_blank_line_skip_whitespace, KeyCode_Up, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_down_to_blank_line_skip_whitespace, KeyCode_Down, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(move_line_up, KeyCode_Up, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(move_line_down, KeyCode_Down, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        Bind(seek_beginning_of_line, KeyCode_Home);
        Bind(seek_end_of_line, KeyCode_End);

        Bind(page_up, KeyCode_PageUp);
        Bind(page_down, KeyCode_PageDown);

        Bind(goto_beginning_of_file, KeyCode_PageUp, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(goto_end_of_file, KeyCode_PageDown, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(reopen_buffer_safely, KeyCode_R, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(kill_buffer, KeyCode_K, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(save, KeyCode_S, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(open_panel_vsplit, KeyCode_3, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(open_panel_hsplit, KeyCode_3, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);

        Bind(close_panel, KeyCode_0, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(change_active_panel, KeyCode_W, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(change_active_panel_backwards, KeyCode_W, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(interactive_open_or_new, KeyCode_F, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(interactive_open_or_new_other_panel, KeyCode_F, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(interactive_switch_buffer, KeyCode_B, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(comment_line_toggle, KeyCode_Semicolon, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(auto_indent_range, KeyCode_Tab, KeyCode_Control);
        Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(delete_alpha_numeric_boundary, KeyCode_Delete, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(set_mark, KeyCode_Space, KeyCode_Control);
        Bind(cursor_mark_swap, KeyCode_Space, KeyCode_Control, KeyCode_Shift);
        Bind(query_replace, KeyCode_O, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(replace_in_range, KeyCode_O, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(copy, KeyCode_Q, KeyCode_Control);
        Bind(cut, KeyCode_W, KeyCode_Control);
        Bind(paste_and_indent, KeyCode_F, KeyCode_Control);
        Bind(undo, KeyCode_U, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(delete_line, KeyCode_L, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(duplicate_line, KeyCode_L, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(toggle_fullscreen, KeyCode_F11);
        Bind(goto_line, KeyCode_G, CLEARFELD_KEYCODE_RIGHT_META);
    }

    //~ Code
    SelectMap(code_id);
    ParentMap(file_id);
    {
        // TODO: create a hydra for comment templates
        // Bind(write_todo, KeyCode_T, CLEARFELD_KEYCODE_RIGHT_META);
        // Bind(write_note, KeyCode_Y, CLEARFELD_KEYCODE_RIGHT_META);

        Bind(comment_line_toggle,        KeyCode_Semicolon, KeyCode_Control);
        Bind(word_complete,              KeyCode_Tab);
        Bind(auto_indent_range,          KeyCode_Tab, KeyCode_Shift);
        Bind(word_complete_drop_down,    KeyCode_Tab, KeyCode_Shift, KeyCode_Control);

        // TODO: bind
        // Bind(if0_off,                    KeyCode_I, CLEARFELD_KEYCODE_RIGHT_META);
        // Bind(open_file_in_quotes,        KeyCode_1, CLEARFELD_KEYCODE_RIGHT_META);
        // Bind(open_long_braces_break,     KeyCode_RightBracket, KeyCode_Control, KeyCode_Shift);

        BindTextInput(write_text_and_auto_indent);

        Bind(windmove_panel_up, KeyCode_Up, KeyCode_Control);
        Bind(windmove_panel_down, KeyCode_Down, KeyCode_Control);
        Bind(windmove_panel_left, KeyCode_Left, KeyCode_Control);
        Bind(windmove_panel_right, KeyCode_Right, KeyCode_Control);
        Bind(windmove_panel_swap_up, KeyCode_Up, KeyCode_Control, KeyCode_Shift);
        Bind(windmove_panel_swap_down, KeyCode_Down, KeyCode_Control, KeyCode_Shift);
        Bind(windmove_panel_swap_left, KeyCode_Left, KeyCode_Control, KeyCode_Shift);
        Bind(windmove_panel_swap_right, KeyCode_Right, KeyCode_Control, KeyCode_Shift);

        //Bind(open_default_keybindings_cheatsheet, KeyCode_F2);
        Bind(keyboard_macro_start_recording, KeyCode_LeftBracket, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(keyboard_macro_finish_recording, KeyCode_RightBracket, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(keyboard_macro_replay, KeyCode_Quote, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_up_to_blank_line_skip_whitespace, KeyCode_Up, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_down_to_blank_line_skip_whitespace, KeyCode_Down, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(move_line_up, KeyCode_Up, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(move_line_down, KeyCode_Down, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(seek_beginning_of_line, KeyCode_Home);
        Bind(seek_end_of_line, KeyCode_End);
        Bind(page_up, KeyCode_PageUp);
        Bind(page_down, KeyCode_PageDown);
        Bind(goto_beginning_of_file, KeyCode_PageUp, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(goto_end_of_file, KeyCode_PageDown, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(reopen_buffer_safely, KeyCode_R, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(kill_buffer, KeyCode_K, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(save, KeyCode_S, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(open_panel_vsplit, KeyCode_3, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(open_panel_hsplit, KeyCode_3, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(close_panel, KeyCode_0, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(change_active_panel, KeyCode_W, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(change_active_panel_backwards, KeyCode_W, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(interactive_open_or_new, KeyCode_F, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(interactive_open_or_new_other_panel, KeyCode_F, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(interactive_switch_buffer, KeyCode_B, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(comment_line_toggle, KeyCode_Semicolon, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(auto_indent_range, KeyCode_Tab, KeyCode_Control);
        Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(delete_alpha_numeric_boundary, KeyCode_Delete, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(set_mark, KeyCode_Space, KeyCode_Control);
        Bind(cursor_mark_swap, KeyCode_Space, KeyCode_Control, KeyCode_Shift);
        Bind(query_replace, KeyCode_O, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(replace_in_range, KeyCode_O, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(copy, KeyCode_Q, KeyCode_Control);
        Bind(cut, KeyCode_W, KeyCode_Control);
        Bind(paste_and_indent, KeyCode_F, KeyCode_Control);
        Bind(undo, KeyCode_U, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(delete_line, KeyCode_L, CLEARFELD_KEYCODE_RIGHT_META);
        Bind(duplicate_line, KeyCode_L, CLEARFELD_KEYCODE_RIGHT_META, KeyCode_Shift);
        Bind(toggle_fullscreen, KeyCode_F11);
        Bind(goto_line, KeyCode_G, CLEARFELD_KEYCODE_RIGHT_META);
    }
}
