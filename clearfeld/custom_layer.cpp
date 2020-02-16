/*
  custom_layer.cpp - Supplies the default bindings used for default 4coder behavior.
*/

#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

//packages under development
#include "../packages/lsp/lsp_mode.cpp"

#include "4coder_default_include.cpp"

// NOTE(allen): Users can declare their own managed IDs here.

#include "generated/managed_id_metadata.cpp"

//~ packages under development
//#include "../packages/rainbow_mode/rainbow_mode.cpp"
//#include "../packages/fill-column-indicator/fill-column-indicator.cpp"
//#include "../packages/echo_area/echo_area.cpp"
//#include "../packages/emmet/emmet.cpp"
//#include "../packages/git/git_full.cpp"
#include "../packages/relative_line_number_mode/relative_line_number_mode.cpp"

//~ package seperate repo

//~ package integrated / integrating
// TODO: add toggles
//#include "../packages/fleury/4coder_fleury_smooth_cursor.cpp"
#include "../packages/divider_comments/divider_comments.cpp"
#include "../packages/paint_functions/paint_functions.cpp"
#include "../packages/smooth_cursor/smooth_cursor.cpp"
#include "../packages/goto_line_preview/goto_line_preview.cpp"

//~ core
#include "private_variables.cpp"
#include "key_bindings.cpp"

// core - prog languages
#include "prog_languages/cpp/file_template.cpp"
#include "prog_languages/python/file_template.cpp"

// core - languages
//

//~ appearance
#include "appearance/margins.cpp"

// themes
global u32 TEMP_HIGHLIGHT_COLOR = 0xFFFF0000;
global u32 BROKEN_HIGHLIGHT_COLOR = 0xFFFF0000;
global u32 HACK_HIGHLIGHT_COLOR = 0xFFFFA500;
global u32 FIXME_HIGHLIGHT_COLOR = 0xFFD4AF37;
global u32 IMPORTANT_HIGHLIGHT_COLOR = 0xFFFFFF00;
#include "../packages/solarized_themes/solarized_themes.cpp"
#include "../packages/wilmersdorf-doom-theme/wilmersdorf_doom_theme.cpp"

//~ end include section

function void
custom_render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id,
                      Buffer_ID buffer, Text_Layout_ID text_layout_id,
                     Rect_f32 rect, Frame_Info frame_info){
    ProfileScope(app, "render buffer");

    View_ID active_view = get_active_view(app, Access_Always);
    b32 is_active_view = (active_view == view_id);
    Rect_f32 prev_clip = draw_set_clip(app, rect);

    // NOTE(allen): Token colorizing
    Token_Array token_array = get_token_array_from_buffer(app, buffer);
    if (token_array.tokens != 0){
        draw_cpp_token_colors(app, text_layout_id, &token_array);

        // NOTE(allen): Scan for TODOs and NOTEs
        if (global_config.use_comment_keyword){
            Comment_Highlight_Pair pairs[] = {
                {string_u8_litexpr("NOTE"), finalize_color(defcolor_comment_pop, 0)},
                {string_u8_litexpr("TODO"), finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("TEMP"), TEMP_HIGHLIGHT_COLOR},
                {string_u8_litexpr("BROKEN"), BROKEN_HIGHLIGHT_COLOR},
                {string_u8_litexpr("HACK"), HACK_HIGHLIGHT_COLOR},
                {string_u8_litexpr("FIXME"), FIXME_HIGHLIGHT_COLOR},
                {string_u8_litexpr("IMPORTANT"), IMPORTANT_HIGHLIGHT_COLOR},
            };
            draw_comment_highlights(app, buffer, text_layout_id,
                                    &token_array, pairs, ArrayCount(pairs));
        }
    }
    else{
        Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
        paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
    }

    i64 cursor_pos = view_correct_cursor(app, view_id);
    view_correct_mark(app, view_id);

    // NOTE(allen): Scope highlight
    if (global_config.use_scope_highlight){
        Color_Array colors = finalize_color_array(defcolor_back_cycle);
        draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
    }

    if (global_config.use_error_highlight || global_config.use_jump_highlight){
        // NOTE(allen): Error highlight
        String_Const_u8 name = string_u8_litexpr("*compilation*");
        Buffer_ID compilation_buffer = get_buffer_by_name(app, name, Access_Always);
        if (global_config.use_error_highlight){
            draw_jump_highlights(app, buffer, text_layout_id, compilation_buffer,
                                 fcolor_id(defcolor_highlight_junk));
        }

        // NOTE(allen): Search highlight
        if (global_config.use_jump_highlight){
            Buffer_ID jump_buffer = get_locked_jump_buffer(app);
            if (jump_buffer != compilation_buffer){
                draw_jump_highlights(app, buffer, text_layout_id, jump_buffer,
                                     fcolor_id(defcolor_highlight_white));
            }
        }
    }

    // NOTE(allen): Color parens
    if (global_config.use_paren_helper){
        Color_Array colors = finalize_color_array(defcolor_text_cycle);
        draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
    }

    // Package: paint_functions
    // NOTE(Skytrias): word highlight before braces ()
    st_paint_functions(app, buffer, text_layout_id);

    // NOTE(allen): Line highlight
    if (global_config.highlight_line_at_cursor && is_active_view){
        i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
        draw_line_highlight(app, text_layout_id, line_number,
                            fcolor_id(defcolor_highlight_cursor_line));
    }

    // Package: divider_comments
    Fleury4RenderDividerComments(app, buffer, view_id, text_layout_id);

    // NOTE(allen): Cursor shape
    Face_Metrics metrics = get_face_metrics(app, face_id);
    f32 cursor_roundness = (metrics.normal_advance*0.5f)*0.9f;
    f32 mark_thickness = 2.f;

    // NOTE(allen): Cursor
    switch (fcoder_mode){
        case FCoderMode_Original:
        {
            if(smooth_cursor_mode) {
                Fleury4RenderCursor(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness, frame_info);
            } else {
                draw_original_4coder_style_cursor_mark_highlight(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);
            }
        }break;

        case FCoderMode_NotepadLike:
        {
            draw_notepad_style_cursor_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
        }break;
    }

    // NOTE(allen): Fade ranges
    paint_fade_ranges(app, text_layout_id, buffer, view_id);

    // NOTE(allen): put the actual text on the actual screen
    draw_text_layout_default(app, text_layout_id);

    draw_set_clip(app, prev_clip);

    //draw_git_gutters(app, view_id, face_id, buffer);
}

