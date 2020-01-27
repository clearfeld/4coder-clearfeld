CUSTOM_COMMAND_SIG(interactive_open_or_new_other_panel)
CUSTOM_DOC("Interactive open or new in other panel.")
{
    change_active_panel_send_command(app, interactive_open_or_new);
}

CUSTOM_COMMAND_SIG(interactive_switch_buffer_other_panel)
CUSTOM_DOC("Interactive switch buffer in other panel.")
{
    change_active_panel_send_command(app, interactive_switch_buffer);
}
