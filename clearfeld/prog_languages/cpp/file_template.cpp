#include <ctime>

void
insert_cpp_header_template(Application_Links *app, Buffer_ID buffer_id) {
    Scratch_Block scratch(app);
    String_Const_u8 file_name = push_buffer_base_name(app, scratch, buffer_id);

    List_String_Const_u8 guard_list = {};
    for (u64 i = 0; i < file_name.size; ++i) {
        u8 c[2] = {};
        u64 c_size = 1;
        u8 ch = file_name.str[i];
        if (ch == '.') {
            c[0] = '_';
        } else if (ch >= 'A' && ch <= 'Z') {
            c_size = 2;
            c[0] = '_';
            c[1] = ch;
        } else if (ch >= 'a' && ch <= 'z') {
            c[0] = ch - ('a' - 'A');
        }
        String_Const_u8 part = push_string_copy(scratch, SCu8(c, c_size));
        string_list_push(scratch, &guard_list, part);
    }
    String_Const_u8 guard = string_list_flatten(scratch, guard_list);

    Buffer_Insertion insert = begin_buffer_insertion_at_buffered(app, buffer_id, 0, scratch, KB(16));
    insertf(&insert,
            "#ifndef %.*s\n"
            "#define %.*s\n"
            "\n"
            "#endif //%.*s\n",
            string_expand(guard),
            string_expand(guard),
            string_expand(guard));

    end_buffer_insertion(&insert);
}

void
insert_cpp_template(Application_Links *app, Buffer_ID buffer_id) {
    Scratch_Block scratch(app);
    String_Const_u8 file_name = push_buffer_base_name(app, scratch, buffer_id);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    String_Const_u8 year_str = push_u8_stringf(scratch, "%d", ltm->tm_year + 1900);

    const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    const char *days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thrusday", "Friday", "Saturday"};

    // Format Year Month Day_Number (Day)
    String_Const_u8 today_str = push_u8_stringf(scratch,
                                                "%d %s %d (%s)",
                                                ltm->tm_year + 1900,
                                                months[ltm->tm_mon],
                                                ltm->tm_mday,
                                                days[ltm->tm_wday]);

    // Format Year/Month/Day
    // String_Const_u8 today_str = push_u8_stringf(scratch,
    //                                             "%d/%d/%d",
    //                                             ltm->tm_year + 1900,
    //                                             ltm->tm_mon + 1,
    //                                             ltm->tm_mday);

    String_Const_u8 full_name = push_u8_stringf(scratch, "%s", PRIVATE_VARIABLE_FULL_NAME);
    String_Const_u8 company_name = push_u8_stringf(scratch, "%s", PRIVATE_VARIABLE_COMPANY_NAME);

    Buffer_Insertion insert = begin_buffer_insertion_at_buffered(app, buffer_id, 0, scratch, KB(16));
    insertf(&insert,
            "/* ==================================================================\n"
            " * $File: %.*s $\n"
            " * $Date: %.*s $\n"
            " * $Revision: v1.00 $\n"
            " * $Creator: %.*s $\n"
            " * $Notice: (C) Copyright %.*s by %.*s, Inc. All Rights Reserved. $\n"
            " * ==================================================================\n"
            " */\n",
            string_expand(file_name),
            string_expand(today_str),
            string_expand(full_name),
            string_expand(year_str),
            string_expand(company_name));

    end_buffer_insertion(&insert);
}