function void
custom_draw_file_bar(Application_Links *app, View_ID view_id, Buffer_ID buffer, Face_ID face_id, Rect_f32 bar){
    Scratch_Block scratch(app);

    draw_rectangle_fcolor(app, bar, 0.f, fcolor_id(defcolor_bar));

    FColor base_color = fcolor_id(defcolor_base);
    FColor pop2_color = fcolor_id(defcolor_pop2);

    i64 cursor_position = view_get_cursor_pos(app, view_id);
    Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_position));

    Fancy_Line list = {};
    String_Const_u8 unique_name = push_buffer_unique_name(app, scratch, buffer);
    push_fancy_string(scratch, &list, fcolor_id(defcolor_list_item_hover), unique_name);
    push_fancy_stringf(scratch, &list, base_color, " - Row: %3.lld Col: %3.lld -", cursor.line, cursor.col);

    Managed_Scope scope = buffer_get_managed_scope(app, buffer);
    Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting,
                                                     Line_Ending_Kind);
    switch (*eol_setting){
        case LineEndingKind_Binary:
        {
            push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" bin"));
        }break;

        case LineEndingKind_LF:
        {
            push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" lf"));
        }break;

        case LineEndingKind_CRLF:
        {
            push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" crlf"));
        }break;
    }

    {
        Dirty_State dirty = buffer_get_dirty_state(app, buffer);
        u8 space[3];
        String_u8 str = Su8(space, 0, 3);
        if (dirty != 0){
            string_append(&str, string_u8_litexpr(" "));
        }
        if (HasFlag(dirty, DirtyState_UnsavedChanges)){
            string_append(&str, string_u8_litexpr("*"));
        }
        if (HasFlag(dirty, DirtyState_UnloadedChanges)){
            string_append(&str, string_u8_litexpr("!"));
        }
        push_fancy_string(scratch, &list, pop2_color, str.string);
    }

    Vec2_f32 p = bar.p0 + V2f32(2.f, 2.f);
    draw_fancy_line(app, face_id, fcolor_zero(), &list, p);
}

