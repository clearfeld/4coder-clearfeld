#include <ctime>

void
insert_python_template(Application_Links *app, Buffer_ID buffer_id) {
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

    String_Const_u8 full_name = push_u8_stringf(scratch, "%s", PRIVATE_VARIABLE_FULL_NAME);
    String_Const_u8 company_name = push_u8_stringf(scratch, "%s", PRIVATE_VARIABLE_COMPANY_NAME);

    Buffer_Insertion insert = begin_buffer_insertion_at_buffered(app, buffer_id, 0, scratch, KB(16));
    insertf(&insert,
            "# ==================================================================\n"
            "# $File: %.*s $\n"
            "# $Date: %.*s $\n"
            "# $Revision: v1.00 $\n"
            "# $Creator: %.*s $\n"
            "# $Notice: (C) Copyright %.*s by %.*s, Inc. All Rights Reserved. $\n"
            "# ==================================================================\n",
            string_expand(file_name),
            string_expand(today_str),
            string_expand(full_name),
            string_expand(year_str),
            string_expand(company_name));

    end_buffer_insertion(&insert);
}
