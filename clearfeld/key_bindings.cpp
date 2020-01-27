//#include "hydra.cpp"

#include "custom_commands/reopen_safely.cpp"
//#include "custom_commands/other_panel_commands.cpp"
#include "custom_commands/rect_operations.cpp"
//#include "custom_commands/align_regexp.cpp"

static void
clearfeld_set_bindings(Mapping *mapping)
{
    MappingScope();
    SelectMapping(mapping);

    //~ Global

    SelectMap(mapid_global);
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
    //Bind(hydra_chord_test, KeyCode_1, KeyCode_Control);
    //Bind(open_default_keybindings_cheatsheet, KeyCode_F2);

    // Macro
    Bind(keyboard_macro_start_recording, KeyCode_LeftBracket, KeyCode_Alt);
    Bind(keyboard_macro_finish_recording, KeyCode_RightBracket, KeyCode_Alt);
    Bind(keyboard_macro_replay, KeyCode_Quote, KeyCode_Alt);

    // Arrow based keys
    Bind(move_up_to_blank_line_skip_whitespace, KeyCode_Up, KeyCode_Alt);
    Bind(move_down_to_blank_line_skip_whitespace, KeyCode_Down, KeyCode_Alt);
    Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, KeyCode_Alt);
    Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, KeyCode_Alt);

    Bind(move_line_up, KeyCode_Up, KeyCode_Alt, KeyCode_Shift);
    Bind(move_line_down, KeyCode_Down, KeyCode_Alt, KeyCode_Shift);

    // TODO
    // Bind(move_buffer_up, KeyCode_Up, KeyCode_Control);
    // Bind(move_buffer_down, KeyCode_Down, KeyCode_Control);
    // Bind(move_buffer_right, KeyCode_Right, KeyCode_Control);
    // Bind(move_buffer_left, KeyCode_Left, KeyCode_Control);

    Bind(seek_beginning_of_line, KeyCode_Home);
    Bind(seek_end_of_line, KeyCode_End);

    Bind(page_up, KeyCode_PageUp);
    Bind(page_down, KeyCode_PageDown);
    Bind(goto_beginning_of_file, KeyCode_PageUp, KeyCode_Alt);
    Bind(goto_end_of_file, KeyCode_PageDown, KeyCode_Alt);

    // buffer shortcuts
    Bind(reopen_buffer_safely, KeyCode_R, KeyCode_Alt);
    Bind(kill_buffer, KeyCode_K, KeyCode_Alt);
    Bind(save, KeyCode_S, KeyCode_Alt);

    // panel shortcuts
    Bind(open_panel_vsplit, KeyCode_3, KeyCode_Alt);
    Bind(open_panel_hsplit, KeyCode_3, KeyCode_Alt, KeyCode_Shift);
    Bind(close_panel, KeyCode_0, KeyCode_Alt);

    // TODO:
    //Bind(close_all_except_active_panel, KeyCode_0, KeyCode_Alt, KeyCode_Shift);

    Bind(change_active_panel, KeyCode_W, KeyCode_Alt);
    Bind(change_active_panel_backwards, KeyCode_W, KeyCode_Alt, KeyCode_Shift);

    // TODO
    // Bind(shrink_panel_h, KeyCode_4, KeyCode_Alt);
    // Bind(shrink_panel_v, KeyCode_4, KeyCode_Alt, KeyCode_Shift);
    // Bind(enlarge_panel_h, KeyCode_5, KeyCode_Alt);
    // Bind(enlarge_panel_v, KeyCode_5, KeyCode_Alt, KeyCode_Shift);

    Bind(interactive_open_or_new, KeyCode_F, KeyCode_Alt);
    Bind(interactive_open_or_new_other_panel, KeyCode_F, KeyCode_Alt, KeyCode_Shift);

    Bind(interactive_switch_buffer, KeyCode_B, KeyCode_Alt);
    // TODO: FIXME: Busted
    Bind(interactive_switch_buffer_other_panel, KeyCode_B, KeyCode_Alt, KeyCode_Shift);

    Bind(comment_line_toggle, KeyCode_Semicolon, KeyCode_Alt);
    // TODO
    //Bind(add_comment_end_of_line, KeyCode_Semicolon, KeyCode_Alt);
    // TODO replace comment_line_toggle with the below
    // ((kbd "M-;") #'comment-or-uncomment-region-or-line)

    // NOTE: look into function for range move lines
    Bind(auto_indent_range, KeyCode_Tab, KeyCode_Control);
    // TODO bind auto_indent_whole_file

    Bind(delete_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Alt);
    // TODO
    //Bind(delete_alpha_numeric_boundary_forward, );

    Bind(set_mark, KeyCode_Space, KeyCode_Control);
    Bind(cursor_mark_swap, KeyCode_Space, KeyCode_Control, KeyCode_Shift);

    Bind(query_replace, KeyCode_O, KeyCode_Alt);
    Bind(replace_in_range, KeyCode_O, KeyCode_Alt, KeyCode_Shift);

    // text editing shortcuts
    Bind(copy, KeyCode_Q, KeyCode_Control);
    Bind(cut, KeyCode_W, KeyCode_Control);
    Bind(paste_and_indent, KeyCode_F, KeyCode_Control);
    Bind(undo, KeyCode_U, KeyCode_Alt);
    Bind(delete_line, KeyCode_L, KeyCode_Alt);
    Bind(duplicate_line, KeyCode_L, KeyCode_Alt, KeyCode_Shift);

    // misc
    Bind(toggle_fullscreen, KeyCode_F11);
    Bind(goto_line, KeyCode_G, KeyCode_Alt);

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

    // TODO: better bindings
    Bind(kill_rect, KeyCode_5, KeyCode_Menu);
    Bind(copy_rect, KeyCode_6, KeyCode_Menu);
    Bind(paste_rect_naive, KeyCode_7, KeyCode_Menu);
    Bind(paste_rect_repeating, KeyCode_8, KeyCode_Menu);

    //Bind(align_regexp, KeyCode_2, KeyCode_Menu);
    //Bind(emmet_expand, KeyCode_2, KeyCode_Menu);


    //~ File
    SelectMap(mapid_file);
    ParentMap(mapid_global);

    //Bind(open_default_keybindings_cheatsheet, KeyCode_F2);
    Bind(keyboard_macro_start_recording, KeyCode_LeftBracket, KeyCode_Alt);
    Bind(keyboard_macro_finish_recording, KeyCode_RightBracket, KeyCode_Alt);
    Bind(keyboard_macro_replay, KeyCode_Quote, KeyCode_Alt);
    Bind(move_up_to_blank_line_skip_whitespace, KeyCode_Up, KeyCode_Alt);
    Bind(move_down_to_blank_line_skip_whitespace, KeyCode_Down, KeyCode_Alt);
    Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, KeyCode_Alt);
    Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, KeyCode_Alt);
    Bind(move_line_up, KeyCode_Up, KeyCode_Alt, KeyCode_Shift);
    Bind(move_line_down, KeyCode_Down, KeyCode_Alt, KeyCode_Shift);
    Bind(seek_beginning_of_line, KeyCode_Home);
    Bind(seek_end_of_line, KeyCode_End);
    Bind(page_up, KeyCode_PageUp);
    Bind(page_down, KeyCode_PageDown);
    Bind(goto_beginning_of_file, KeyCode_PageUp, KeyCode_Alt);
    Bind(goto_end_of_file, KeyCode_PageDown, KeyCode_Alt);
    Bind(reopen, KeyCode_R, KeyCode_Alt);
    Bind(kill_buffer, KeyCode_K, KeyCode_Alt);
    Bind(save, KeyCode_S, KeyCode_Alt);
    Bind(open_panel_vsplit, KeyCode_3, KeyCode_Alt);
    Bind(open_panel_hsplit, KeyCode_3, KeyCode_Alt, KeyCode_Shift);
    Bind(close_panel, KeyCode_0, KeyCode_Alt);
    Bind(change_active_panel, KeyCode_W, KeyCode_Alt);
    Bind(change_active_panel_backwards, KeyCode_W, KeyCode_Alt, KeyCode_Shift);
    Bind(interactive_open_or_new, KeyCode_F, KeyCode_Alt);
    Bind(interactive_open_or_new_other_panel, KeyCode_F, KeyCode_Alt, KeyCode_Shift);
    Bind(interactive_switch_buffer, KeyCode_B, KeyCode_Alt);
    Bind(comment_line_toggle, KeyCode_Semicolon, KeyCode_Alt);
    Bind(auto_indent_range, KeyCode_Tab, KeyCode_Control);
    Bind(delete_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Alt);
    Bind(set_mark, KeyCode_Space, KeyCode_Control);
    Bind(cursor_mark_swap, KeyCode_Space, KeyCode_Control, KeyCode_Shift);
    Bind(query_replace, KeyCode_O, KeyCode_Alt);
    Bind(replace_in_range, KeyCode_O, KeyCode_Alt, KeyCode_Shift);
    Bind(copy, KeyCode_Q, KeyCode_Control);
    Bind(cut, KeyCode_W, KeyCode_Control);
    Bind(paste_and_indent, KeyCode_F, KeyCode_Control);
    Bind(undo, KeyCode_U, KeyCode_Alt);
    Bind(delete_line, KeyCode_L, KeyCode_Alt);
    Bind(duplicate_line, KeyCode_L, KeyCode_Alt, KeyCode_Shift);
    Bind(toggle_fullscreen, KeyCode_F11);
    Bind(goto_line, KeyCode_G, KeyCode_Alt);

    //~ Code
    SelectMap(mapid_code);
    ParentMap(mapid_file);

    //Bind(open_default_keybindings_cheatsheet, KeyCode_F2);
    Bind(keyboard_macro_start_recording, KeyCode_LeftBracket, KeyCode_Alt);
    Bind(keyboard_macro_finish_recording, KeyCode_RightBracket, KeyCode_Alt);
    Bind(keyboard_macro_replay, KeyCode_Quote, KeyCode_Alt);
    Bind(move_up_to_blank_line_skip_whitespace, KeyCode_Up, KeyCode_Alt);
    Bind(move_down_to_blank_line_skip_whitespace, KeyCode_Down, KeyCode_Alt);
    Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, KeyCode_Alt);
    Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, KeyCode_Alt);
    Bind(move_line_up, KeyCode_Up, KeyCode_Alt, KeyCode_Shift);
    Bind(move_line_down, KeyCode_Down, KeyCode_Alt, KeyCode_Shift);
    Bind(seek_beginning_of_line, KeyCode_Home);
    Bind(seek_end_of_line, KeyCode_End);
    Bind(page_up, KeyCode_PageUp);
    Bind(page_down, KeyCode_PageDown);
    Bind(goto_beginning_of_file, KeyCode_PageUp, KeyCode_Alt);
    Bind(goto_end_of_file, KeyCode_PageDown, KeyCode_Alt);
    Bind(reopen, KeyCode_R, KeyCode_Alt);
    Bind(kill_buffer, KeyCode_K, KeyCode_Alt);
    Bind(save, KeyCode_S, KeyCode_Alt);
    Bind(open_panel_vsplit, KeyCode_3, KeyCode_Alt);
    Bind(open_panel_hsplit, KeyCode_3, KeyCode_Alt, KeyCode_Shift);
    Bind(close_panel, KeyCode_0, KeyCode_Alt);
    Bind(change_active_panel, KeyCode_W, KeyCode_Alt);
    Bind(change_active_panel_backwards, KeyCode_W, KeyCode_Alt, KeyCode_Shift);
    Bind(interactive_open_or_new, KeyCode_F, KeyCode_Alt);
    Bind(interactive_open_or_new_other_panel, KeyCode_F, KeyCode_Alt, KeyCode_Shift);
    Bind(interactive_switch_buffer, KeyCode_B, KeyCode_Alt);
    Bind(comment_line_toggle, KeyCode_Semicolon, KeyCode_Alt);
    Bind(auto_indent_range, KeyCode_Tab, KeyCode_Control);
    Bind(delete_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Alt);
    Bind(set_mark, KeyCode_Space, KeyCode_Control);
    Bind(cursor_mark_swap, KeyCode_Space, KeyCode_Control, KeyCode_Shift);
    Bind(query_replace, KeyCode_O, KeyCode_Alt);
    Bind(replace_in_range, KeyCode_O, KeyCode_Alt, KeyCode_Shift);
    Bind(copy, KeyCode_Q, KeyCode_Control);
    Bind(cut, KeyCode_W, KeyCode_Control);
    Bind(paste_and_indent, KeyCode_F, KeyCode_Control);
    Bind(undo, KeyCode_U, KeyCode_Alt);
    Bind(delete_line, KeyCode_L, KeyCode_Alt);
    Bind(duplicate_line, KeyCode_L, KeyCode_Alt, KeyCode_Shift);
    Bind(toggle_fullscreen, KeyCode_F11);
    Bind(goto_line, KeyCode_G, KeyCode_Alt);
}