function void
custom_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id){
    ProfileScope(app, "default render caller");
    View_ID active_view = get_active_view(app, Access_Always);
    b32 is_active_view = (active_view == view_id);

    Rect_f32 region = cl_draw_background_and_margin(app, view_id, is_active_view);
    //Rect_f32 region = draw_background_and_margin(app, view_id, is_active_view);
    Rect_f32 prev_clip = draw_set_clip(app, region);

    Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
    Face_ID face_id = get_face_id(app, buffer);
    Face_Metrics face_metrics = get_face_metrics(app, face_id);
    f32 line_height = face_metrics.line_height;
    f32 digit_advance = face_metrics.decimal_digit_advance;

    // NOTE(allen): file bar
    b64 showing_file_bar = false;
    if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar){
        //Rect_f32_Pair pair = layout_file_bar_on_top(region, line_height);
        //custom_draw_file_bar(app, view_id, buffer, face_id, pair.min);
        //region = pair.max;

        // TODO: LOW: fix mouse one line below cursor placement
        // Filebar on the bottom
        Rect_f32_Pair pair = layout_file_bar_on_bot(region, line_height);
        custom_draw_file_bar(app, view_id, buffer, face_id, pair.max);
        region = pair.min;
    }

    Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);

    Buffer_Point_Delta_Result delta = delta_apply(app, view_id,
                                                  frame_info.animation_dt, scroll);
    if (!block_match_struct(&scroll.position, &delta.point)){
        block_copy_struct(&scroll.position, &delta.point);
        view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
    }
    if (delta.still_animating){
        animate_in_n_milliseconds(app, 0);
    }

    // NOTE(allen): query bars
    {
        Query_Bar *space[32];
        Query_Bar_Ptr_Array query_bars = {};
        query_bars.ptrs = space;
        if (get_active_query_bars(app, view_id, ArrayCount(space), &query_bars)){
            for (i32 i = 0; i < query_bars.count; i += 1){
                Rect_f32_Pair pair = layout_query_bar_on_top(region, line_height, 1);
                draw_query_bar(app, query_bars.ptrs[i], face_id, pair.min);
                region = pair.max;
            }
        }
    }

    // NOTE(allen): FPS hud
    if (show_fps_hud){
        Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
        draw_fps_hud(app, frame_info, face_id, pair.max);
        region = pair.min;
        animate_in_n_milliseconds(app, 1000);
    }

    // NOTE(allen): layout line numbers
    Rect_f32 line_number_rect = {};
    if (global_config.show_line_number_margins){
        Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
        line_number_rect = pair.min;
        region = pair.max;
    }

    // NOTE(allen): begin buffer render
    Buffer_Point buffer_point = scroll.position;
    Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);

    // NOTE(allen): draw line numbers
    if(global_config.show_line_number_margins) {
        if(use_relative_line_number_mode) {
            draw_relative_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
        } else {
            draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
        }
    }

    // NOTE(allen): draw the buffer
    //default_render_buffer(app, view_id, face_id, buffer, text_layout_id, region);
    custom_render_buffer(app, view_id, face_id, buffer, text_layout_id, region, frame_info);

    text_layout_free(app, text_layout_id);
    draw_set_clip(app, prev_clip);

    // if(render_hydra_chord_map) {
    //     draw_hydra_chord_map(app, view_id, face_id);
    // }
}

BUFFER_HOOK_SIG(custom_new_file) {
    Scratch_Block scratch(app);
    String_Const_u8 file_name = push_buffer_base_name(app, scratch, buffer_id);

    if (string_match(string_postfix(file_name, 2), string_u8_litexpr(".h"))
        || string_match(string_postfix(file_name, 4), string_u8_litexpr(".hpp"))
        )
    {
        insert_cpp_header_template(app, buffer_id);
    }
    else if(string_match(string_postfix(file_name, 2), string_u8_litexpr(".c"))
            || string_match(string_postfix(file_name, 4), string_u8_litexpr(".cpp")))
    {
        insert_cpp_template(app, buffer_id);
    }
    else if(string_match(string_postfix(file_name, 3), string_u8_litexpr(".py")))
    {
        insert_python_template(app, buffer_id);
    }
    else if(string_match(string_postfix(file_name, 3), string_u8_litexpr(".go")))
    {
        //insert_go_template(app, buffer_id);
    }
    else if(string_match(string_postfix(file_name, 3), string_u8_litexpr(".js"))
            || string_match(string_postfix(file_name, 3), string_u8_litexpr(".ts"))
            || string_match(string_postfix(file_name, 4), string_u8_litexpr(".jsx"))
            || string_match(string_postfix(file_name, 4), string_u8_litexpr(".tsx"))
            )
    {
        //insert js / ts template
    }

    return(0);
}

void
custom_layer_init(Application_Links *app){
    Thread_Context *tctx = get_thread_context(app);

    // NOTE(allen): setup for default framework
    async_task_handler_init(app, &global_async_system);
    code_index_init();
    buffer_modified_set_init();
    Profile_Global_List *list = get_core_profile_list(app);
    ProfileThreadName(tctx, list, string_u8_litexpr("main"));
    initialize_managed_id_metadata(app);
    set_default_color_scheme(app);

    // NOTE(allen): default hooks and command maps
    set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    //setup_default_mapping(&framework_mapping, mapid_global, mapid_file, mapid_code);

    clearfeld_set_bindings(&framework_mapping, mapid_global, mapid_file, mapid_code);

    wilmersdorf_doom_theme(app);

    // start_docker_lang_server();

    set_custom_hook(app, HookID_RenderCaller, custom_render_caller);
    set_custom_hook(app, HookID_NewFile, custom_new_file);
}

#endif //FCODER_DEFAULT_BINDINGS
