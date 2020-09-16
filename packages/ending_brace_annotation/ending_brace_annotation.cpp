
//~ NOTE(rjf): Closing-brace Annotation

static void
F4_RenderCloseBraceAnnotation(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id,
                              i64 pos, Face_ID arg_face_id)
{
    ProfileScope(app, "[Fleury] Brace Annotation");

    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    Token_Array token_array = get_token_array_from_buffer(app, buffer);
    Face_ID face_id = arg_face_id;//global_small_code_face;

    if(token_array.tokens != 0)
    {
        Token_Iterator_Array it = token_iterator_pos(0, &token_array, pos);
        Token *token = token_it_read(&it);

        if(token != 0 && token->kind == TokenBaseKind_ScopeOpen)
        {
            pos = token->pos + token->size;
        }
        else if(token_it_dec_all(&it))
        {
            token = token_it_read(&it);
            if (token->kind == TokenBaseKind_ScopeClose &&
                pos == token->pos + token->size)
            {
                pos = token->pos;
            }
        }
    }

    Scratch_Block scratch(app);
    Range_i64_Array ranges = get_enclosure_ranges(app, scratch, buffer, pos, RangeHighlightKind_CharacterHighlight);

    for (i32 i = ranges.count - 1; i >= 0; i -= 1)
    {
        Range_i64 range = ranges.ranges[i];

        if(range.start >= visible_range.start)
        {
            continue;
        }

        Rect_f32 close_scope_rect = text_layout_character_on_screen(app, text_layout_id, range.end);
        Vec2_f32 close_scope_pos = { close_scope_rect.x0 + 12, close_scope_rect.y0 };

        // NOTE(rjf): Find token set before this scope begins.
        Token *start_token = 0;
        i64 token_count = 0;
        {
            Token_Iterator_Array it = token_iterator_pos(0, &token_array, range.start-1);
            int paren_nest = 0;

            for(;;)
            {
                Token *token = token_it_read(&it);

                if(token)
                {
                    token_count += 1;

                    if(token->kind == TokenBaseKind_ParentheticalClose)
                    {
                        ++paren_nest;
                    }
                    else if(token->kind == TokenBaseKind_ParentheticalOpen)
                    {
                        --paren_nest;
                    }
                    else if(paren_nest == 0 &&
                            (token->kind == TokenBaseKind_ScopeClose ||
                             (token->kind == TokenBaseKind_StatementClose && token->sub_kind != TokenCppKind_Colon)))
                    {
                        break;
                    }
                    else if((token->kind == TokenBaseKind_Identifier || token->kind == TokenBaseKind_Keyword ||
                             token->kind == TokenBaseKind_Comment) &&
                            !paren_nest)
                    {
                        start_token = token;
                        break;
                    }

                }
                else
                {
                    break;
                }

                if(!token_it_dec_non_whitespace(&it))
                {
                    break;
                }
            }

        }

        // NOTE(rjf): Draw.
        if(start_token)
        {
            draw_string(app, face_id, string_u8_litexpr("<-"), close_scope_pos, finalize_color(defcolor_comment, 0));
            close_scope_pos.x += 28;
            String_Const_u8 start_line = push_buffer_line(app, scratch, buffer,
                                                          get_line_number_from_pos(app, buffer, start_token->pos));

            u64 first_non_whitespace_offset = 0;
            for(u64 c = 0; c < start_line.size; ++c)
            {
                if(start_line.str[c] <= 32)
                {
                    ++first_non_whitespace_offset;
                }
                else
                {
                    break;
                }
            }
            start_line.str += first_non_whitespace_offset;
            start_line.size -= first_non_whitespace_offset;

            //NOTE(rjf): Special case to handle CRLF-newline files.
            if(start_line.str[start_line.size - 1] == 13)
            {
                start_line.size -= 1;
            }

            u32 color = finalize_color(defcolor_comment, 0);
            color &= 0x00ffffff;
            color |= 0x80000000;
            draw_string(app, face_id, start_line, close_scope_pos, color);
        }
    }
}
